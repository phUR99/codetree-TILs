#include <iostream>
#include <vector>
using namespace std;
void input();
void solve();
int n;
int dp[20];
vector<pair<int, int>> arr;

int func(int idx)
{
    if(idx == n) return 0;
    int &ret = dp[idx];
    if (ret != -1) return ret;
    ret = func(idx + 1);
    if(idx + arr[idx].first <= n)
        ret = max(func(idx + arr[idx].first) + arr[idx].second, ret);
    return ret;
}

void solve()
{
    for (int i = 0; i < 20; i++) dp[i] = -1;
    int ans = func(0);
    cout << ans;
}


void input()
{    
    cin >> n;
    arr.resize(n);
    for (auto &i : arr) cin >> i.first >> i.second;
}

int main() {
    input();
    solve();
    return 0;
}