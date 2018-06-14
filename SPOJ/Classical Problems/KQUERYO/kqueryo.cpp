#include <bits/stdc++.h>
using namespace std;
int marray[30001];
map<int,int> cordcomp;
vector<int> sortv,v;
struct node
{
	int cnt;
	node *left;
	node *right;
	node(int val,node *l,node *r)
	{
		cnt=val;
		left=l;
		right=r;
	}
};
node *nodes[30001];
void buildst(node *current,int l,int r)
{	
	if(l==r)
	{
		current->cnt=0;
		return ;
	}
	int mid=(l+r)>>1;
	current->left=new node(0,NULL,NULL);
	current->right=new node(0,NULL,NULL);
	buildst(current->left,l,mid);
	buildst(current->right,mid+1,r);
}
void update(node *current,node *prev,int l,int r,int pos)
{
	if(l==r && l==pos)
	{
		current->cnt++;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	{
		current->right=prev->right;
		current->left=new node(prev->left->cnt,NULL,NULL);
		update(current->left,prev->left,l,mid,pos);
	}
	else
	{
		current->left=prev->left;
		current->right=new node(prev->right->cnt,NULL,NULL);
		update(current->right,prev->right,mid+1,r,pos);
	}
	current->cnt=current->left->cnt+current->right->cnt;
}
int query(node *current,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return 0;
	if(l>=x && r<=y)
	return current->cnt;
	int mid=(l+r)>>1;
	return query(current->left,l,mid,x,y)+query(current->right,mid+1,r,x,y);
}
int main()
{
	int n,q;
	scanf("%d",&n);
	map<int,int> exist;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",marray+i);
		if(exist[marray[i]]==0)
		sortv.push_back(marray[i]);
		exist[marray[i]]++;
	}
	int num=0;
	sort(sortv.begin(),sortv.end());
	v=sortv;
	reverse(v.begin(),v.end());
	for(int i=0;i<sortv.size();i++)
	cordcomp[v[i]]=++num;
	scanf("%d",&q);
	nodes[0]=new node(0,NULL,NULL);
	buildst(nodes[0],1,num);
	for(int i=1;i<=n;i++)
	{
		nodes[i]=new node(0,NULL,NULL);
		update(nodes[i],nodes[i-1],1,num,cordcomp[marray[i]]);
	}
	int lastans=0;
	while(q--)
	{
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		a^=lastans;
		b^=lastans;
		c^=lastans;
		if(a<1)
		a=1;
		if(b>n)
		b=n;
		if(a>b)
		{
			lastans=0;
			printf("0\n");
			continue;
		}
		int x=upper_bound(sortv.begin(),sortv.end(),c)-sortv.begin();
		x=sortv.size()-x;
		if(x<=0)
		lastans=0;
		else
		lastans=query(nodes[b],1,num,1,x)-query(nodes[a-1],1,num,1,x);
		printf("%d\n",lastans);
	}
	return 0;
}
