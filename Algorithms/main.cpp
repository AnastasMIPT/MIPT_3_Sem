#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using std::vector;

const long long StrMaxLen = 4e5 + 2;


class SuffArr {
    long long n;
    vector<long long> p;
    vector<long long> c;
    vector<long long> lcp;
public:
    SuffArr (vector<long long>& str);
    vector<long long> getArrVector ();
    void calculateLcp (vector<long long>& val);
    vector<long long> getLcpVector ();
    
};

int main () {

    char str[StrMaxLen];
    scanf ("%s", str);
    long long k = 0;
    scanf ("%lld", &k);

    vector<long long> str_int;
    for (long long i = 0; str[i] != '\0'; i++) {
        str_int.push_back (str[i] - 'a' + 1);
    }
    long long n = static_cast<long long> (str_int.size ());

    SuffArr arr (str_int);
    vector<long long> suff_arr = arr.getArrVector ();

    // for (long long i = 0; i < suff_arr.size(); i++) {
    //     printf ("i = %lld, arr[i] = %lld, el = %s\n", i, suff_arr[i], str + suff_arr[i]);
    // }
    // printf ("\n");
    arr.calculateLcp (str_int);
    vector<long long> lcp = arr.getLcpVector ();

    // for (long long i = 0; i < lcp.size(); i++) {
    //     prlong longf ("%lld ", lcp[i]);
    // }
    // prlong longf ("\n");

    //prlong longf ("n = %lld\n", n);
    long long res_ind_r = 0;
    long long res_ind_l = 0;
    long long ind = 0;
    for (; ind < n; ++ind) {
        //printf ("i = %lld, k = %lld\n", i, k);
        if (k - (n - (suff_arr[ind] + lcp[ind])) > 0) {
            k -= (n - (suff_arr[ind] + lcp[ind]));
        } else {
            
            res_ind_r = suff_arr[ind] + lcp[ind] + k;
            res_ind_l = suff_arr[ind];
            //printf ("i = %lld, lcp = %lld, suf[i] = %lld, k = %lld\n", i, lcp[i], suff_arr[i], k);
            break;
        }
        
    }
    if (ind == n) {
        printf ("%s\n", str + suff_arr[n - 1]);
    } else {
        str[res_ind_r] = '\0';
        //prtinf ("ind_l = %lld, ind _r = %lld\n", res_ind_l, res_ind_r);
        printf ("%s\n", str + res_ind_l);
    
    }
    
    return 0;
}

vector<long long> SuffArr::getLcpVector () {
    return vector<long long> (lcp.begin (), lcp.end ());;
}

vector<long long> SuffArr::getArrVector () {
    return vector<long long> (p.begin () + 1, p.end ());
}

void SuffArr::calculateLcp (vector<long long>& val) {
    //prlong longf ("Hello\n");
    long long size = val.size();
    long long cur_lcp = 0;
    lcp.resize (size);
    // prlong longf ("lcp:\n");
    // for (long long x : lcp) {
    //     prlong longf ("%lld ", x);
    // }
    for (long long i = 0; i < size; i++) {
        if (c[i] == size - 1)
            continue;
        long long nxt = p[c[i] + 1];
        while (std::max (i, nxt) + cur_lcp < size && val[nxt + cur_lcp] == val[i + cur_lcp])
            cur_lcp++;
        lcp[c[i]] = cur_lcp;
        cur_lcp = std::max ((long long)0, cur_lcp - 1);
    }
    // prlong longf ("\nlcp:\n");
    // for (long long x : lcp) {
    //     prlong longf ("%lld ", x);
    // }
}


SuffArr::SuffArr (vector<long long>& str) : n (static_cast<long long> (str.size () + 1)), p (n), c (n) {
    str.push_back (0);

    long long eclass_num = 0;
    long long cnt = 0;

    //k = 0
    std::map <long long, vector<long long>> sufs_starts_by_symb;
    for (long long i = 0; i < n; i++) {
        sufs_starts_by_symb[str[i]].push_back (i);
    }
    for (auto pair : sufs_starts_by_symb) {
        for (long long suf : pair.second) {
            c[suf] = eclass_num;
            p[cnt] = suf;
            cnt++;
        }
        eclass_num++;
    }

    for (long long l = 1; eclass_num < n; l++) {
        vector<vector<long long>> a (eclass_num); 
        
        long long d = (1 << l) / 2;
        long long new_eclass_num = 0;
        cnt = 0;

        vector<long long> new_c (n);

        for (long long i = 0; i < n; i++) {
            long long k = (p[i] - d + n) % n;
            a[c[k]].push_back (k);
        }

        for (long long i = 0; i < eclass_num; i++) {
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
    // prlong longf ("p:\n");
    // for (long long x : p) {
    //     prlong longf ("%lld ", x);
    // }
    // prlong longf ("\nc:\n");
    // for (long long x : c) {
    //     prlong longf ("%lld ", x);
    // } 
    // prlong longf ("\n");
}
