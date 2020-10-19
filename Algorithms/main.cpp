#include <cstdio>
#include <iostream>

#include <vector>
#include <memory>   
#include <queue>

using std::vector;

const int MaxCap = 300;
const int MaxDist = 2000000000;

struct edge 
{
    int form;
    int to;
    int cap;
    int flow;
};


int MaxFlow (vector<vector<int>>& f, vector<vector<int>>& cap, vector<int>& ptr, vector<int>& d, int n, int s, int t);

int Dinica (int n, int s, int t, vector<vector<int>>& f, vector<vector<int>>& cap) {
    vector<int> d (n);
    vector<int> ptr (n);

    return MaxFlow (f, cap, ptr, d, n, s, t);
}



bool bfs (vector<int>& d, vector<vector<int>>& f, vector<vector<int>>& cap, int s, int t, int n) {
    d.assign (d.size (), MaxDist);
  
    d[s] = 0;
    std::queue <int> Q;
    Q.push (s);
    while (!Q.empty ())
    {
        int u = Q.front ();
        Q.pop ();
        //printf ("u = %d\n", u);
        
        for (int v = 0; v < n; ++v) {
            if (cap[u][v] != 0) {
                //printf ("v = %d ", v);
                if ((f[u][v] < cap[u][v]) && (d[v] == MaxDist)) {
                    d[v] = d[u] + 1;
                    Q.push (v);
                }
            }
        }

    }

    //printf ("Hello\n");
    
    return d[t] != MaxDist;
}

int dfs (int u, int min_cap, int t, int n, vector<int>& ptr, 
        vector<int>& d, vector<vector<int>>& f, vector<vector<int>>& cap, vector<int>& dfs_path) {
    if (0 != min_cap) printf ("u = %d. cap = %d\n", u + 1, min_cap);
    
    if (u == t || 0 == min_cap) {
        if (u == t) printf ("\n*** min_cap = %d\n", min_cap);
        return min_cap;
    }
    
    for (int v = ptr[u]; v < n; ++v) {
        if (d[v] == d[u] + 1) {
            //if (v == 4) printf ("?? u = %d\n", u + 1);
            int delta = dfs (v, std::min (min_cap, cap[u][v] - f[u][v]), t, n, ptr, d, f, cap, dfs_path);
        
            if (delta) {
                f[u][v] += delta;
                f[v][u] -= delta;
                return delta;
            }
        }
        ptr[u]++;
    }
    return 0;
}

int MaxFlow (vector<vector<int>>& f, vector<vector<int>>& cap, vector<int>& ptr, vector<int>& d, int n, int s, int t) {
    int max_flow = 0;
    while (bfs (d, f, cap, s, t, n)) {
        ptr.assign (n, 0);
        vector <int> dfs_path;

        int flow = dfs (s, MaxCap, t, n, ptr, d, f, cap, dfs_path);
        
        while (flow)
        {
            max_flow += flow;
            flow = dfs (s, MaxCap, t, n, ptr, d, f, cap, dfs_path);
        }
        for (auto el : dfs_path) {
            printf ("%d ", el);
        }
        printf ("\n");
    }
    return max_flow;
}



int main ()
{
    int n (0), m (0), a (0), b (0), c (0);

    FILE* f_in = fopen ("dominoes.in", "r");
    fscanf (f_in, "%d%d", &n, &m);

    vector<vector<int>> f (n, vector<int> (n, 0));
    vector<vector<int>> cap (n, vector<int> (n, 0));
    

    for (int i = 0; i < m; ++i) {
        //printf ("i = %d\n", i);
        fscanf (f_in, "%d%d%d", &a, &b, &c);
        cap[a - 1][b - 1] = c;
    }

   
    int max_flow = Dinica (n, 0, n - 1, f, cap);
    printf ("%d\n", max_flow);
    return 0;
}

/*
7 9
1 2 3
1 3 5
2 5 2
3 5 2
3 6 2
3 4 1
4 6 1
5 7 4
6 7 4
*/