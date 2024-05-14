#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#define endl '\n'

#define square(x) ((x) * (x))
#define distance(x1, y1, x2, y2) (square(x1 - x2) + square(y1 - y2))

using ll = long long;

using namespace std;

map<pair<ll, ll>, string> mp;
set<pair<ll, ll>> points;

struct record {
    ll dist;
    pair<ll, ll> pos;
};

const record& min(const record& a, const record& b) {
    return a.dist < b.dist || (a.dist == b.dist && mp[a.pos] < mp[b.pos]) ? a : b;
}

int main() {

    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            string s; ll x, y;
            cin >> s >> x >> y;
            points.insert({x, y});
            mp[{x, y}] = s;
        } else {
            ll x, y; cin >> x >> y;
            auto it = points.lower_bound(make_pair(x, y));
            if (it == points.end())
                it--;

            // closest point to the left
            record left = {LLONG_MAX, {LLONG_MAX, LLONG_MAX}};
            for (auto it1 = it; square(it1->first - x) <= left.dist; it1--) {
                auto& [x1, y1] = *it1;
                left = min(left, {distance(x, y, x1, y1), *it1});
                if (it1 == points.begin()) break;
            }

            // closest point to the right
            record right = {LLONG_MAX, {LLONG_MAX, LLONG_MAX}};
            for (auto it1 = it; it1 != points.end() && square(it1->first - x) <= right.dist; it1++) {
                auto& [x1, y1] = *it1;
                right = min(right, {distance(x, y, x1, y1), *it1});
            }

            // closest point
            record res = min(left, right);
            cout << mp[res.pos] << endl;
        }
    }
}
