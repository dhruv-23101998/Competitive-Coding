#include <bits/stdc++.h>
using namespace std;
int st[100000],marray[20001];
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		st[node]=1;
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	st[node]=st[2*node]+st[2*node+1];
}
void update(int node,int l,int r,int pos)
{
	if(l>r || l>pos || r<pos)
	return ;
	if(l==r && l==pos)
	{
		st[node]=0;
		return ;
	}
	int mid=(l+r)>>1;
	update(2*node,l,mid,pos);
	update(2*node+1,mid+1,r,pos);
	st[node]=st[2*node]+st[2*node+1];
}
int query(int node,int l,int r,int k)
{
	if(l==r)
	return l;
	int mid=(l+r)>>1;
	int cnt=st[2*node];
	if(cnt>=k)
	return query(2*node,l,mid,k);
	return query(2*node+1,mid+1,r,k-cnt);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int cnt=1,incre=1;
		buildst(1,1,n);
		for(int i=1;i<=n;i++)
		{
			cnt+=incre;
			incre++;
			cnt=(cnt%(n-i+1));
			if(cnt==0)
			cnt=n-i+1;
			int ans=query(1,1,n,cnt);
			marray[ans]=i;
			update(1,1,n,ans);
		}
		for(int i=1;i<=n;i++)
		printf("%d ",marray[i]);
		printf("\n");
	}
	return 0;
}
