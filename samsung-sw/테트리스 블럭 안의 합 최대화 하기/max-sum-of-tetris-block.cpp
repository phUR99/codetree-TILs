#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector<vector<int>> mp;

void input();
void solve();
int count(int x, int y);
bool out(int x, int y) {return x < 0 || x >= n || y < 0 || y >= m;}
vector<pair<int,int>> rotate(vector<pair<int, int>> tmp, int dir);

vector<vector<pair<int, int>>> state =
{
    {
        {0, 0}, {0, 1}, {0, 2}, {0, 3}
        // {0, 0}, {1, 0}, {2, 0}, {3, 0}
        // {0, 0}, {0, -1}, {0, -2}, {0, -3}
        // {0, 0}, {-1, 0}, {-2, 0}, {-3, 0}
    },
    {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    },
    {
        {0, 0}, {1, 0}, {2, 0}, {2, 1}
    },
    {
        {0, 0}, {1, 0}, {1, 1}, {2, 1}
    },
    {
        {0, 0}, {1, 0}, {2, 0}, {1, 1}
    },
    {
        {0, 0}, {1, 0}, {2, 0}, {2, -1}
    },
    {
        {0, 0}, {1, 0}, {1, -1}, {2, -1}
    },
};

vector<pair<int, int>> rotate(vector<pair<int, int>> tmp, int dir)
{
    vector<pair<int, int>> ret;
    for (int i = 0; i < dir; i++)
    {
        for (auto &j : tmp)
        {                    
            j.first = - j.first;
            swap(j.first, j.second);
        }
    }    
    return ret = tmp;
}
void input()
{
    cin >> n >> m;
    mp.resize(n, vector<int>(m, 0));
    for (auto &i : mp) for (auto &j : i) cin >> j;
}

void solve()
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ans = max(count(i, j), ans);
        }
    }
    cout << ans;
}

int count(int x, int y)
{
    int ret = 0;
    for (auto s : state)
    {
        vector<pair<int, int>> cur, tmp = s;

        for (int dir = 0 ; dir < 4; dir++)
        {
            int p = 0;
            cur = rotate(tmp, dir);
            for (auto c : cur)
            {
                int nx = c.first + x;
                int ny = c.second + y;
                if(out(nx, ny)) 
                {
                    p = -987654321;
                    break;
                }
                else p += mp[nx][ny];
            }
            ret = max(ret, p);
        }
    }
    return ret;
}

int main() {
    input();
    solve();
    return 0;
}