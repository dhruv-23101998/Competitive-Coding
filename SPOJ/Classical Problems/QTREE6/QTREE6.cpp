#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
const int LOGN=20;
int n;
int color[2][MAXN],c[MAXN];
int segtree[2][MAXN<<2],lazy[2][MAXN<<2],en[2][MAXN<<2];
int parent[MAXN],subsz[MAXN];
vector<int> edge[MAXN];
int chainno,nbase;
int chainhead[MAXN];
int base[MAXN];
int chainind[MAXN];
int pib[MAXN];
void dfs(int u,int p=0)
{
	subsz[u]=1;
	parent[u]=p;
	for(int i=0;i<edge[u].size();i++)
	if(edge[u][i]!=p)
	{
		dfs(edge[u][i],u);
		subsz[u]+=subsz[edge[u][i]];
	}
}
void hld(int u)
{
	if(chainhead[chainno]==-1)
	chainhead[chainno]=u;
	chainind[u]=chainno;
	base[++nbase]=u;
	pib[u]=nbase;
	int sc=-1;
	for(int i=0;i<edge[u].size();i++)
	if(edge[u][i]!=parent[u] && (sc==-1 || subsz[edge[u][i]]>subsz[sc]))
	sc=edge[u][i];
	if(sc!=-1)
	hld(sc);
	for(int i=0;i<edge[u].size();i++)
	if(edge[u][i]!=parent[u] && edge[u][i]!=sc)
	{
		chainno++;
		hld(edge[u][i]);
	}
}
void init(int root)
{
	memset(chainhead,-1,sizeof(chainhead));
	chainno=nbase=0;
	dfs(root,0);
	hld(root);
}
inline void push(int node,int l,int r,int col)
{
	if(lazy[col][node])
	{
		segtree[col][node]+=(r-l+1)*lazy[col][node];
		if(l!=r)
		{
			lazy[col][node<<1]+=lazy[col][node];
			lazy[col][(node<<1)+1]+=lazy[col][node];
		}
		lazy[col][node]=0;
	}
}
inline void combine(int node,int l,int r,int col)
{
	segtree[col][node]=segtree[col][node<<1]+segtree[col][(node<<1)+1];
	en[col][node]=max(en[col][node<<1],en[col][(node<<1)+1]);
}
void build(int node,int l,int r)
{
	lazy[0][node]=lazy[1][node]=0;
	if(l==r)
	{
		segtree[0][node]=color[0][l];
		segtree[1][node]=color[1][l];
		en[c[base[l]]][node]=l;
		en[c[base[l]]^1][node]=INT_MIN;
		return ;
	}
	int mid=(l+r)>>1;
	build((node<<1),l,mid);
	build((node<<1)+1,mid+1,r);
	combine(node,l,r,0);
	combine(node,l,r,1);
}
void updatecolor(int node,int l,int r,int pos)
{
	push(node,l,r,0);
	push(node,l,r,1);
	if(l>r || l>pos || r<pos)
	return ;
	if(l==r && l==pos)
	{
		en[c[base[l]]][node]=l;
		en[c[base[l]]^1][node]=INT_MIN;
		return ;
	}
	int mid=(l+r)>>1;
	updatecolor((node<<1),l,mid,pos);
	updatecolor((node<<1)+1,mid+1,r,pos);
	en[0][node]=max(en[0][node<<1],en[0][(node<<1)+1]);
	en[1][node]=max(en[1][node<<1],en[1][(node<<1)+1]);
}
void update(int node,int l,int r,int x,int y,int val,int col)
{
	push(node,l,r,col);
	if(l>r || l>y || r<x)
	return ;
	if(l>=x && r<=y)
	{
		lazy[col][node]+=val;
		push(node,l,r,col);
		return ;
	}
	int mid=(l+r)>>1;
	update((node<<1),l,mid,x,y,val,col);
	update((node<<1)+1,mid+1,r,x,y,val,col);
	combine(node,l,r,col);
}
int query(int node,int l,int r,int x,int y,int col)
{
	push(node,l,r,col);
	if(l>r || l>y || r<x) return 0;
	if(l>=x && r<=y)
	return segtree[col][node];
	int mid=(l+r)>>1;
	return query((node<<1),l,mid,x,y,col)+query((node<<1)+1,mid+1,r,x,y,col);
}
int findindx(int node,int l,int r,int x,int y,int col)
{
	if(l>r || l>y || r<x)
	return INT_MIN;
	if(l>=x && r<=y)
	return en[col][node];
	int mid=(l+r)>>1;
	int a=findindx((node<<1),l,mid,x,y,col);
	int b=findindx((node<<1)+1,mid+1,r,x,y,col);
	return max(a,b);
}
int query(int u)
{
	int uchain,indx;
	while(u!=0)
	{
		uchain=chainind[u];
		indx=findindx(1,1,n,pib[chainhead[uchain]],pib[u],c[u]^1);
		if(indx>=pib[chainhead[uchain]] && indx<=pib[u])
		return query(1,1,n,indx+1,indx+1,c[u]);
		u=chainhead[uchain];
		if(parent[u]==0 || c[u]!=c[parent[u]])
		break;
		u=parent[u];
	}
	return query(1,1,n,pib[u],pib[u],c[u]);
}
void toggle(int u)
{
	int a=query(1,1,n,pib[u],pib[u],c[u]);
	update(1,1,n,pib[u],pib[u],-1,c[u]);
	c[u]^=1;
	updatecolor(1,1,n,pib[u]);
	int b=query(1,1,n,pib[u],pib[u],c[u])+1;
	update(1,1,n,pib[u],pib[u],1,c[u]);
	int col=c[u];
	u=parent[u];
	int v=u,indx,uchain;
	if(c[u]!=col)
	update(1,1,n,pib[u],pib[u],b,col);
	while(u!=0 && c[u]==col)
	{
		uchain=chainind[u];
		indx=findindx(1,1,n,pib[chainhead[uchain]],pib[u],col^1);
		if(indx<=pib[u] && indx>=pib[chainhead[uchain]])
		{
			update(1,1,n,indx,pib[u],b,col);
			break;
		}
		update(1,1,n,pib[chainhead[uchain]],pib[u],b,col);
		u=chainhead[uchain];
		if(parent[u]==0)
		break;
		u=parent[u];
		if(c[u]!=col)
		{
			update(1,1,n,pib[u],pib[u],b,col);
			break;
		}
	}
	col^=1;
	if(c[v]!=col)
	update(1,1,n,pib[v],pib[v],-a,col);
	while(v!=0 && col==c[v])
	{
		uchain=chainind[v];
		indx=findindx(1,1,n,pib[chainhead[uchain]],pib[v],col^1);
		if(indx<=pib[v] && indx>=pib[chainhead[uchain]])
		{
			update(1,1,n,indx,pib[v],-a,col);
			break;
		}
		update(1,1,n,pib[chainhead[uchain]],pib[v],-a,col);
		v=chainhead[uchain];
		if(parent[v]==0)
		break;
		v=parent[v];
		if(c[v]!=col)
		{
			update(1,1,n,pib[v],pib[v],-a,col);
			break;
		}
	}
}
int main()
{
	int m,u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d %d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	init(1);
	for(int i=1;i<=n;i++)
	{
		c[i]=0;
		color[1][pib[i]]=0;
		color[0][pib[i]]=subsz[i];
	}
	build(1,1,n);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d %d",&u,&v);
		if(u==0)
		printf("%d\n",query(v));
		else
		toggle(v);
	}
	return 0;
}
