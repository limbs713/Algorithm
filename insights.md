# 통찰 카드

사용자 본인의 말로 기록된 것만 담는다. 모델이 요약해 넣지 않는다.

## #3 Longest Substring Without Repeating Characters [medium] · sliding-window

- 기록일: 2026-07-27 (힌트 H1)
- **통찰**: 인덱스가 두 번 안 들어오니까 최대 2n번만 처리된다
- **신호**: 연속된 부분 문자열 → 투 포인터가 가장 빠르다, 최대 O(2n). 한 번 나온 걸 찾는 건 set으로 O(1)
- 내 코드: `solutions/0003_longest-substring-without-repeating-characters.py`

## #11 Container With Most Water [medium] · two-pointers

- 기록일: 2026-07-28 (힌트 H3)
- **통찰**: 천장보다 크면 추가분은 버려진다
- **신호**: "~의 최댓값을 구하시오" → 값을 구하는 수식을 먼저 정하고, 각 항이 언제 최대가 되는지 본다
- 내 코드: `solutions/0011_container-with-most-water.py`

## #33 Search in Rotated Sorted Array [medium] · binary-search

- 기록일: 2026-07-29 (힌트 H4, 40분)
- **통찰 1**: 인덱스는 `0 ~ n-1` 그대로 쓰고, **값을 읽을 때만** `(mid-k) % n`으로 실제 위치로 바꾼다. 비교하는 줄도 반드시 같은 자리를 봐야 한다 (한 줄만 `nums[mid]`로 두면 조용히 틀림)
- **통찰 2**: `==`로 검사하는 게 아니라서 mid도 정답일 수 있고, 그래서 `en = mid`로 남겨야 한다. 짝 규칙 — `en = mid`는 내림 mid, `st = mid`는 올림 mid
- **신호**: 정렬된 배열이면 어떻게든 이진 탐색이 된다. 틀어진 배열을 원복하는 키(회전량)를 O(log n)으로 구하는 게 핵심
- 내 코드: `solutions/0033_search-in-rotated-sorted-array.py`
## #560 Subarray Sum Equals K [medium] · prefix-sum
- 기록일: 2026-08-14 (힌트 H3)
- **통찰**: 부분합의 차가 곧 부분배열의 합이므로, prefix - k가 이미 나왔던 횟수만큼 답이다. 조회가 먼저, 자기 등록은 나중(i<=j 보장)
- 신호: 연속 부분배열의 합 + 음수 포함(슬라이딩 윈도우 불가) → prefix sum + 해시맵
- 내 코드: `solutions/0560_subarray-sum-equals-k.py`

