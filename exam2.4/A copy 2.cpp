#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;
int N;
double D1, C, D2, P, cnt;
double price_now, gas_now = 0, dis_now = 0, MAX_S;
struct zhan
{
    double D, P;
    bool operator<(const zhan &other) const
    {
        return (D < other.D);
    }
} jiayou[MAX];

int main()
{
    cin >> D1 >> C >> D2 >> P >> N;
    MAX_S = C * D2;
    for (int i = 1; i <= N; i++)
        cin >> jiayou[i].D >> jiayou[i].P;
    if (D2 <= 0)
    {
        cout << "No Solution";
        return 0;
    }
    jiayou[0].P = P, jiayou[0].D = 0;
    jiayou[N + 1].P = INT_MAX, jiayou[N + 1].D = D1;
    sort(jiayou, jiayou + N + 1);

    price_now = jiayou[0].P;
    for (int i = 0; i != -1;)
    {
        int idx = 0;
        for (int j = i + 1; j <= N && jiayou[i].D - dis_now <= MAX_S; j++)
        {
            if (jiayou[j].P < price_now)
            {
                idx = j;
                break;
            }
        }
        idx = -1;
        cout << __LINE__ << ' ' << idx << endl;
        if (idx = -1)
        {
            idx = i + 1;
            gas_now = C;
        }
        i = idx;
        cnt += price_now * ((jiayou[idx].D - dis_now) / D2 - gas_now);
        price_now = jiayou[idx].P;
        dis_now = jiayou[idx].D;
        gas_now -= (jiayou[idx].D - dis_now) / D2;
    }
    cout << dis_now << ' ' << price_now << ' ' << cnt << endl;
    cnt += price_now * (jiayou[N + 1].D - dis_now) / D2;
    printf("%.2f", cnt);
    return 0;
}