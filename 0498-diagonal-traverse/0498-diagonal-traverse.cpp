class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> ans;
        ans.reserve(m * n);

        int r = 0, c = 0;
        bool up = true;

        for (int k = 0; k < m * n; k++) {
            ans.push_back(mat[r][c]);

            if (up) {
                // moving up-right
                if (c == n - 1) {        // hit right border
                    r++;
                    up = false;
                } else if (r == 0) {     // hit top border
                    c++;
                    up = false;
                } else {
                    r--;
                    c++;
                }
            } else {
                // moving down-left
                if (r == m - 1) {        // hit bottom border
                    c++;
                    up = true;
                } else if (c == 0) {     // hit left border
                    r++;
                    up = true;
                } else {
                    r++;
                    c--;
                }
            }
        }
        return ans;
    }
};

