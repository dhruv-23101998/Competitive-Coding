#include <bits/stdc++.h>
using namespace std;
#define INF 1000000000
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
struct nodetype
{
	int nodeno;
	int dist;
	nodetype(int val,int no)
	{
		nodeno=no;
		dist=val;
	}
	bool operator < (nodetype x)const
	{
		return dist>x.dist;
	}
};
int depth[100001],parent[100001][17],subsz[100001],cenfather[100001];
bool iscentroid[100001],white[100001];
priority_queue<nodetype> q[100001];
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
int answer(int x)
{
	priority_queue<nodetype> &g=q[x];
	while(!g.empty())
	{
		nodetype current=g.top();
		if(!white[current.nodeno])
		g.pop();
		else
		return current.dist;
	}
	return INF;
}
void dfs(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	parent[s][0]=prev;
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
int sz;
void subdfs(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL)? -1 : yptr->nodei;
	sz++;
	subsz[s]=1;
	while(ynode!=-1)
	{
		if(ynode!=prev && !iscentroid[ynode])
		{
			subdfs(ynode,s);
			subsz[s]+=subsz[ynode];
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
int findcentre(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev && !iscentroid[ynode] && subsz[ynode]>sz/2)
		return findcentre(ynode,s);
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
	return s;
}
void decompose(int s,int prev)
{
	sz=0;
	subdfs(s,prev);
	int centroid=findcentre(s,prev);
	cenfather[centroid]=prev;
	iscentroid[centroid]=true;
	struct arc *yptr=nodes[centroid].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(!iscentroid[ynode])
		decompose(ynode,centroid);
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
int main()
{
	int n,m;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		addarc(x,y);
		addarc(y,x);
	}
	memset(parent,-1,sizeof(parent));
	memset(iscentroid,false,sizeof(iscentroid));
	memset(white,false,sizeof(white));
	depth[1]=0;
	dfs(1,-1);
	for(int j=1;j<17;j++)
	for(int i=1;i<=n;i++)
	if(parent[i][j-1]!=-1)
	parent[i][j]=parent[parent[i][j-1]][j-1];
	decompose(1,-1);
	scanf("%d",&m);
	while(m--)
	{
		int type,v;
		scanf("%d %d",&type,&v);
		if(type==0)
		{
			white[v]=!white[v];
			if(white[v])
			{
				int x=v;
				while(x!=-1)
				{
					q[x].push(nodetype(depth[v]+depth[x]-2*depth[lca(v,x)],v));
					x=cenfather[x];
				}                  
			}
		}
		else
		{
			int ans=INF;
			int x=v;
			while(x!=-1)
			{
				ans=min(ans,depth[v]+depth[x]-2*depth[lca(v,x)]+answer(x));
				x=cenfather[x];
			}
			printf("%d\n",(ans>=INF ? -1 : ans));
		}
	}
	return 0;
}
