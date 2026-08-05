class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj, vector<int>& suspicious) {
        suspicious[node] = 1;

        for (int nbr : adj[node]) {
            if (!suspicious[nbr])
                dfs(nbr, adj, suspicious);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        vector<vector<int>> adj(n);

        for (auto &edge : invocations)
            adj[edge[0]].push_back(edge[1]);

        vector<int> suspicious(n, 0);
        dfs(k, adj, suspicious);

        for (auto &edge : invocations) {
            if (!suspicious[edge[0]] && suspicious[edge[1]]) {
                vector<int> ans(n);
                iota(ans.begin(), ans.end(), 0);
                return ans;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (!suspicious[i])
                ans.push_back(i);

        return ans;
    }
};