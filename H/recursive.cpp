#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> state;
vector<bool> visited;
vector<pair<int, int>> groups;
vector<vector<bool>> used;

int ans = INT_MAX;
int n, m;

// recursive function to split bipartite graph (state[i] -> {0 || 1})
bool bipartite(int u, int color) {
    state[u] = color;
    for (int v : graph[u]) {
        if (state[v] == -1) {
            if (!bipartite(v, 1 - color)) {
                return false;
            }
        } else if (state[v] == state[u]) {
            return false;
        }
    }
    return true;
}

// recursive function to determine how many people in each of the two bipartite groups for each connected component
pair<int, int> group(int u) {
    pair<int, int> res = {0, 0};
    if (state[u] == 0) res.first++;
    else res.second++;
    visited[u] = true;
    for (int v : graph[u]) {
        if (visited[v]) continue;
        auto [x, y] = group(v);
        res.first += x, res.second += y;
    }
    return res;
}


void solve(int i, int a) {
    if (i == groups.size()) {
        ans = min(ans, abs(n - 2 * a)); // update answer when all groups are visited
        return;
    }

    if (used[i][a]) return; // don't repeat work
    used[i][a] = true; // mark as visited

    solve(i + 1, a + groups[i].first); // add to first group
    solve(i + 1, a + groups[i].second); // add to second group
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    state.assign(n, -1);
    for (int i = 0; i < n; i++) {
        if (state[i] != -1) continue;
        if (!bipartite(i, 0)) {
            cout << -1 << endl; // not bipartite
            return 0;
        }
    }

    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue; // skip visited nodes as they are already part of a group
        groups.push_back(group(i)); // get number of people in each group for each connected component
    }

    used.assign(groups.size(), vector<bool>(n, false));
    solve(0, 0);
    cout << ans << endl;
}
