#include <bits/stdc++.h>
using namespace std;
int a[21],b[21];
unsigned long long dp[21][101];
int main()
{
	int n,m;
	while(true)
	{
		scanf("%d %d",&m,&n);
		if(n==0 && m==0)
		break;
		for(int i=1;i<=m;i++)
		scanf("%d %d",a+i,b+i);
		memset(dp,0,sizeof(dp));
		for(int i=a[1];i<=b[1];i++)
		dp[1][i]=1;
		for(int i=2;i<=m;i++)
		for(int j=0;j<=n;j++)
		for(int k=a[i];k<=b[i];k++)
		dp[i][j]+=((j>=k) ? dp[i-1][j-k] : 0);
		printf("%lld\n",dp[m][n]);
	}
	return 0;
}
