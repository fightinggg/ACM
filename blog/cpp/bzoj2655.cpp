#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll mod;

ll qpow(ll a,ll b,ll mod){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}

//  (mod%i)=== -mod/i*i
const int maxn=1200;
ll fac_inv[maxn]={1,1};
void inv_ini(){
    for(ll i=0,fac=1;i<maxn;i++,fac=fac*i%mod) {
        fac_inv[i]=qpow(fac,mod-2,mod);
    }
}

ll prepre[maxn],suf[maxn],*pre=prepre+1;
ll getval(ll *y,ll n,ll x){// O(n) n次多项式有n+1项 y[0]...y[n] -> y[x]
    pre[-1]=suf[n+1]=1;
    for(int i=0;i<=n;i++) pre[i]=pre[i-1]*(x-i+mod)%mod;
    for(int i=n;i>=0;i--) suf[i]=suf[i+1]*(i-x+mod)%mod;
    ll ret=0;
    for(int i=0;i<=n;i++) {
        ll up=pre[i-1]*suf[i+1]%mod;
        ll down=fac_inv[i]*fac_inv[n-i]%mod;
        ret=(ret+y[i]*up%mod*down)%mod;
    }
    return ret;
}

// f(i,j)-> 前i个元素中最大值为j的方案的权的和
// f(i,j)=f(i-1,j-1)*i*j+f(i,j-1)
// 用数学归纳法证明f(i,j)关于j是一个最高次为2*i的多项式
ll f[maxn][maxn*3];
int main(){
    ll n,a;
    while(~scanf("%lld%lld%lld",&a,&n,&mod)){
        inv_ini();
        for(ll j=1;j<=3*n;j++) f[1][j]=(f[1][j-1]+j)%mod;
        for(ll i=2;i<=n;i++){
            for(ll j=i;j<=3*n;j++){
                f[i][j]=(i*j*f[i-1][j-1]+f[i][j-1])%mod;
            }
        }
        //we know f(n) f(n+1) ... f(3n)
        //if g(i)=f(i+n)
        // than f(a)=g(a-n)
        printf("%lld\n",getval(f[n]+n,2*n,(a-n+mod)%mod));
    }
}