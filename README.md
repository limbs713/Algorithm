# Algorithm

알고리즘 문제 풀이 기록입니다. 지금은 **리트코드 데일리 훈련**이 메인 — 하루 1문제를 직접 풀고,
그 문제에서 건진 핵심 관찰 한 줄을 간격 반복으로 되살립니다. 많이 푸는 게 목적이 아니라
**Hard를 봤을 때 접근법이 몇 분 안에 떠오르는 상태**를 만드는 게 목적입니다.

| 경로 | 내용 |
| --- | --- |
| [`solutions/`](solutions/) | 리트코드 데일리 풀이 |
| [`insights.md`](insights.md) | 통찰 카드 — 문제별 핵심 관찰 한 줄 |
| [`progress.json`](progress.json) | 간격 반복 상태 (힌트 이력·다음 복습일) |
| [`skill/`](skill/) | 훈련 스킬 사본 — 다른 기기에서 환경 복구용 |
| [`archive/`](archive/) | 백준 56 · 프로그래머스 56 (2025-02 종료), 초기 리트코드 풀이 2개 |

<!--- LEETCODE-DAILY:START --->

## 리트코드 데일리 훈련

[`skill/`](skill/)의 훈련 스킬이 매 세션 자동으로 갱신합니다. 통찰 카드는 간격 반복(1/3/7/21일)으로 되살립니다.

| 푼 문제 | 해결 | 복습 횟수 | 누적 시간 | 갱신 |
| --- | --- | --- | --- | --- |
| 6 | 6 | 6 | 180분 | 2026-08-19 |

### 통찰 카드

| # | 문제 | 난이도 | 패턴 | 힌트 | 통찰 | 코드 |
| --- | --- | --- | --- | --- | --- | --- |
| 3 | Longest Substring Without Repeating Characters | medium | `sliding-window` | H1 | 인덱스가 두 번 안 들어오니까 최대 2n번만 처리된다 | [.py](solutions/0003_longest-substring-without-repeating-characters.py) |
| 11 | Container With Most Water | medium | `two-pointers` | H3 | 천장보다 크면 추가분은 버려진다 | [.py](solutions/0011_container-with-most-water.py) |
| 33 | Search in Rotated Sorted Array | medium | `binary-search` | H4 | 경계 찾기 이진 탐색(== 로 답을 확정하는 줄이 없는 경우)은 mid 자신이 답일 수 있으므로 en = mid-1로 버리면 안 되고 en = mid로 후보를 남겨야 한다. 값 찾기는 == 로 확정하니 버려도 안전. 짝 규칙: en=mid는 내림 mid, st=mid는 올림 mid. | [.py](solutions/0033_search-in-rotated-sorted-array.py) |
| 560 | Subarray Sum Equals K | medium | `prefix-sum` | H3 | 부분합의 차가 곧 부분배열의 합이므로, prefix - k가 이미 나왔던 횟수만큼 답이다. 조회가 먼저, 자기 등록은 나중(i<=j 보장) | [.py](solutions/0560_subarray-sum-equals-k.py) |
| 739 | Daily Temperatures | medium | `monotonic-stack` | H1 | 스택이 이 로직으로 돌면 top이 항상 가장 작으므로, 한 값은 한 번 들어갔다 한 번 나오면 다시는 안 봐도 된다 — 그래서 while로 연달아 pop해도 전체가 O(n) | [.py](solutions/0739_daily-temperatures.py) |
| 1696 | Jump Game VI | medium | `monotonic-deque` | H3 | 확정된 dp[j] 하나에 j까지 오는 경로 전체가 접혀 있다. 그래서 dp[i]는 경로가 아니라 dp[i-k]~dp[i-1] 값만 보면 된다 | [.py](solutions/1696_jump-game-vi.py) |

### 복습 예정

| 날짜 | # | 문제 |
| --- | --- | --- |
| 2026-08-20 | 33 | Search in Rotated Sorted Array |
| 2026-08-21 | 739 | Daily Temperatures |
| 2026-08-21 | 1696 | Jump Game VI |
| 2026-08-23 | 560 | Subarray Sum Equals K |
| 2026-08-28 | 3 | Longest Substring Without Repeating Characters |
| 2026-08-31 | 11 | Container With Most Water |

<!--- LEETCODE-DAILY:END --->