#include <bits/stdc++.h>
using namespace std;
struct arc 
{
	int nodei;
	int val;
	struct arc *next;
};
struct node
{
	struct arc *point;
};
struct node nodes[10001];
void addarc(int x,int y,int length)
{
	struct arc *r1=(struct arc*)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->val=length;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
int depth[10001],parent[10001][15];
long long int dist[10001];
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
			dist[ynode]=dist[s]+yptr->val;
			dfs(ynode,s);
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
int lca(int u,int  v)
{
	if(depth[u]>depth[v])
	{
		u=u^v;
		v=v^u;
		u=u^v;
	}
	int diff=depth[v]-depth[u];
	for(int i=0;i<15;i++)
	if((diff>>i) & 1)
	v=parent[v][i];
	if(u==v)
	return u;
	for(int i=14;i>=0;i--)
	if(parent[u][i]!=parent[v][i])
	{
		u=parent[u][i];
		v=parent[v][i];
	}
	return parent[u][0];
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=0;i<=n;i++)
		nodes[i].point=NULL;
		for(int i=1;i<n;i++)
		{
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			addarc(a,b,c);
			addarc(b,a,c);
		}
		memset(parent,0,sizeof(parent));
		depth[1]=0;
		dist[1]=0;
		dfs(1,-1);
		for(int j=1;j<15;j++)
		for(int i=1;i<=n;i++)
		if(parent[i][j-1]!=-1)
		parent[i][j]=parent[parent[i][j-1]][j-1];
		while(true)
		{
			char s[4];
			scanf(" %s",s);
			if(s[0]=='D' && s[1]=='O')
			{
				printf("\n");
				break;
			}
			if(s[0]=='D')
			{
				int a,b;
				scanf("%d %d",&a,&b);
				long long int ans=dist[a]+dist[b]-2*dist[lca(a,b)];
				printf("%lld\n",ans);
			}
			else if(s[0]=='K')
			{
				int a,b,k;
				scanf("%d %d %d",&a,&b,&k);
				k--;
				int p=lca(a,b);
				if(k+1>=depth[a]+depth[b]-2*depth[p]+1)
				printf("%d\n",b);
				else if(depth[a]-depth[p]>=k)
				{
					for(int i=0;i<15;i++)
					if((k>>i) & 1)
					a=parent[a][i];
					printf("%d\n",a);
				}
				else 
				{
					k=depth[b]+depth[a]-2*depth[p]-k;
					for(int i=0;i<15;i++)
					if((k>>i) & 1)
					b=parent[b][i];
					printf("%d\n",b);
				}
			}
		}
	}
	return 0;
} 
