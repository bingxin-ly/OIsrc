#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+10;
typedef long long ll;
struct ufs//
{
	int fa[N];
	int siz[N];
	void init(int n)
	{
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=n;i++)siz[i]=1;
	}
	int f(int x)
	{
		return fa[x]=(fa[x]==x)?x:f(fa[x]);
	}
	void u(int x,int y)
	{
		x=f(x);y=f(y);
		if(x==y)return;	

		//if(siz[x]>siz[y])swap(x,y);
		//siz[y]+=siz[x];
		fa[x]=y;
	}
}s;
int main()
{
	int n;int m;
	scanf("%d%d",&n,&m);
	s.init(n);
	for(int i=1;i<=m;i++)
	{
		int x;int y;int z;
		scanf("%d%d%d",&z,&x,&y);
		if(z==1)
			s.u(x,y);
		else printf("%s\n",(s.f(x)==s.f(y))?"Y":"N");
	}
	return 0;
}
			
