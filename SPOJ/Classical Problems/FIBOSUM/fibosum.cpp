#include <bits/stdc++.h>
using namespace std;
const int M=1e9+7;
map<long long int,long long int> f;
long long int  fibo(long long int x)
{
	if(f.count(x))
	return f[x];
	long long int k=x/2;
	if(x%2==0)
	return f[x]=(fibo(k)*fibo(k)+fibo(k-1)*fibo(k-1))%M;
	else
	return f[x]=(fibo(k)*fibo(k+1)+fibo(k-1)*fibo(k))%M;
}
int main()
{
	int t;
	f[0]=1;
	f[1]=1;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		long long int ans=0;
		scanf("%d %d",&n,&m);
		ans=(fibo(m+1)-fibo(n))%M;
		if(ans<0)
		ans+=M;
		printf("%lld\n",ans);
	}
	return 0;
}
