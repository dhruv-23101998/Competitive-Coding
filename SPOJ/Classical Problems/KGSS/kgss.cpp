#include <bits/stdc++.h>
using namespace std;
#define IOBOOST ios_base::sync_with_stdio(false)
#define FLUSHOUT cin.tie(NULL)
struct nodetype
{
   int m1;
   int m2;
};
struct nodetype nodes[3*100000];
int marray[100010];
void buildst(int node,int l,int r)
{
    if(l==r)
    {
    	nodes[node].m1=marray[l];
    	nodes[node].m2=0;
      	return ;
   	}
   	int mid=(l+r)>>1;
	buildst(2*node,l,mid);
	buildst(2*node+1,mid+1,r);
	int v[4];
	v[0]=nodes[2*node].m1;
	v[1]=nodes[2*node].m2;
	v[2]=nodes[2*node+1].m1;
	v[3]=nodes[2*node+1].m2;
	sort(v,v+4);
	nodes[node].m1=v[3];
	nodes[node].m2=v[2];
}
void update(int node,int l,int r,int pos,int value)
{
    if(l==r)
    {
    	nodes[node].m1=value;
        nodes[node].m2=0;
        return ;
    }
   	if(l>r || l>pos || r<pos)
   	return ;
   	int mid=(l+r)>>1;
    if(pos<=mid)
   	update(2*node,l,mid,pos,value);
   	else
    update(2*node+1,mid+1,r,pos,value);
    int v[4];
	v[0]=nodes[2*node].m1;
    v[1]=nodes[2*node].m2;
	v[2]=nodes[2*node+1].m1;
  	v[3]=nodes[2*node+1].m2;
 	sort(v,v+4);
  	nodes[node].m1=v[3];
  	nodes[node].m2=v[2];
}
struct nodetype query(int node,int l,int r,int x,int y)
{
    struct nodetype ans;
    ans.m1=ans.m2=0;
    if(l>r || l>y || r<x)
    return ans;
    if(l>=x && r<=y)
    return nodes[node];   
    int mid=(l+r)>>1;
    struct nodetype ans1=query(2*node,l,mid,x,y);
    struct nodetype ans2=query(2*node+1,mid+1,r,x,y);
    if(y<=mid)
    return ans1;  
    if(x>=mid+1)
    return ans2; 
    int v[4];
    v[0]=ans1.m1;
    v[1]=ans1.m2;
    v[2]=ans2.m1;
    v[3]=ans2.m2;
    sort(v,v+4);
    ans.m1=v[3];
    ans.m2=v[2];
    return ans;
}
int main() 
{
    IOBOOST;
    FLUSHOUT;
    int n,q;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>marray[i];
    buildst(1,1,n);
    cin>>q;
    for(int i=0;i<q;i++)
    {
    	int x,y;
    	char type;
        cin>>type>>x>>y;
        if(type=='Q')
        {
        	struct nodetype ans=query(1,1,n,x,y);
            cout<<ans.m1+ans.m2<<"\n";
        }   
        else
        update(1,1,n,x,y);
    }
    return 0;
}
