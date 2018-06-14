#include <bits/stdc++.h>
using namespace std;
#define INF 100000000
int marray[10001];
struct nodes
{
	int lsum;
	int rsum;
	int asum;
	int sum;
};
struct nodes st[4*10000];
void merge(nodes &t,nodes &l,nodes &r)
{
	t.sum=l.sum+r.sum;
	t.lsum=max(l.lsum,l.sum+r.lsum);
	t.rsum=max(r.rsum,r.sum+l.rsum);
	t.asum=max(max(l.asum,r.asum),l.rsum+r.lsum);
}
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		st[node].sum=st[node].lsum=st[node].rsum=st[node].asum=marray[l];
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	merge(st[node],st[2*node],st[2*node+1]);
}
nodes query(int node,int l,int r,int x,int y)
{	
	nodes c;
	c.lsum=c.rsum=c.sum=c.asum=0;
	if(l>r || l>y || r<x || x>y)
	{
		c.sum=0;
		c.lsum=c.rsum=c.asum=-INF;
		return c;
	}
	if(l>=x  && r<=y)
	return st[node];
	int mid=(l+r)>>1;
	nodes a=query(2*node,l,mid,x,y);
	nodes b=query(2*node+1,mid+1,r,x,y);
	merge(c,a,b);
	return c;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",marray+i);
		scanf("%d",&m);
		buildst(1,1,n);
		while(m--)
		{
			int ans,x1,x2,y1,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if(y1<x2)
			ans=query(1,1,n,x1,y1).rsum+query(1,1,n,y1+1,x2-1).sum+query(1,1,n,x2,y2).lsum;
			else
			{
				nodes a=query(1,1,n,x1,x2-1);
				nodes b=query(1,1,n,x2,y1);
				nodes c=query(1,1,n,y1+1,y2);
				nodes d=query(1,1,n,x2,y2);
				nodes e=query(1,1,n,x1,y1);
				ans=max(a.rsum+d.lsum,e.rsum+c.lsum);
				ans=max(b.asum,ans);
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
