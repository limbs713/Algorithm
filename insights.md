# 통찰 카드

사용자 본인의 말로 기록된 것만 담는다. 모델이 요약해 넣지 않는다.

## #3 Longest Substring Without Repeating Characters [medium] · sliding-window
- 기록일: 2026-07-27 (힌트 H1)
- **통찰**: 인덱스가 두 번 안 들어오니까 최대 2n번만 처리된다
- 신호: 연속된 부분 문자열 → 이어진 구간을 찾는 건 투 포인터가 가장 빠르다, 최대 O(2n). 한 번 나온 걸 찾는 건 set으로 O(1)
- 내 코드: `solutions/0003_longest-substring-without-repeating-characters.py`

