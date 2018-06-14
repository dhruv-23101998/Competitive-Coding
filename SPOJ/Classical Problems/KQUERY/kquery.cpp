#include <bits/stdc++.h>
using namespace std;
int nodes[3*30000];
struct myarray
{
	int data;
	char type;
	int l;
	int r;
	int indx;
};
struct myarray marray[230001];
bool compare(myarray x,myarray y)
{
	if(x.data>y.data)
	return true;
	else if(x.data<y.data)
	return false;
	else
	return (x.type=='0');
}
void update(int node,int l,int r,int pos)
{
	if(l==r)
	{
		nodes[node]=1;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	update(2*node,l,mid,pos);
	else
	update(2*node+1,mid+1,r,pos);
	nodes[node]=nodes[2*node]+nodes[2*node+1];
}
int query(int node,int l,int r,int x,int y)
{
	if(l>=x && r<=y)
	return nodes[node];
	if(l>r || l>y || r<x)
	return 0;
	int mid=(l+r)>>1;
	return query(2*node,l,mid,x,y)+query(2*node+1,mid+1,r,x,y);
}
int main()
{
	int n,t;
	scanf("%d",&n);
	for(int i=1;i<n+1;i++)
	{
		scanf("%d",&marray[i].data);
		marray[i].type='1';
		marray[i].indx=i;
	}
	memset(nodes,0,sizeof(nodes));
	cin>>t;
	int size=n+1;
	for(int ti=0;ti<t;ti++)
	{
		int x,y,k;
		scanf("%d %d %d",&x,&y,&k);
		marray[size].data=k;
		marray[size].type='0';
		marray[size].l=x;
		marray[size].r=y;
		marray[size++].indx=ti;
	}
	sort(marray+1,marray+size,compare);
	int ans[200001];
	for(int i=1;i<size;i++)
	{
		if(marray[i].type=='1')
		update(1,1,n,marray[i].indx);
		else
		ans[marray[i].indx]=query(1,1,n,marray[i].l,marray[i].r);
	}
	for(int i=0;i<t;i++)
	printf("%d\n",ans[i]);
	return 0;
}
