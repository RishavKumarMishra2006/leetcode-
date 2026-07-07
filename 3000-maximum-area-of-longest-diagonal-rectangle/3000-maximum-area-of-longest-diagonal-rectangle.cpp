class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        long long bestDiag = -1;
        int bestArea = 0;

        for (auto &d : dimensions) {
            long long a = d[0], b = d[1];
            long long diag = a * a + b * b;   // compare squared diagonal
            int area = (int)(a * b);

            if (diag > bestDiag || (diag == bestDiag && area > bestArea)) {
                bestDiag = diag;
                bestArea = area;
            }
        }
        return bestArea;
    }
};
