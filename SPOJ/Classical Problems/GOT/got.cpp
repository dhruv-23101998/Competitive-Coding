#include <bits/stdc++.h>
using namespace std;
int marray[100001],n,m;
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
struct nodetype tree[100001];
node *nodes[100001];
int depth[100001],parent[100001][18];
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=tree[x].point;
	tree[x].point=r1;
}
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
	if(l>r || pos>r || pos<l)
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
int query(node *current,int l,int r,int pos)
{
	if(!current)
	return 0;
	if(l==r && l==pos)
	return current->cnt;
	int mid=(l+r)>>1;
	if(pos<=mid)
	return query(current->left,l,mid,pos);
	else
	return query(current->right,mid+1,r,pos);
}
void dfs(int s,int prev)
{
	struct arc *yptr=tree[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	parent[s][0]=prev;
	nodes[s]=new node(0,NULL,NULL);
	update(nodes[s],(prev==-1 ? nodes[0] : nodes[prev]),0,n,marray[s]);
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
		v=v^u;
		u=u^v;
	}
	int diff=depth[v]-depth[u];
	for(int i=0;i<18;i++)
	if((diff>>i) & 1)
	v=parent[v][i];
	if(u==v)
	return u;
	for(int i=17;i>=0;i--)
	if(parent[u][i]!=parent[v][i])
	{
		u=parent[u][i];
		v=parent[v][i];
	}
	return parent[u][0];
}
int main()
{
	int t=0;
	while(scanf("%d %d",&n,&m)!=EOF)
	{
		if(t!=0)
		printf("\n");
		t++;
		for(int i=1;i<=n;i++)
		tree[i].point=NULL;
		for(int i=1;i<=n;i++)
		scanf("%d",marray+i);
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d %d",&u,&v);
			addarc(u,v);
			addarc(v,u);
		}
		memset(parent,-1,sizeof(parent));
		nodes[0]=new node(0,NULL,NULL);
		buildst(nodes[0],0,n);
		depth[1]=0;
		dfs(1,-1);
		for(int j=1;j<18;j++)
		for(int i=1;i<=n;i++)
		if(parent[i][j-1]!=-1)
		parent[i][j]=parent[parent[i][j-1]][j-1];
		for(int i=0;i<m;i++)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			int p=lca(a,b);
			int ans=query(nodes[a],0,n,c)+query(nodes[b],0,n,c)-query(nodes[p],0,n,c)-query((p==1 ? nodes[0] : nodes[parent[p][0]]),0,n,c);
			if(ans>0)
			printf("Find\n");
			else
			printf("NotFind\n");
		}
	}
	return 0;
}
