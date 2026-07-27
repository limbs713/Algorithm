"""3. Longest Substring Without Repeating Characters  [medium]
https://leetcode.com/problems/longest-substring-without-repeating-characters/

제약: 0 <= s.length <= 5 * 10^4
      s는 영문자, 숫자, 기호, 공백으로 구성

여기에 직접 구현하세요. 다 되면 이 파일을 그냥 실행해서 스스로 확인할 수 있습니다:
    python3 ~/leetcode-practice/0003_longest-substring-without-repeating-characters.py
"""


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        w = set()
        st = 0
        ans = 0
        curr = 0
        for en in range(len(s)):
            while s[en] in w :
                w.remove(s[st])
                st+=1
                curr-=1
            w.add(s[en])
            curr+=1
            ans = max(ans,curr)
        return ans
                






# ── 확인용 (건드리지 않아도 됩니다) ──────────────────────────
if __name__ == "__main__":
    tests = [
        (("abcabcbb",), 3),
        (("bbbbb",), 1),
        (("pwwkew",), 3),
    ]
    for args, expected in tests:
        got = Solution().lengthOfLongestSubstring(*args)
        print(f"{'OK  ' if got == expected else 'FAIL'} {args} → {got} (기대 {expected})")

