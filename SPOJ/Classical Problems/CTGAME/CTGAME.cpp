#include <bits/stdc++.h>
using namespace std;
int mat[1005][1005];
int calculatehist(int row,int m)
{
	stack<int> s;
	int i=0;
	int ans=0;
	while(i<m)
	{
		if(s.empty() || mat[row][i]>=mat[row][s.top()])
		s.push(i++);
		else
		{
			int x=s.top();
			s.pop();
			int area=mat[row][x]*(s.empty() ? i : i-s.top()-1);
			ans=max(ans,area);
		}
	}
	while(!s.empty())
	{
		int x=s.top();
		s.pop();
		int area=mat[row][x]*(s.empty() ? i : i-s.top()-1);
		ans=max(ans,area);
	}
	return ans;
}
int main()
{
	int t,n,m;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&m);
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			char ch;
			scanf(" %c",&ch);
			mat[i][j]=(ch=='F') ? 1 : 0;
		}
		int ans=calculatehist(0,m);
		for(int i=1;i<n;i++)
		{
			for(int j=0;j<m;j++)
			if(mat[i][j])
			mat[i][j]+=mat[i-1][j];
			ans=max(ans,calculatehist(i,m));
		}
		ans*=3;
		printf("%d\n",ans);
	}
	return 0;
}
