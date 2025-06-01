#include <bits/stdc++.h>
using namespace std;
using namespace chrono;
#ifndef yoshi_likes_e4
#define endl '\n'
#endif
#define problem ""
#define multitest 0
#define debug(x) cerr << #x << " = " << x << endl;
#define BR 32
#define BC 128
#define BX 8
chrono::high_resolution_clock Clock;
template <typename T> double naive(const T *a, const T *b, T *c, const int N)
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
    double Gflops = (2 * 1024 * 1024 * 1024.0) / duration_cast<nanoseconds>(Clock.now() - t0).count();
    cerr << "GFLOPS (" << typeid(T).name()
         << "): " << (2 * 1024 * 1024 * 1024.0) / duration_cast<nanoseconds>(Clock.now() - t0).count() << endl;
    return Gflops;
}
void init()
{
}
#if defined(__aarch64__) || defined(_M_ARM64)
#define __float128 _Float128
#endif
__float128 a[1048576];
__float128 b[1048576];
__float128 c[1048576];
#define N(T) naive<T>((const T *)a, (const T *)b, (T *)c, 1024)
void Yoshi()
{
    // Will be slow on non-FP16 systems.
    double Gflops16 = N(_Float16);
    double Gflops32 = N(float);
    double Gflops64 = N(double);
    // Usually 16-32x slower than double.
    double GflopsExtended = N(long double);
    double Gflops128 = N(__float128);
    cout << "FP16: 1:" << Gflops32 / Gflops16 << endl;
    cout << "FP64: 1:" << Gflops32 / Gflops64 << endl;
    cout << "Extended: 1:" << Gflops32 / GflopsExtended << endl;
    cout << "FP128: 1:" << Gflops32 / Gflops128 << endl;
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
