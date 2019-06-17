#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod=1e9+7;


struct Sarray{
    static const ll mod=1e9+6;
    static const ll LEN=3;
    ll len,data[LEN][LEN];

    Sarray(ll len,ll flag):len(len){
        for(ll i=0;i<len;i++){
            for(ll j=0;j<len;j++)data[i][j]=0;
            data[i][i]=flag;
        }
    }

    Sarray operator *(const Sarray&a){
        Sarray tem(a.len,0);
        for(ll i=0;i<len;i++){
            for(ll j=0;j<len;j++){
                for(ll k=0;k<len;k++){
                    tem.data[i][j]=(tem.data[i][j]+data[i][k]*a.data[k][j])%mod;
                }
            }
        }
        return tem;
    }

    Sarray operator +(const Sarray&a){
        Sarray tem(a.len,0);
        for(ll i=0;i<len;i++){
            for(ll j=0;j<len;j++){
                tem.data[i][j]=(data[i][j]+a.data[i][j])%mod;
            }
        }
        return tem;
    }
};

Sarray qpow(Sarray a,ll b){//会更改a，不能按引用传递
    Sarray tem(a.len,1);
    while(b){
        if(b&1)tem=a*tem;
        a=a*a;
        b>>=1;
    }
    return tem;
}

ll qpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}


ll oria[3][3]={
        0,0,0,
        0,0,0,
        1,0,0
};

ll orib[3][3]={
        0,0,0,
        1,0,0,
        0,0,0
};

ll oric[3][3]={
        1,0,0,
        0,0,0,
        0,0,0
};

ll transs[3][3]={
        1,1,1,
        1,0,0,
        0,1,0
};

ll get(ll n,ll beg[3][3]){
    Sarray orn(3,1),trans(3,1);
    memcpy(orn.data,beg,sizeof(orn.data));
    memcpy(trans.data,transs,sizeof(trans.data));
    if(n==1) return beg[2][0];
    if(n==2) return beg[1][0];
    return (qpow(trans,n-3)*orn).data[0][0];
}

int  main(){
    ll n,f1,f2,f3,c;
    cin>>n>>f1>>f2>>f3>>c;
    ll g1=f1*c%mod;
    ll g2=f2*c%mod*c%mod;
    ll g3=f3*c%mod*c%mod*c%mod;

    ll A=get(n,oria);
    ll B=get(n,orib);
    ll C=get(n,oric);

    ll gn=qpow(g1,A)*qpow(g2,B)%mod*qpow(g3,C)%mod;
    ll t=qpow(c,n);
    cout<<gn*qpow(t,mod-2)%mod<<endl;

}
