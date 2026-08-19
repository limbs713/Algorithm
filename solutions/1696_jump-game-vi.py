"""1696. Jump Game VI  [medium]
https://leetcode.com/problems/jump-game-vi/

제약: 1 <= nums.length, k <= 10^5, -10^4 <= nums[i] <= 10^4

여기에 직접 구현하세요. 다 되면 이 파일을 그냥 실행해서 스스로 확인할 수 있습니다:
    python3 ~/leetcode-practice/1696_jump-game-vi.py
"""

from typing import List
import heapq

class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        heap = []
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        heapq.heappush(heap,(-nums[0],0))
        for i in range(1,n):
            while heap and heap[0][1] not in range(i-k, i):
                heapq.heappop(heap)
            dp[i] = -heap[0][0] + nums[i]
            heapq.heappush(heap,(-dp[i],i))
        return dp[n-1]
        
                




# ── 확인용 (건드리지 않아도 됩니다) ──────────────────────────
if __name__ == "__main__":
    tests = [
        (([1, -1, -2, 4, -7, 3], 2), 7),
        (([10, -5, -2, 4, 0, 3], 3), 17),
        (([1, -5, -20, 4, -1, 3, -6, -3], 2), 0),
    ]
    for args, expected in tests:
        got = Solution().maxResult(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args} → {got} (기대 {expected})")
