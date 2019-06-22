#include<bits/stdc++.h>
using namespace std;

map<int,int>fa;
int find(int x){
    if(fa.find(x)==fa.end()) fa[x]=x;
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void join(int x,int y){
    int f1=find(x);
    int f2=find(y);
    if(f1>f2) swap(f1,f2); // f1<f2
    fa[f1]=f2;
}

map<int,int>mp;
const int maxn=1e5+5;
int p[maxn];

int main(){
    int n,a,b;
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++) {
        scanf("%d",p+i);
        mp[p[i]]++;
    }
    const int A=1e9+123;
    const int B=1e9+124;
    for(int i=1;i<=n;i++) {
        if(mp.find(a-p[i])!=mp.end()) join(p[i],a-p[i]);
        else join(p[i],B);
        if(mp.find(b-p[i])!=mp.end()) join(p[i],b-p[i]);
        else join(p[i],A);
    }
    if(find(A)==find(B)){
        printf("NO\n");
    }
    else{
        printf("YES\n");
        for(int i=1;i<=n;i++) {
            if(find(p[i])<=1e9) join(p[i],A);
            if(find(p[i])==A) printf("0 ");
            else printf("1 ");
        }
    }
}





