"""739. Daily Temperatures  [medium]
https://leetcode.com/problems/daily-temperatures/

제약: 1 <= temperatures.length <= 10^5, 30 <= temperatures[i] <= 100

여기에 직접 구현하세요. 다 되면 이 파일을 그냥 실행해서 스스로 확인할 수 있습니다:
    python3 ~/leetcode-practice/0739_daily-temperatures.py
"""

from typing import List


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        stack = []
        answer = [0] * len(temperatures)
        for i, t in enumerate(temperatures) :
            while stack and stack[-1][1] < t  :
                ci, ct = stack.pop()
                answer[ci] = i - ci
            stack.append((i,t))

        return answer       

# ── 확인용 (건드리지 않아도 됩니다) ──────────────────────────
if __name__ == "__main__":
    tests = [
        (([73, 74, 75, 71, 69, 72, 76, 73],), [1, 1, 4, 2, 1, 1, 0, 0]),
        (([30, 40, 50, 60],), [1, 1, 1, 0]),
        (([30, 60, 90],), [1, 1, 0]),
    ]
    for args, expected in tests:
        got = Solution().dailyTemperatures(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args} → {got} (기대 {expected})")
