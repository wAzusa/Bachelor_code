#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	char a[10000];
	string ans[10];
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if (a[i] == '1')
		{

			ans[1] += "..X.";
			ans[2] += "..X.";
			ans[3] += "..X.";
			ans[4] += "..X.";
			ans[5] += "..X.";
		}
		if (a[i] == '2')
		{
			ans[1] += "XXX.";
			ans[2] += "..X.";
			ans[3] += "XXX.";
			ans[4] += "X...";
			ans[5] += "XXX.";
		}
		if (a[i] == '3')
		{
			ans[1] += "XXX.";
			ans[2] += "..X.";
			ans[3] += "XXX.";
			ans[4] += "..X.";
			ans[5] += "XXX.";
		}
		if (a[i] == '4')
		{
			ans[1] += "X.X.";
			ans[2] += "X.X.";
			ans[3] += "XXX.";
			ans[4] += "..X.";
			ans[5] += "..X.";
		}
		if (a[i] == '5')
		{
			ans[1] += "XXX.";
			ans[2] += "X...";
			ans[3] += "XXX.";
			ans[4] += "..X.";
			ans[5] += "XXX.";
		}
		if (a[i] == '6')
		{
			ans[1] += "XXX.";
			ans[2] += "X...";
			ans[3] += "XXX.";
			ans[4] += "X.X.";
			ans[5] += "XXX.";
		}
		if (a[i] == '7')
		{
			ans[1] += "XXX.";
			ans[2] += "..X.";
			ans[3] += "..X.";
			ans[4] += "..X.";
			ans[5] += "..X.";
		}
		if (a[i] == '8')
		{
			ans[1] += "XXX.";
			ans[2] += "X.X.";
			ans[3] += "XXX.";
			ans[4] += "X.X.";
			ans[5] += "XXX.";
		}
		if (a[i] == '9')
		{
			ans[1] += "XXX.";
			ans[2] += "X.X.";
			ans[3] += "XXX.";
			ans[4] += "..X.";
			ans[5] += "XXX.";
		}
		if (a[i] == '0')
		{
			ans[1] += "XXX.";
			ans[2] += "X.X.";
			ans[3] += "X.X.";
			ans[4] += "X.X.";
			ans[5] += "XXX.";
		}
	}
	for (int i = 1; i <= 5; i++)
	{
		ans[i] = ans[i].substr(0, ans[i].length() - 1);
		cout << ans[i] << endl;
	}
	return 0;
}