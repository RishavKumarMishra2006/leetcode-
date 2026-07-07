class Solution {
public:
    int numOfWays(int n) {
        const long long MOD = 1000000007LL;

        long long A = 6; // patterns like ABA
        long long B = 6; // patterns like ABC

        for (int i = 2; i <= n; i++) {
            long long newA = (3 * A + 2 * B) % MOD;
            long long newB = (2 * A + 2 * B) % MOD;
            A = newA;
            B = newB;
        }

        return (int)((A + B) % MOD);
    }
};
