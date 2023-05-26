#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

const int N = 1000010;
int n, m;
int he[N], e[N], ne[N], idx;
char s[N];

int siz[N], dep[N], son[N];
int cnt[N][30];
bool vis[N], ans[N];

struct question{
    int h, id;
};
vector<question> q[N];

inline void adds(int a, int b){
    e[++idx] = b;
    ne[idx] = he[a];
    he[a] = idx;
}

//---

void calc(int x, int fa, int val){
    cnt[dep[x]][s[x] - 'a'] += val;
    for(int i = he[x]; i; i = ne[i]){
        int j = e[i];
        if(j == fa || vis[j]) continue;
        calc(j, x, val);
    }
}

bool check(int c[]){
    int num = 0;
    for(int i = 0; i < 26; ++ i ){
        if(c[i] & 1) ++num;
        if(num > 1) return 0;
    }
    if(num > 1) return 0;
    return 1;
}

//---

void dfs1(int x, int fa){
    siz[x] = 1, dep[x] = dep[fa] + 1;
    for(int i = he[x]; i; i = ne[i]){
        int j = e[i];
        if(j == fa) continue;
        dfs1(j, x);
        siz[x] += siz[j];
        if(!son[x] || siz[j] > siz[son[x]]) son[x] = j;
    }
}

void dfs2(int x, int fa, bool keep){
    for(int i = he[x]; i; i = ne[i]){
        int j = e[i];
        if(j == fa || j == son[x]) continue;
        dfs2(j, x, 0);
    }

    if(son[x]){
        dfs2(son[x], x, 1);
        vis[son[x]] = 1;
    }

    calc(x, fa, 1), vis[son[x]] = 0;
    for(int i = 0; i < q[x].size(); ++ i )
        ans[q[x][i].id] = check(cnt[q[x][i].h]);
    
    if(!keep) calc(x, fa, -1);
}

void init(){
    scanf("%d%d", &n, &m);
    for(int i = 2; i <= n; ++ i ){
        int x; scanf("%d", &x);
        adds(x, i), adds(i, x);
    }

    scanf("%s", (s + 1));
    for(int i = 1; i <= m; ++ i ){
        int a, b; scanf("%d%d", &a, &b);
        q[a].push_back((question){b, i});
    }
}

int main(){
    init();
    dfs1(1, 0);
    dfs2(1, 0, 0);
    
    for(int i = 1; i <= m; ++ i )
        (ans[i]) ? puts("Yes") : puts("No");
    return 0;
}