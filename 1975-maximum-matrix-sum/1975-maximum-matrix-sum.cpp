class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long sumAbs = 0;
        long long minAbs = LLONG_MAX;
        int negCount = 0;

        for (auto &row : matrix) {
            for (int x : row) {
                if (x < 0) negCount++;
                long long ax = llabs((long long)x);
                sumAbs += ax;
                minAbs = min(minAbs, ax);
            }
        }

        if (negCount % 2 == 0) return sumAbs;
        return sumAbs - 2 * minAbs;
    }
};
