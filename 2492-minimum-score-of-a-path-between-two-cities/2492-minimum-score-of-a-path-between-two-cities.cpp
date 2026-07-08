class Solution {
public:
    void dfs(int node, vector<vector<pair<int,int>>>& graph, vector<bool>& visited) {
        visited[node] = true;
        
        for (auto& [nei, dist] : graph[node]) {
            if (!visited[nei]) {
                dfs(nei, graph, visited);
            }
        }
    }
    
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int,int>>> graph(n + 1);
        
        for (auto& r : roads) {
            int u = r[0], v = r[1], d = r[2];
            graph[u].push_back({v, d});
            graph[v].push_back({u, d});
        }
        
        vector<bool> visited(n + 1, false);
        
        // Step 1: find connected component of node 1
        dfs(1, graph, visited);
        
        // Step 2: find minimum edge in this component
        int ans = INT_MAX;
        
        for (auto& r : roads) {
            if (visited[r[0]]) {
                ans = min(ans, r[2]);
            }
        }
        
        return ans;
    }
};