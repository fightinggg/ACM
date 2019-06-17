#include<bits/stdc++.h>
using namespace std;

//
//   | sin(px/qpi) |
//
//   (px/q)%1 -> 1/2
//
//   (2px)%(2q) -> q



typedef long long ll;
const ll maxn=3e4+55;
struct node{
    ll x,gx;
    bool operator<(const node&rhs) const {
        if(gx!=rhs.gx) return gx<rhs.gx;
        else return x<gx;
    }
}g[maxn];

ll get(ll p,ll q,ll x){
    return 2*p*x%(2*q);
}
ll dis(ll p,ll q,ll x){
    return abs(get(p,q,x)-q);
}
void update(ll&ans,ll cur,ll p,ll q){
    if(ans==-1) ans=cur;
    else if(dis(p,q,cur)<dis(p,q,ans)) ans=cur;
    else if(dis(p,q,cur)==dis(p,q,ans)) ans=min(ans,cur);
}
int main(){
    ll n;
    cin>>n;
    while(n--){
        ll a,b,p,q;
        cin>>a>>b>>p>>q;
        ll k=10000;
        map<int,int> mp;
        for(ll i=k-1;i>=0;i--) mp[get(p,q,i)]=i;//g[i]=node{i,get(p,q,i)};
        ll sz=0;
        for(auto x:mp) g[sz++]=node{x.second,x.first};

        ll bg=a,ans=-1;
        while(bg+k-1<=b){
            ll base=get(p,q,bg), idx;
            if(base<=q) idx=lower_bound(g,g+sz,node{-1,q-base})-g;
            else idx=lower_bound(g,g+sz,node{-1,3*q-base})-g;

            update(ans,bg+g[idx%sz].x,p,q);
            update(ans,bg+g[(idx-1+sz)%sz].x,p,q);
            bg+=k;
        }
        if(bg<=b){
            for(ll i=bg;i<=b;i++) update(ans,i,p,q);
        }
        cout<<ans<<endl;
    }
}