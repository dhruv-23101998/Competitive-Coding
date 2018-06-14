#include <bits/stdc++.h>
using namespace std;
#define INF 1000000
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
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			scanf(" %1c",&grid[i][j]);
			dp1[i][j]=dp2[i][j]=INF;
			}
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		if(grid[i][j]!='#')
		{
			if((grid[i+1][j]=='#' && grid[i][j+1]=='#') || (j==m-1 && (i==n-1 || grid[i+1][j]=='#')) || (i==n-1 && (j==m-1 || grid[i][j+1]=='#')))
			dp1[i][j]=(grid[i][j]=='T') ? 1 : 0;
			if((j==0 && (i==n-1 || grid[i+1][j]=='#')) || (grid[i+1][j]=='#' && grid[i][j-1]=='#') || (i==n-1 && (j==0 || grid[i][j-1]=='#')))
			dp2[i][j]=(grid[i][j]=='T') ? 1 : 0;
		}
		else
		dp1[i][j]=dp2[i][j]=0;
		for(int i=n-1;i>=0;i--)
		{
			for(int j=0;j<m;j++)
			if(dp2[i][j]==INF)
			{
				dp2[i][j]=(j==0 ? 0 : dp2[i][j-1])+((grid[i][j]=='T') ? 1 : 0);
				dp2[i][j]=max(dp2[i][j],(i<n-1 ? dp1[i+1][j] : 0)+((grid[i][j]=='T') ? 1 : 0));
			}
			for(int j=m-1;j>=0;j--)
			if(dp1[i][j]==INF)
			{
				dp1[i][j]=(j<m-1 ? dp1[i][j+1] : 0)+((grid[i][j]=='T') ? 1 : 0);
				dp1[i][j]=max(dp1[i][j],(i<n-1 ? dp2[i+1][j] : 0)+((grid[i][j]=='T') ? 1 : 0));
			}
		}
		printf("%d\n",dp1[0][0]);
	}
	return 0;
}
