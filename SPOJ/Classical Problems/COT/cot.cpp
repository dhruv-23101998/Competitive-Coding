#include <bits/stdc++.h>
using namespace std;
int marray[100001],answer[100001],depth[100001],parent[100001][17],num;
vector<int> sortv;
map<int,int> cordcomp;
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
struct arc
{
	int nodei;
	struct arc *next;
};
struct nodetype
{
	struct arc *point;
};
struct nodetype treenodes[100001];
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
void update(node *current,node *prev,int l,int r,int pos)
{
	if(pos>r || pos<l || l>r)
	return ;
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
int query(node *x,node *y,node *a,node *b,int l,int r,int k)
{
	if(l==r)
	return l;
	int mid=(l+r)>>1;
	int cnt=x->left->cnt+y->left->cnt-a->left->cnt-b->left->cnt;
	if(cnt>=k)
	return query(x->left,y->left,a->left,b->left,l,mid,k);
	return query(x->right,y->right,a->right,b->right,mid+1,r,k-cnt);
}
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=treenodes[x].point;
	treenodes[x].point=r1;
}
void dfs(int s,int prev)
{
	struct arc *yptr=treenodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	parent[s][0]=prev;
	nodes[s]=new node(0,NULL,NULL);
	update(nodes[s],(prev==-1 ? nodes[0] : nodes[prev]),1,num,cordcomp[marray[s]]);
	while(ynode!=-1)
	{
		if(ynode!=prev)
		{
			depth[ynode]=depth[s]+1;
			dfs(ynode,s);
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
int lca(int u,int v)
{
    if(depth[u]>depth[v])
    {
        u=u^v;
        v=u^v;
        u=u^v;
    }
    int diff=depth[v]-depth[u];
    for(int i=0;i<17;i++)
    if((diff>>i) & 1)
    v=parent[v][i];
    if(u==v)
    return u;
    for(int i=16;i>=0;i--)
    if(parent[u][i]!=parent[v][i])
    {
        u=parent[u][i];
        v=parent[v][i];
    }
    return parent[u][0];
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	map<int,int> exist;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",marray+i);
		if(exist[marray[i]]==0)
		sortv.push_back(marray[i]);
		exist[marray[i]]++;
	}
	num=0;
	sort(sortv.begin(),sortv.end());
	for(int i=0;i<sortv.size();i++)
	{
		cordcomp[sortv[i]]=++num;
		answer[num]=sortv[i];
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		addarc(u,v);
		addarc(v,u);
	}
	nodes[0]=new node(0,NULL,NULL);
	buildst(nodes[0],1,num);
	memset(parent,-1,sizeof(parent));
	depth[1]=0;
	dfs(1,-1);
	for(int j=1;j<17;j++)
    for(int i=1;i<=n;i++)
    if(parent[i][j-1]!=-1)
    parent[i][j]=parent[parent[i][j-1]][j-1];
	while(m--)
	{
		int u,v,k;
		scanf("%d %d %d",&u,&v,&k);
		int p=lca(u,v);
		int ans=query(nodes[u],nodes[v],nodes[p],((parent[p][0]==-1) ? nodes[0] : nodes[parent[p][0]]),1,num,k);
		printf("%d\n",answer[ans]);
	}
	return 0;
}
