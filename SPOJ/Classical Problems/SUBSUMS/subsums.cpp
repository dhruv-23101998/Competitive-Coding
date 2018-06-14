#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int leftx[150000],rightx[150000];
int marray[35];
void subsets(int *x,int n,int k)
{
	for(int  i=0;i<(1<<n);i++)
	{
		long long int sum=0;
		for(int j=0;j<n;j++)
		if(i & (1<<j))
		sum+=marray[j+k];
		x[i]=sum;
	}
}
int main()
{
	int n,a,b;
	scanf("%d %d %d",&n,&a,&b);
	for(int i=0;i<n;i++)
	scanf("%d",marray+i);
	subsets(leftx,n/2,0);
	subsets(rightx,n-n/2,n/2);
	int szl=1<<(n/2);
	int szr=1<<(n-n/2);
	sort(rightx,rightx+szr);
	long long int answer=0;
	for(int i=0;i<szl;i++)
	{
		int x=lower_bound(rightx,rightx+szr,a-leftx[i])-rightx;
		int y=upper_bound(rightx,rightx+szr,b-leftx[i])-rightx;
		y--;
		answer+=(ll)(y-x+1);
	}
	printf("%lld\n",answer);
	return 0;
}
