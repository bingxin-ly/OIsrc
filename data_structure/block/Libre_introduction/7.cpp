#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, K = 320, MOD = 10007;
int pos[N], st[K], ed[K];
int arr[N], add[K], mul[K];

inline void reach(int id)
{
    for (int i = st[id]; i <= ed[id]; i++)
        (((arr[i] *= mul[id]) %= MOD) += add[id]) %= MOD;
    mul[id] = 1, add[id] = 0;
}
bool ismul;
void force(int l, int r, int v)
{
    int id = pos[l];
    reach(id);
    if (ismul)
        for (int i = l; i <= r; i++)
            (arr[i] *= v) %= MOD;
    else
        for (int i = l; i <= r; i++)
            (arr[i] += v) %= MOD;
}
void multi(int l, int r, int v)
{
    ismul = true;
    int sid = pos[l], eid = pos[r];
    if (sid == eid)
        return force(l, r, v);
    force(l, ed[sid], v);
    for (int i = sid + 1; i <= eid - 1; i++)
        (mul[i] *= v) %= MOD, (add[i] *= v) %= MOD;
    force(st[eid], r, v);
}
void range(int l, int r, int v)
{
    ismul = false;
    int sid = pos[l], eid = pos[r];
    if (sid == eid)
        return force(l, r, v);
    force(l, ed[sid], v);
    for (int i = sid + 1; i <= eid - 1; i++)
        (add[i] += v) %= MOD;
    force(st[eid], r, v);
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    int len = sqrt(n), num = (n - 1) / len + 1;
    for (int i = 1; i <= num; i++)
        st[i] = (i - 1) * len + 1,
        ed[i] = i * len,
        mul[i] = 1;
    ed[num] = n;
    for (int i = 1; i <= n; i++)
        pos[i] = (i - 1) / len + 1,
        cin >> arr[i];

    for (int op, l, r, c; n--;)
    {
        cin >> op >> l >> r >> c;
        if (op == 0)
            range(l, r, c);
        else if (op == 1)
            multi(l, r, c);
        else
            cout << (arr[r] * mul[pos[r]] % MOD + add[pos[r]]) % MOD << '\n';
    }
    return 0;
}