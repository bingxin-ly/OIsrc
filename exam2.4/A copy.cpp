#include <bits/stdc++.h>
using namespace std;

const int MAX = 10;
int N;
double D1, C, D2, P, cnt;
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
    static const double MAX_S = C * D2;
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

    double price_now = jiayou[0].P, gas_now = 0, dis_now = 0;
    for (int i = 1; i <= N + 1;)
    {
        cout << price_now << endl;
        if (jiayou[i].D - dis_now > MAX_S)
            cout << "No Solution" << endl;
        int j = i + 1;
        cout << (j + 1 <= N) << endl;
        while (jiayou[j].P > price_now &&
               jiayou[j].D - dis_now <= MAX_S)
            j++;
        if (j > N)
        {
            i++;
            continue;
        }
        cout << j << endl;
        dis_now = jiayou[j - 1].D;
        cnt += price_now * (jiayou[j].D - dis_now) / D2;
        price_now = jiayou[j].P;
        i += j;
    }
    printf("%.2f", cnt);
    return 0;
}