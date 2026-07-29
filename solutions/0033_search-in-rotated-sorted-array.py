"""33. Search in Rotated Sorted Array  [medium]
https://leetcode.com/problems/search-in-rotated-sorted-array/

제약: 1 <= nums.length <= 5000, -10^4 <= nums[i] <= 10^4,
      모든 값은 유일, 오름차순 정렬 후 회전되었을 수 있음,
      -10^4 <= target <= 10^4
      O(log n) 런타임 요구

여기에 직접 구현하세요. 다 되면 이 파일을 그냥 실행해서 스스로 확인할 수 있습니다:
    python3 ~/leetcode-practice/0033_search-in-rotated-sorted-array.py
"""

from typing import List


class Solution:
    
    def search(self, nums: List[int], target: int) -> int:
        n = len(nums)
        def k_binary_search() -> int:
                st = 0
                en = n-1
                tg = nums[en]
                while(st <= en):
                    mid = (en + st) // 2
                    if st == en:
                        return n - st 
                    elif nums[mid] > tg:
                        st = mid+1
                    else :
                        en = mid 
                return -1
        k = k_binary_search() 

        def t_binary_search() -> int:
            st = 0
            en = n-1
            while(st <= en):
                mid = (en + st) // 2
                if nums[(mid - k) % n] == target:
                    return (mid - k) % n
                elif nums[(mid - k) % n] > target:
                    en = mid -1
                else :
                    st = mid + 1
            return -1
        
        return t_binary_search()

# ── 확인용 (건드리지 않아도 됩니다) ──────────────────────────
if __name__ == "__main__":
    tests = [
        (([4, 5, 6, 7, 0, 1, 2], 0), 4),
        (([2, 0, 1], 1), 2),
        (([4, 5, 6, 7, 0, 1, 2], 3), -1),
        (([1], 0), -1)
    ]
    for args, expected in tests:
        got = Solution().search(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args} → {got} (기대 {expected})")
