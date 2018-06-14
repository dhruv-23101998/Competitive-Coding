#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
struct arc
{
	int nodei;
	struct arc *next;
};
struct nodetype
{
	struct arc *point;
};
struct nodetype nodes[100001];
struct queryans
{
	int sum;
	int leftsum;
	int rightsum;
	int maxsum;
};
queryans st[3*100001];
int marray[100001],t[100001],depth[100001],subsz[100001],parent[100001][17],chainhead[100001],chainind[100001],posst[100001];
int tree[3*100000],lazy[3*100000];
int chainno,pointer,n,q;
void addarc(int x,int y)
{
	struct arc *r1=(struct arc *)malloc(sizeof(struct arc));
	r1->nodei=y;
	r1->next=nodes[x].point;
	nodes[x].point=r1;
}
void dfs(int s,int prev)
{
	struct arc *yptr=nodes[s].point;
	int ynode=(yptr==NULL) ? -1 : yptr->nodei;
	parent[s][0]=prev;
	subsz[s]=1;
	while(ynode!=prev)
	{
		if(ynode!=prev)
		{
			depth[ynode]=depth[s]+1;
			dfs(ynode,s);
			subsz[s]+=subsz[ynode];
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
void hld(int node,int prev)
{
	if(chainhead[chainno]==-1)
	chainhead[chainno]=node;
	chainind[node]=chainno;
	posst[node]=pointer;
	t[pointer++]=marray[node];
	int sc=-1;
	struct arc *yptr=nodes[node].point;
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
	hld(sc,node);
	yptr=nodes[node].point;
	ynode=(yptr==NULL) ? -1 : yptr->nodei;
	while(ynode!=-1)
	{
		if(ynode!=prev && ynode!=sc)
		{
			chainno++;
			hld(ynode,node);
		}
		yptr=yptr->next;
		ynode=(yptr==NULL) ? -1 : yptr->nodei;
	}
}
void merge(queryans &t,queryans &l,queryans &r)
{
	t.sum=l.sum+r.sum;
	t.maxsum=max(max(l.maxsum,r.maxsum),l.rightsum+r.leftsum);
	t.leftsum=max(l.leftsum,l.sum+r.leftsum);
	t.rightsum=max(r.rightsum,r.sum+l.rightsum);
}
void propagatelazy(int node,int l,int r,int c)
{
	lazy[node]=(l==r) ? 0 : 1;
	tree[node]=c;
	st[node].sum=(r-l+1)*c;
	st[node].maxsum=st[node].leftsum=st[node].rightsum=(c>0) ? st[node].sum : c;
}
void buildst(int node,int l,int r)
{
	if(l==r)
	{
		propagatelazy(node,l,r,t[l]);
		return ;
	}
	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	merge(st[node],st[2*node],st[2*node+1]);
}
void updatest(int node,int l,int r,int x,int y,int c)
{
	if(l==x && r==y)
	{
		propagatelazy(node,l,r,c);
		return ;
	}
	int mid=(l+r)>>1;
	if(l<r && lazy[node])
	{
		lazy[node]=0;
		propagatelazy(2*node,l,mid,tree[node]);
		propagatelazy(2*node+1,mid+1,r,tree[node]);
	}
	if(y<=mid)
	updatest(2*node,l,mid,x,y,c);
	else if(x>=mid+1)
	updatest(2*node+1,mid+1,r,x,y,c);
	else
	{
		updatest(2*node,l,mid,x,mid,c);
		updatest(2*node+1,mid+1,r,mid+1,y,c);
	}
	merge(st[node],st[2*node],st[2*node+1]);
}
queryans queryst(int node,int l,int r,int x,int y)
{
	queryans q1,q2,q3;
	if(lazy[node]!=0)
	{
		q3.sum=(y-x+1)*tree[node];
		q3.leftsum=q3.rightsum=q3.maxsum=(tree[node]>0) ? q3.sum : tree[node];
		return q3;
	}
	if(l==x && r==y)
	return st[node];
	int mid=(l+r)>>1;
	if(y<=mid)
	return queryst(2*node,l,mid,x,y);
	else if(x>=mid+1)
	return queryst(2*node+1,mid+1,r,x,y);
	else
	{
		q1=queryst(2*node,l,mid,x,mid);
		q2=queryst(2*node+1,mid+1,r,mid+1,y);
		merge(q3,q1,q2);
		return q3;
	}
}
void update(int u,int v,int value)
{
	int uchain,vchain=chainind[v];
	while(depth[u]>depth[v])
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			updatest(1,1,pointer-1,posst[v]+1,posst[u],value);
			break;
		}
		updatest(1,1,pointer-1,posst[chainhead[uchain]],posst[u],value);
		u=chainhead[uchain];
		u=parent[u][0];
	}
}
queryans query(int u,int v)
{
	int uchain,vchain=chainind[v];
	queryans q1,q2,q3;
	q2.leftsum=q2.rightsum=q2.sum=q2.maxsum=-15000;
	while(depth[u]>depth[v])
	{
		uchain=chainind[u];
		if(uchain==vchain)
		{
			q1=queryst(1,1,pointer-1,posst[v]+1,posst[u]);
			merge(q3,q1,q2);
			q2=q3;
			break;
		}
		q1=queryst(1,1,pointer-1,posst[chainhead[uchain]],posst[u]);
		merge(q3,q1,q2);
		q2=q3;
		u=chainhead[uchain];
		u=parent[u][0];
	}
	return q2;
}
int main()
{
	queryans q1,q2,q3,q4;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",marray+i);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		addarc(x,y);
		addarc(y,x);
	}
	memset(parent,-1,sizeof(parent));
	memset(chainhead,-1,sizeof(chainhead));
	memset(lazy,0,sizeof(lazy));
	scanf("%d",&q);
	pointer=chainno=1;
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
		int type,a,b,c;
		scanf("%d %d %d",&type,&a,&b);
		int p=lca(a,b);
		if(type==1)
		{
			q1=query(a,p);
			q2=query(b,p);
			q3=queryst(1,1,pointer-1,posst[p],posst[p]);
			q4.leftsum=max(q3.leftsum,q3.sum+q1.leftsum);
			q4.maxsum=max(q1.leftsum+q3.sum,max(q1.maxsum,q3.maxsum));
			q1=q4;
			q4.maxsum=max(0,max(max(q1.maxsum,q2.maxsum),q1.leftsum+q2.leftsum));
			printf("%d\n",q4.maxsum);
		}
		else
		{
			scanf("%d",&c);
			update(a,p,c);
			update(b,p,c);
			updatest(1,1,pointer-1,posst[p],posst[p],c);
		}
	}
	return 0;
}
