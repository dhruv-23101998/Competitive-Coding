#include <bits/stdc++.h>
using namespace std;
long long int nodes[3*100000];
long long int lazy[3*100000];
void update(int node,int l,int r,int x,int y,int value)
{
	if(lazy[node]!=0)
	{
		nodes[node]+=(long long int)(r-l+1)*lazy[node];
		if(l!=r)
		{
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(l>r || l>y || r<x)
	return ;
	if(l>=x && r<=y)
	{
		nodes[node]+=(long long int)(r-l+1)*(long long int)value;
		if(l!=r)
		{
			lazy[2*node]+=(long long int)value;
			lazy[2*node+1]+=(long long int)value;
		}
		return ;
	}
	int mid=(l+r)>>1;
	update(2*node,l,mid,x,y,value);
	update(2*node+1,mid+1,r,x,y,value);
	nodes[node]=nodes[2*node]+nodes[2*node+1];
}
long long int query(int node,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return  0;
	if(lazy[node]!=0)
	{
		nodes[node]+=(long long int)(r-l+1)*lazy[node];
		if(l!=r)
		{
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(l>=x && r<=y)
	return nodes[node];
	int mid=(l+r)>>1;
	return query(2*node,l,mid,x,y)+query(2*node+1,mid+1,r,x,y);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,c;
		scanf("%d %d",&n,&c);
		memset(nodes,0,sizeof(nodes));
		memset(lazy,0,sizeof(lazy));
		while(c--)
		{
			int type;
			scanf("%d",&type);
			if(type==0)
			{
				int p,q,v;
				scanf("%d %d %d",&p,&q,&v);
				update(1,1,n,p,q,v);
			}
			else
			{
				int p,q;
				scanf("%d %d",&p,&q);
				printf("%lld\n",query(1,1,n,p,q));
			}
		}
	}
	return 0;
}
