// sto HEoier GCY_XZT orz
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

#define int long long

using namespace std;

const int N = 1e6 + 9; // 数据范围是10^19  k>=3的时候只需要处理前10^6的数据

int n, k, ans;
int primes[N], cnt;
bool st[N];

int gcd(int a, int b) // 找最大公因数
{
	if (a < b)
		swap(a, b);
	return b == 0ll ? a : gcd(b, a % b);
}

void shai(int n) // 线筛筛质数
{
	for (int i = 2; i <= n; ++i)
	{
		if (!st[i])
		{
			primes[++cnt] = i;
		}
		for (int j = 1; primes[j] <= n / i; ++j)
		{
			st[primes[j] * i] = true;
			if (i % primes[j] == 0)
				break;
		}
	}
}

bool check(int x)
{
	// 筛出被遗漏的只由两个互质的数表达的数（如6，12，15等）  
	// ps:因为他们的平方不能只由质数的n次方所表达
	int g;
	bool flag = false;
	for (int z = 1; primes[z] <= x / primes[z] && z <= cnt; ++z)
	{
		// 如果第z号位置的质数的平方小于查验的数，并且还有质数没有被查验

		int i = primes[z]; // 取出该质数
		if (x % i == 0)
		{ //
			int sz = 0;
			while (x % i == 0)
			{
				sz++; // 该质数最大的次方数
				x /= i;
			}
			if (!flag)
				g = sz, flag = true; // 标记一个质数底
			else
				g = gcd(g, sz);
		}
	}
	if (x != 1)
		return true; // 说明该数可以被表示两个互质的数表示如（56=2^3*7 ：因为先取出2，发现不能整除）
	return (g == 1); // g=1说明这个数由两个质数构成    g!=1筛掉如 196=2^2*7^2 的数因为在主函数中的14的次方中包含
}

signed main()
{

	// freopen("power.in", "r", stdin);
	// freopen("power.out", "w", stdout);

	cin >> n >> k;

	if (k == 1) // k=1的情况
	{
		cout << n;
		return 0;
	}

	shai(N - 1); // 处理k>=3的情况

	for (int i = 2; i < N; ++i)
	{
		if (check(i))
		{
			int z = 1, sz = 0;
			while (z <= n / i)
				z *= i, sz++;
			if (sz < k)
				break; // 如果该数不能被表示答案就不加上这个数
			ans += sz - k + 1;
		}
	}

	cout << ans + 1 << endl;

	return 0;
}
