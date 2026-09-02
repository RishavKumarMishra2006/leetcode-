class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;

        vector<pair<int, int>> litter;
        
        // Find S and all L cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        // No litter to collect
        if (k == 0) return 0;

        // Map each litter position to its bit
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            litterId[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;

        // best[r][c][mask] = maximum energy with which
        // we have reached (r,c) having collected mask.
        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(1 << k, -1))
        );

        // {row, col, mask, remainingEnergy, moves}
        queue<array<int, 5>> q;

        best[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c, mask, currEnergy, moves] = q.front();
            q.pop();

            // All litter collected
            if (mask == fullMask) {
                return moves;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                // Outside grid
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                // Obstacle
                if (classroom[nr][nc] == 'X')
                    continue;

                // If we have no energy, we cannot move
                if (currEnergy == 0)
                    continue;

                int newEnergy = currEnergy - 1;
                int newMask = mask;

                // Collect litter
                if (litterId[nr][nc] != -1) {
                    newMask |= (1 << litterId[nr][nc]);
                }

                // Reset energy on R
                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                // If we've already reached this state
                // with at least as much energy, skip it.
                if (best[nr][nc][newMask] >= newEnergy)
                    continue;

                best[nr][nc][newMask] = newEnergy;

                q.push({
                    nr,
                    nc,
                    newMask,
                    newEnergy,
                    moves + 1
                });
            }
        }

        return -1;
    }
};