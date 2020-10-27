#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <array>
using std::vector;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma,sse2,sse3,sse4")


constexpr unsigned int MaxLen = 1e6 + 1;
constexpr unsigned int Hash_p = 27644437;
constexpr unsigned int Hash_m = 1073676287;


constexpr unsigned int LoopLimit = 262140 + 2;

void print_cubes (int * cubes, int n) {
    for (int i = 0; i < n; ++i) {
        printf ("%d ", cubes[i]);
    }
}

constexpr unsigned int mod_pow (unsigned int base, unsigned int exp, unsigned int mod) noexcept {
    auto result = 1;
    for (int i = 0; i < exp; ++i) result = (result * base) % mod;
    return result;
}


template<unsigned int N, unsigned int base, unsigned int mod>
struct Mod_Pow_Arr {
    unsigned int vals[N];
    constexpr Mod_Pow_Arr() : vals() {
        auto result = 1;
        for (auto i = 0; i != N; ++i) {
            vals[i] = result;
            result = (result * base) % mod;
            }
    }
};

// static constexpr std::array<int, MaxLen> mod_pow_arr (int base, int mod) {
//     std::array<int, MaxLen> result {};
//     for (int i = 0; i < MaxLen; ++i) {
//         result[i] = mod_pow (base, i, mod);
//     }
//     return result;
// }

//static constexpr std::array<int, MaxLen> (mod_pow_arr (Hash_p, Hash_m));

inline constexpr unsigned int mod_mul (unsigned int a, unsigned int b, unsigned int mod) {
    return (a * b) % mod;
}

inline constexpr unsigned int mod_sum (unsigned int a, unsigned int b, unsigned int mod) {
    return a + b > mod? a + b - mod: a + b;
}



unsigned int hash_pref (unsigned int* str, unsigned int right, const unsigned int* arr) {
    unsigned int hash_sum = 0;
    for (unsigned int i = 0; i < right; ++i) {
        hash_sum += (str[i] * arr[i]) % Hash_m;
    }
    return hash_sum;
}

unsigned int hash_pref_rev (unsigned int* str, unsigned int left, unsigned int len, const unsigned int* arr) {
    unsigned int hash_sum = 0;
    unsigned int ind = 0;
    for (unsigned int i = len - 1; i > left; --i, ++ind) {
        hash_sum += (str[i] * arr[ind]) % Hash_m;
    }
    return hash_sum;
}

int main () {
    constexpr auto p_arr = Mod_Pow_Arr<LoopLimit, Hash_p, Hash_m> ();
    
    // printf ("%u\n", p_arr.vals[1000]);
    // printf ("\n");
    int n (0), m (0);
    scanf ("%d%d", &n, &m);
    unsigned int cubes[n];
    for (int i = 0; i < n; ++i) {
        scanf ("%d", &cubes[i]);
    }
    printf ("%u\n%u\n", hash_pref (cubes, 2, p_arr.vals), hash_pref_rev (cubes, 1, n, p_arr.vals));
    return 0;
}

