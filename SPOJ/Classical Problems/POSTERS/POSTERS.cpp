#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int nodes[4*100000],lazy[4*100000];
int tl[50000],tr[50000],a[100000];
set<int> s;
void update(int node,int l,int r,int x,int y,int color)
{
	if(l>r || l>y || r<x)
	return ;
	if(l>=x && r<=y)
	{
		lazy[node]=color;
		return ;
	}
	if(lazy[node]!=0)
	{
		lazy[node<<1]=lazy[(node<<1)+1]=lazy[node];
		lazy[node]=0;
	}
	int mid=(l+r)>>1;
	update(node<<1,l,mid,x,y,color);
	update((node<<1)+1,mid+1,r,x,y,color);
}
void query(int node,int l,int r)
{
	if(lazy[node]!=0)
	{
		s.insert(lazy[node]);
		return ;
	}
	if(l>=r)
	return ;
	int mid=(l+r)>>1;
	query(node<<1,l,mid);
	query((node<<1)+1,mid+1,r);
}
int main()
{
	int t,n;
	scanf("%d",&t);
	map<int,int> cnt,indx;
	while(t--)
	{
		s.clear();
		memset(lazy,0,sizeof(lazy));
		cnt.clear();
		indx.clear();
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		scanf("%d %d",tl+i,tr+i);
		int sz=0;
		for(int i=0;i<n;i++)
		{
			cnt[tl[i]]++;
			cnt[tr[i]]++;
			if(cnt[tl[i]]==1)
			a[++sz]=tl[i];
			if(cnt[tr[i]]==1)
			a[++sz]=tr[i];
		}
		sort(a+1,a+sz+1);
		for(int i=1;i<=sz;i++)
		indx[a[i]]=i;
		for(int i=0;i<n;i++)
		update(1,1,sz,indx[tl[i]],indx[tr[i]],i+1);
		query(1,1,sz);
		printf("%d\n",(int)s.size());
	}
	return 0;
}
