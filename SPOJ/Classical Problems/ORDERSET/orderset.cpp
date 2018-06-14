#include <bits/stdc++.h>
using namespace std;
int marray[200001],answer[200001];;
map<int,int> cordcomp;
struct query
{
	char type;
	int val;
};
struct query q[200001];
int size,num;
int st[3*200000];
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		st[node]=0;
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
}
void update(int node,int l,int r,int pos,bool add)
{
	if(l>r || l>pos || r<pos)
	return ;
	if(l==r && l==pos)
	{
		if(add && st[node]==0)
		st[node]++;
		else if(!add && st[node]>0)
		st[node]--;
		return ;
	}
	int mid=(l+r)>>1;
	update(2*node,l,mid,pos,add);
	update(2*node+1,mid+1,r,pos,add);
	st[node]=st[2*node]+st[2*node+1];
}
int query1(int node,int l,int r,int k)
{
	if(l==r)
	return l;
	int mid=(l+r)>>1;
	int cnt=st[2*node];
	if(cnt>=k)
	return query1(2*node,l,mid,k);
	return query1(2*node+1,mid+1,r,k-cnt);
}
int query2(int node,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return 0;
	if(l>=x && r<=y)
	return st[node];
	int mid=(l+r)>>1;
	return query2(2*node,l,mid,x,y)+query2(2*node+1,mid+1,r,x,y);
}
int main()
{
	int t;
	size=num=0;
	scanf("%d",&t);
	vector<int> v;
	map<int,int> exist;
	for(int i=1;i<=t;i++)
	{
		scanf(" %c %d",&q[i].type,&q[i].val);
		if(q[i].type=='I' || q[i].type=='D')
		if(exist[q[i].val]==0)
		{
			marray[++size]=q[i].val;
			exist[q[i].val]++;
			v.push_back(q[i].val);
		}
	}
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
	{
		cordcomp[v[i]]=++num;
		answer[num]=v[i];
	}
	buildst(1,1,num);
	for(int i=1;i<=t;i++)
	{
		if(q[i].type=='I')
		update(1,1,num,cordcomp[q[i].val],true);
		else if(q[i].type=='D')
		update(1,1,num,cordcomp[q[i].val],false);
		else if(q[i].type=='K')
		{
			if(st[1]<q[i].val)
			printf("invalid\n");
			else
			{
				int ans=query1(1,1,num,q[i].val);
				printf("%d\n",answer[ans]);
			}
		}
		else 
		{
			int x=upper_bound(v.begin(),v.end(),q[i].val)-v.begin();
			if(x==0)
			printf("0\n");
			else
			{
				if(v[x-1]==q[i].val)
				x--;
				if(x==0)
				printf("0\n");
				else
				printf("%d\n",query2(1,1,num,1,x));
			}
		}
	}
	return 0;
}
