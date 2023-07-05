#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define maxn 100

inline void qr(int &x) {
    char ch=getchar();int f=1;
    while(ch>'9'||ch<'0')    {
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')    x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x*=f;
    return;
}

inline int max(const int &a,const int &b) {if(a>b) return a;else return b;}
inline int min(const int &a,const int &b) {if(a<b) return a;else return b;}
inline int abs(const int &x) {if(x>0) return x;else return -x;}

inline void swap(int &a,int &b) {
    int c=a;a=b;b=c;return;
}

int n,a,b,c,frog[maxn];

struct Block {
    int h,l1,l2;
};
Block block[maxn];int top,cnt,ans;

inline void add(int x,int y,int z) {
    block[++top].h=x;block[top].l1=y;block[top].l2=z;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
    block[++top].h=y;block[top].l1=x;block[top].l2=z;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
    block[++top].h=z;block[top].l1=x;block[top].l2=y;
    if(block[top].l1<block[top].l2)    swap(block[top].l2,block[top].l1);
}

void clear() {
    std::memset(block,0,sizeof block);top=0;
    std::memset(frog,0,sizeof frog);ans=0;
}

inline bool cmp(const Block &a,const Block &b) {
    int sa=a.l1+a.l2,sb=b.l1+b.l2;
    return sa<sb;
}

inline bool judge(const Block &a,const Block &b) {
    return (a.l1<b.l1&&a.l2<b.l2)||(a.l2<b.l1&&a.l1<b.l2);
}

int main() {
    qr(n);
    while(n) {
        clear();
        for(int i=1;i<=n;++i) {
            a=b=c=0;qr(a);qr(b);qr(c);
            add(a,b,c);
        }
        std::sort(block+1,block+1+top,cmp);
        for(int i=1;i<=top;++i) {
            int &emm=block[i].h;
            frog[i]=emm;
            for(int j=1;j<i;++j) {
                if(judge(block[j],block[i])) frog[i]=max(frog[i],frog[j]+emm);
            }
            ans=max(ans,frog[i]);
        }
        printf("Case %d: maximum height = %d\n",++cnt,ans);
        n=0;qr(n);
    }
    return 0;
}