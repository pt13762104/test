#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
#ifndef yoshi_likes_e4
#define endl '\n'
#endif
#define problem ""
#define multitest 0
#define debug(x) cerr << #x << " = " << x << endl;
chrono::high_resolution_clock Clock;
template <typename T>
double naive(const T *__restrict__ a, const T *__restrict__ b, T *__restrict__ c, const int N, const int BR,
             const int BC, const int BX)
{
    auto t0 = Clock.now();
    memset(c, 0, N * N * sizeof(T));
    for (int i = 0; i < N; i += BR)
        for (int j = 0; j < N; j += BC)
            for (int k = 0; k < N; k += BX)
                for (int n = 0; n < BR; n++)
                    for (int m = 0; m < BC; m++)
                        for (int kk = k; kk < k + BX; kk++)
                            c[(i + n) * N + j + m] += (size_t)a[(i + n) * N + kk] * b[kk * N + j + m];
    double Gflops = (2.0 * N * N * N) / duration_cast<nanoseconds>(Clock.now() - t0).count();
    cerr << "GFLOPS (" << typeid(T).name() << "): " << Gflops << endl;
    return Gflops;
}
void init()
{
}
__float128 a[1048576];
__float128 b[1048576];
__float128 c[1048576];
#define N(T, BR, BC, BX) naive<T>((const T *)a, (const T *)b, (T *)c, 1024, BR, BC, BX);
void Yoshi()
{
#pragma GCC unroll 3
    for (int BR = 16; BR <= 64; BR <<= 1)
#pragma GCC unroll 3
        for (int BC = 32; BC <= 128; BC <<= 1)
#pragma GCC unroll 4
            for (int BX = 4; BX <= 32; BX <<= 1)
            {
                cout << BR << " " << BC << " " << BX << endl;
                N(_Float16, BR, BC, BX)
                N(float, BR, BC, BX)
                N(double, BR, BC, BX)
                N(long double, BR, BC, BX)
            }
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
