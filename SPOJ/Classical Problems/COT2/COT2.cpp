/* SPOJ - COT2 Mo's Algorithm On Trees */
#include <bits/stdc++.h>
using namespace std;
const int MAXN=40005;
const int MAXM=100005;
const int LOG=16;
map<int,int> cordcomp;
vector<int> edge[MAXN];
int a[MAXN],parent[MAXN][LOG],st[MAXN],en[MAXN],depth[MAXN],id[MAXN<<1],cnt[MAXN],blocksz,indx,res[MAXM],visited[MAXN];
struct MOQuery
{
	int l,r,indx,lca;
	bool operator < (const MOQuery &x)
	{
		if(l/blocksz!=x.l/blocksz)
		return l/blocksz<x.l/blocksz;
		return r<x.r;
	}
};
MOQuery q[MAXM];
void dfs(int s,int prev)
{
	id[indx]=s;
	st[s]=indx++;
	parent[s][0]=prev;
	for(int i=0;i<edge[s].size();i++)
	if(edge[s][i]!=prev)
	{	
		depth[edge[s][i]]=depth[s]+1;
		dfs(edge[s][i],s);
	}
	id[indx]=s;
	en[s]=indx++;
}
int lca(int u,int v)
{
	if(depth[u]>depth[v])
	{
		u=u^v;
		v=u^v;
		u=u^v;
	}
	int del=depth[v]-depth[u];
	for(int i=0;i<LOG;i++)
	if((del>>i) & 1)
	v=parent[v][i];
	if(u==v)
	return u;
	for(int i=LOG-1;i>=0;i--)
	if(parent[u][i]!=parent[v][i])
	{
		u=parent[u][i];
		v=parent[v][i];
	}
	return parent[u][0];
}
void deal(int x,int &ans)
{
	if(visited[x] && --cnt[a[x]]==0)
	ans--;
	else if(!visited[x] && ++cnt[a[x]]==1)
	ans++;
	visited[x]^=1;
}
void performMO(int m)
{
	sort(q,q+m);
	int l,r,ans=0;
	int currentl=0,currentr=0;
	for(int i=0;i<m;i++)
	{
		l=q[i].l;
		r=q[i].r;
		while(currentl<l)
		deal(id[currentl++],ans);
		while(currentl>l)
		deal(id[--currentl],ans);
		while(currentr<=r)
		deal(id[currentr++],ans);
		while(currentr>r+1)
		deal(id[--currentr],ans);
		if(q[i].lca!=-1)
		deal(q[i].lca,ans);
		res[q[i].indx]=ans;
		if(q[i].lca!=-1)
		deal(q[i].lca,ans);
	}
}
int main()
{
	int n,m,u,v;
	indx=0;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",a+i);
	int num=0;
	for(int i=1;i<=n;i++)
	{
		if(cordcomp[a[i]]==0)
		cordcomp[a[i]]=++num;
		a[i]=cordcomp[a[i]];
	}
	for(int i=1;i<n;i++)
	{	
		scanf("%d %d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	memset(parent,-1,sizeof parent);
	memset(visited,0,sizeof visited);
	memset(cnt,0,sizeof cnt);
	depth[1]=0;
	dfs(1,-1);
	blocksz=sqrt(indx);
	for(int j=1;j<LOG;j++)
	for(int i=1;i<=n;i++)
	if(parent[i][j-1]!=-1)
	parent[i][j]=parent[parent[i][j-1]][j-1];
	for(int i=0;i<m;i++)
	{
		scanf("%d %d",&u,&v);
		q[i].indx=i;
		q[i].lca=lca(u,v);
		if(st[u]<st[v])
		{
			u=u^v;
			v=u^v;
			u=u^v;
		}
		if(u==q[i].lca)
		{
			q[i].l=st[u];
			q[i].r=st[v];
			q[i].lca=-1;
		}
		else
		{
			q[i].l=en[u];
			q[i].r=st[v];
		}
	}
	performMO(m);
	for(int i=0;i<m;i++)
	printf("%d\n",res[i]);
	return 0;
}
