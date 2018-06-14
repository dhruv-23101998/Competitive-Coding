#include <bits/stdc++.h>
using namespace std;
int marray[100001];
int nodes[3*100000];
int freql[3*100000];
int freqr[3*100000];
void buildst(int node,int l,int r)
{	
	if(l==r)
	{
		nodes[node]=1;
		freql[node]=1;
		freqr[node]=1;
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	if(freql[2*node]==(r-l+1)/2 && marray[mid]==marray[mid+1])
	freql[node]=freql[2*node]+freql[2*node+1];
	else
	freql[node]=freql[2*node];
	if(marray[mid]==marray[mid+1] && freqr[2*node+1]==(r-l+1)/2)
	freqr[node]=freqr[2*node+1]+freqr[2*node];
	else
	freqr[node]=freqr[2*node+1];
	nodes[node]=max(nodes[2*node],nodes[2*node+1]);
	if(marray[mid]==marray[mid+1])
	nodes[node]=max(nodes[node],freql[2*node+1]+freqr[2*node]);
}
int query(int node,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return 0;
	if(l>=x && r<=y)
	return nodes[node];
	int mid=(l+r)>>1;
	int ans1=query(2*node,l,mid,x,y);
	int ans2=query(2*node+1,mid+1,r,x,y);
	if(y<=mid)
	return ans1;
	if(x>=mid+1)
	return ans2;
	int ans=max(ans1,ans2);
	if(marray[mid]==marray[mid+1])
	ans=max(ans,min(mid-x+1,freqr[2*node])+min(y-mid,freql[2*node+1]));
	return ans;
}
int main()
{
	while(true)
	{
		int n,q;
		scanf("%d",&n);
		if(!n) return 0;
		scanf("%d",&q);
		for(int i=1;i<n+1;i++)
		scanf("%d",marray+i);
		buildst(1,1,131072);
		while(q--)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			printf("%d\n",query(1,1,131072,x,y));
		}
	}
	return 0;
}
