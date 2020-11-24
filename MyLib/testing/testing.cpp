#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
const int k = 26;
 
struct TrieNode {
    TrieNode* to[k];
    TrieNode* go[k];
    TrieNode* par;
    int par_ch;
    TrieNode* up_link = nullptr;
    TrieNode* suff_link = nullptr;
    vector<int> dict_str_idx;
    bool terminal = false;
 
    TrieNode(int par_ch, TrieNode* par) : par_ch(par_ch), par(par) {
        for (auto& el : to) el = nullptr;
        for (auto& el : go) el = nullptr;
    }
};
 
TrieNode* root = nullptr;
 
void add(string str, size_t str_idx) {
    TrieNode* cur = root;
    for (char c : str) {
        c -= 'a';
        if (!cur->to[c]) {
            cur->to[c] = new TrieNode(c, cur);
        }
        cur = cur->to[c];
    }
    cur->terminal = true;
    cur->dict_str_idx.push_back(str_idx);
}
 
TrieNode* suff_link(TrieNode* v);
 
TrieNode* go(TrieNode* from, char c) { // c --> char-'a' !!
    if (from->go[c]) return from->go[c];
 
    if (from->to[c])
        from->go[c] = from->to[c];
    else if (from == root)
        from->go[c] = root;
    else
        from->go[c] = go(suff_link(from), c);
    return from->go[c];
}
 
TrieNode* suff_link(TrieNode* v) {
    if (v->suff_link) return v->suff_link;
    if (v == root || v->par == root)
        v->suff_link = root;
    else
        v->suff_link = go(suff_link(v->par), v->par_ch);
    return v->suff_link;
}
 
TrieNode* up_link(TrieNode* v) {
    if (v->up_link) return v->up_link;
    if (suff_link(v)->terminal)
        v->up_link = suff_link(v);
    else if (suff_link(v) == root)
        v->up_link = root;
    else
        v->up_link = up_link(suff_link(v));
    return v->up_link;
}
 
void show(const vector<vector<int>>& v) {
    for (auto a : v) {
        cout << a.size() << " ";
        for (auto b : a) {
            cout << b << " ";
        }
        cout << "\n";
    }
}
 
int main() {
    string text;
    cin >> text;
    int n;
    scanf ("%d", &n);
    vector<string> dict(n);
    vector<vector<int>> occurs(n, vector<int>());
    root = new TrieNode(-1, nullptr);
    TrieNode* cur = root;
    for (int i = 0; i < n; ++i) {
        cin >> dict[i];
        add(dict[i], i);
    }
 
    for (int i = 0; i < text.length(); ++i) {
        char el = text[i] - 'a';
        cur = go(cur, el);
        TrieNode* cur_up = up_link(cur);
        while (cur_up != root) {
            for (auto idx : cur_up->dict_str_idx) {
                int start_idx = i + 2 - dict[idx].length();
                occurs[idx].push_back(start_idx);
            }
            cur_up = up_link(cur_up);
        }
        if (cur->terminal) {
            for (auto idx : cur->dict_str_idx) {
                int start_idx = i + 2 - dict[idx].length();
                occurs[idx].push_back(start_idx);
            }
 
        }
 
    }
 
    show(occurs);
 
    return 0;
}