#include <bits/stdc++.h>
using namespace std;
int marray[30001],n,t;
struct query
{
	int l;
	int r;
	int indx;
};
int bsize;
struct query q[200001];
bool compare(query x,query y)
{
	if(x.l/bsize!=y.l/bsize)
	return (x.l/bsize<y.l/bsize);
	return x.r<y.r;
}
int countx[1000001];
int main()
{
	scanf("%d",&n);
	bsize=sqrt(n);
	for(int i=1;i<n+1;i++)
	scanf("%d",marray+i);
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		scanf("%d %d",&q[i].l,&q[i].r);
		q[i].indx=i;
	}
	sort(q,q+t,compare);
	int currentl=0,currentr=0;
	int ans=0,answer[t];
	memset(countx,0,sizeof(countx));
	for(int i=0;i<t;i++)
	{
		int x=q[i].l;
		int y=q[i].r;
		while(currentl<x)
		{
			countx[marray[currentl]]--;
			if(countx[marray[currentl]]==0)
			ans--;
			currentl++;
		}
		while(currentl>x)
		{
			countx[marray[currentl-1]]++;
			if(countx[marray[currentl-1]]==1)
			ans++;
			currentl--;
		}
		while(currentr<=y)
		{	
			countx[marray[currentr]]++;
			if(countx[marray[currentr]]==1)
			ans++;
			currentr++;
		}
		while(currentr>y+1)
		{
			countx[marray[currentr-1]]--;
			if(countx[marray[currentr-1]]==0)
			ans--;
			currentr--;
		}
		answer[q[i].indx]=ans;
	}
	for(int  i=0;i<t;i++)
	printf("%d\n",answer[i]);
	return 0;
}
