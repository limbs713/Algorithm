# 통찰 카드

사용자 본인의 말로 기록된 것만 담는다. 모델이 요약해 넣지 않는다.

## #3 Longest Substring Without Repeating Characters [medium] · sliding-window
- 기록일: 2026-07-27 (힌트 H1)
- **통찰**: 인덱스가 두 번 안 들어오니까 최대 2n번만 처리된다
- 신호: 연속된 부분 문자열 → 이어진 구간을 찾는 건 투 포인터가 가장 빠르다, 최대 O(2n). 한 번 나온 걸 찾는 건 set으로 O(1)
- 내 코드: `solutions/0003_longest-substring-without-repeating-characters.py`

## #11 Container With Most Water [medium] · two-pointers
- 기록일: 2026-07-28 (힌트 H3)
- **통찰**: 천장보다 크면 추가분은 버려진다
- 신호: ~의 최댓값을 구하시오 → 최댓값을 구하기 전에 그 값을 구하는 수식이 뭔지 먼저 정하고, 식의 각 항이 언제 최대가 되는지 본다
- 내 코드: `solutions/0011_container-with-most-water.py`

## #33 Search in Rotated Sorted Array [medium] · binary-search
- 기록일: 2026-07-29 (힌트 H4)
- **통찰**: 정렬 배열을 실제로 만들거나 O(n)으로 옮기지 않고, 논리 인덱스(0~n-1)로 이진 탐색을 돌리되 값을 읽는 순간에만 (mid-k)%n으로 실제 위치를 계산한다. 비교하는 값과 이동 판단이 같은 자리를 봐야 한다.
- 신호: 어쨌든 정렬된 배열이면 반드시 이진 탐색이 가능하다. 틀어진 배열을 원복하는 키(회전량)를 O(log n)으로 구하는 것이 핵심.
- 내 코드: `solutions/0033_search-in-rotated-sorted-array.py`

## #33 Search in Rotated Sorted Array [medium] · binary-search
- 기록일: 2026-07-29 (힌트 H4)
- **통찰**: 경계 찾기 이진 탐색(== 로 답을 확정하는 줄이 없는 경우)은 mid 자신이 답일 수 있으므로 en = mid-1로 버리면 안 되고 en = mid로 후보를 남겨야 한다. 값 찾기는 == 로 확정하니 버려도 안전. 짝 규칙: en=mid는 내림 mid, st=mid는 올림 mid.
- 신호: 이진 탐색에서 == 비교로 즉시 return하는 줄이 없다면 값 찾기가 아니라 경계 찾기 → mid를 버리지 말 것
- 내 코드: `solutions/0033_search-in-rotated-sorted-array.py`

