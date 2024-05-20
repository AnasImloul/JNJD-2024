#include <vector>
#include <string>
#include <iostream>


using ll = long long;

using namespace std;

struct Trie {
    struct Node {
        Node* next[26] = {nullptr};
        ll count = 0, copies = 0;
    };

    Node* root;

    Trie() : root(new Node()) {}

    void insert(const string& s, ll count) const {
        Node* node = root;
        for (const char& c : s) {
            if (node->next[c - 'a'] == nullptr)
                node->next[c - 'a'] = new Node();
            node = node->next[c - 'a'];
            node->count += count;
        }
        node->copies += count;
    }

    ll solve(string& start, string& end) {
        string prefix;
        return helper(root, prefix, start, end);
    }

    ll helper(Node* node, string& prefix, string& start, string& end) {
        if (node == nullptr || !intersect(prefix, start, end)) return 0;

        if (contains(prefix, start, end)) {
            return node->count;
        }

        ll res = (start <= prefix && prefix <= end) ? node->copies : 0;
        for (ll letter = 0; letter < 26; letter++) {
            if (node->next[letter] != nullptr) {
                prefix.push_back(char('a' + letter));
                res += helper(node->next[letter], prefix, start, end);
                prefix.pop_back();
            }
        }
        return res;
    }

    inline static bool intersect(const string& prefix, const string& start, const string& end) {
        return (
                start.substr(0, min(start.size(), prefix.size())) <= prefix
                &&
                prefix <= end.substr(0, min(end.size(), prefix.size()))
        );
    }

    inline static bool contains(const string& prefix, const string& start, const string& end) {
        return (
                start.substr(0, min(start.size(), prefix.size())) < prefix
                &&
                prefix < end.substr(0, min(end.size(), prefix.size()))
        );
    }

};

int32_t main() {
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);

    Trie trie;

    ll q; cin >> q;

    while (q--) {
        ll type; cin >> type;
        if (type == 1) {
            string s; cin >> s;
            ll c; cin >> c;
            trie.insert(s, c);
        } else {
            string start, end; cin >> start >> end;
            cout << trie.solve(start, end) << endl;
        }
    }
}
