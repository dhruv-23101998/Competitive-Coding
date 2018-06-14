#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int marray[100001];
long long int sqtree[3*100000];
int sumtree[3*100000];
int lazyplus[3*100000],lazyset[3*100000];
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		sqtree[node]=marray[l]*marray[l];
		sumtree[node]=marray[l];
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	sumtree[node]=sumtree[2*node]+sumtree[2*node+1];
	sqtree[node]=sqtree[2*node]+sqtree[2*node+1];
}
void propagatelazy(int node,int l,int r)
{
	if(lazyset[node]!=2000)
	{
		sqtree[node]=(ll)(r-l+1)*(ll)lazyset[node]*(ll)lazyset[node];
		sumtree[node]=(r-l+1)*lazyset[node];
		if(l!=r)
		{
			lazyset[2*node]=lazyset[node];
			lazyset[2*node+1]=lazyset[node];
		}
		lazyset[node]=2000;
	}
	if(lazyplus[node]!=0)
	{
		sqtree[node]+=(ll)(r-l+1)*(ll)lazyplus[node]*(ll)lazyplus[node]+(ll)2*(ll)lazyplus[node]*(ll)sumtree[node];
		sumtree[node]+=(r-l+1)*lazyplus[node];
		if(l!=r)
		{
			lazyplus[2*node]+=lazyplus[node];
			lazyplus[2*node+1]+=lazyplus[node];
		}
		lazyplus[node]=0;
	}
}
void update1(int node,int l,int r,int x,int y,int value)
{
	propagatelazy(node,l,r);	
	if(l>r || l>y || x>r)
	return ;
	if(l>=x && r<=y)
	{
		sqtree[node]+=(ll)(r-l+1)*(ll)value*(ll)value+(ll)2*(ll)value*(ll)sumtree[node];
		sumtree[node]+=(r-l+1)*value;
		if(l!=r)
		{	
			lazyplus[2*node]+=value;
			lazyplus[2*node+1]+=value;
		}
		return ;
	}
	int mid=(l+r)>>1;
	update1(2*node,l,mid,x,y,value);
	update1(2*node+1,mid+1,r,x,y,value);
	sqtree[node]=sqtree[2*node]+sqtree[2*node+1];
	sumtree[node]=sumtree[2*node]+sumtree[2*node+1];
}
void update2(int node,int l,int r,int x,int y,int value)
{
	propagatelazy(node,l,r);
	if(l>r || l>y || x>r)
	return ;
	if(l>=x && r<=y)
	{
		sqtree[node]=(ll)(r-l+1)*(ll)value*(ll)value;
		sumtree[node]=(r-l+1)*value;
		if(l!=r)
		{
			lazyset[2*node]=value;
			lazyset[2*node+1]=value;
			lazyplus[2*node]=lazyplus[2*node+1]=0;
		}
		return ;
	}
	int mid=(l+r)>>1;
	update2(2*node,l,mid,x,y,value);
	update2(2*node+1,mid+1,r,x,y,value);
	sqtree[node]=sqtree[2*node]+sqtree[2*node+1];
	sumtree[node]=sumtree[2*node]+sumtree[2*node+1];
}
long long int query(int node,int l,int r,int x,int y)
{
	propagatelazy(node,l,r);
	if(l>r || l>y || x>r)
	return 0;
	if(l>=x && r<=y)
	return sqtree[node];
	int mid=(l+r)>>1;
	return query(2*node,l,mid,x,y)+query(2*node+1,mid+1,r,x,y);
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int ti=1;ti<=t;ti++)
	{
		printf("Case %d:\n",ti);
		int n,q;
		scanf("%d %d",&n,&q);
		for(int i=1;i<=n;i++)
		scanf("%d",marray+i);
		memset(lazyplus,0,sizeof(lazyplus));
		for(int i=0;i<3*100000;i++)
		lazyset[i]=2000;
		buildst(1,1,n);
		while(q--)
		{
			int type,l,r,x;
			scanf("%d %d %d",&type,&l,&r);
			if(type==0)
			{
				scanf("%d",&x);
				update2(1,1,n,l,r,x);
			}
			else if(type==1)
			{
				scanf("%d",&x);
				update1(1,1,n,l,r,x);
			}
			else
			printf("%lld\n",query(1,1,n,l,r));
		}
	}
	return 0;
}
