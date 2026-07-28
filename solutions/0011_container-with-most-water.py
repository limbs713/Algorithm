"""11. Container With Most Water  [medium]
https://leetcode.com/problems/container-with-most-water/

제약: n == height.length, 2 <= n <= 10^5, 0 <= height[i] <= 10^4
"""

from typing import List


class Solution:
    def maxArea(self, height: List[int]) -> int:
        st = 0
        en = len(height) - 1
        curr = 0
        while st != en:
            curr = max((en - st) * min(height[st], height[en]), curr)
            if height[st] < height[en]:
                st += 1
            else:
                en -= 1

        return curr


# ── 확인용 ──────────────────────────
if __name__ == "__main__":
    tests = [
        (([1, 8, 6, 2, 5, 4, 8, 3, 7],), 49),
        (([1, 1],), 1),
    ]
    for args, expected in tests:
        got = Solution().maxArea(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args[0]} → {got} (기대 {expected})")
