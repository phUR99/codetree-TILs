#include <iostream>
#include <vector>
using namespace std;
int n, ans = 987654321;
vector<vector<int>> mp;
vector<int> visit;
void input();
void solve();
void func(int cnt, int idx);
int cal();

int cal()
{
    vector<int> p1, p2;
    for (int i  = 0; i < n; i++)
    {
        if (visit[i]) p1.push_back(i);
        else p2.push_back(i);
    }
    int ret = 0;
    for (int i = 0; i < n/2; i++)
    {
        for (int j = i; j <n/2; j++)
        {
            ret += (mp[p1[i]][p1[j]] + mp[p1[j]][p1[i]]) - (mp[p2[i]][p2[j]] + mp[p2[j]][p2[i]]);
        }
    }
    return abs(ret);
}

void func(int cnt, int idx)
{
    if(cnt == n / 2)
    {
        ans = min(ans, cal());
        return;
    }
    for (int i = idx; i < n; i++)
    {
        visit[i] = 1;
        func(cnt + 1, i + 1);
        visit[i] = 0;
    }
}

void input()
{
    cin >> n;
    mp.resize(n, vector<int>(n));
    visit.resize(n, 0);
    for (auto &i : mp) for (auto &j : i) cin >> j;
}

void solve()
{
    func(0, 0);
    cout << ans;
}


int main() {
    input();
    solve();
    return 0;
}