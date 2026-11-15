#include <iostream>
#include <vector>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void input(void);
void solve(void);
using namespace std;

int n, lead_num, mem_num;
vector<int> arr;

void input(void)
{
    cin >> n;
    arr.resize(n);
    for (auto &i : arr) cin >> i;
    cin >> lead_num >> mem_num;
}

void solve(void)
{
    ll ans = 0;
    for (auto i : arr)
    {
        ll tmp = 0;
        if(lead_num >= i) tmp++;
        else
        {
            tmp = 1 + (i + mem_num - 1 - lead_num) / mem_num;
        }
        ans += tmp;
    }
    cout << ans;
}

int main() {
    fastio;
    input();
    solve();
    return 0;
}