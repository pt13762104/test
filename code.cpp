#include <bits/stdc++.h>
#include <stdfloat>
using namespace std;
using namespace chrono;
#ifndef yoshi_likes_e4
#define endl '\n'
#endif
#define problem ""
#define multitest 0
#define debug(x) cerr << #x << " = " << x << endl;
chrono::high_resolution_clock Clock;
// Force inlining to make the compiler actually compiles for all tile sizes instead of relying on a function call (which
// gives off really poor performance).
template <typename T, typename TC>
static inline __attribute__((always_inline)) double naive(const T *__restrict__ a, const T *__restrict__ b,
                                                          TC *__restrict__ c, const int N, const int BR, const int BC,
                                                          const int BX)
{
    auto t0 = Clock.now();
    memset(c, 0, N * N * sizeof(T));
    for (int i = 0; i < N; i += BR)
        for (int j = 0; j < N; j += BC)
            for (int k = 0; k < N; k += BX)
                for (int ii = i; ii < i + BR; ii++)
                    for (int kk = k; kk < k + BX; kk++)
                        for (int jj = j; jj < j + BC; jj++)
                            c[ii * N + jj] += a[ii * N + kk] * b[kk * N + jj];
    double Gflops = (2.0 * N * N * N) / duration_cast<nanoseconds>(Clock.now() - t0).count();
    cerr << "GFLOPS (" << typeid(T).name() << "): " << Gflops << endl;
    return Gflops;
}
void init()
{
}
float128_t a[1048576];
float128_t b[1048576];
float128_t c[1048576];
#define N(T, TC, BR, BC, BX) naive<T, TC>((const T *)a, (const T *)b, (TC *)c, 1024, BR, BC, BX);
void Yoshi()
{
#ifdef __clang__
#pragma clang loop unroll(full)
#else
#pragma GCC unroll 1000
#endif
    for (int BR = 64; BR <= 256; BR <<= 1)
#ifdef __clang__
#pragma clang loop unroll(full)
#else
#pragma GCC unroll 1000
#endif
        for (int BC = 32; BC <= 256; BC <<= 1)
#ifdef __clang__
#pragma clang loop unroll(full)
#else
#pragma GCC unroll 1000
#endif
            for (int BX = 16; BX <= 64; BX <<= 1)
            {
                cerr << BR << " " << BC << " " << BX << endl;
                N(int8_t, int16_t, BR, BC, BX)
                N(int16_t, int32_t, BR, BC, BX)
                N(int32_t, int64_t, BR, BC, BX)
                N(int64_t, int64_t, BR, BC, BX)
                N(uint8_t, uint16_t, BR, BC, BX)
                N(uint16_t, uint32_t, BR, BC, BX)
                N(uint32_t, uint64_t, BR, BC, BX)
                N(uint64_t, uint64_t, BR, BC, BX)
        // AVX512-FP16 and other archs needs to be considered.
#if defined(__aarch64__) || defined(_M_ARM64)
                N(float16_t, float16_t, BR, BC, BX)
#endif
#if defined(ENABLE_BF16)
                N(bfloat16_t, float32_t, BR, BC, BX)
#endif
                N(float32_t, float32_t, BR, BC, BX)
                N(float64_t, float64_t, BR, BC, BX)
            }
#if not(defined(__aarch64__) || defined(_M_ARM64))
    N(float16_t, float16_t, 4, 4, 4)
#endif
#if not(defined(ENABLE_BF16))
    N(bfloat16_t, float32_t, 4, 4, 4)
#endif
    N(long double, long double, 4, 4, 4)
// ARM64 extended precision is already FP128.
#if not(defined(__aarch64__) || defined(_M_ARM64))
    N(float128_t, float128_t, 4, 4, 4)
#endif
    N(__int128_t, __int128_t, 4, 4, 4)
}
signed main()
{
#ifndef yoshi_likes_e4
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (fopen(problem ".inp", "r"))
    {
        freopen(problem ".inp", "r", stdin);
        freopen(problem ".out", "w", stdout);
    }
#endif
    init();
    int t = 1;
#if multitest
    cin >> t;
#endif
    while (t--)
        Yoshi();
}
