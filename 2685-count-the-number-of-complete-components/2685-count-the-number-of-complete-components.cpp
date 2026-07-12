class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited,
             int& nodes, int& edges) {
        
        visited[node] = true;
        nodes++;
        edges += graph[node].size(); // count degrees
        
        for (int nei : graph[node]) {
            if (!visited[nei]) {
                dfs(nei, graph, visited, nodes, edges);
            }
        }
    }
    
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        
        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        
        vector<bool> visited(n, false);
        int complete = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int nodes = 0;
                int edgeCount = 0;
                
                dfs(i, graph, visited, nodes, edgeCount);
                
                edgeCount /= 2; // each edge counted twice
                
                if (edgeCount == nodes * (nodes - 1) / 2) {
                    complete++;
                }
            }
        }
        
        return complete;
    }
};