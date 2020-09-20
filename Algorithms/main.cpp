#include <cstdio>
#include <iostream>

#include "../MyLib/my_vector.h"

bool search_of_chain (unsigned int vertex, Vector<bool>& used, const Vector<Vector<unsigned int>>& bi_graph,
                      Vector<int>& matches);
Vector<int> KunhAlgorithm (const Vector<Vector<unsigned int>>& bi_graph, unsigned int l_size, unsigned int r_size);

void SquareMoreProfitable (FILE* f_in, FILE* f_out, int n, int m); 

void RectangleMoreProfitable (FILE* f_in, FILE* f_out, int n, int m); 

int main (int argc, char** argv)
{
    int n (0), m (0), a (0), b (0);

    FILE* f_in  = fopen ("dominoes.in",  "r");
    FILE* f_out = fopen ("dominoes.out", "w");

    fscanf (f_in, "%d%d%d%d\n", &n, &m, &a, &b);
    
    if (2 * b < a) {
        SquareMoreProfitable (f_in, f_out, n, m);
    } else {
        RectangleMoreProfitable (f_in, f_out, n, m);
    }

    return 0;
}

void RectangleMoreProfitable (FILE* f_in, FILE* f_out, int n, int m) {
    // char symbol = 0;
    // size_t quantity = 0;
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         fscanf (f_in, "%c", &symbol);
    //         if (symbol == '*') {
    //             quantity++;
    //         }
    //     }
    // }
    // fprintf (f_out, "%lu\n", quantity);

}



void SquareMoreProfitable (FILE* f_in, FILE* f_out, int n, int m) {
    char symbol = 0;
    size_t quantity = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fscanf (f_in, "%c", &symbol);
            if (symbol == '*') {
                quantity++;
            }
        }
    }
    fprintf (f_out, "%lu\n", quantity);
    
}


Vector<int> KunhAlgorithm (const Vector<Vector<unsigned int>>& bi_graph, unsigned int l_size, unsigned int r_size) {
    Vector<int> matches (r_size, -1);
    Vector<bool> used (l_size, false);

    for (int i = 0; i < l_size; ++i) {
        search_of_chain (i, used, bi_graph, matches);
        for (int k = 0; k < used.size (); ++k) used[k] = false;
    }

    return matches;
}

bool search_of_chain (unsigned int vertex, Vector<bool>& used, const Vector<Vector<unsigned int>>& bi_graph,
                      Vector<int>& matches) {

    if (used[vertex] == true) return false;
    used[vertex] = true;
    for (int i = 0; i < bi_graph[vertex].size (); ++i) {
        unsigned int cur_v = bi_graph[vertex][i];
        if (matches[cur_v] == -1 || search_of_chain (matches[cur_v],used, bi_graph, matches)) {
            matches[cur_v] = vertex;
            return true;
        }
    }
    return false;
}