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
struct nodetype nodes[10001];
int parent[10010][14],depth[10010],subsz[10010],chainhead[10010],chainind[10010],posst[10010],marray[10010],otherend[10010];
int tree[10000*4];
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
	tree[node]=max(tree[2*node],tree[2*node+1]);
}
void update(int node,int l,int r,int pos,int value)
{
	if(l>r || pos>r || pos<l)
	return ;
	if(l==r)
	{
		tree[node]=value;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
	update(2*node,l,mid,pos,value);
	else 
	update(2*node+1,mid+1,r,pos,value);
	tree[node]=max(tree[2*node],tree[2*node+1]);
}
int queryst(int node,int l,int r,int x,int y)
{
	if(l>=x && r<=y)
	return tree[node];
	if(l>r || l>y || r<x)
	return -1;
	int mid=(l+r)>>1;
	int ans1=queryst(2*node,l,mid,x,y);
	int ans2=queryst(2*node+1,mid+1,r,x,y);
	return max(ans1,ans2);
}
int query(int u,int v)
{
	if(u==v)
	return 0;
	int uchain,vchain=chainind[v],ans=-1;
	while(true)
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			if(u==v)
			break;
			int ans1=queryst(1,1,pointer-1,posst[v]+1,posst[u]);
			if(ans1>ans)
			ans=ans1;
			break;
		}
		int ans1=queryst(1,1,pointer-1,posst[chainhead[uchain]],posst[u]);
		if(ans1>ans)
		ans=ans1;
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
	for(int i=0;i<14;i++)
	if((diff>>i) & 1)
	v=parent[v][i];
	if(u==v)
	return u;
	for(int i=13;i>=0;i--)
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
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		nodes[i].point=NULL;
		for(int i=1;i<n;i++)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			addarc(a,b,c,i);
			addarc(b,a,c,i);
		}
		pointer=chainno=1;
		memset(parent,-1,sizeof(parent));
		memset(chainhead,-1,sizeof(chainhead));
		depth[1]=0;
		dfs(1,-1);
		hld(1,-1,-1);
		builtst(1,1,pointer-1);
		for(int i=1;i<14;i++)
		for(int j=1;j<=n;j++)
		if(parent[j][i-1]!=-1)
		parent[j][i]=parent[parent[j][i-1]][i-1];
		while(true)
		{
			char s[6];
			scanf("%s",s);
			if(s[0]=='D')
			break;
			int x,y;
			scanf("%d %d",&x,&y);
			if(s[0]=='C')
			update(1,1,pointer-1,posst[otherend[x]],y);
			else
			{
				int p=lca(x,y);
				int ans1=query(x,p);
				int ans2=query(y,p);
				if(ans2>ans1)
				ans1=ans2;
				printf("%d\n",ans1);
			}
		}
	}
	return 0;
}
