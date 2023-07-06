#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#ifndef ONLINE_JUDGE
ifstream fin("D:\\OIsrc\\.in");
ofstream fout("D:\\OIsrc\\std.out");
#define cin fin
#define cout fout
#undef endl
#endif

const int N=1e5+1;
int a[N];
bool mp[4];
map<int,map<int,int> >ans;
signed main(){
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++) cin >> a[i];
    while(m--){
        int op,l,r;
        cin >> op >> l >> r;
        mp[op]=1;
//      for(int i=0;i<n;i++) cout<<a[i]<<" ";
//      puts("");
        if(!op) fill(a+l,a+r+1,0);
        else if(op==1) fill(a+l,a+r+1,1);
        else if(op==2) for(int i=l;i<=r;i++) a[i]=(!a[i]);
        else if(op==3){
            int ans=0;
            for(int i=l;i<=r;i++) ans+=a[i];
            printf("%d\n",ans);
        }
        else{
            if(!mp[0]&&!mp[1]&&!mp[2]&&ans[l][r]){
                printf("%d\n",ans[l][r]);
                continue;
            }
            int anss=0,t=0;
            for(int i=l;i<=r;i++){
                if(a[i]) t++;
                else t=0;
                anss=max(anss,t);
            }
            ans[l][r]=anss;
            printf("%d\n",anss);
        }
//      for(int i=0;i<n;i++) cout<<a[i]<<" ";
//      puts("");
    }
    return 0;
}