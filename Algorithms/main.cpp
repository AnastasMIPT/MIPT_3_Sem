#include <cstdio>
#include <iostream>

#include <vector>

using std::vector;


bool search_of_chain (unsigned int vertex, vector<bool>& used, const vector<vector<unsigned int>>& bi_graph,
                      vector<int>& matches);
vector<int> KunhAlgorithm (const vector<vector<unsigned int>>& bi_graph, unsigned int l_size, unsigned int r_size);

size_t SquareMoreProfitable (FILE* f_in, FILE* f_out, int n, int m, int a, int b); 

size_t RectangleMoreProfitable (FILE* f_in, FILE* f_out, int n, int m, int a, int b); 

int main ()
{
    int n (0), m (0), a (0), b (0);

    FILE* f_in  = fopen ("dominoes.in",  "r");
    FILE* f_out = fopen ("dominoes.out", "w");

    fscanf (f_in, "%d%d%d%d\n", &n, &m, &a, &b);
    
    size_t quantity = 0;
    quantity = RectangleMoreProfitable (f_in, f_out, n, m, a, b);

    fprintf (f_out, "%lu", quantity);

    return 0;
}

size_t RectangleMoreProfitable (FILE* f_in, FILE* f_out, int n, int m, int a, int b) {
    vector <vector <unsigned int>> bi_graph;

    char** table = reinterpret_cast<char**> (calloc (n, sizeof(char*)));
    for (int i = 0; i < n; ++i) {
        char* temp = reinterpret_cast<char*> (calloc (m, sizeof (char)));
        fscanf (f_in, "%s", temp);
        table[i] = temp;
    }

    unsigned int num_free = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] == '*') num_free++;
        }
    }
    
    if (2 * b <= a) return num_free * b;

    int black_number = -1;
    int white_number = -1;
    bool is_black = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] != '.') {
                is_black = (((i + j) % 2 == 0)? (black_number++, true ): (white_number++, false));
                if (!is_black) continue;
                
                vector <unsigned int> temp_vec;
                
                if (j != 0     && table[i][j - 1] != '.')   temp_vec.push_back (white_number);              //left
                if (j != m - 1 && table[i][j + 1] != '.')   temp_vec.push_back (white_number + 1);          //right
                if (i != 0     && table[i - 1][j] != '.')   temp_vec.push_back ((i - 1) * m / 2 + j / 2);   //up
                if (i != n - 1 && table[i + 1][j] != '.')   temp_vec.push_back (i * m / 2 + j / 2);         // down
                
                bi_graph.push_back (temp_vec);
            }
        }
    }

    vector<int> matches (KunhAlgorithm (bi_graph, black_number + 1, white_number + 1));
    size_t num_matches = 0;
    for (int i = 0; i < matches.size (); ++i) {
        if (matches[i] != -1) num_matches++;
    }
    printf ("num_matches = %lu\n", num_matches);


    for (int i = 0; i < n; ++i) free (table[i]);
    free (table);

    return num_matches * a + (num_free - num_matches * 2) * b;
}



vector<int> KunhAlgorithm (const vector<vector<unsigned int>>& bi_graph, unsigned int l_size, unsigned int r_size) {
    vector<int> matches (l_size, -1);
    vector<bool> used (l_size, false);

    for (int i = 0; i < l_size; ++i) {
        search_of_chain (i, used, bi_graph, matches);
        for (int k = 0; k < used.size (); ++k) used[k] = false;
    }

    return matches;
}

bool search_of_chain (unsigned int vertex, vector<bool>& used, const vector<vector<unsigned int>>& bi_graph,
                      vector<int>& matches) {

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