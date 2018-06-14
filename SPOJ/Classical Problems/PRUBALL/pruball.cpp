#include <bits/stdc++.h>
using namespace std;
int dp[1005][1005];
int main()
{
	int t,n,k,d;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&d,&n,&k);
		for(int i=0;i<=k;i++)
		dp[1][i]=i;
		for(int i=0;i<=n;i++)
		dp[i][1]=1;
		for(int i=0;i<=n;i++)
		dp[i][0]=0;
		for(int i=2;i<=n;i++)
		for(int j=2;j<=k;j++)
		{
			dp[i][j]=1e9;
			for(int l=1;l<=j;l++)
			dp[i][j]=min(dp[i][j],1+max(dp[i-1][l-1],dp[i][j-l]));
		}
		printf("%d %d\n",d,dp[n][k]);
	}
	return 0;
}
