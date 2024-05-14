#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int res = INT_MAX;
int n, m;

// recursive function to split bipartite graph (state[i] -> {0 || 1})
bool bipartite(int u, int color, vector<vector<int>>& graph, vector<int>& state) {
    state[u] = color;
    for (int v : graph[u]) {
        if (state[v] == -1) {
            if (!bipartite(v, 1 - color, graph, state)) {
                return false;
            }
        } else if (state[v] == state[u]) {
            return false;
        }
    }
    return true;
}

// recursive function to determine how many people in each of the two bipartite groups for each connected component
pair<int, int> group(int u, vector<vector<int>>& graph, vector<int>& state, vector<bool>& visited) {
    pair<int, int> res = {0, 0};
    if (state[u] == 0) res.first++;
    else res.second++;
    visited[u] = true;
    for (int v : graph[u]) {
        if (visited[v]) continue;
        auto [x, y] = group(v, graph, state, visited);
        res.first += x;
        res.second += y;
    }
    return res;
}


void solve(int i, vector<pair<int, int>>& groups, int a, vector<vector<bool>>& used) {
    if (i == groups.size()) {
        res = min(res, abs(n - 2 * a)); // update answer when all groups are visited
        return;
    }

    if (used[i][a]) return; // don't repeat work
    used[i][a] = true; // mark as visited

    solve(i + 1, groups, a + groups[i].first, used); // add to first group
    solve(i + 1, groups, a + groups[i].second, used); // add to second group
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> state(n, -1);
    for (int i = 0; i < n; i++) {
        if (state[i] != -1) continue;
        if (!bipartite(i, 0, graph, state)) {
            cout << -1 << endl; // not bipartite
            return 0;
        }
    }

    vector<bool> visited(n, false);
    vector<pair<int, int>> groups;
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue; // skip visited nodes as they are already part of a group
        groups.push_back(group(i, graph, state, visited)); // get number of people in each group for each connected component
    }

    vector<vector<bool>> used(groups.size(), vector<bool>(n + 1, false));
    solve(0, groups, 0, used);
    cout << res << endl;
}
