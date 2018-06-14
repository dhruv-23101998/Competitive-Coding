#include <bits/stdc++.h>
using namespace std;
long long int marray[100001];
long long int st[3*100000];
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		st[node]=marray[l];
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	st[node]=st[2*node]+st[2*node+1];
}
void update(int node,int l,int r,int x,int y)
{
	if(st[node]==r-l+1)
	return ;
	if(l==r)
	{
		st[node]=(long long int)sqrt(st[node]);
		return ;
	}
	int mid=(l+r)>>1;
	if(y<=mid)
	update(2*node,l,mid,x,y);
	else if(x>=mid+1)
	update(2*node+1,mid+1,r,x,y);
	else
	{
		update(2*node,l,mid,x,mid);
		update(2*node+1,mid+1,r,mid+1,y);
	}
	st[node]=st[2*node]+st[2*node+1];
}
long long int query(int node,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return 0;
	if(l>=x && r<=y)
	return st[node];
	int mid=(l+r)>>1;
	return query(2*node,l,mid,x,y)+query(2*node+1,mid+1,r,x,y);
}
int main()
{
	int n,m,t=1;
	while(scanf("%d",&n)!=EOF)
	{
		printf("Case #%d: \n",t);
		t++;
		for(int i=1;i<=n;i++)
		scanf("%lld",marray+i);
		scanf("%d",&m);
		buildst(1,1,n);
		while(m--)
		{
			int type,x,y;
			scanf("%d %d %d",&type,&x,&y);
			if(x>y)
			swap(x,y);
			if(type==0)
			update(1,1,n,x,y);
			else
			printf("%lld\n",query(1,1,n,x,y));
		}
		printf("\n");
	}
	return 0;
}
