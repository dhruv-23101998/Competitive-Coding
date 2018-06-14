#include <bits/stdc++.h>
using namespace std;
int dp1[202][202],dp2[201][201];
char grid[201][201];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		scanf(" %1c",&grid[i][j]);
		memset(dp1,0,sizeof(dp1));
		memset(dp2,0,sizeof(dp2));
		for(int i=n;i>=1;i--)
		{
			for(int j=1;j<=m;j++)
			if(grid[i][j]!='#')
			{
				dp2[i][j]=dp2[i][j-1]+((grid[i][j]=='T') ? 1 : 0);
				dp2[i][j]=max(dp2[i][j],dp1[i+1][j]+((grid[i][j]=='T') ? 1 : 0));
			}
			for(int j=m;j>=1;j--)
			if(grid[i][j]!='#')
			{
				dp1[i][j]=dp1[i][j+1]+((grid[i][j]=='T') ? 1 : 0);
				dp1[i][j]=max(dp1[i][j],dp2[i+1][j]+((grid[i][j]=='T') ? 1 : 0));
			}
		}
		printf("%d\n",dp1[1][1]);
	}
	return 0;
}
