#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 1e5 + 9;
int id, n, c, k;
int v[N];

//---

ll sum[N];

bool check1(int x) {
    memset(sum, 0, sizeof sum);

    ll res = k, dif;
    for (int i = 1; i <= n; ++i) {
        sum[i] += sum[i - 1];
        dif = sum[i] + v[i];

        if (res < dif)
            return 0;
        else if (dif > 0) {
            res -= dif;
            sum[i] -= dif, sum[min(i + x, n + 1)] += dif;
        }
    }
    return 1;
}

//---

ll tag[N];

bool check2(int x) {
    memset(sum, 0, sizeof sum);
    memset(tag, 0, sizeof tag);

    ll res = k, dif;
    for (int i = 1; i <= n; ++i) {
        tag[i] += tag[i - 1];
        sum[i] += tag[i] + sum[i - 1];
        dif = (sum[i] + v[i] + x - 1) / x;

        if (res < dif)
            return 0;
        else if (dif > 0) {
            res -= dif;
            tag[i] += dif, tag[min(i + x + 1, n + 1)] -= dif;
            sum[i] -= x * dif;
        }
    }
    return 1;
}

//---

ll tag2[N];

bool check3(int x) {
    memset(sum, 0, sizeof sum);
    memset(tag, 0, sizeof tag);
    memset(tag2, 0, sizeof tag2);

    ll res = k, dif;
    for (int i = 1; i <= n; ++i) {
        tag2[i] += tag2[i - 1];
        tag[i] += tag2[i] + tag[i - 1];
        sum[i] += tag[i] + sum[i - 1];
        dif = (sum[i] + v[i] + 1ll * x * x - 1) / (1ll * x * x);

        if (res < dif)
            return 0;
        else if (dif > 0) {
            res -= dif;
            tag2[i] -= dif << 1, tag2[min(i + x + 1, n + 1)] += dif << 1;
            tag[i] += ((x << 1) + 1) * dif, tag[min(i + x + 1, n + 1)] -= dif;
            sum[i] -= 1ll * x * x * dif;
        }
    }
    return 1;
}

//---

int main() {
    scanf("%d%d%d%d", &id, &n, &c, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &v[i]);

    int l = 0, r = n;
    bool flag;
    while (l < r) {
        int mid = (l + r) >> 1;

        if (!c)
            flag = check1(mid);
        else if (c == 1)
            flag = check2(mid);
        else
            flag = check3(mid);

        if (flag)
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", ((!c) ? check1(r) : ((c == 1) ? check2(r) : check3(r))) ? r : -1);
    return 0;
}
