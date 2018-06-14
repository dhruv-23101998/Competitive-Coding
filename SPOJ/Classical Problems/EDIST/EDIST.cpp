#include <bits/stdc++.h>
using namespace std;
int dp[5005][5005];
char s1[5005],s2[5005];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf(" %s",s1);
		scanf(" %s",s2);
		int n=strlen(s1);
		int m=strlen(s2);
		for(int i=0;i<=m;i++)
		dp[0][i]=i;
		for(int i=0;i<=n;i++)
		dp[i][0]=i;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(s1[i-1]==s2[j-1])
			dp[i][j]=dp[i-1][j-1];
			else
			dp[i][j]=1+min(dp[i][j-1],min(dp[i-1][j-1],dp[i-1][j]));
		}
		printf("%d\n",dp[n][m]);
	}
	return 0;
}
