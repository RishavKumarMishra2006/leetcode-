class Solution {
public:
    unordered_map<int, int> dp;

    int solve(int n) {
        if (n == 0)
            return 0;

        // If n is a power of 2
        if ((n & (n - 1)) == 0)
            return 1;

        if (dp.count(n))
            return dp[n];

        int lowbit = n & (-n);

        return dp[n] = 1 + min(solve(n - lowbit),
                               solve(n + lowbit));
    }

    int minOperations(int n) {
        return solve(n);
    }
};