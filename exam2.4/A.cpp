#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;
int N;
double D1, C, D2, P, cnt;
double price_now, dis_now, gas_now, MAX_S;

struct zhan
{
    double D, P;
    bool operator<(const zhan &other) const
    {
        return (D < other.D);
    }
} jiayou[MAX];
int get_nxt(int pos)
{
    if (pos == N)
        return -1;
    for (int j = pos + 1; j <= N; j++)
        if (jiayou[j].P < price_now)
            return j;
    return -2;
}

int main()
{
    cin >> D1 >> C >> D2 >> P >> N;
    for (int i = 1; i <= N; i++)
        cin >> jiayou[i].D >> jiayou[i].P;
    jiayou[0].P = P, jiayou[0].D = 0;
    MAX_S = C * D2;
    jiayou[N + 1].P = INT_MAX, jiayou[N + 1].D = D1;
    sort(jiayou, jiayou + N + 1);

    price_now = jiayou[0].P;
    int pos = 0, nxt = 0;
    while (pos <= N)
    {
        if (jiayou[pos + 1].D - dis_now > MAX_S)
            cout << "No Solution" << endl;
        nxt = get_nxt(pos);
        if (nxt >= 0)
        {
            // gas_now -= (dis_now - jiayou[pos - 1].D) / D2;
            cnt += price_now * ((jiayou[nxt].D - dis_now) / D2 - gas_now);
            dis_now = jiayou[nxt].D;
            price_now = jiayou[nxt].P;
            // gas_now += (jiayou[nxt].D - dis_now) / D2;
        }
        else if (nxt == -2)
        {
            for (int j = pos + 1; jiayou[j].D - dis_now <= MAX_S; j++)
                if (price_now > jiayou[j].P)
                    nxt = j;
            gas_now -= (jiayou[nxt].D - dis_now) / D2;
            cnt += price_now * (C - gas_now);
            gas_now = C;
            dis_now = jiayou[nxt].D;
            price_now = jiayou[nxt].P;
        }
        else
        {
            gas_now -= (jiayou[nxt].D - dis_now) / D2;
            cnt += price_now * ((D1 - dis_now) / D2 - gas_now);
            break;
        }
        pos = nxt;
    }
    printf("%.2f", cnt);
    return 0;
}