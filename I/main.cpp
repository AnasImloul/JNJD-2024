#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<pair<ll, ll>> intervals;
ll trees, m;

bool isPossible(ll trees, ll d) {
    ll count = 0, current = intervals[0].first, index = 0;
    while (count < trees && index < m) {
        count++;
        current += d;
        while (index + 1 < m && current > intervals[index].second) {
            current = max(current, intervals[++index].first);
        }
        if (index == m - 1 && current > intervals[index].second) break;
    }
    return count == trees;
}

ll binary_search(ll trees) {
    ll low = 0, high = LLONG_MAX, ans, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (isPossible(trees, mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}


int main () {
    cin >> trees >> m;
    for (ll i = 0; i < m; i++) {
        ll a, b; cin >> a >> b;
        intervals.emplace_back(a, b);
    }
    sort(intervals.begin(), intervals.end());
    cout << binary_search(trees) << endl;
}