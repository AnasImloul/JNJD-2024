#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>

using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;

vector<vector<int>> graph(MAXN);
vector<int> group(MAXN), visited(MAXN), score(MAXN);

void dfs(int i, int g) {
    if (visited[i]) return;
    visited[i] = true;
    group[i] = g;
    for (int& j : graph[i]) {
        dfs(j, g);
    }
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> score[i];
        score[i] = score[i] % 2;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (score[a] != score[b]) continue;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i, i);
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        cout << (group[a] == group[b] ? "YES" : "NO") << endl;
    }
}
