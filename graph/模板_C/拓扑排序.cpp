#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1e6+10;
typedef long long ll;
int v[N];int x[N];int al[N];int d[N];
int ct;
void add(int u,int V)
{
	v[++ct]=V;x[ct]=al[u];al[u]=ct;d[V]++;
}
queue <int> q;
void toposort(int n,int* srt)
{
	for(int i=1;i<=n;i++)
		if(d[i]==0)q.push(i);
	int hd=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		srt[++hd]=u;
		for(int i=al[u];i;i=x[i])
		{
			d[v[i]]--;
			if(d[v[i]]==0)q.push(v[i]);
		}
	}
}
int main()
{
	return 0;
}
