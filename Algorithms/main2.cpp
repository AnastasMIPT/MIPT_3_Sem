#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using std::vector;

const int StrMaxLen = 4e5 + 2;


vector<int> suf_arr (vector<int> &str);
int main () {
    char str[StrMaxLen];
    scanf ("%s", str);
    vector<int> int_str;
    for (int i = 0; str[i] != '\0'; i++) {
        int_str.push_back (str[i] - 'a' + 1);
    }

    vector<int> suff_arr = suf_arr (int_str);

    for (int i = 0; i < suff_arr.size(); i++) {
        printf ("%d ", suff_arr[i] + 1);
    }
    printf ("\n");
    
    return 0;
}

vector<int> suf_arr (vector<int>& str)  {
    str.push_back (0);

    int n = static_cast<int> (str.size ());
    vector <int> p (n), c (n);

    int eclass_num = 0;
    int cnt = 0;

    //k = 0
    std::map <int, vector<int>> sufs_starts_by_symb;
    for (int i = 0; i < n; i++) {
        sufs_starts_by_symb[str[i]].push_back (i);
    }
    for (auto pair : sufs_starts_by_symb) {
        for (int suf : pair.second) {
            c[suf] = eclass_num;
            p[cnt] = suf;
            cnt++;
        }
        eclass_num++;
    }

    for (int l = 1; eclass_num < n; l++) {
        vector<vector<int>> a (eclass_num); 
        
        int d = (1 << l) / 2;
        int new_eclass_num = 0;
        cnt = 0;

        vector<int> new_c (n);

        for (int i = 0; i < n; i++) {
            int k = (p[i] - d + n) % n;
            a[c[k]].push_back (k);
        }

        for (int i = 0; i < eclass_num; i++) {
            for (size_t j = 0; j < a[i].size (); j++) {
                if (j == 0 || c[(a[i][j] + d) % n] != c[(a[i][j - 1] + d) % n])
                    new_eclass_num++;
                new_c[a[i][j]] = new_eclass_num - 1;
                p[cnt] = a[i][j];
                cnt++;
            }
        }

        eclass_num = new_eclass_num;
        c = new_c;
    }
    printf ("p:\n");
    for (int x : p) {
        printf ("%d ", x);
    }
    printf ("\nc:\n");
    for (int x : c) {
        printf ("%d ", x);
    }
    printf ("\n");
    return vector<int> (p.begin () + 1, p.end ());


}
