#include <iostream>
#include <vector>

using namespace std;

int solve(vector<string>& logs) {
    int errors = 0, res = 0;
    for (const string& log: logs) {
        if (log == "ERROR") errors++;
        else if (log == "RESOLVED") {
            if (errors > 0) {
                errors--;
                res++;
            }
        }
    }
    return res;
}

int main() {
    int t; cin >> t;

    vector<string> logs;
    for (int i = 0; i < t; i++) {
        string s; cin >> s;
        logs.push_back(s);
    }

    cout << solve(logs) << endl;
    return 0;
}