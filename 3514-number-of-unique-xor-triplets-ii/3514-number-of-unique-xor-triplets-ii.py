from typing import List

class Solution:
    def uniqueXorTriplets(self, nums: List[int]) -> int:
        MAX = 2048

        # pair[x] = whether x can be formed by nums[i] ^ nums[j], i <= j
        pair = [False] * MAX

        n = len(nums)
        for i in range(n):
            ai = nums[i]
            for j in range(i, n):
                pair[ai ^ nums[j]] = True

        ans = [False] * MAX

        for x in range(MAX):
            if pair[x]:
                for v in nums:
                    ans[x ^ v] = True

        return sum(ans)