#include <bits/stdc++.h>
using namespace std;

/*
Add `int max_of_four(int a, int b, int c, int d)` here.
*/

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int ans;
    ans = max(a, b, c, d);

    cout << ans << endl;
    return 0;
}
