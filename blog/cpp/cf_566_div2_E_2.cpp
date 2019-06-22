#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int LEN=3;

void sarray_cpy(int a[][LEN],int b[][LEN],int n){
    for(int i=0;i<n;i++){// a/b可以为同一个数组
        for(int j=0;j<n;j++) b[i][j]=a[i][j];
    }
}

void sarray_mul(int a[][LEN],int b[][LEN],int ret[][LEN],int n,int mod){
    static int c[LEN][LEN];// a/b/ret可以为同一个数组
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++){
            c[i][j]=0;
            for(int k=0;k<n;k++){
                c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
            }
        }
    }
    sarray_cpy(c,ret,n);
}

void sarray_qpow(int aa[][LEN],ll b,int ret[][LEN],int n,int mod){
    static int a[LEN][LEN];// aa ret可以为同一个数组
    sarray_cpy(aa,a,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) ret[i][j]=0;
        ret[i][i]=1;
    }
    while(b){
        if(b&1) sarray_mul(ret,a,ret,n,mod);
        sarray_mul(a,a,a,n,mod);
        b>>=1;
    }
}

void sarray_add(int a[][LEN],int b[][LEN],int c[][LEN],int n,int mod){
    for(int i=0;i<n;i++){// a,b,c可以为同一个数组
        for(int j=0;j<n;j++){
            c[i][j]=(a[i][j]+b[i][j])%mod;
        }
    }
}

// a^0 a^1 a^2 a^3 ... a^b
void sarray_sum(int a[][LEN],ll b,int ret[][LEN],int n,int mod){
    static int tmp[LEN][LEN];
    if(b==0) sarray_qpow(a,b,ret,n,mod);
    else{
        ll mid=(b-1)>>1;
        sarray_sum(a,mid,ret,n,mod);
        sarray_qpow(a,mid+1,tmp,n,mod);
        for(int i=0;i<n;i++) tmp[i][i]=(tmp[i][i]+1)%mod;
        sarray_mul(ret,tmp,ret,n,mod);
        if((b&1)==0) {
            sarray_mul(ret,a,ret,n,mod);
            for(int i=0;i<n;i++) ret[i][i]=(ret[i][i]+1)%mod;
        }
    }
}

int qpow(int a,int b,int mod){
    int ret=1;
    while(b){
        if(b&1)ret=1ll*ret*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ret;
}

// a^x === b   x=lg(a,b)
int bsgs_lg(int a,int b,int mod){
    map<int,int>mp;
    int sqr=sqrt(mod-1)+1;
    for(int i=0;i<sqr;i++) mp[qpow(a,i,mod)]=i; // baby step
    for(int i=0;i<mod-1;i+=sqr){ // giant step
        int tp=1ll*b*qpow(a,mod-1-i,mod)%mod; // a^(-i)
        if(mp.find(tp)!=mp.end()) return i+mp[tp];
    }
    return -1;// error
}

int main(){
    const int mod=1e9+7;
    ll n;
    int f1,f2,f3,c;
    cin>>n>>f1>>f2>>f3>>c;
    int g1=1ll*f1*c%mod;
    int g2=1ll*f2*c%mod*c%mod;
    int g3=1ll*f3*c%mod*c%mod*c%mod;

    g1=bsgs_lg(5,g1,mod);
    g2=bsgs_lg(5,g2,mod);
    g3=bsgs_lg(5,g3,mod);
    // cout<<g1<<endl<<g2<<endl<<g3<<endl;

    int orn[LEN][LEN]={
            g3,0,0,
            g2,0,0,
            g1,0,0
    };

    int trans[LEN][LEN]={
            1,1,1,
            1,0,0,
            0,1,0
    };

    int ans[LEN][LEN],t;
    if(n==1) t=g1;
    else if(n==2) t=g2;
    else if(n==3) t=g3;
    else {
        int ans1[LEN][LEN];
        int ans2[LEN][LEN];
        sarray_sum(trans,n-3,ans1,3,mod-1);
        sarray_mul(ans1,orn,ans1,3,mod-1);
        sarray_sum(trans,n-4,ans2,3,mod-1);
        sarray_mul(ans2,orn,ans2,3,mod-1);
        t=(ans1[0][0]-ans2[0][0]+mod-1)%(mod-1);

        // for(int i=0;i<3;i++)for(int j=0;j<3;j++)ans[i][j]=(ans1[i][j]-ans2[i][j]+mod)%mod;
        // sarray_mul(ans,orn,ans,3,mod-1);
        // t=ans[0][0];
    }
    int gn=qpow(5,t,mod);
    int inv=qpow(c,mod-1-n%(mod-1),mod);
    cout<<1ll*gn*inv%mod<<endl;

}

