#include <bits/stdc++.h>
using namespace std;
#define INF 0x7fffffff
long long int marray[50001];
long long int nodes[3*50000];
long long int lsum[3*50000];
long long int rsum[3*50000];
long long int asum[3*50000];
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		nodes[node]=marray[l];
		lsum[node]=marray[l];
		rsum[node]=marray[l];
		asum[node]=marray[l];
		return ;
	}
	else if(l<r)
	{
		int mid=(l+r)/2;
		buildst(2*node,l,mid);
		buildst(2*node+1,mid+1,r);
		nodes[node]=nodes[2*node]+nodes[2*node+1];
		lsum[node]=max(lsum[2*node],nodes[2*node]+lsum[2*node+1]);
		rsum[node]=max(rsum[2*node+1],nodes[2*node+1]+rsum[2*node]);
		asum[node]=max(lsum[2*node+1]+rsum[2*node],max(asum[2*node],asum[2*node+1]));
	}
}
void update(int node,int l,int r,int pos,int value)
{
	if(l==r)
	{
		nodes[node]=value;
		lsum[node]=value;
		rsum[node]=value;
		asum[node]=value;
		return ;
	}
	if(l>r)
	return ;
	int mid=(l+r)/2;
	if(pos<=mid)
	update(2*node,l,mid,pos,value);
	else
	update(2*node+1,mid+1,r,pos,value);
	nodes[node]=nodes[2*node]+nodes[2*node+1];
	lsum[node]=max(lsum[2*node],nodes[2*node]+lsum[2*node+1]);
	rsum[node]=max(rsum[2*node+1],nodes[2*node+1]+rsum[2*node]);
	asum[node]=max(lsum[2*node+1]+rsum[2*node],max(asum[2*node],asum[2*node+1]));
}
void query(int node,int l,int r,int x,int y,vector<int> &v)
{
	if(l>=x && r<=y)
	{
		v.push_back(node);
		return ;
	}
	if(l>r || l>y || r<x)
	return ;
	int mid=(l+r)/2;
	query(2*node,l,mid,x,y,v);
	query(2*node+1,mid+1,r,x,y,v);
}
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<n+1;i++)
	scanf("%lld",&marray[i]);
	memset(nodes,0,sizeof(nodes));
	memset(lsum,0,sizeof(lsum));
	memset(rsum,0,sizeof(rsum));
	memset(asum,0,sizeof(asum));
	buildst(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		int type;
		scanf("%d",&type);
		if(type==1)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			vector<int> v;
			query(1,1,n,x,y,v);
			long long int ans=-INF;
			long long int local=-INF;
			for(int i=0;i<v.size();i++)
			{
				ans=max(ans,asum[v[i]]);
				ans=max(ans,local+lsum[v[i]]);
				local=max(local+nodes[v[i]],rsum[v[i]]);
			}
			printf("%lld\n",ans);
		}
		else
		{
			int x,y;
			scanf("%d %d",&x,&y);
			update(1,1,n,x,y);
		}
	}
	return 0;
}
