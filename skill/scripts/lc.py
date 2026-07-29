#!/usr/bin/env python3
"""리트코드 데일리 훈련 진도 관리.

  lc.py today                 오늘 복습 카드 + 신규 추천 문제
  lc.py record --id 424 ...   신규 문제 결과 기록 (통찰 카드 생성)
  lc.py review --id 424 ...   복습 결과 기록 (간격 갱신)
  lc.py stats                 패턴별 숙련도
  lc.py card --id 424         저장된 카드 원문 보기
  lc.py pull                  아카이브 레포에서 진도·통찰·풀이를 받아 로컬에 병합
  lc.py sync                  공부 흔적을 아카이브 레포에 커밋·푸시

표준 라이브러리만 사용한다.
"""

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import unicodedata
from datetime import date, timedelta
from pathlib import Path

SKILL_DIR = Path(__file__).resolve().parent.parent
BANK_PATH = SKILL_DIR / "assets" / "problems.json"
DATA_DIR = Path.home() / ".claude" / "leetcode-daily"
PROGRESS_PATH = DATA_DIR / "progress.json"
INSIGHTS_PATH = DATA_DIR / "insights.md"

# 공부 흔적을 누적 보관하는 원격 아카이브 (git 레포의 로컬 클론)
REPO_DIR = Path(os.environ.get("LC_ARCHIVE_REPO", str(Path.home() / "Algorithm")))
PRACTICE_DIR = Path.home() / "leetcode-practice"

HINT_LEVELS = ["H0", "H1", "H2", "H3", "H4", "H5"]
MAX_INTERVAL = 60
MAX_REVIEWS_PER_DAY = 5


# ---------------------------------------------------------------- 저장소

def load_bank():
    with open(BANK_PATH, encoding="utf-8") as f:
        return json.load(f)


def load_progress():
    if not PROGRESS_PATH.exists():
        return {"version": 1, "created": date.today().isoformat(), "problems": {}}
    with open(PROGRESS_PATH, encoding="utf-8") as f:
        return json.load(f)


def save_progress(prog):
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    with open(PROGRESS_PATH, "w", encoding="utf-8") as f:
        json.dump(prog, f, ensure_ascii=False, indent=2)


def find_problem(bank, pid):
    """문제 번호로 은행에서 찾는다. 여러 패턴에 걸친 문제는 첫 번째 패턴을 주 패턴으로."""
    for pat_key, pat in bank["patterns"].items():
        for p in pat["problems"]:
            if p["id"] == pid:
                return pat_key, p
    return None, None


# ---------------------------------------------------------------- 간격 반복

def next_interval(prev_interval, hint, solved):
    """SM-2 간소화. 힌트를 적게 받을수록 간격이 크게 늘어난다.

    회상이 즉각적이었다면(H0~H1) 그 기억은 견고하므로 오래 비워도 된다.
    H4 이상이나 실패는 사실상 처음 보는 것과 같으므로 1일로 되돌린다.
    """
    if not solved or hint in ("H4", "H5"):
        return 1
    if prev_interval == 0:  # 첫 기록
        return 3 if hint in ("H0", "H1") else 2
    mult = 2.5 if hint in ("H0", "H1") else 1.5
    return min(MAX_INTERVAL, max(2, round(prev_interval * mult)))


def due_cards(prog, today):
    out = []
    for pid, rec in prog["problems"].items():
        if rec.get("next_review") and rec["next_review"] <= today.isoformat():
            out.append((pid, rec))
    out.sort(key=lambda kv: (kv[1]["next_review"], -kv[1].get("lapses", 0)))
    return out


# ---------------------------------------------------------------- 숙련도

def pattern_mastery(bank, prog):
    """패턴별 (푼 문제 수, 잘 푼 수, 마지막 학습일)."""
    stat = {}
    for key, pat in bank["patterns"].items():
        stat[key] = {"ko": pat["ko"], "solved": 0, "clean": 0, "hard_done": 0, "last": None}
    for pid, rec in prog["problems"].items():
        key = rec.get("pattern")
        if key not in stat:
            continue
        stat[key]["solved"] += 1
        first = rec["history"][0] if rec.get("history") else {}
        if first.get("hint") in ("H0", "H1", "H2") and first.get("solved"):
            stat[key]["clean"] += 1
        if rec.get("difficulty") == "hard" and first.get("solved"):
            stat[key]["hard_done"] += 1
        d = rec["history"][-1]["date"] if rec.get("history") else None
        if d and (stat[key]["last"] is None or d > stat[key]["last"]):
            stat[key]["last"] = d
    return stat


def pick_new(bank, prog, force_difficulty=None, force_pattern=None):
    """다음 신규 문제를 고른다.

    원칙: 패턴 커버리지를 먼저 넓히되, 한 패턴에서 Medium을 2개 이상 깔끔히
    풀었으면 그 패턴의 Hard로 승급시킨다. 목표가 Hard 즉발이므로 Medium만
    무한히 도는 건 의미가 없고, 기반 없이 Hard만 파면 패턴이 안 붙는다.
    """
    done = set(int(p) for p in prog["problems"])
    mastery = pattern_mastery(bank, prog)

    def candidates(pat_key, difficulty):
        pat = bank["patterns"][pat_key]
        return [p for p in pat["problems"]
                if p["id"] not in done and p["difficulty"] == difficulty]

    order = [k for k in bank["order"] if k in bank["patterns"]]
    if force_pattern:
        order = [force_pattern] if force_pattern in bank["patterns"] else []
        if not order:
            return None, None, f"알 수 없는 패턴: {force_pattern}"

    def coverage_pick():
        """아직 손대지 않은 패턴의 Medium."""
        for key in order:
            if mastery[key]["solved"] == 0:
                c = candidates(key, "medium")
                if c:
                    return key, c[0], "새 패턴 — 기반 문제"
        return None

    def promote_pick(force=False):
        """Medium을 H2 이하로 2개 이상 푼 패턴의 Hard."""
        ranked = sorted(order, key=lambda k: -mastery[k]["clean"])
        for key in ranked:
            if force or mastery[key]["clean"] >= 2:
                c = candidates(key, "hard")
                if c:
                    return key, c[0], f"{mastery[key]['ko']} 승급 — Hard"
        return None

    def reinforce_pick():
        """즉발률이 낮거나 오래된 패턴의 Medium 보강."""
        ranked = sorted(order, key=lambda k: (mastery[k]["clean"], mastery[k]["last"] or ""))
        for key in ranked:
            c = candidates(key, "medium")
            if c:
                return key, c[0], f"{mastery[key]['ko']} 보강"
        return None

    if force_difficulty == "hard":
        return promote_pick(force=True) or reinforce_pick() or (None, None, "남은 Hard 없음")
    if force_difficulty == "medium":
        return coverage_pick() or reinforce_pick() or (None, None, "남은 Medium 없음")

    # 커버리지와 승급을 번갈아 간다. 커버리지만 우선하면 패턴을 다 돌 때까지
    # Hard가 한 번도 안 나오고(목표가 Hard 즉발인데 몇 주를 Medium만 돈다),
    # 승급만 우선하면 안 배운 패턴이 영영 안 나온다. 둘 다 실패 모드다.
    prefer_hard = len(prog["problems"]) % 2 == 1
    chain = [promote_pick, coverage_pick] if prefer_hard else [coverage_pick, promote_pick]
    for step in chain:
        got = step()
        if got:
            return got
    got = reinforce_pick()
    if got:
        return got

    # 4순위: 남은 아무 문제
    for key in order:
        for diff in ("hard", "medium"):
            c = candidates(key, diff)
            if c:
                return key, c[0], "잔여 문제"
    return None, None, "은행의 문제를 모두 풀었습니다. assets/problems.json에 추가하세요."


# ---------------------------------------------------------------- 명령

def cmd_today(args):
    bank, prog = load_bank(), load_progress()
    today = date.today()
    first_run = not PROGRESS_PATH.exists()

    print(f"=== 리트코드 데일리 · {today.isoformat()} ===\n")

    cards = due_cards(prog, today)
    if cards:
        shown = cards[:MAX_REVIEWS_PER_DAY]
        print(f"[복습 {len(shown)}장]" + (f"  (전체 {len(cards)}장 중 오래된 순 {MAX_REVIEWS_PER_DAY}장, 나머지는 내일)" if len(cards) > MAX_REVIEWS_PER_DAY else ""))
        for pid, rec in shown:
            overdue = (today - date.fromisoformat(rec["next_review"])).days
            flag = "  ※3회 이상 백지 — 다시 풀 것" if rec.get("lapses", 0) >= 3 else ""
            late = f" ({overdue}일 밀림)" if overdue > 0 else ""
            print(f"  #{pid} {rec['title']} [{rec['difficulty']}]{late}{flag}")
        print("\n  → 통찰을 먼저 회상시키고, 답한 뒤에 카드를 보여줄 것. 카드 원문: lc.py card --id <번호>\n")
    else:
        print("[복습] 오늘 예정된 카드 없음\n")

    key, prob, why = pick_new(bank, prog,
                              force_difficulty=args.difficulty,
                              force_pattern=args.pattern)
    if prob:
        slug = prob["title"].lower().replace("(", "").replace(")", "").replace("`", "")
        slug = "-".join(slug.split())
        print(f"[신규] #{prob['id']} {prob['title']} [{prob['difficulty']}]")
        print(f"  https://leetcode.com/problems/{slug}/")
        print(f"  선정 이유(사용자에게 말하지 말 것): {why} / 패턴={key}")
    else:
        print(f"[신규] {why}")

    if first_run:
        print("\n(진도 파일이 아직 없습니다. 첫 기록 시 ~/.claude/leetcode-daily/ 에 생성됩니다.)")


def cmd_record(args):
    bank, prog = load_bank(), load_progress()
    key, prob = find_problem(bank, args.id)
    if prob is None:
        print(f"경고: #{args.id}는 은행에 없습니다. 패턴 미상으로 기록합니다.", file=sys.stderr)
        key = args.pattern or "unknown"
        prob = {"id": args.id, "title": args.title or f"Problem {args.id}",
                "difficulty": args.difficulty or "medium"}

    if not args.insight.strip():
        print("에러: --insight 가 비었습니다. 통찰 카드 없이는 간격 반복이 성립하지 않습니다.\n"
              "      사용자 본인의 말로 '이 관찰이 없었으면 못 풀었을 한 줄'을 받아 넣으세요.",
              file=sys.stderr)
        return 1

    today = date.today()
    solved = args.solved == "yes"
    interval = next_interval(0, args.hint, solved)
    rec = {
        "title": prob["title"],
        "pattern": args.pattern or key,
        "difficulty": prob["difficulty"],
        "insight": args.insight.strip(),
        "signal": (args.signal or "").strip(),
        "file": str(Path(args.file).expanduser()) if args.file else "",
        "history": [{"date": today.isoformat(), "hint": args.hint,
                     "minutes": args.minutes, "solved": solved, "kind": "new"}],
        "interval_days": interval,
        "next_review": (today + timedelta(days=interval)).isoformat(),
        "lapses": 0 if solved else 1,
    }
    prog["problems"][str(args.id)] = rec
    save_progress(prog)
    append_insight(rec, args.id)

    print(f"기록 완료: #{args.id} {prob['title']}")
    print(f"  힌트 {args.hint} / {args.minutes}분 / {'해결' if solved else '미해결'}")
    print(f"  다음 복습: {rec['next_review']} ({interval}일 뒤)")
    return 0


def cmd_review(args):
    prog = load_progress()
    rec = prog["problems"].get(str(args.id))
    if rec is None:
        print(f"에러: #{args.id}는 아직 기록에 없습니다. record 먼저 하세요.", file=sys.stderr)
        return 1

    today = date.today()
    solved = args.hint not in ("H4", "H5")
    interval = next_interval(rec.get("interval_days", 0), args.hint, solved)
    rec["history"].append({"date": today.isoformat(), "hint": args.hint,
                           "solved": solved, "kind": "review"})
    rec["interval_days"] = interval
    rec["next_review"] = (today + timedelta(days=interval)).isoformat()
    if not solved:
        rec["lapses"] = rec.get("lapses", 0) + 1
    if args.insight:
        rec["insight"] = args.insight.strip()
    save_progress(prog)

    print(f"복습 기록: #{args.id} {rec['title']} — {args.hint}")
    print(f"  다음 복습: {rec['next_review']} ({interval}일 뒤)")
    if rec.get("lapses", 0) >= 3:
        print("  ※ 3회 이상 백지입니다. 회상이 아니라 이해가 안 된 것이니 신규처럼 다시 푸세요.")
    return 0


def cmd_card(args):
    prog = load_progress()
    rec = prog["problems"].get(str(args.id))
    if rec is None:
        print(f"#{args.id} 기록 없음", file=sys.stderr)
        return 1
    print(f"#{args.id} {rec['title']} [{rec['difficulty']}] · {rec['pattern']}")
    print(f"  통찰: {rec['insight']}")
    if rec.get("signal"):
        print(f"  신호: {rec['signal']}")
    if rec.get("file"):
        exists = "" if Path(rec["file"]).exists() else "  (파일 없음)"
        print(f"  내 코드: {rec['file']}{exists}")
    hints = " → ".join(h["hint"] for h in rec["history"])
    print(f"  이력: {hints}  (백지 {rec.get('lapses', 0)}회)")
    return 0


def disp_width(s):
    """한글·전각 문자는 터미널에서 두 칸을 차지한다."""
    return sum(2 if unicodedata.east_asian_width(c) in "WF" else 1 for c in s)


def pad(s, n):
    return s + " " * max(0, n - disp_width(s))


def cmd_stats(args):
    bank, prog = load_bank(), load_progress()
    mastery = pattern_mastery(bank, prog)
    total = len(prog["problems"])
    hard = sum(1 for r in prog["problems"].values() if r.get("difficulty") == "hard")
    print(f"=== 진도 ===  총 {total}문제 (Hard {hard})\n")
    print(f"{pad('패턴', 34)} {'푼 수':>4} {'즉발':>4} {'Hard':>5}  최근")
    print("-" * 62)
    weak = []
    for key in bank["order"]:
        m = mastery.get(key)
        if not m:
            continue
        last = m["last"] or "-"
        print(f"{pad(m['ko'], 34)} {m['solved']:>5} {m['clean']:>5} {m['hard_done']:>5}  {last}")
        if m["solved"] > 0 and m["clean"] == 0:
            weak.append(m["ko"])
        elif m["solved"] == 0:
            weak.append(f"{m['ko']}(미착수)")
    print()
    if weak:
        print("보강 필요: " + ", ".join(weak[:8]))
    print("'즉발' = 힌트 H2 이하로 첫 시도에 해결한 문제 수")
    return 0


def append_insight(rec, pid):
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    new = not INSIGHTS_PATH.exists()
    with open(INSIGHTS_PATH, "a", encoding="utf-8") as f:
        if new:
            f.write("# 통찰 카드\n\n사용자 본인의 말로 기록된 것만 담는다. 모델이 요약해 넣지 않는다.\n\n")
        f.write(f"## #{pid} {rec['title']} [{rec['difficulty']}] · {rec['pattern']}\n")
        f.write(f"- 기록일: {rec['history'][0]['date']} (힌트 {rec['history'][0]['hint']})\n")
        f.write(f"- **통찰**: {rec['insight']}\n")
        if rec.get("signal"):
            f.write(f"- 신호: {rec['signal']}\n")
        if rec.get("file"):
            f.write(f"- 내 코드: `{rec['file']}`\n")
        f.write("\n")


# ---------------------------------------------------------------- 아카이브 동기화

MARK_START = "<!--- LEETCODE-DAILY:START --->"
MARK_END = "<!--- LEETCODE-DAILY:END --->"

# 자격증명·캐시. 공개 레포에 올라가면 계정이 넘어가므로 무조건 차단한다.
GITIGNORE_BLOCK = """\
# --- leetcode-daily: 절대 커밋 금지 (자격증명) ---
session
login.cjs
browser-profile/
*.cookie
# --- 캐시 ---
__pycache__/
*.pyc
.DS_Store
"""


def _run(args, **kw):
    return subprocess.run(args, cwd=str(REPO_DIR), capture_output=True,
                          text=True, **kw)


def _repo_path(local_file):
    """연습 파일의 절대 경로를 레포 상대 경로로 바꾼다. 홈 경로가 공개되지 않게."""
    name = Path(local_file).name
    return f"solutions/{name}" if name else ""


def ensure_gitignore():
    gi = REPO_DIR / ".gitignore"
    cur = gi.read_text(encoding="utf-8") if gi.exists() else ""
    if "leetcode-daily: 절대 커밋 금지" in cur:
        return
    sep = "" if not cur or cur.endswith("\n") else "\n"
    gi.write_text(cur + sep + GITIGNORE_BLOCK, encoding="utf-8")


def copy_skill():
    """스킬 자체를 레포에 복사한다 — 다른 기기에서 훈련을 재현할 수 있게."""
    dst = REPO_DIR / "skill"
    if dst.exists():
        shutil.rmtree(dst)
    shutil.copytree(SKILL_DIR, dst,
                    ignore=shutil.ignore_patterns("__pycache__", "*.pyc", ".DS_Store"))


def copy_solutions():
    dst = REPO_DIR / "solutions"
    dst.mkdir(exist_ok=True)
    n = 0
    if PRACTICE_DIR.exists():
        for src in sorted(PRACTICE_DIR.glob("*.py")):
            shutil.copy2(src, dst / src.name)
            n += 1
    return n


def export_data(prog):
    """진도·통찰을 레포로 내보낸다. 절대 경로는 레포 상대 경로로 치환한다."""
    exported = json.loads(json.dumps(prog))
    for rec in exported.get("problems", {}).values():
        if rec.get("file"):
            rec["file"] = _repo_path(rec["file"])
    (REPO_DIR / "progress.json").write_text(
        json.dumps(exported, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

    if INSIGHTS_PATH.exists():
        text = INSIGHTS_PATH.read_text(encoding="utf-8")
        text = text.replace(str(PRACTICE_DIR) + "/", "solutions/")
        text = text.replace(str(Path.home()), "~")
        (REPO_DIR / "insights.md").write_text(text, encoding="utf-8")


def render_dashboard(bank, prog):
    today = date.today()
    probs = prog.get("problems", {})
    solved = [r for r in probs.values()
              if r["history"] and r["history"][0].get("solved")]
    total_min = sum(h.get("minutes", 0) for r in probs.values() for h in r["history"])
    reviews = sum(1 for r in probs.values() for h in r["history"]
                  if h.get("kind") == "review")

    L = [MARK_START, "", "## 리트코드 데일리 훈련", "",
         "[`skill/`](skill/)의 훈련 스킬이 매 세션 자동으로 갱신합니다. "
         "통찰 카드는 간격 반복(1/3/7/21일)으로 되살립니다.", "",
         f"| 푼 문제 | 해결 | 복습 횟수 | 누적 시간 | 갱신 |",
         f"| --- | --- | --- | --- | --- |",
         f"| {len(probs)} | {len(solved)} | {reviews} | {total_min}분 | {today.isoformat()} |",
         ""]

    if probs:
        L += ["### 통찰 카드", "",
              "| # | 문제 | 난이도 | 패턴 | 힌트 | 통찰 | 코드 |",
              "| --- | --- | --- | --- | --- | --- | --- |"]
        for pid, r in sorted(probs.items(), key=lambda kv: int(kv[0])):
            h0 = r["history"][0]
            code = f"[.py]({_repo_path(r['file'])})" if r.get("file") else "—"
            insight = r["insight"].replace("|", "\\|")
            L.append(f"| {pid} | {r['title']} | {r['difficulty']} | "
                     f"`{r['pattern']}` | {h0['hint']} | {insight} | {code} |")
        L.append("")

        due = sorted(((r["next_review"], pid, r["title"])
                      for pid, r in probs.items()), key=lambda t: t[0])[:8]
        L += ["### 복습 예정", "", "| 날짜 | # | 문제 |", "| --- | --- | --- |"]
        for d, pid, title in due:
            mark = " ⏰" if d <= today.isoformat() else ""
            L.append(f"| {d}{mark} | {pid} | {title} |")
        L.append("")

    L += [MARK_END]
    return "\n".join(L)


def update_readme(block):
    """LeetHub/BaekjoonHub이 관리하는 구간은 건드리지 않고 내 블록만 갈아끼운다."""
    path = REPO_DIR / "README.md"
    text = path.read_text(encoding="utf-8") if path.exists() else "# Algorithm\n"

    if MARK_START in text and MARK_END in text:
        head = text.split(MARK_START)[0]
        tail = text.split(MARK_END, 1)[1]
        text = head + block + tail
    else:
        # LeetHub 마커 앞에 끼워넣는다. 없으면 맨 끝에.
        anchor = "<!---LeetCode Topics Start-->"
        if anchor in text:
            head, tail = text.split(anchor, 1)
            text = head + block + "\n\n" + anchor + tail
        else:
            text = text.rstrip("\n") + "\n\n" + block + "\n"
    path.write_text(text, encoding="utf-8")


# ---------------------------------------------------------------- 아카이브 → 로컬

def _local_path(repo_file):
    """레포 상대 경로를 로컬 연습 파일 경로로 되돌린다. _repo_path의 역방향."""
    if not repo_file:
        return ""
    p = Path(repo_file)
    return str(p) if p.is_absolute() else str(PRACTICE_DIR / p.name)


def _last_touch(rec):
    """이 기록이 마지막으로 갱신된 날짜. 어느 쪽이 최신인지 판단하는 기준."""
    dates = [h.get("date", "") for h in rec.get("history", [])]
    return max(dates) if dates else ""


def git_pull():
    """원격을 받아온다. 실패해도 훈련은 로컬 진도로 계속하므로 예외를 던지지 않는다."""
    dirty = _run(["git", "status", "--porcelain"]).stdout.strip()
    if dirty:
        _run(["git", "fetch", "origin"])
        return False, ("로컬에 커밋되지 않은 변경이 있어 pull을 건너뜁니다 "
                       "(fetch만 완료). 세션 끝의 sync가 함께 올립니다.")
    branch = _run(["git", "rev-parse", "--abbrev-ref", "HEAD"]).stdout.strip() or "HEAD"
    r = _run(["git", "pull", "--ff-only", "origin", branch])
    if r.returncode != 0:
        return False, f"pull 실패 — 로컬 진도로 진행합니다.\n{r.stderr.strip()}"
    return True, r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "최신 상태"


def merge_progress(local, remote):
    """원격 진도를 로컬에 병합한다.

    문제별로 이력이 더 많은 쪽을, 같으면 더 최근에 갱신된 쪽을 채택한다.
    한쪽을 통째로 덮어쓰지 않는 이유는 두 기기에서 서로 다른 문제를 푼 경우가
    정상 시나리오이기 때문이다.
    """
    out = json.loads(json.dumps(local))
    lp = out.setdefault("problems", {})
    added, updated = [], []

    for pid, rrec in remote.get("problems", {}).items():
        rrec = json.loads(json.dumps(rrec))
        rrec["file"] = _local_path(rrec.get("file", ""))
        lrec = lp.get(pid)
        if lrec is None:
            lp[pid] = rrec
            added.append(pid)
            continue
        lkey = (len(lrec.get("history", [])), _last_touch(lrec))
        rkey = (len(rrec.get("history", [])), _last_touch(rrec))
        if rkey > lkey:
            if lrec.get("file") and not rrec.get("file"):
                rrec["file"] = lrec["file"]
            lp[pid] = rrec
            updated.append(pid)

    rc = remote.get("created", "")
    if rc and (not out.get("created") or rc < out["created"]):
        out["created"] = rc
    return out, added, updated


def merge_insights():
    """로컬에 없는 카드 섹션만 덧붙인다.

    사용자 본인의 문장이 원본이므로 이미 있는 카드는 절대 덮어쓰지 않는다.
    """
    src = REPO_DIR / "insights.md"
    if not src.exists():
        return 0
    text = src.read_text(encoding="utf-8")
    text = text.replace("`solutions/", "`" + str(PRACTICE_DIR) + "/")
    text = text.replace("~/", str(Path.home()) + "/")

    have = INSIGHTS_PATH.read_text(encoding="utf-8") if INSIGHTS_PATH.exists() else ""
    existing = set(re.findall(r"(?m)^## #(\d+)", have))

    add = []
    for chunk in re.split(r"(?m)^(?=## #)", text):
        m = re.match(r"## #(\d+)", chunk)
        if m and m.group(1) not in existing:
            add.append(chunk.rstrip() + "\n\n")
    if not add:
        return 0

    DATA_DIR.mkdir(parents=True, exist_ok=True)
    if not have:
        INSIGHTS_PATH.write_text(
            "# 통찰 카드\n\n사용자 본인의 말로 기록된 것만 담는다. "
            "모델이 요약해 넣지 않는다.\n\n" + "".join(add), encoding="utf-8")
    else:
        with open(INSIGHTS_PATH, "a", encoding="utf-8") as f:
            if not have.endswith("\n"):
                f.write("\n")
            f.write("".join(add))
    return len(add)


def restore_solutions():
    """레포의 풀이를 연습 디렉토리로 되돌린다.

    로컬에 같은 이름이 있으면 건드리지 않는다 — 지금 작업 중인 파일일 수 있고,
    덮어쓰면 되돌릴 방법이 없다.
    """
    src = REPO_DIR / "solutions"
    if not src.exists():
        return 0
    PRACTICE_DIR.mkdir(parents=True, exist_ok=True)
    n = 0
    for f in sorted(src.glob("*.py")):
        dst = PRACTICE_DIR / f.name
        if not dst.exists():
            shutil.copy2(f, dst)
            n += 1
    return n


def cmd_pull(args):
    """세션 시작 시 원격 아카이브의 진행 상황을 로컬로 가져온다.

    무슨 일이 있어도 0을 반환한다. 아카이브를 못 받는 건 훈련을 멈출 이유가 아니다.
    """
    if not (REPO_DIR / ".git").exists():
        print(f"아카이브 없음: {REPO_DIR} 는 git 레포가 아닙니다. 로컬 진도로 진행합니다.\n"
              f"  (git clone <원격주소> {REPO_DIR} 또는 LC_ARCHIVE_REPO 환경변수)")
        return 0

    if not args.no_fetch:
        ok, msg = git_pull()
        print(f"{'pull' if ok else '경고'}: {msg}")

    remote_prog = REPO_DIR / "progress.json"
    n_add = n_upd = 0
    if remote_prog.exists():
        try:
            remote = json.loads(remote_prog.read_text(encoding="utf-8"))
        except json.JSONDecodeError as e:
            print(f"경고: 원격 progress.json 파싱 실패 ({e}). 진도 병합을 건너뜁니다.")
        else:
            merged, added, updated = merge_progress(load_progress(), remote)
            if added or updated:
                save_progress(merged)
            n_add, n_upd = len(added), len(updated)

    n_card = merge_insights()
    n_sol = restore_solutions()

    if n_add or n_upd or n_card or n_sol:
        print(f"병합: 문제 +{n_add}개 / 갱신 {n_upd}개 / 통찰 카드 +{n_card}장 / 풀이 +{n_sol}개")
    else:
        print("병합: 로컬이 이미 최신입니다")
    return 0


# ---------------------------------------------------------------- 로컬 → 아카이브

def cmd_sync(args):
    if not (REPO_DIR / ".git").exists():
        print(f"에러: {REPO_DIR} 가 git 레포가 아닙니다.\n"
              f"      git clone <원격주소> {REPO_DIR} 로 먼저 클론하세요.\n"
              f"      다른 경로를 쓰려면 LC_ARCHIVE_REPO 환경변수를 지정하세요.",
              file=sys.stderr)
        return 1

    bank, prog = load_bank(), load_progress()
    ensure_gitignore()
    copy_skill()
    n_sol = copy_solutions()
    export_data(prog)
    update_readme(render_dashboard(bank, prog))

    _run(["git", "add", "-A"])
    if _run(["git", "diff", "--cached", "--quiet"]).returncode == 0:
        print("동기화: 변경 없음 (커밋 생략)")
        return 0

    msg = args.message or f"train: {date.today().isoformat()} 훈련 기록 갱신"
    r = _run(["git", "commit", "-m", msg])
    if r.returncode != 0:
        print(f"에러: 커밋 실패\n{r.stderr}", file=sys.stderr)
        return 1
    sha = _run(["git", "rev-parse", "--short", "HEAD"]).stdout.strip()
    print(f"커밋 {sha}: {msg}  (풀이 {n_sol}개)")

    if args.no_push:
        print("푸시 생략 (--no-push)")
        return 0

    r = _run(["git", "push", "origin", "HEAD"])
    if r.returncode != 0:
        print(f"에러: 푸시 실패 — 커밋은 로컬에 남아 있습니다.\n{r.stderr}",
              file=sys.stderr)
        return 1
    print("푸시 완료 → origin")
    return 0


# ---------------------------------------------------------------- 진입점

def main():
    ap = argparse.ArgumentParser(description="리트코드 데일리 훈련 진도 관리")
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("today", help="오늘 복습 카드 + 신규 추천")
    p.add_argument("--difficulty", choices=["medium", "hard"], help="난이도 강제")
    p.add_argument("--pattern", help="패턴 강제 (예: sliding-window)")
    p.set_defaults(func=cmd_today)

    p = sub.add_parser("record", help="신규 문제 결과 기록")
    p.add_argument("--id", type=int, required=True)
    p.add_argument("--hint", choices=HINT_LEVELS, required=True)
    p.add_argument("--minutes", type=int, default=0)
    p.add_argument("--solved", choices=["yes", "no"], default="yes")
    p.add_argument("--insight", required=True, help="사용자 본인의 말로 된 핵심 관찰 한 줄")
    p.add_argument("--signal", default="", help="이 패턴을 알아볼 신호")
    p.add_argument("--file", default="", help="사용자가 짠 코드 경로 (~/leetcode-practice/...)")
    p.add_argument("--pattern", default="", help="은행에 없는 문제일 때")
    p.add_argument("--title", default="", help="은행에 없는 문제일 때")
    p.add_argument("--difficulty", default="", help="은행에 없는 문제일 때")
    p.set_defaults(func=cmd_record)

    p = sub.add_parser("review", help="복습 결과 기록")
    p.add_argument("--id", type=int, required=True)
    p.add_argument("--hint", choices=HINT_LEVELS, required=True)
    p.add_argument("--insight", default="", help="더 나은 표현이 나왔으면 갱신")
    p.set_defaults(func=cmd_review)

    p = sub.add_parser("card", help="저장된 카드 보기")
    p.add_argument("--id", type=int, required=True)
    p.set_defaults(func=cmd_card)

    p = sub.add_parser("stats", help="패턴별 숙련도")
    p.set_defaults(func=cmd_stats)

    p = sub.add_parser("pull", help="아카이브에서 진도·통찰·풀이를 받아 로컬에 병합")
    p.add_argument("--no-fetch", action="store_true",
                   help="git pull 없이 이미 받아둔 레포 내용만 병합")
    p.set_defaults(func=cmd_pull)

    p = sub.add_parser("sync", help="공부 흔적을 아카이브 레포에 커밋·푸시")
    p.add_argument("--message", default="", help="커밋 메시지")
    p.add_argument("--no-push", action="store_true", help="커밋만 하고 푸시는 생략")
    p.set_defaults(func=cmd_sync)

    args = ap.parse_args()
    sys.exit(args.func(args) or 0)


if __name__ == "__main__":
    main()
