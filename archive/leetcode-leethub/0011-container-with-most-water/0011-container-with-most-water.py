class Solution:
    def maxArea(self, height: List[int]) -> int:
        st = 0
        en = len(height)-1
        curr = 0
        while st != en:
            curr = max((en - st) * min(height[st], height[en]), curr)
            if height[st] < height[en] : st+=1
            else : en-=1

        return curr