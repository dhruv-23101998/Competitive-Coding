#include <bits/stdc++.h>
using namespace std;
int marray[100001];
struct treap
{
	int size;
	int value;
	int randval;
	int lsum;
	int rsum;
	int asum;
	int nodesum;
	treap *left;
	treap *right;
	treap(int x)
	{
		size=1;
		nodesum=lsum=rsum=asum=value=x;
		randval=rand();
		left=right=NULL;
	}
};
int sz(treap *t)
{
	return t ? t->size : 0;
}
int getnodesum(treap *t)
{
	return t ? t->nodesum : 0;
}
int getlsum(treap *t)
{
	return t ? t->lsum : 0;
}
int getrsum(treap *t)
{
	return t ? t->rsum : 0;
}
int getasum(treap *t)
{
	return t ? t->asum : INT_MIN;
}
void update(treap *t)
{
	if(t)
	{
		t->size=1+sz(t->left)+sz(t->right);
		t->nodesum=getnodesum(t->left)+t->value+getnodesum(t->right);
		t->lsum=max(getlsum(t->left),getnodesum(t->left)+t->value+max(0,getlsum(t->right)));
		t->rsum=max(getrsum(t->right),getnodesum(t->right)+t->value+max(0,getrsum(t->left)));
		t->asum=max(max(getasum(t->left),getasum(t->right)),max(0,getrsum(t->left))+t->value+max(0,getlsum(t->right)));
	}
}
void split(treap *t,treap *&l,treap *&r,int pos,int add)
{
	if(!t)
	return void(l=r=NULL);
	int currentpos=add + sz(t->left)+1;
	if(pos>=currentpos)
	{
		split(t->right,t->right,r,pos,currentpos);
		l=t;
	}
	else
	{
		split(t->left,l,t->left,pos,add);
		r=t;
	}
	update(t);
}
void merge(treap *&t,treap *l,treap *r)
{
	if(!l || !r)
	t=l ? l : r;
	else if(l->randval>r->randval)
	{
		merge(l->right,l->right,r);
		t=l;
	}
	else
	{
		merge(r->left,l,r->left);
		t=r;
	}
	update(t);
}
void insert(treap *&t,int pos,int value)
{
	treap *l,*r,*x=new treap(value);
	split(t,l,r,pos-1,0);
	merge(r,x,r);
	merge(t,l,r);
}
void erase(treap *&t,int pos)
{
	treap *l,*r,*x;
	split(t,l,r,pos-1,0);
	split(r,x,t,1,0);
	merge(t,l,t);
}
void replace(treap *&t,int pos,int value)
{
	treap *l,*r,*x;
	split(t,l,r,pos-1,0);
	split(r,x,t,1,0);
	x->value=x->asum=x->lsum=x->rsum=x->nodesum=value;
	merge(r,x,t);
	merge(t,l,r);
}
int query(treap *&t,int l,int r)
{
	if(!t)
	return 0;
	treap *lx,*rx,*l1x,*r1x;
	split(t,lx,rx,r,0);
	split(lx,l1x,r1x,l-1,0);
	update(r1x);
	int ans=getasum(r1x);
	merge(lx,l1x,r1x);
	merge(t,lx,rx);
	return ans;
}
int main()
{
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",marray+i);
	treap *root=new treap(marray[1]);
	for(int i=2;i<=n;i++)
	merge(root,root,new treap(marray[i]));
	scanf("%d",&q);
	while(q--)
	{
		char type;
		scanf(" %c",&type);
		int x,y;
		if(type=='I')
		{
			scanf("%d %d",&x,&y);
			insert(root,x,y);
		}
		else if(type=='D')
		{
			scanf("%d",&x);
			erase(root,x);
		}
		else if(type=='R')
		{
			scanf("%d %d",&x,&y);
			replace(root,x,y);
		}
		else if(type=='Q')
		{
			scanf("%d %d",&x,&y);
			printf("%d\n",query(root,x,y));
		}
	}
	return 0;
}
