#include <bits/stdc++.h>
using namespace std;
int marray[100001],answer[100001];
map<int,int> cordcomp;
vector<int> v;
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
node *nodes[100001];
void buildst(node *current,int l,int r)
{
    if(l==r)
    {
        current->cnt=0;
        current->left=current->right=NULL;
        return ;
    }
   	current->left=new node(0,NULL,NULL);
   	current->right=new node(0,NULL,NULL);
    int mid=(l+r)>>1;
    buildst(current->left,l,mid);
    buildst(current->right,mid+1,r);
}
void update(node *current,node *prev,int l,int r,int val)
{
	if(val>r || val<l || l>r)
	return ;
	if(l==r && l==val)
	{
		current->cnt++;
		return ;
	}
	int mid=(l+r)>>1;
	if(val<=mid)
	{
		current->right=prev->right;
		current->left=new node(0,NULL,NULL);
		update(current->left,prev->left,l,mid,val);
	}
	else
	{
		current->left=prev->left;
		current->right=new node(0,NULL,NULL);
		update(current->right,prev->right,mid+1,r,val);
	}
	current->cnt=current->left->cnt+current->right->cnt;
}
int query(node *x,node *y,int l,int r,int k)
{
	if(l==r)
	return l;
	int mid=(l+r)>>1;
	int cnt=x->left->cnt-y->left->cnt;
	if(cnt>=k)
	return query(x->left,y->left,l,mid,k);
	return query(x->right,y->right,mid+1,r,k-cnt);
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	int num=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",marray+i);
		v.push_back(marray[i]);
	}
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++)
	{
		cordcomp[v[i]]=++num;
		answer[num]=v[i];
	}
	nodes[0]=new node(0,NULL,NULL);
	buildst(nodes[0],1,num);
	for(int i=1;i<=n;i++)
	{
		nodes[i]=new node(0,NULL,NULL);
		update(nodes[i],nodes[i-1],1,num,cordcomp[marray[i]]);
	}
	while(m--)
	{
		int u,v,k;
		scanf("%d %d %d",&u,&v,&k);
		int ans=query(nodes[v],nodes[u-1],1,num,k);
		printf("%d\n",answer[ans]);
	}
	return 0;
}
