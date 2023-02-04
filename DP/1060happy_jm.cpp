#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e5 + 10;

int N, V;
int v[MAX], w[MAX];
int f[MAX];

int main()
{
    cin >> V >> N;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i],
            w[i] *= v[i];
    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
            f[j] = max(f[j], f[j - v[i]] + w[i]);
    cout << f[V] << endl;
    return 0;
}
