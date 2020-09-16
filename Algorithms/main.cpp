#include <cstdio>
#include <iostream>

#include "../MyLib/my_vector.h"

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

Vector<int> KunhAlgorithm (const Vector<Vector<unsigned int>>& bi_graph, unsigned int l_size, unsigned int r_size) {
    Vector<int> matches (r_size, -1);
    Vector<bool> used (l_size, false);

    for (int i = 0; i < l_size; ++i) {
        search_of_chain (i, used, bi_graph, matches);
        for (int k = 0; k < used.size (); ++k) used[k] = false;
    }

    return matches;
}

int main (int argc, char** argv)
{
    unsigned int l_size = 0;
    unsigned int r_size = 0;
    scanf ("%u%u", &l_size, &r_size);

    Vector<Vector<unsigned int>> bi_graph;

    unsigned int temp_v = 0;
    for (int i = 0; i < l_size; ++i) {
        Vector <unsigned int> temp_vec;
        scanf ("%u", &temp_v);
        while (temp_v)
        {
            temp_vec.push_back (temp_v - 1);
            scanf ("%u", &temp_v);
        }
        bi_graph.push_back (temp_vec);
    }

    // for (int i = 0; i < bi_graph.size (); ++i) {
    //     for (int j = 0; j < bi_graph[i].size (); ++j) {
    //         printf ("%u ", bi_graph[i][j]);
    //     }
    //     printf ("\n");
    // }
    Vector<int> matches (KunhAlgorithm (bi_graph, l_size, r_size));
    unsigned int num_matches = 0;
    for (int i = 0; i < matches.size (); ++i) {
        if (matches[i] != -1) num_matches++;
    }
    printf ("%u\n", num_matches);
    for (int i = 0; i < matches.size (); ++i) {
        if (matches[i] != -1) printf ("%d %d\n", matches[i] + 1, i + 1);
    }


    return 0;
}