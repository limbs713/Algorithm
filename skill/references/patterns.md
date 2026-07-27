# 패턴 레퍼런스 (Python)

힌트 H2~H4를 만들 때, 또는 사용자가 특정 패턴 정리를 요청할 때 읽는다. **사용자에게 통째로 복사해 보여주지 않는다** — 읽기는 회상이 아니고, 이 사용자에게 필요한 건 회상이다. 필요한 한 줄만 뽑아 쓴다.

각 항목은 신호(무엇을 보고 이 패턴을 떠올리나) → 템플릿 → 흔한 함정 → Hard로 가는 다리 순이다.

## 목차
1. [슬라이딩 윈도우](#1-슬라이딩-윈도우) 2. [투 포인터](#2-투-포인터) 3. [이분 탐색](#3-이분-탐색)
4. [누적합 + 해시맵](#4-누적합--해시맵) 5. [단조 스택](#5-단조-스택) 6. [단조 덱](#6-단조-덱)
7. [힙](#7-힙) 8. [구간 처리](#8-구간-처리) 9. [그래프 BFS/DFS](#9-그래프-bfsdfs)
10. [위상 정렬](#10-위상-정렬) 11. [유니온 파인드](#11-유니온-파인드) 12. [최단 경로](#12-최단-경로)
13. [백트래킹](#13-백트래킹) 14. [1차원 DP](#14-1차원-dp) 15. [2차원 DP](#15-2차원-dp)
16. [구간 DP](#16-구간-dp) 17. [트리 DFS](#17-트리-dfs) 18. [트라이](#18-트라이)
19. [그리디](#19-그리디) 20. [펜윅 트리](#20-펜윅-트리)

---

## 0. 복잡도 역추론표 (매 세션 1단계에서 사용)

| 제약 | 허용 복잡도 | 떠올릴 것 |
|------|------------|----------|
| n ≤ 10 | O(n!) | 순열 전탐색 |
| n ≤ 20~25 | O(2ⁿ), O(2ⁿ·n) | 비트마스크 DP, 부분집합 |
| n ≤ 100 | O(n³) | 구간 DP, 플로이드 |
| n ≤ 1,000 | O(n²) | 2차원 DP, 완전탐색 |
| n ≤ 10⁵ | O(n log n) | 정렬, 힙, 이분탐색, 세그트리 |
| n ≤ 10⁶ | O(n) | 투 포인터, 슬라이딩 윈도우, 누적합 |
| n ≤ 10⁹ | O(log n) | 답에 대한 이분탐색, 수학 |

값의 범위가 10⁹인데 개수가 10⁵면 **좌표 압축**이나 **답에 대한 이분탐색**을 의심한다.

---

## 1. 슬라이딩 윈도우

**신호** — 연속된 부분배열/부분문자열 + "가장 긴/짧은" + "최대 k개 허용". 순서를 바꾸면 안 되는 구조.

```python
left = 0
state = {}          # 윈도우 내부 상태
best = 0
for right, ch in enumerate(s):
    state[ch] = state.get(ch, 0) + 1        # 확장
    while not valid(state):                  # 위반하면 축소
        state[s[left]] -= 1
        left += 1
    best = max(best, right - left + 1)
```

**함정** — 축소 조건을 `if`로 쓰면 한 칸만 줄어든다. 위반이 여러 칸일 수 있으면 `while`. 반대로 "최대 길이"를 구할 때 윈도우를 절대 줄이지 않고 한 칸씩만 미는 변형(424)도 있는데, 이건 답이 커질 때만 갱신되므로 축소가 불필요하다는 관찰에 기반한다.

**"정확히 k개"는 `atMost(k) - atMost(k-1)`로 바꾼다** (992). 정확히를 직접 세려 하면 윈도우가 단조롭지 않아 무너진다.

**Hard로 가는 다리** — 윈도우 안의 max/min이 필요해지면 단조 덱(239), 카운팅이 복잡해지면 해시맵 + 충족 카운터(76).

## 2. 투 포인터

**신호** — 정렬된 배열, 양 끝에서 좁혀오기, 쌍/삼중쌍, 면적 최대화.

```python
lo, hi = 0, len(a) - 1
while lo < hi:
    cur = a[lo] + a[hi]
    if cur == target: return (lo, hi)
    if cur < target: lo += 1
    else: hi -= 1
```

**함정** — 3Sum류는 중복 제거를 잊기 쉽다. 정렬 후 `if i > 0 and a[i] == a[i-1]: continue`.

**핵심 논리** — 왜 한쪽을 버려도 되는지 항상 말할 수 있어야 한다. 11번은 "짧은 쪽을 옮겨야만 넓이가 커질 여지가 있다"가 그 논리다. 이걸 못 말하면 그냥 외운 것이다.

## 3. 이분 탐색

두 종류를 구분한다. **배열 위 탐색**과 **답에 대한 탐색**. Hard의 대부분은 후자다.

**신호(답 탐색)** — "최소의 최대", "최대의 최소", "k개 이하로 나눌 때", 값 범위가 10⁹인데 개수는 작음.

```python
def feasible(x): ...          # x가 가능한가? 단조여야 한다
lo, hi = 최소값, 최대값
while lo < hi:
    mid = (lo + hi) // 2
    if feasible(mid): hi = mid
    else: lo = mid + 1
return lo
```

**함정** — `feasible`의 단조성을 확인하지 않고 쓰면 틀린다. "x가 되면 x+1도 된다"가 성립해야 한다. 그리고 `lo = mid + 1` / `hi = mid`의 짝을 바꾸면 무한 루프다. 짝을 외우지 말고 **불변식**("답은 항상 [lo, hi]에 있다")으로 유도한다.

**Hard로 가는 다리** — feasible을 그리디로 O(n)에 판정(410), 두 배열의 파티션 불변식(4), 이분탐색 안에 투 포인터(719).

## 4. 누적합 + 해시맵

**신호** — "부분배열의 합이 정확히 k", "나머지가 같은 지점", 0/1 개수가 같은 구간(0을 -1로 치환).

```python
from collections import defaultdict
seen = defaultdict(int); seen[0] = 1
cur = ans = 0
for x in nums:
    cur += x
    ans += seen[cur - k]     # 이전에 같은 차이를 본 횟수
    seen[cur] += 1
```

**함정** — `seen[0] = 1` 초기화를 빠뜨리면 처음부터 시작하는 구간을 놓친다. 그리고 최댓값을 구할 땐 카운트가 아니라 **가장 이른 인덱스**를 저장해야 한다.

**Hard로 가는 다리** — 2차원이면 행 구간을 고정해 1차원으로 축약(1074), 음수가 섞이면 슬라이딩 윈도우가 죽으므로 누적합 + 단조 덱(862).

## 5. 단조 스택

**신호** — "다음으로 큰 원소", 히스토그램, 각 원소의 좌우 경계를 알아야 함.

```python
stack = []                      # 인덱스를 담는다 (값이 아니라)
for i, h in enumerate(heights):
    while stack and heights[stack[-1]] > h:
        top = stack.pop()
        width = i - stack[-1] - 1 if stack else i
        best = max(best, heights[top] * width)
    stack.append(i)
```

**함정** — 값 대신 **인덱스**를 넣어야 폭을 계산할 수 있다. 그리고 루프가 끝난 뒤 스택에 남은 원소 처리를 잊기 쉽다 — 배열 끝에 센티널 0을 붙이면 한 번에 정리된다.

**Hard로 가는 다리** — 2차원을 행별 히스토그램으로 환원(85).

## 6. 단조 덱

**신호** — 슬라이딩 윈도우인데 max/min이 필요, DP 전이에 구간 최댓값.

```python
from collections import deque
dq = deque()                    # 인덱스, 값 기준 내림차순 유지
for i, x in enumerate(nums):
    while dq and nums[dq[-1]] <= x: dq.pop()      # 나보다 작은 건 영원히 쓸모없다
    dq.append(i)
    if dq[0] <= i - k: dq.popleft()               # 윈도우 밖
    if i >= k - 1: ans.append(nums[dq[0]])
```

**핵심 관찰** — "나보다 뒤에 있고 나보다 큰 원소가 있으면, 나는 절대 답이 될 수 없다." 이 한 줄이 덱의 존재 이유다.

## 7. 힙

**신호** — k번째, 상위 k개, 스트리밍 중앙값, 매 단계 최적을 꺼내는 그리디.

```python
import heapq
h = []
for x in nums:
    heapq.heappush(h, x)
    if len(h) > k: heapq.heappop(h)   # 최소 힙 크기 k → 루트가 k번째로 큰 값
```

**함정** — `heapq`는 최소 힙만 있다. 최대 힙은 `-x`를 넣는다. 튜플을 넣을 때 두 번째 원소가 비교 불가능(예: dict)이면 터지므로 카운터를 끼워 넣는다: `(priority, counter, obj)`.

**두 힙 패턴(295)** — 작은 절반은 최대 힙, 큰 절반은 최소 힙, 크기 차 ≤ 1 불변식.

**후회 교환(regret swap, 871/630)** — 일단 다 넣고 가다가 불가능해지면 과거 선택 중 최악을 힙에서 꺼내 취소한다. Hard 그리디의 단골이다.

## 8. 구간 처리

**신호** — `[start, end]` 배열, 겹침 병합, 회의실.

```python
intervals.sort(key=lambda x: x[0])
out = [intervals[0]]
for s, e in intervals[1:]:
    if s <= out[-1][1]: out[-1][1] = max(out[-1][1], e)
    else: out.append([s, e])
```

**개수만 필요하면 스윕이 더 낫다** — 시작에 +1, 끝에 -1을 찍고 정렬해 누적한다. 최대 동시 개수가 바로 나온다.

**함정** — 끝점 정렬 vs 시작점 정렬. "최소 제거 개수"(435)는 **끝점** 기준 정렬이 맞다. 왜인지 교환 논증으로 말할 수 있어야 한다.

## 9. 그래프 BFS/DFS

**신호** — 격자 연결 요소, 가중치 없는 최단 경로, 상태 공간 탐색.

```python
from collections import deque
q = deque([(start, 0)]); seen = {start}
while q:
    node, d = q.popleft()
    if node == goal: return d
    for nxt in neighbors(node):
        if nxt not in seen:
            seen.add(nxt); q.append((nxt, d + 1))
```

**함정** — `seen`은 큐에 **넣을 때** 표시한다. 꺼낼 때 표시하면 같은 노드가 중복으로 들어가 지수 폭발한다.

**Hard로 가는 다리** — 노드가 명시적 그래프가 아니라 "상태"일 때(127의 단어, 773의 보드 배치). 상태를 어떻게 인코딩할지가 문제의 절반이다. 그리고 격자 DFS + 메모이제이션은 사실 암묵적 DAG 위의 DP다(329).

## 10. 위상 정렬

**신호** — 선수 관계, 사이클 검출, 유효한 순서 출력.

```python
from collections import deque
indeg = [0] * n
for u, v in edges: indeg[v] += 1        # u → v
q = deque([i for i in range(n) if indeg[i] == 0])
order = []
while q:
    u = q.popleft(); order.append(u)
    for v in graph[u]:
        indeg[v] -= 1
        if indeg[v] == 0: q.append(v)
return order if len(order) == n else []  # 길이가 모자라면 사이클
```

**함정** — 간선 방향을 뒤집어 놓고 헤매는 경우가 압도적으로 많다. "a를 들으려면 b가 필요" → `b → a`.

## 11. 유니온 파인드

**신호** — 연결 요소 개수, 간선을 추가하며 병합, 사이클 만드는 간선.

```python
par = list(range(n))
def find(x):
    while par[x] != x:
        par[x] = par[par[x]]     # 경로 압축
        x = par[x]
    return x
def union(a, b):
    ra, rb = find(a), find(b)
    if ra == rb: return False    # 이미 같은 집합 = 사이클
    par[rb] = ra
    return True
```

**Hard로 가는 다리** — **시간을 거꾸로 돌리는 것**(803). 유니온 파인드는 분리를 못 하므로, 제거 문제는 마지막 상태에서 시작해 역순으로 붙인다. 이 발상이 Hard 유니온 파인드의 거의 전부다.

## 12. 최단 경로

**신호** — 가중 그래프 최소 비용, 경유지 제한, 격자에서 "최대 높이를 최소화".

```python
import heapq
dist = {start: 0}; pq = [(0, start)]
while pq:
    d, u = heapq.heappop(pq)
    if d > dist.get(u, float('inf')): continue    # 낡은 항목
    for v, w in graph[u]:
        nd = d + w
        if nd < dist.get(v, float('inf')):
            dist[v] = nd; heapq.heappush(pq, (nd, v))
```

**변형** — "경로상 최댓값을 최소화"면 `nd = max(d, w)`로 바꾼다(778, 1631). 다익스트라의 완화식만 갈아끼우면 되는 문제군이 꽤 넓다.

**경유지 k개 제한(787)은 다익스트라가 아니라 벨만-포드/BFS 레이어**다. 상태에 단계 수가 들어가야 하기 때문.

## 13. 백트래킹

**신호** — 모든 조합/순열, n ≤ 20, 제약 만족.

```python
def bt(start, path):
    if ok(path): res.append(path[:]); return
    for i in range(start, n):
        if not promising(i, path): continue    # 가지치기가 본체다
        path.append(cand[i])
        bt(i + 1, path)                        # i면 재사용 허용, i+1이면 금지
        path.pop()
```

**함정** — `res.append(path)`는 참조를 넣는 것이라 나중에 다 비어버린다. `path[:]`로 복사한다. 중복 원소가 있으면 정렬 후 `if i > start and cand[i] == cand[i-1]: continue`.

**Hard로 가는 다리** — 가지치기 없이는 시간 초과다. 212는 트라이로 "이 접두사로 시작하는 단어가 아예 없으면 즉시 컷"을 만든다.

## 14. 1차원 DP

**신호** — "i번째까지의 최적", 선택/건너뛰기, 조합 개수.

```python
dp = [초기값] * (n + 1)
for i in range(1, n + 1):
    dp[i] = 전이(dp[i-1], dp[i-2], ...)
```

**설계 순서를 지킨다**: ① 상태 정의를 한국어 문장으로 말한다 ("dp[i] = i번째 집까지 봤을 때 최대 금액") ② 전이식 ③ 초기값 ④ 답의 위치. 상태 정의를 말로 못 하면 코드는 100% 틀린다.

**LIS는 O(n log n) 버전을 알아야 한다** — `bisect_left`로 tails 배열을 갱신. tails는 실제 부분수열이 아니라 "길이 k인 증가 부분수열의 가능한 최소 끝값"이다.

## 15. 2차원 DP

**신호** — 두 문자열 비교, 격자 경로, 부분수열 매칭.

```python
dp = [[0] * (m + 1) for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(1, m + 1):
        if a[i-1] == b[j-1]: dp[i][j] = dp[i-1][j-1] + 1
        else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

**함정** — 인덱스 off-by-one. `dp[i][j]`가 "a의 앞 i글자, b의 앞 j글자"면 문자 접근은 `a[i-1]`이다. 이걸 섞으면 디버깅이 지옥이다.

**Hard로 가는 다리** — 전이가 3갈래 이상으로 갈라지는 케이스 분석(10, 44의 `*` 처리). 케이스를 종이에 다 적고 시작하지 않으면 못 짠다.

## 16. 구간 DP

**신호** — 구간을 나누는 분할점 선택, 터뜨리는 순서, n ≤ 500.

```python
for length in range(2, n + 1):          # 짧은 구간부터
    for i in range(n - length + 1):
        j = i + length - 1
        for k in range(i + 1, j):        # 분할점
            dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + cost(i, k, j))
```

**핵심 트릭** — "마지막에 무엇을 하는가"로 뒤집는다. 312(풍선)는 "먼저 터뜨릴 것"으로 생각하면 상태가 안 닫히지만, "마지막에 남는 것"으로 뒤집으면 좌우가 독립이 되어 닫힌다. 구간 DP Hard의 절반이 이 뒤집기다.

## 17. 트리 DFS

**신호** — 이진 트리, 부모-자식 집계, 경로 합, 직렬화.

```python
def dfs(node):
    if not node: return 0
    left = max(dfs(node.left), 0)      # 음수면 안 쓰는 게 낫다
    right = max(dfs(node.right), 0)
    nonlocal best
    best = max(best, node.val + left + right)   # 여기서 갈라지는 경로
    return node.val + max(left, right)          # 부모에게 줄 수 있는 건 한쪽뿐
```

**핵심 관찰(124)** — **반환값과 정답이 다르다.** 부모에게 넘기는 값(한쪽 가지만)과 답 후보(양쪽 합)를 분리하는 것. 이 분리를 못 보면 트리 Hard는 거의 다 막힌다.

## 18. 트라이

**신호** — 접두사 검색, 사전 다수 조회, 와일드카드.

```python
trie = {}
for w in words:
    node = trie
    for ch in w: node = node.setdefault(ch, {})
    node['$'] = w                     # 종료 표시에 원본을 넣어두면 편하다
```

dict 중첩이 클래스보다 짧고 빠르다. 백트래킹과 합칠 땐 노드를 인자로 같이 넘긴다.

## 19. 그리디

**신호** — 정렬 후 한 번 훑기, 도달 가능성, 최소 개수로 덮기.

**그리디는 항상 증명을 요구한다.** "이게 최적일 것 같다"는 근거가 아니다. 교환 논증으로 말할 수 있어야 한다: "최적해가 내 선택과 다르다면, 내 선택으로 바꿔도 답이 나빠지지 않는다."

증명이 안 서면 그건 DP다. 실전에서 그리디로 오답을 내는 대부분은 이 검증을 건너뛴 경우다.

**2패스 그리디(135)** — 왼쪽 제약과 오른쪽 제약을 각각 한 번씩 훑고 max를 취한다. 한 번에 둘 다 만족시키려 하면 안 된다.

## 20. 펜윅 트리

**신호** — "나보다 뒤에 있으면서 작은 원소 개수", 역순 쌍, 동적 구간 합.

```python
class BIT:
    def __init__(self, n): self.t = [0] * (n + 1)
    def add(self, i, v):
        while i < len(self.t): self.t[i] += v; i += i & -i
    def query(self, i):                     # [1, i] 합
        s = 0
        while i > 0: s += self.t[i]; i -= i & -i
        return s
```

**함정** — 1-based다. 값이 크면 **좌표 압축** 먼저: `rank = {v: i+1 for i, v in enumerate(sorted(set(nums)))}`.

**대안** — 같은 문제를 머지 소트로도 푼다(315, 493). 둘 중 하나만 확실히 손에 붙이면 된다.
