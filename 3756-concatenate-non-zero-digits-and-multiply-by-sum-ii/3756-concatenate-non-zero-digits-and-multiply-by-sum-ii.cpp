class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int MOD = 1000000007;

        int n = s.size();

        vector<int> pos, val;

        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';
            if (d != 0) {
                pos.push_back(i);
                val.push_back(d);
            }
        }

        int m = val.size();

        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> prefNum(m + 1, 0);
        for (int i = 1; i <= m; i++)
            prefNum[i] = (prefNum[i - 1] * 10 + val[i - 1]) % MOD;

        vector<int> prefSum(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefSum[i + 1] = prefSum[i] + (s[i] - '0');

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int L = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int R = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;

            if (L > R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;

            long long x = (prefNum[R + 1] -
                           prefNum[L] * pow10[len] % MOD + MOD) % MOD;

            long long digitSum = prefSum[r + 1] - prefSum[l];

            ans.push_back((x * digitSum) % MOD);
        }

        return ans;
    }
};