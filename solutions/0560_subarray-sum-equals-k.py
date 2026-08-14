"""560. Subarray Sum Equals K  [medium]
https://leetcode.com/problems/subarray-sum-equals-k/

제약: 1 <= nums.length <= 2 * 10^4, -1000 <= nums[i] <= 1000, -10^7 <= k <= 10^7

여기에 직접 구현하세요. 다 되면 이 파일을 그냥 실행해서 스스로 확인할 수 있습니다:
    python3 ~/leetcode-practice/0560_subarray-sum-equals-k.py
"""

from typing import List
from collections import defaultdict

class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        count = defaultdict(int)
        count[0] = 1
        curr = 0
        sum = 0
        for x in nums:
            curr += x
            sum += count[curr - k]
            count[curr] += 1
        return sum


# ── 확인용 (건드리지 않아도 됩니다) ──────────────────────────
if __name__ == "__main__":
    tests = [
        (([1, 1, 1], 2), 2),
        (([1, 2, 3], 3), 2),
    ]
    for args, expected in tests:
        got = Solution().subarraySum(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args} → {got} (기대 {expected})")
