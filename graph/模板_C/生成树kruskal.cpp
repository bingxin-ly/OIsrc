#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 2 * 1e5 + 10;
typedef long long ll;
struct ufs
{
	int fa[N];
	void init(int n)
	{
		for (int i = 1; i <= n; i++)
			fa[i] = i;
	}
	int f(int x)
	{
		return fa[x] = (fa[x] == x) ? x : f(fa[x]);
	}
	bool u(int x, int y)
	{
		x = f(x);
		y = f(y);
		if (x == y)
			return false;
		fa[x] = y;
		return true;
	}
} s;
struct edge
{
	int u;
	int v;
	ll w;
	friend bool operator<(edge a, edge b)
	{
		return a.w < b.w;
	}
} e[N];
vector<int> v;
int main()
{
	int n;
	int m;
	scanf("%d%d", &n, &m);
	s.init(n);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
	sort(e + 1, e + m + 1);
	ll ret = 0;
	int cnt = 0;
	for (int i = 1; i <= m; i++)
		if (s.u(e[i].u, e[i].v))
			ret += e[i].w, cnt++;
	if (cnt != n - 1)
		printf("orz");
	else
		printf("%lld", ret);
	return 0;
}
