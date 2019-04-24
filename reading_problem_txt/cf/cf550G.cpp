#include<iostream>
using namespace std;

struct RQM
{
	static const int MAXN = 1e5+10;
    int mm[MAXN],rmq[MAXN][20],num[MAXN];
    void st(int l,int r){
        mm[0]=-1;
        for (int i = 0; i < MAXN; ++i)
        {
            mm[i]=((i&i-1)==0)?mm[i-1]+1:mm[i-1];
        }
        for (int i = l; i < r; ++i)
        {
            rmq[i][0]=num[i];
        }
        for (int j = 1; j <=mm[r-l+1]; ++j)
        {
            for(int i = 1;i+(1<<j)-1<=r; ++i)
            {
                //rmq[i][j]=max(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
                if(num[rmq[i][j-1]]<num[rmq[i+(1<<(j-1))][j-1]]){
                    rmq[i][j]=rmq[i+(1<<(j-1))][j-1];
                }
                else{
                    rmq[i][j]=rmq[i][j-1];
                }
            }
        }
    }

    int query(int l,int r){
        int k=mm[r-l+1];
        if(num[rmq[l][k]]<num[rmq[r-(1<<k)+1][k]]){
            return rmq[r-(1<<k)+1][k];
        }
        else{
            return rmq[l][k];
        }
        //return max(rmq[l][k],rmq[r-(1<<k)+1][k]);
    }
}rmq;

const int MAXN=1e5+5;

int ans[MAXN];
int left[MAXN],right[MAXN];


bool checkleft(int l,int r){
    return left[l]>=r;
}

bool checkright(int l,int r){
    return right[r]<=l;
}



bool dfs(int l,int r){
    if(l<r)return true;

    int idx=rmq.query(l,r);
    bool checkl=checkleft(l,idx-1);
    bool checkr=checkright(idx+1,r);
    if(checkl&&checkr){
        for(int i=l;i<=idx;i++){
            ans[i]=0;
        }
        for(int i=idx+1;i<=r;i++){
            ans[i]=1;
        }
        return true;
    }
    else if(checkl){
        for(int i=l;i<=idx;i++){
            ans[i]=0;
        }
        return dfs(idx+1,r);
    }
    else if(checkr){
        for(int i=idx;i<=r;i++){
            ans[i]=1;
        }
        return dfs(l,idx-1);
    }
    else{
        return false;
    }
}

int num[MAXN];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",num+i);
    }
    memcpy(num,rmq.num,sizeof(num));
    rmq.ini(1,n);

    left[n]=n;
    for(int i=n-1;i>=1;i--){
        if(num[i]<num[i+1])left[i]=left[i+1];
        else left[i]=i;
    }

    right[1]=1;
    for(int i=2;i<=n;i++){
        if(num[i-1]>num[i])right[i]=right[i-1];
        else right[i]=i;
    }

    if(dfs(1,n)){
        puts("YES");
        for (int i = 1; i <= n; ++i)
        {
           printf("%d ", ans[i]);
        }
    }
    else{
        puts("NO");
    }
}









// 9 
// 5 1 3 6 8 2 9 0 10
// 
// .......*..........

// 1 可作为单调增的最后一个 ,则右边全体单调减
// 2 可作为单调减的第一个，  则左边全体单调增






