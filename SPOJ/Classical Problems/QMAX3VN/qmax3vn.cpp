#include <bits/stdc++.h>
using namespace std;
struct treap
{
	int value;
	int mval;
	int size;
	int randval;
	treap *left;
	treap *right;
	treap(int x)
	{
		value=x;
		size=1;
		randval=rand();
		left=NULL;
		right=NULL;
	}
};
int sz(treap *t)
{
	return !t ? 0 : t->size;
}
int maxval(treap *t)
{
	return t? t->mval : INT_MIN;
}
void split(treap *t,treap *&l,treap *&r,int pos,int add)
{
	if(!t)
	return void(l=r=NULL);
	int currentpos=add+sz(t->left)+1;
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
	if(t)
	{
		t->size=sz(t->left)+sz(t->right)+1;
		t->mval=max(maxval(t->left),max(t->value,maxval(t->right)));
	}
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
	if(t)
	{
		t->size=sz(t->left)+sz(t->right)+1;
		t->mval=max(maxval(t->left),max(t->value,maxval(t->right)));
	}
}
int query(treap *t,int l,int r)
{
	if(!t)
	return 0;
	treap *midx,*lx,*rx;
	split(t,lx,midx,l-1,0);
	split(midx,t,rx,r-l+1,0);
	int ans=maxval(t);
	merge(midx,lx,t);
	merge(t,midx,rx);
	return ans;
}
void update(treap *&t,int value,int y)
{
	if(t==NULL)
	{
		t=new treap(value);
		return ;
	}
	treap *x=new treap(value);
	treap *l,*r;
	split(t,l,r,y-1,0);
	merge(l,l,x);
	merge(t,l,r);
}
int main()
{
	int n;
	scanf("%d",&n);
	treap *root=NULL;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		char type;
		scanf(" %c %d %d",&type,&x,&y);
		if(type=='A')
		update(root,x,y);
		else
		printf("%d\n",query(root,x,y));
	}
	return 0;
}
