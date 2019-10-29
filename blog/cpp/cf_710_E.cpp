// #include<bits/stdc++.h>
// using namespace std;

// typedef long long ll;
// const ll maxn=2e7+7;
// ll d[maxn];

// struct node{
//     ll n,step;
//     bool operator <(const node&rhs) const{
//         return step>rhs.step;
//     }
// };

// int main(){
//     ll n,x,y;
//     scanf("%lld%lld%lld",&n,&x,&y);
//     for(ll i=0;i<=2*n;i++) d[i]=1e18;
//     priority_queue<node> q;
//     d[1]=x;
//     q.push(node{1,x});

//     ll ans=x*n;
//     while(true){
//         node top=q.top(); q.pop();
//         ans=min(ans,d[]+);
//         if(top.n==n) break;
//         else{
//             if(top.n-1>=1&&d[top.n]+x<d[top.n-1]){
//                 d[top.n-1]=d[top.n]+x;
//                 q.push(node{top.n-1,d[top.n]+x});
//             }
//             if(top.n+1<=2*n&&d[top.n]+x<d[top.n+1]){
//                 d[top.n+1]=d[top.n]+x;
//                 q.push(node{top.n+1,d[top.n]+x});
//             }
//             if(top.n*2<=2*n&&d[top.n]+y<d[top.n*2]){
//                 d[top.n*2]=d[top.n]+y;
//                 q.push(node{top.n*2,d[top.n]+y});
//             }
//         }
//     }
//     cout<<ans<<endl;
// }



#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=2e7+7;
ll dp[maxn];

int main(){
    ll n,x,y;
    scanf("%lld%lld%lld",&n,&x,&y);
    for(int i=1;i<=n;i++){
        if(i&1){//odd
            dp[i]=min(dp[i-1]+x,dp[(i+1)/2]+y+x);
        }
        else{
            dp[i]=min(dp[i-1]+x,dp[i/2]+y);
        }
    }
    cout<<dp[n]<<endl;
}













