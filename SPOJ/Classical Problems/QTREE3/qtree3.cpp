#include <bits/stdc++.h>
using namespace std;
struct arc
{
	int nodei;
	struct arc *next;
};
struct node
{
	struct arc *point;
};
struct node nodes[100001];
int st[3*100000],indx[100001],marray[100001];
int chainno,pointer;
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
int parent[100001][17],depth[100001],chainhead[100001],chainind[100001],posst[100001],subsz[100001];
void dfs(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	parent[s][0]=prev;
	subsz[s]=1;
	while(ynode!=-1)
	{
		if(ynode!=prev)
		{
			depth[ynode]=depth[s]+1;
			dfs(ynode,s);
			subsz[ynode]+=subsz[s];
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
void hld(int s,int prev)
{
	if(chainhead[chainno]==-1)
	chainhead[chainno]=s;
	chainind[s]=chainno;
	posst[s]=pointer;
	marray[pointer++]=s;
	int sc=-1;
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev)
		if(sc==-1 || subsz[sc]<subsz[ynode])
		sc=ynode;
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
	if(sc!=-1)
	hld(sc,s);
	yptr=nodes[s].point;
	ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev && ynode!=sc)
		{
			chainno++;
			hld(ynode,s);
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		indx[l]=0;
		st[node]=-1;
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	st[node]=(st[2*node]==-1) ? st[2*node+1] : st[2*node];
}
void update(int node,int l,int r,int pos)
{
	if(l>r || pos<l || pos>r)
	return ;
	if(l==r && l==pos)
	{
		indx[l]^=1;
		st[node]=(indx[l]==1) ? l : -1; 
		return ;
	}
	int mid=(l+r)>>1;
	update(2*node,l,mid,pos);
	update(2*node+1,mid+1,r,pos);
	st[node]=(st[2*node]==-1) ? st[2*node+1] : st[2*node];
}
int queryst(int node,int l,int r,int x,int y)
{
	if(l>r || l>y || r<x)
	return -1;
	if(l>=x && r<=y)
	return st[node];
	int mid=(l+r)>>1;
	int ans1=queryst(2*node,l,mid,x,y);
	int ans2=queryst(2*node+1,mid+1,r,x,y);
	return (ans1==-1 ? ans2 : ans1);
}
int query(int u)
{
	int ans=-1,uchain,vchain=chainind[1];
	while(true)
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			int ans1=queryst(1,1,pointer-1,posst[1],posst[u]);
			if(ans1!=-1)
			ans=ans1;
			break;
		}
		int ans2=queryst(1,1,pointer-1,posst[chainhead[uchain]],posst[u]);
		if(ans2!=-1)
		ans=ans2;
		u=chainhead[uchain];
		u=parent[u][0];
	}
	return (ans==-1 ? -1 : marray[ans]);
}
int main()
{
	int n,q;
	scanf("%d %d",&n,&q);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		addarc(x,y);
		addarc(y,x);
	}
	chainno=pointer=1;
	memset(chainhead,-1,sizeof(chainhead));
	memset(parent,-1,sizeof(parent));
	depth[1]=0;
	dfs(1,-1);
	for(int j=1;j<17;j++)
	for(int i=1;i<=n;i++)
	if(parent[i][j-1]!=-1)
	parent[i][j]=parent[parent[i][j-1]][j-1];
	hld(1,-1);
	buildst(1,1,pointer-1);
	while(q--)
	{
		int type,v;
		scanf("%d %d",&type,&v);
		if(type==0)
		update(1,1,pointer-1,posst[v]);
		else
		printf("%d\n",query(v));
	}
	return 0;
}
