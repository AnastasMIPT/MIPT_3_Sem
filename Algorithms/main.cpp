//#include "bits/stdc++.h"
#include <stdio.h>
#include <vector>
#include <map>

using std::vector;
const int INF = 1e9 + 7;

struct AutomatonNode {
    int link = -1;
    int len = 0;
    std::map<char, int> go;
    int first = INF;
    int last = 0;
    AutomatonNode () = default;
    AutomatonNode (AutomatonNode const& n) : link (n.link), len(n.len), go(n.go), first(n.first), last(0) {}
    AutomatonNode (int _len) : link(-1), len(_len), go(), first(_len), last (0) {}
};



vector<AutomatonNode> automaton;
vector<bool> used;
vector<vector<int>> graph;

int dfs (int v) {
    automaton[v].last = automaton[v].first;
    for (int to : graph[v]) {
        if (!used[to]) {
            dfs (to);
            automaton[v].last = std::max (automaton[v].last, automaton[to].last);
        }
    }
    return 0;
}

const int MaxStrLen = 1e6 + 5;

int main() {
    
    char buf[MaxStrLen];
    scanf("%s", buf);

    automaton.push_back (AutomatonNode());

    int last = 0;
    for (int i = 0; buf[i]; ++i) {
        automaton.push_back (AutomatonNode (automaton[last].len + 1));
        int cur = automaton.size () - 1;
        char symb = buf[i];
        while (last != -1) {
            if (automaton[last].go.count (symb)) {
                break;
            }
            automaton[last].go[symb] = cur;
            last = automaton[last].link;
        }
        if (last != -1) {
            int to = automaton[last].go[symb];
            if (automaton[to].len == automaton[last].len + 1) {
                automaton[cur].link = to;
            } else {
                automaton.push_back(automaton[to]);
                int added = automaton.size () - 1;
                automaton[to].link = added;
                automaton[added].len = automaton[last].len + 1;
                automaton[cur].link = added;
                while (last != -1 && automaton[last].go[symb] == to) {
                    automaton[last].go[symb] = added;
                    last = automaton[last].link;
                }
            }
        } else {
            automaton[cur].link = 0;
        }
        last = cur;
    }

    graph.resize (automaton.size ());
    used.resize  (automaton.size ());
    for (int i = 1; i < automaton.size (); ++i) {
        graph[automaton[i].link].push_back (i);
    }

    dfs (0);

    long long ans = 0;

    for (int i = 0; i < automaton.size (); ++i) {
        if (automaton[i].last <= automaton[i].first) {
            ans = std::max(ans, static_cast<long long> (automaton[i].len));
        } else {
            ans = std::max(ans, static_cast <long long> (automaton[i].len * automaton[i].len)
                                + (automaton[i].last - automaton[i].first + automaton[i].len));
        }
    }

    printf ("%lld\n", ans);

    return 0;
}