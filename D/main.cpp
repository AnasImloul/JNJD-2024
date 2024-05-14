#include "iostream"

using namespace std;
const int MOD = 37;
const int PERIOD = 76; // Pisano period of 37 (you need to calculate it)

int fib[PERIOD];

void build() {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < PERIOD; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
}

int string_mod(string& s, int mod) {
    int res = 0, p = 1;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        res = (res + (s[i] - '0') * p) % mod;
        p = (p * 10) % mod;
    }
    return res;
}

int main() {
    build();
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = string_mod(s, PERIOD);
        cout << fib[n] << endl;
    }
    return 0;
}