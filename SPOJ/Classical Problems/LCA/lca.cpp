#include <bits/stdc++.h>
using namespace std;
int parent[1001],level[1001],p[1001],height;
vector<int> graph[1001];
bool visited[1001];
struct queuetype
{
	int rear;
	int front;
	int data[1001];
};
struct queuetype q;
void bfs(int s)
{
	q.rear=q.front=-1;
	height=0;
	visited[s]=true;
	q.data[++q.rear]=s;
	while(q.rear!=q.front)
	{
		int x=q.data[++q.front];
		for(int i=0;i<graph[x].size();i++)
		if(!visited[graph[x][i]])
		{
			visited[graph[x][i]]=true;
			level[graph[x][i]]=level[x]+1;
			parent[graph[x][i]]=x;
			q.data[++q.rear]=graph[x][i];
			if(level[graph[x][i]]>height)
			height=level[graph[x][i]];
		}
	}
}
void dfs(int s,int sqh)
{
	visited[s]=true;
	if(level[s]<sqh)
	p[s]=1;
	else if(!(level[s]%sqh))
	p[s]=parent[s];
	else
	p[s]=p[parent[s]];
	for(int i=0;i<graph[s].size();i++)
	if(!visited[graph[s][i]])
	dfs(graph[s][i],sqh);
}
int lca(int v,int w)
{
	while(p[v]!=p[w])
	if(level[v]>level[w])
	v=p[v];
	else
	w=p[w];
	while(v!=w)
	if(level[v]>level[w])
	v=parent[v];
	else
	w=parent[w];
	return v;
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int ti=1;ti<=t;ti++)
	{
		int n,q;
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			int m,x;
			scanf("%d",&m);
			while(m--)
			{
				scanf("%d",&x);
				graph[i+1].push_back(x);
				graph[x].push_back(i+1);
			}
		}
		memset(level,0,sizeof(level));
		memset(parent,-1,sizeof(parent));
		memset(visited,false,sizeof(visited));
		bfs(1);
		memset(visited,false,sizeof(visited));
		dfs(1,sqrt(height));
		scanf("%d",&q);
		printf("Case %d:\n",ti);
		while(q--)
		{
			int v,w;
			scanf("%d %d",&v,&w);
			printf("%d\n",lca(v,w));
		}
	}
	return 0;
}
