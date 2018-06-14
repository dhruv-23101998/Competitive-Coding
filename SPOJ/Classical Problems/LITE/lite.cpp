#include <bits/stdc++.h>
using namespace std;
int nodes[3*100000];
int lazy[3*100000];
void update(int node,int l,int r,int x,int y)
{
	if(lazy[node]!=0)
	{
		nodes[node]=(r-l+1)-nodes[node];
		if(l!=r)
		{
			lazy[2*node]=(lazy[2*node]+lazy[node])%2;
			lazy[2*node+1]=(lazy[2*node+1]+lazy[node])%2;
		}
		lazy[node]=0;
	}
	if(l>r || l>y || r<x)
	return ;
	if(l>=x && r<=y)
	{
		nodes[node]=(r-l+1)-nodes[node];
		if(l!=r)
		{
			lazy[2*node]=(lazy[2*node]+1)%2;
			lazy[2*node+1]=(lazy[2*node+1]+1)%2;
		}
		return ;
	}
	int mid=(l+r)>>1;
	update(2*node,l,mid,x,y);
	update(2*node+1,mid+1,r,x,y);
	nodes[node]=nodes[2*node]+nodes[2*node+1];
}
int query(int node,int l,int r,int x,int y)
{
	if(lazy[node]!=0)
	{
		nodes[node]=(r-l+1)-nodes[node];
		if(l!=r)
		{
			lazy[2*node]=(lazy[2*node]+lazy[node])%2;
			lazy[2*node+1]=(lazy[2*node+1]+lazy[node])%2;
		}
		lazy[node]=0;
	}
	if(l>r || l>y || r<x)
	return 0;
	if(l>=x && r<=y)
	return nodes[node];
	int mid=(l+r)>>1;
	return query(2*node,l,mid,x,y)+query(2*node+1,mid+1,r,x,y);
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	memset(nodes,0,sizeof(nodes));
	memset(lazy,0,sizeof(lazy));
	while(m--)
	{
		int type,si,ei;
		scanf("%d %d %d",&type,&si,&ei);
		if(type==0)
		update(1,1,n,si,ei);
		else
		printf("%d\n",query(1,1,n,si,ei));
	}
	return 0;
}
