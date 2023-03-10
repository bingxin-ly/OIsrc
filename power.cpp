#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, k, cnt = 1;
unordered_map<__int128, bool> mp;

__int128 qmi(__int128 a, __int128 k)
{
	__int128 res = 1;
	while(k)
	{
		if(k & 1) res = res * a;
		a = a * a;
		k >>= 1;
	}
	return res;
}

void file()
{
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
}

int main()
{
	// double st = clock();
	file(); 
	cin >> n >> k;
	
	if(k == 1)
	{
		cout << n << endl;
		return 0;
	}
	
	__int128 up = ceil((double)pow(n, 1.0 / k));

	for(__int128 a = 2; a <= up; a ++ )
	{
		for(__int128 b = k; ; b ++ )
		{
			__int128 res = qmi(a, b);
			if(res > n) break;
			if(!mp[res]) cnt ++;
			mp[res] = true;
		}
	}
	
	cout << cnt << endl;
	// cout << (clock() - st) / CLOCKS_PER_SEC << endl;
	return 0;
}
