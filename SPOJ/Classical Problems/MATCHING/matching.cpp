#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
int n,m,p,a,b;
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
int pairuv[100001],dist[50001];
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
bool bfs()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
	if(pairuv[i]==0)
	{
		dist[i]=0;
		q.push(i);
	}
	else
	dist[i]=INF;
	dist[0]=INF;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(x!=0)
		{
			struct arc *yptr=nodes[x].point;
			int ynode=(yptr==NULL) ? -1 : yptr->nodei;
			while(ynode!=-1)
			{
				if(dist[pairuv[ynode]]==INF)
				{
					dist[pairuv[ynode]]=dist[x]+1;
					q.push(pairuv[ynode]);
				}
				yptr=yptr->next;
				ynode=(yptr==NULL) ? -1 : yptr->nodei;
			}
		}
	}
	return (dist[0]!=INF);
}
bool dfs(int s)
{
	if(s!=0)
	{
		struct arc *yptr=nodes[s].point;
		int ynode=(yptr==NULL) ? -1 : yptr->nodei;
		while(ynode!=-1)
		{
			if(dist[pairuv[ynode]]==dist[s]+1)
			{
				if(dfs(pairuv[ynode]))
				{
					pairuv[s]=ynode;
					pairuv[ynode]=s;
					return true;
				}
			}
			yptr=yptr->next;
			ynode=(yptr==NULL) ? -1 : yptr->nodei;
		}
		dist[s]=INF;
		return false;
	}
	return true;
}
int main()
{
	scanf("%d %d %d",&n,&m,&p);
	memset(pairuv,0,sizeof(pairuv));
	while(p--)
	{
		scanf("%d %d",&a,&b);
		addarc(a,b+n);
	}
	int answer=0;
	while(bfs())
	{
		for(int i=1;i<=n;i++)
		if(pairuv[i]==0 && dfs(i))
		answer++;
	}
	printf("%d\n",answer);
	return 0;
}
