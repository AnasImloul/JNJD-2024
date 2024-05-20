#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;
using ll = long long;

vector<pair<ll, ll>> intervals;
ll trees, m;

bool isPossible(ll d) {
    ll count = 0, current = 0;
    for (auto [a, b]: intervals) {
        if (current < a) current = a;
        while (current <= b) {
            if (++count >= trees) return true;
            current += d;
        }
    }
    return false;
}


int main () {
    cin >> trees >> m;
    for (ll i = 0; i < m; i++) {
        ll a, b; cin >> a >> b;
        intervals.emplace_back(a, b);
    }

    sort(intervals.begin(), intervals.end());

    ll low = 0, high = LLONG_MAX, ans, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (isPossible(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }
    cout << ans << endl;
}