#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn=3e3+333;
const int maxm=maxn; 
ll dp[maxm][maxn],sum[maxn],q[maxn];

int main(){
	// freopen("/Users/s/Desktop/in.txt","r",stdin);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%lld",sum+i);
	for(int i=1;i<=n;i++)sum[i]+=sum[i-1];
	for(int j=1;j<=n;j++)dp[1][j]=sum[j]*sum[j];

	// for(int j=1;j<=n;j++)printf("(%lld,%lld)",2*sum[j],dp[1][j]+sum[j]*sum[j]);

	for(int i=2;i<=m;i++){
		int l=0,r=0;
		dp[i][i]=dp[i-1][i-1]+(sum[i]-sum[i-1])*((sum[i]-sum[i-1]));
		// cout<<endl;
		q[l]=i-1;
		q[++r]=i;//两个是因为，i-1的有dp[i-1][i-1]和dp[i-1][i]两个合法状态
		for(int j=i+1;j<=n;j++){//下凹曲线
			while(true){
				if(l==r)break;

				int u=q[l+1];
				int v=q[l];
				ll yu=dp[i-1][u]+sum[u]*sum[u];
				ll yv=dp[i-1][v]+sum[v]*sum[v];
				ll xu=2*sum[u];
				ll xv=2*sum[v];
				if(yu-yv>(xu-xv)*sum[j])break;
				// else cout<<(yu-yv)<<" "<<(xu-xv)*sum[j]<<endl;
				l++;
			}
			// cout<<"l:"<<q[l]<<endl;

			dp[i][j]=dp[i-1][q[l]]+(sum[j]-sum[q[l]])*(sum[j]-sum[q[l]]);
			while(true){
				if(l==r)break;

				int a=q[r-1];
				int b=q[r];
				int c=j;
				ll ya=dp[i-1][a]+sum[a]*sum[a];
				ll yb=dp[i-1][b]+sum[b]*sum[b];
				ll yc=dp[i-1][c]+sum[c]*sum[c];
				ll xa=2*sum[a];
				ll xb=2*sum[b];
				ll xc=2*sum[c];
				if((yc-yb)*(xb-xa)>(yb-ya)*(xc-xb))break;
				r--;
			}
			q[++r]=j;
		}
	}
	// for(int i=1;i<=m;i++){
	// 	for(int j=1;j<=n;j++){//下凹曲线
	// 		cout<<dp[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	cout<<dp[m][n]*m-sum[n]*sum[n]<<endl;
} 










