#include <bits/stdc++.h>
using namespace std;
struct arc
{
	int nodei;
	int cost;
	int indx;
	struct arc *next;
};
struct nodetype
{
	struct arc *point;
};
struct nodetype nodes[100001];
int parent[100001][17],depth[100001],subsz[100001],chainhead[100001],chainind[100001],posst[100001],marray[100001],otherend[100001];
int tree[100000*3],lazy[3*100000];
int chainno,pointer;
void builtst(int node,int l,int r)
{	
	if(l==r)
	{
		tree[node]=marray[l];
		return ;
	}
	int mid=(l+r)>>1;
	builtst(2*node,l,mid);
	builtst(2*node+1,mid+1,r);
	tree[node]=tree[2*node]+tree[2*node+1];
}
void updatest(int node,int l,int r,int x,int y)
{
	if(lazy[node]!=0)
	{
		tree[node]+=(r-l+1)*lazy[node];
		if(l!=r)
		{
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(l>r || x>r || y<l)
	return ;
	if(l>=x && r<=y)
	{
		tree[node]+=(r-l+1);
		if(l!=r)
		{
			lazy[2*node]++;
			lazy[2*node+1]++;
		}
		return ;
	}
	int mid=(l+r)>>1;
	updatest(2*node,l,mid,x,y);
	updatest(2*node+1,mid+1,r,x,y);
	tree[node]=tree[2*node]+tree[2*node+1];
}
void update(int u,int v)
{
	if(u==v)
	return ;
	int uchain,vchain=chainind[v];
	while(true)
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			if(u==v)
			break;
			updatest(1,1,pointer-1,posst[v]+1,posst[u]);
			break;
		}
		updatest(1,1,pointer-1,posst[chainhead[uchain]],posst[u]);
		u=chainhead[uchain];
		u=parent[u][0];
	}
}
int queryst(int node,int l,int r,int x,int y)
{
	if(lazy[node]!=0)
	{
		tree[node]+=(r-l+1)*lazy[node];
		if(l!=r)
		{
			lazy[2*node]+=lazy[node];
			lazy[2*node+1]+=lazy[node];
		}
		lazy[node]=0;
	}
	if(l>=x && r<=y)
	return tree[node];
	if(l>r || l>y || r<x)
	return 0;
	int mid=(l+r)>>1;
	int ans1=queryst(2*node,l,mid,x,y);
	int ans2=queryst(2*node+1,mid+1,r,x,y);
	return ans1+ans2;
}
int query(int u,int v)
{
	if(u==v)
	return 0;
	int uchain,vchain=chainind[v],ans=0;
	while(true)
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			if(u==v)
			break;
			int ans1=queryst(1,1,pointer-1,posst[v]+1,posst[u]);
			ans+=ans1;
			break;
		}
		int ans1=queryst(1,1,pointer-1,posst[chainhead[uchain]],posst[u]);
		ans+=ans1;
		u=chainhead[uchain];
		u=parent[u][0];
	}
	return ans;
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
void hld(int node,int cost,int prev)
{
	if(chainhead[chainno]==-1)
	chainhead[chainno]=node;
	chainind[node]=chainno;
	posst[node]=pointer;
	marray[pointer++]=cost;
	int sc=-1,ncost;
	struct arc *yptr=nodes[node].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev)
		if(sc==-1 || subsz[sc]<subsz[ynode])
		{
			sc=ynode;
			ncost=yptr->cost;
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
	if(sc!=-1)
	hld(sc,ncost,node);
	yptr=nodes[node].point;
	ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev && ynode!=sc)
		{
			chainno++;
			hld(ynode,yptr->cost,node);
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
void dfs(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	subsz[s]=1;
	parent[s][0]=prev;
	while(ynode!=-1)
	{
		if(ynode!=prev)
		{
			otherend[yptr->indx]=ynode;
			depth[ynode]=depth[s]+1;
			dfs(ynode,s);
			subsz[s]+=subsz[ynode];
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
void addarc(int x,int y,int cost,int edgeno)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->cost=cost;
	r1->indx=edgeno;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int a,b,c;
		scanf("%d %d",&a,&b);
		addarc(a,b,0,i);
		addarc(b,a,0,i);
	}
	pointer=chainno=1;
	memset(parent,-1,sizeof(parent));
	memset(chainhead,-1,sizeof(chainhead));
	memset(lazy,0,sizeof(lazy));
	depth[1]=0;
	dfs(1,-1);
	hld(1,-1,-1);
	builtst(1,1,pointer-1);
	for(int i=1;i<17;i++)
	for(int j=1;j<=n;j++)
	if(parent[j][i-1]!=-1)
	parent[j][i]=parent[parent[j][i-1]][i-1];
	while(m--)
	{
		char type;
		int x,y;
		scanf(" %c %d %d",&type,&x,&y);
		int p=lca(x,y);
		if(type=='P')
		{
			update(x,p);
			update(y,p);
		}
		else
		printf("%d\n",query(x,p)+query(y,p));
	}
	return 0;
}
