#include <bits/stdc++.h>
using namespace std;
int fee[100],fun[100];
int sfun[101][501],sfee[101][501];
int main()
{
	while(true)
	{
		int budget,n;
		scanf("%d %d",&budget,&n);
		if(budget==0 && n==0)
		break;
		for(int i=0;i<n;i++)
		scanf("%d %d",&fee[i],&fun[i]);
		for(int i=0;i<n+1;i++)
		for(int j=0;j<=budget;j++)
		{
			if(i==0 || j==0)
			{
				sfun[i][j]=0;
				sfee[i][j]=0;
			}
			else if(fee[i-1]>j)
			{
				sfun[i][j]=sfun[i-1][j];
				sfee[i][j]=sfee[i-1][j];
			}
			else
			{
				sfun[i][j]=max(sfun[i-1][j-fee[i-1]]+fun[i-1],sfun[i-1][j]);
				if(sfun[i][j]==sfun[i-1][j-fee[i-1]]+fun[i-1])
				sfee[i][j]=fee[i-1]+sfee[i-1][j-fee[i-1]];
				else
				sfee[i][j]=sfee[i-1][j];
			}
		}
		for(int i=0;i<n+1;i++)
		for(int j=0;j<=budget;j++)
		if(sfun[i][j]==sfun[n][budget])
		if(sfee[i][j]<sfee[n][budget])
		sfee[n][budget]=sfee[i][j];
		printf("%d %d\n",sfee[n][budget],sfun[n][budget]);
	}
	return 0;
}
