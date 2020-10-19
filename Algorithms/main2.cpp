#include<iostream>
#include<vector>
#include<queue>
struct Edge {
    int from;
    int to;
    long long cap;
    long long flow;
};

int N = 0, M = 0;
const long long INF = 1e10;

using std::vector;
using std::queue;

vector<char> chars;
vector<Edge> edges;
vector<vector<int>> graph;
vector<int> ptr;
vector<int> d;

int edge_counter = 0;
int s = 0, t = 0;

void add_edge (int from, int to, long long cap) {
    graph[from].push_back (edge_counter);
    graph[to].push_back (edge_counter + 1);
    edges[edge_counter++] = {from, to, cap, 0};
    edges[edge_counter++] = {to, from, 0, 0};
}


bool bfs_dinic () {
    queue<int> que;
    d.assign (N * M * 2 + 3, -1);

    d[s] = 0;
    que.push (s);
    while  (!que.empty ()) {
        int v = que.front ();
        que.pop ();
    
        for  (int i: graph[v]) {
            int to = edges[i].to;
            long long cap = edges[i].cap - edges[i].flow;
            if  (d[to] == -1 && cap > 0) {
                d[to] = d[v] + 1;
                que.push (to);
            }
        }
    }
    return d[t] != -1;
}

long long dfs_dinic (int v, long long flow) {
    if  (v == t) return flow;
    while  (ptr[v] < graph[v].size ()) {
        int e = graph[v][ptr[v]];

        if  (edges[e].cap > edges[e].flow && d[edges[e].to] == d[v] + 1) {
            long long cur_flow = dfs_dinic (edges[e].to, std::min (flow, edges[e].cap - edges[e].flow));
            if  (cur_flow > 0) {
                edges[e].flow += cur_flow;
                edges[e^1].flow -= cur_flow;
                return cur_flow;
            }
        }
        ++ptr[v];
    }
    return 0;
}

long long dinic () {
    long long flow = 0;
    while  (bfs_dinic ()) {
        ptr.assign (2 * N * M + 3, 0);
        while  (long long cur_flow = dfs_dinic (s, INF))
            flow += cur_flow;
    }
    return flow;
}


void calculate () {
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};

    long long source_sum = 0;
    for  (int i = 0; i < N; ++i)
        for  (int j = 0; j < M; ++j) {
            if  (chars[i * M + j] == '.')
                continue;
            
            add_edge (s, i * M + j, chars[i * M + j]);
            add_edge (N * M + i * M + j, t, chars[i * M + j]);
            source_sum += chars[i * M + j];



            for  (int k = 0; k < 4; ++k) {
                if  (i+dx[k] < N && j+dy[k] < M && i + dx[k] >= 0 && j+dy[k] >= 0 && chars[ (i + dx[k]) * M + j + dy[k]] != '.') 
                    add_edge (i * M + j, N * M +  ( (i + dx[k]) * M + j + dy[k]), 1);
            }
        }
    if (dinic () == source_sum && source_sum != 0) {
        printf ("Valid\n");
    } else {
        printf ("Invalid\n");
    }
}


void read_data () {
    char cur_char = 0;
    chars.resize (N * M);
    for  (int i = 0; i < N; ++i)
        for  (int j = 0; j < M; ++j) {
            std::cin >> cur_char;
            switch (cur_char) {
                case 'H': chars[i * M + j] = 1;
                    break;
                case 'O': chars[i * M + j] = 2;
                    break;
                case 'N': chars[i * M + j] = 3;
                    break;
                case 'C': chars[i * M + j] = 4;
                    break;
                case '.': chars[i * M + j] = '.';
                    break;
                
            }
        }
}

int main () {

    scanf ("%d%d", &N, &M);
    s = 2 * N * M + 1;
    t = 2 * N * M + 2;

    graph.resize (N * M * 2 + 3);
    edges.resize (N * M * 12);
    
    read_data ();
    calculate ();
}