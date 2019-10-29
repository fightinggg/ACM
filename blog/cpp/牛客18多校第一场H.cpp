#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pwx2(x) ((x)*(x))

const ll maxn=1e5+5;
struct star{ll v,w,nex;}edge[maxn<<1];
ll head[maxn],cnt,n;
ll down[maxn],up[maxn],ans[maxn];
struct line{ll k,b,id;};// y=kx+b
double cross(line l1,line l2){// k1x+b1=k2x+b2 -> k1x-k2x=b2-b1
    return -double(l1.b-l2.b)/(l1.k-l2.k);
}
ll val_at(line l1,ll x){
    return x*l1.k+l1.b;
}

void ini(ll _n){
    n=_n;
    cnt=-1;
    for(ll i=0;i<=n;i++) head[i]=-1,down[i]=up[i]=ans[i]=0;
}

void add_edge(ll u,ll v,ll w){
    edge[++cnt]=star{v,w,head[u]}; head[u]=cnt;
    edge[++cnt]=star{u,w,head[v]}; head[v]=cnt;
}

void dfs1(ll u,ll father=0,ll w=0){
    for(ll i=head[u];~i;i=edge[i].nex){
        if(edge[i].v==father) continue;
        dfs1(edge[i].v,u,edge[i].w);
        if(father) {
            down[u]=max(down[u],down[edge[i].v]+pwx2(w-edge[i].w));
            ans[father]=max(ans[father],down[u]);
        }
    }
}

void dfs2(ll u,ll father=0){
    vector<line> vec;
    for(ll i=head[u];~i;i=edge[i].nex){
        ll v=edge[i].v,w=edge[i].w;
        if(v==father) vec.push_back(line{-2*w,up[u]+w*w,i});
        else vec.push_back(line{-2*w,down[v]+w*w,i});
    }
    sort(vec.begin(),vec.end(),[](line l,line r){return l.k<r.k;});
    static line stk[maxn];
    ll tot=0;
    for(ll i=0;i<vec.size();i++){// k++ x--
        star&e=edge[vec[i].id];
        while(tot>=2&&cross(stk[tot],stk[tot-1])>e.w)tot--;
        if(e.v!=father&&tot>=1) {
            star&e2=edge[stk[tot].id];
            up[e.v]=max(up[e.v],val_at(stk[tot],e.w)+e.w*e.w);
            ans[e.v]=max(ans[e.v],up[e.v]);
        }
        if(tot>=1&&vec[i].k==stk[tot].k){
            if(vec[i].b>stk[tot].b)tot--;
            else continue;
        }
        while(tot>=2&&cross(vec[i],stk[tot])<cross(stk[tot],stk[tot-1]))tot--;
        stk[++tot]=vec[i];
    }
    tot=0;
    for(ll i=int(vec.size())-1;i>=0;i--){// k--
        star&e=edge[vec[i].id];
        while(tot>=2&&cross(stk[tot],stk[tot-1])<e.w)tot--;
        if(e.v!=father&&tot>=1) {
            star&e2=edge[stk[tot].id];
            up[e.v]=max(up[e.v],val_at(stk[tot],e.w)+e.w*e.w);
            ans[e.v]=max(ans[e.v],up[e.v]);
        }
        if(tot>=1&&vec[i].k==stk[tot].k){
            if(vec[i].b>stk[tot].b)tot--;
            else continue;
        }
        while(tot>=2&&cross(vec[i],stk[tot])>cross(stk[tot],stk[tot-1]))tot--;
        stk[++tot]=vec[i];
    }
    for(ll i=head[u];~i;i=edge[i].nex){
        if(edge[i].v==father) continue;
        dfs2(edge[i].v,u);
    }
}

int main(){
    ll n;
    while(~scanf("%lld",&n)){
        ini(n);
        for(ll i=0;i<n-1;i++){
            ll u,v,w;
            scanf("%lld%lld%lld",&u,&v,&w);
            add_edge(u,v,w);
        }
        dfs1(1);
        dfs2(1);
        for(ll i=1;i<=n;i++) printf("%lld\n",ans[i]);
    }
}
