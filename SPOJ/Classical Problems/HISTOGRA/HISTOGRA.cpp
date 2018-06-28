#include <bits/stdc++.h>
using namespace std;
int a[100001];
int main()
{
	int n;
	while(true)
	{
		scanf("%d",&n);
		if(n==0)
		break;
		for(int i=0;i<n;i++)
		scanf("%d",a+i);
		stack<int> s;
		long long ans=0;
		int i=0;
		while(i<n)
		{
			if(s.empty() || a[s.top()]<=a[i])
			s.push(i++);
			else
			{
				int x=s.top();
				s.pop();
				long long area=(long long)a[x]*(long long)(s.empty() ? i : (i-s.top()-1));
				ans=max(ans,area);
			}
		}
		while(!s.empty())
		{
			int x=s.top();
			s.pop();
			long long area=(long long)a[x]*(long long)(s.empty() ? i : i-s.top()-1);
			ans=max(area,ans);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
