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
    if (D2 <= 0)
    {
        cout << "No Solution";
        return 0;
    }
    for (int i = 1; i <= N; i++)
        cin >> jiayou[i].D >> jiayou[i].P;
    jiayou[0].P = P, jiayou[0].D = 0;
    jiayou[N + 1].P = INT_MAX, jiayou[N + 1].D = D1;
    sort(jiayou, jiayou + N + 1);

    double price_now = jiayou[0].P;
    int l_now = 0;
    for (int i = 1; i <= N + 1; i++)
    {
        if (l_now + jiayou[i].D - jiayou[i - 1].D);
        cnt += price_now * (jiayou[i].D- jiayou[i - 1].D);
        price_now = min(price_now, jiayou[i].P);
    }
    printf("%.2f", cnt / D2);
    return 0;
}