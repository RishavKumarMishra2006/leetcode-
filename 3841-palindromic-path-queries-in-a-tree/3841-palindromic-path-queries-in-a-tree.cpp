class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 2, 0) {}

        void add(int idx, int val) {
            for (; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        }

        void rangeXor(int l, int r, int val) {
            add(l, val);
            add(r + 1, val);
        }

        int query(int idx) {
            int res = 0;
            for (; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n, 0), tin(n), tout(n);
        vector<int> basePref(n, 0), parent(n, 0);

        int timer = 0;

        // Iterative DFS: avoids stack overflow on a chain-shaped tree.
        stack<tuple<int, int, bool>> st;
        st.push({0, 0, false});

        while (!st.empty()) {
            auto [u, p, exiting] = st.top();
            st.pop();

            if (exiting) {
                tout[u] = timer - 1;
                continue;
            }

            parent[u] = p;
            up[0][u] = p;
            tin[u] = timer++;

            int own = 1 << (s[u] - 'a');
            basePref[u] = (u == 0)
                            ? own
                            : basePref[p] ^ own;

            st.push({u, p, true});

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                st.push({v, u, false});
            }
        }

        // Binary lifting table for LCA.
        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j))
                    u = up[j][u];
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        Fenwick fw(n + 1);
        vector<bool> answer;

        auto getPrefix = [&](int u) {
            return basePref[u] ^ fw.query(tin[u] + 1);
        };

        for (const string& q : queries) {
            string type;
            int u;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');
                int delta = oldMask ^ newMask;

                if (delta != 0) {
                    fw.rangeXor(
                        tin[u] + 1,
                        tout[u] + 1,
                        delta
                    );
                    s[u] = c;
                }
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int mask = getPrefix(u)
                         ^ getPrefix(v)
                         ^ (1 << (s[w] - 'a'));

                // At most one character may have odd frequency.
                answer.push_back((mask & (mask - 1)) == 0);
            }
        }

        return answer;
    }
};