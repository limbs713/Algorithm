# Algorithm
This is a auto push repository for Baekjoon Online Judge created with [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub).

<!--- LEETCODE-DAILY:START --->

## 리트코드 데일리 훈련

[`skill/`](skill/)의 훈련 스킬이 매 세션 자동으로 갱신합니다. 통찰 카드는 간격 반복(1/3/7/21일)으로 되살립니다.

| 푼 문제 | 해결 | 복습 횟수 | 누적 시간 | 갱신 |
| --- | --- | --- | --- | --- |
| 4 | 4 | 3 | 120분 | 2026-08-14 |

### 통찰 카드

| # | 문제 | 난이도 | 패턴 | 힌트 | 통찰 | 코드 |
| --- | --- | --- | --- | --- | --- | --- |
| 3 | Longest Substring Without Repeating Characters | medium | `sliding-window` | H1 | 인덱스가 두 번 안 들어오니까 최대 2n번만 처리된다 | [.py](solutions/0003_longest-substring-without-repeating-characters.py) |
| 11 | Container With Most Water | medium | `two-pointers` | H3 | 천장보다 크면 추가분은 버려진다 | [.py](solutions/0011_container-with-most-water.py) |
| 33 | Search in Rotated Sorted Array | medium | `binary-search` | H4 | 경계 찾기 이진 탐색(== 로 답을 확정하는 줄이 없는 경우)은 mid 자신이 답일 수 있으므로 en = mid-1로 버리면 안 되고 en = mid로 후보를 남겨야 한다. 값 찾기는 == 로 확정하니 버려도 안전. 짝 규칙: en=mid는 내림 mid, st=mid는 올림 mid. | [.py](solutions/0033_search-in-rotated-sorted-array.py) |
| 560 | Subarray Sum Equals K | medium | `prefix-sum` | H3 | 부분합의 차가 곧 부분배열의 합이므로, prefix - k가 이미 나왔던 횟수만큼 답이다. 조회가 먼저, 자기 등록은 나중(i<=j 보장) | [.py](solutions/0560_subarray-sum-equals-k.py) |

### 복습 예정

| 날짜 | # | 문제 |
| --- | --- | --- |
| 2026-08-15 | 33 | Search in Rotated Sorted Array |
| 2026-08-16 | 560 | Subarray Sum Equals K |
| 2026-08-18 | 3 | Longest Substring Without Repeating Characters |
| 2026-08-19 | 11 | Container With Most Water |

<!--- LEETCODE-DAILY:END --->

<!---LeetCode Topics Start-->
# LeetCode Topics
## Array
|  |
| ------- |
| [0011-container-with-most-water](https://github.com/limbs713/Algorithm/tree/master/0011-container-with-most-water) |
| [0088-merge-sorted-array](https://github.com/limbs713/Algorithm/tree/master/0088-merge-sorted-array) |
## Two Pointers
|  |
| ------- |
| [0011-container-with-most-water](https://github.com/limbs713/Algorithm/tree/master/0011-container-with-most-water) |
| [0088-merge-sorted-array](https://github.com/limbs713/Algorithm/tree/master/0088-merge-sorted-array) |
## Sorting
|  |
| ------- |
| [0088-merge-sorted-array](https://github.com/limbs713/Algorithm/tree/master/0088-merge-sorted-array) |
## Greedy
|  |
| ------- |
| [0011-container-with-most-water](https://github.com/limbs713/Algorithm/tree/master/0011-container-with-most-water) |
<!---LeetCode Topics End-->