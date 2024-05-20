#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

const int MAX = 1 << 16;

using namespace std;

using ll = long long;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = (ll)round(fa[i].real());
    }

    return result;
}

vector<ll> build(vector<ll>& nums) {
    vector<ll> a(MAX), // count of each number i -> i
               b(MAX << 1); // count of each duplicate pair i -> 2 * i

    for (ll num: nums) // populate the count of each number i
        a[num] += 1, b[2 * num] += 1;

    // generate all possible pairs (i, j)
    vector<ll> res = multiply(a, a);
    for (ll i: nums) // remove the repeated duplicates (i, i) -> 2 * i
        res[2 * i] -= 1;

    // generate all possible triples (i, j, k) where i != j
    res = multiply(res, a);

    // generate all possible triples (i, j, j)
    vector<ll> repeat = multiply(a, b);
    for (ll i: nums) // don't count the case where i = j (i, i, i) -> 3 * i
        repeat[3 * i] -= 1;

    // remove the repeated duplicates (i, i, j) & (j, j, i)
    for (int i = 0; i < repeat.size(); i++)
        res[i] -= 2 * repeat[i];

    return res;
}


int main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    ll n, m; cin >> n >> m;

    vector<ll> a(n), b(m);
    for (ll& ai : a) cin >> ai;
    for (ll& bi : b) cin >> bi;

    vector<ll> count_a = build(a), count_b = build(b);
    count_b.resize(count_a.size(), 0);

    ll total_a = n * (n - 1) * (n - 2) , total_b = m * (m - 1) * (m - 2);

    ll less_than = 0;
    double ans = 0;
    for (int i = 0; i <= 3 * MAX; i++) {
        ans += (double) count_a[i] * (double) less_than / ((double) total_a * (double) total_b);
        less_than += count_b[i];
    }

    cout << fixed << setprecision(6) << ans << endl;
}