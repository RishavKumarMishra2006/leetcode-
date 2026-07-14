class Solution {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {
        const int MAX = 200;

        // Precompute gcd
        int G[201][201];
        for (int i = 0; i <= MAX; i++) {
            for (int j = 0; j <= MAX; j++) {
                if (i == 0) G[i][j] = j;
                else if (j == 0) G[i][j] = i;
                else G[i][j] = std::gcd(i, j);
            }
        }

        vector<vector<int>> dp(MAX + 1, vector<int>(MAX + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp = dp;

            for (int g1 = 0; g1 <= MAX; g1++) {
                for (int g2 = 0; g2 <= MAX; g2++) {
                    if (dp[g1][g2] == 0) continue;

                    int cur = dp[g1][g2];

                    // Put x into seq1
                    int ng1 = G[g1][x];
                    ndp[ng1][g2] += cur;
                    if (ndp[ng1][g2] >= MOD) ndp[ng1][g2] -= MOD;

                    // Put x into seq2
                    int ng2 = G[g2][x];
                    ndp[g1][ng2] += cur;
                    if (ndp[g1][ng2] >= MOD) ndp[g1][ng2] -= MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAX; g++) {
            ans += dp[g][g];
        }

        return ans % MOD;
    }
};