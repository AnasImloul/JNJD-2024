#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define endl '\n'

#define square(x) ((x) * (x))
#define distance(x1, y1, x2, y2) (square(x1 - x2) + square(y1 - y2))

const ll MAX = 1 << 30;
const ll CHUNKS = 1 << 6;
const ll CHUNK_SIZE = MAX / CHUNKS;

const ll BOUNDS = 2;

map<pair<ll, ll>, string> mp;

struct record {
    ll dist;
    pair<ll, ll> pos;
};

inline record min(const record& a, const record& b) {
    return a.dist < b.dist || (a.dist == b.dist && mp[a.pos] < mp[b.pos]) ? a : b;
}

int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    vector<vector<vector<pair<int, int>>>> grid(CHUNKS, vector<vector<pair<int, int>>>(CHUNKS));
    vector<pair<ll, ll>> points;

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            string s; ll x, y;
            cin >> s >> x >> y;
            mp[{x, y}] = s;
            grid[x / CHUNK_SIZE][y / CHUNK_SIZE].emplace_back(x, y);
            points.emplace_back(x, y);
        } else {
            ll x, y; cin >> x >> y;
            record res = {LLONG_MAX, {LLONG_MAX, LLONG_MAX}};

            if (points.size() < 10000) {
                for (auto& p: points)
                    res = min(res, {distance(x, y, p.first, p.second), p});
            }

            ll chunk_x = x / CHUNK_SIZE, chunk_y = y / CHUNK_SIZE;
            for (int dx = -BOUNDS; dx <= BOUNDS; dx++) {
                for (int dy = -BOUNDS; dy <= BOUNDS; dy++) {
                    if (chunk_x + dx < 0 || chunk_x + dx >= CHUNKS) continue;
                    if (chunk_y + dy < 0 || chunk_y + dy >= CHUNKS) continue;
                    for (auto& p: grid[chunk_x + dx][chunk_y + dy]) {
                        res = min(res, {distance(x, y, p.first, p.second), p});
                    }
                }
            }

            cout << mp[res.pos] << endl;
        }
    }
}
