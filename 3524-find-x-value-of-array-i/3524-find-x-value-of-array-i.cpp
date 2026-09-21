class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);

            // Start a new subarray with nums[i]
            ndp[num % k]++;

            // Extend all subarrays ending at previous position
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int nr = (r * (num % k)) % k;
                    ndp[nr] += dp[r];
                }
            }

            dp = ndp;

            // Every subarray ending here contributes to its remainder
            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};