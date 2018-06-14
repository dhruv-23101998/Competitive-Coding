#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int logx=20;
int marray[100001];
struct trie
{
	int lsum;
	int rsum;
	trie *left;
	trie *right;
	trie()
	{
		left=NULL;
		right=NULL;
		lsum=0;
		rsum=0;
	}
};
trie *insert(trie *node,int val,int depth)
{
	if(depth==-1)
	return node;
	int x=(val>>depth) & 1;
	if(x)
	{	
		node->rsum++;
		if(node->right==NULL)
		node->right=new trie();
		node->right=insert(node->right,val,depth-1);
	}
	else
	{
		node->lsum++;
		if(node->left==NULL)
		node->left=new trie();
		node->left=insert(node->left,val,depth-1);
	}
	return node;
}
int query(trie *node,int q,int k,int depth)
{	
	if(node==NULL || depth==-1)
	return 0;
	int x=(q>>depth) & 1;
	int y=(k>>depth) & 1;
	if(x)
	{
		if(y)
		return node->rsum+query(node->left,q,k,depth-1);
		return query(node->right,q,k,depth-1);
	}
	else
	{
		if(y)
		return node->lsum+query(node->right,q,k,depth-1);
		return query(node->left,q,k,depth-1);
	}
} 
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,k;
		scanf("%d %d",&n,&k);
		trie *root=new trie();
		long long int q,ans=0,p=0;
		for(int i=0;i<n;i++)
		scanf("%d",marray+i);
		root=insert(root,0,logx);
		for(int i=0;i<n;i++)
		{
			q=(ll)p^(ll)marray[i];
			ans+=(ll)query(root,q,k,logx);
			root=insert(root,q,logx);
			p=q;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
