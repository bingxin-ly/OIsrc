#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2*1e5+10;
typedef long long ll;
struct data
{
	ll dis;int id;
	friend bool operator <(data a,data b)
	{
		return a.dis>b.dis;
	}
};
priority_queue <data> pq;
int v[N<<1];int x[N<<1];ll w[N<<1];
int al[N];int ct;bool book[N];
void add(int u,int V,ll va)
{
	v[++ct]=V;x[ct]=al[u];al[u]=ct;w[ct]=va;
}
int main()
{
	int n;int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u;int v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	ll ans=0;int cnt=0;
	pq.push((data){0,1});
	while(!pq.empty())
	{	
		int u=pq.top().id;
		ans+=pq.top().dis;
		cnt++;
		book[u]=true;
		pq.pop();
		for(int i=al[u];i;i=x[i])
			if(!book[v[i]])
				pq.push((data){w[i],v[i]});
		while(!pq.empty()&&book[pq.top().id])
			pq.pop();
				
	}
	if(cnt<n)
		printf("orz");
	else 
		printf("%lld",ans);
	return 0;
}
