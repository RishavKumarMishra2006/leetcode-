class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> rows;

        // Store reserved seats as a bitmask for each affected row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Only seats 2-9 matter
            if (col >= 2 && col <= 9) {
                rows[row] |= (1 << col);
            }
        }

        // Initially every row can hold 2 groups
        long long ans = 2LL * n;

        for (auto &[row, mask] : rows) {
            // We already counted 2 groups for this row.
            // Recalculate its actual maximum.

            bool left  = !(mask & (1 << 2)) &&
                         !(mask & (1 << 3)) &&
                         !(mask & (1 << 4)) &&
                         !(mask & (1 << 5));

            bool middle = !(mask & (1 << 4)) &&
                          !(mask & (1 << 5)) &&
                          !(mask & (1 << 6)) &&
                          !(mask & (1 << 7));

            bool right = !(mask & (1 << 6)) &&
                         !(mask & (1 << 7)) &&
                         !(mask & (1 << 8)) &&
                         !(mask & (1 << 9));

            int groups;

            if (left && right)
                groups = 2;
            else if (left || middle || right)
                groups = 1;
            else
                groups = 0;

            // Replace the assumed 2 groups with actual value
            ans -= 2;
            ans += groups;
        }

        return ans;
    }
};