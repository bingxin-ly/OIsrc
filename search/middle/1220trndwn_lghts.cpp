#include <bits/stdc++.h>
using namespace std;

const int N = 60;
int n, bg, ans = INT_MAX;
int pl[N], w[N];

void dfs(int p, int l, int r, int cst)
{
	if (l == 0 && r == n + 1)
	{
		ans = min(ans, cst);
		return;
	}
	if (cst > ans)
		return;

	int ps_cst = 0, dis;
	int ans1, ans2;
	if (l)
	{
		dis = pl[p] - pl[l];
		for (int i = 1; i <= l; i++)
			ps_cst += w[i] * dis;
		for (int i = r; i <= n; i++)
			ps_cst += w[i] * dis;
		dfs(l, l - 1, r, cst + ps_cst);
	}
	if (r <= n)
	{
		dis = pl[r] - pl[p];
		ps_cst = 0;
		for (int i = 1; i <= l; i++)
			ps_cst += w[i] * dis;
		for (int i = r; i <= n; i++)
			ps_cst += w[i] * dis;
		dfs(r, l, r + 1, cst + ps_cst);
	}
}

int main()
{
	scanf("%d%d", &n, &bg);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &pl[i], &w[i]);
	}

	dfs(bg, bg - 1, bg + 1, 0);
	printf("%d", ans);
	return 0;
}
