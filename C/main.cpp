#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SCC {
public:
    explicit SCC(vector<vector<int>>& graph) : graph(graph) {
        int n = (int)graph.size();
        disc.assign(n, -1);
        low.assign(n, -1);
        component.assign(n, -1);
        inStack.assign(n, false);

        int t = 0;
        for (int i = 1; i < n; i++) {
            scc(i, t);
        }
    }

    void scc(int i, int& t) {
        if (disc[i] != -1) return;

        disc[i] = low[i] = t++;
        inStack[i] = true;
        stack.push_back(i);

        for (int& j : graph[i]) {
            if (disc[j] == -1) {
                scc(j, t);
                low[i] = min(low[i], low[j]);
            } else if (inStack[j]) {
                low[i] = min(low[i], disc[j]);
            }
        }

        if (disc[i] != low[i]) return;

        component[i] = i;
        int current = -1;
        while (current != i) {
            current = stack.back();
            inStack[current] = false;
            component[current] = i;
            stack.pop_back();
        }
    }

    vector<vector<int>>& graph;
    vector<int> stack, disc, low, component;
    vector<bool> inStack;
};

class TopologicalSort {
public:
    explicit TopologicalSort(vector<vector<int>>& graph) : graph(graph) {
        int n = (int)graph.size();
        visited.assign(n, false);

        for (int i = 1; i < n; i++) {
            if (!visited[i]) dfs(i);
        }
    }

    void dfs(int u) {
        visited[u] = true;
        for (int& v : graph[u]) {
            if (!visited[v]) dfs(v);
        }
        order.push_back(u);
    }

    vector<vector<int>>& graph;
    vector<int> order;
    vector<bool> visited;
};

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m; cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
    }

    SCC scc(graph);
    vector<int>& component = scc.component;

    vector<int> cycle(n + 1, 0);

    vector<vector<int>> root_graph(n + 1);
    for (int i = 1; i <= n; i++) {
        cycle[component[i]]++;
        for (int& j : graph[i]) {
            if (component[i] == component[j]) continue;
            root_graph[component[i]].push_back(component[j]);
        }
    }

    TopologicalSort ts(root_graph);
    vector<int>& order = ts.order;

    vector<int> dp(n + 1, 0);
    for (int u : order) {
        if (component[u] != u) continue;
        dp[u] = cycle[u];
        for (int& v : root_graph[u]) {
            dp[u] = max(dp[u], dp[v] + cycle[u]);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}