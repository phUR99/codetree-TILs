#include <iostream>
#include <vector>
#include <queue>
#define FIRE 2
#define WALL 1
#define ROAD 0
using namespace std;
int n, m, ans = 0;
vector<vector<int>> mp;
void input();
void solve();
void dfs(int cnt, int st);
int bfs();
bool out(int nx, int ny) {return nx < 0 || nx >= n || ny < 0 || ny >=m;}

int bfs()
{
    int ret = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    vector<vector<int>> visit(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if(mp[i][j] == FIRE && visit[i][j] == 0)
            {
                queue<pair<int, int>> q;
                q.push({i, j});
                visit[i][j] = 1;
                while(!q.empty())
                {
                    auto cur = q.front(); q.pop();
                    for (int dir = 0; dir < 4; dir++)
                    {
                        int nx = dx[dir] + cur.first;
                        int ny = dy[dir] + cur.second;
                        if(out(nx, ny)) continue;
                        if(mp[nx][ny] == WALL || visit[nx][ny] == 1) continue;
                        q.push({nx, ny});
                        visit[nx][ny] = 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ret += (mp[i][j] == ROAD && visit[i][j] != 1);
        }
    }
    return ret;
}



void dfs(int cnt, int st)
{
    int MX = m * n;
    if(cnt == 3)
    {
        ans = max(bfs(), ans);
        return;
    }
    for (int i = st; i < MX; i++)
    {
        int x = i / m;
        int y = i % m;
        if(mp[x][y]) continue;
        mp[x][y] = WALL;
        dfs(cnt + 1, i);
        mp[x][y] = ROAD;
    }
}

void input()
{
    cin >> n >> m;
    mp.resize(n, vector<int>(m, 0));
    for (auto &i : mp) for (auto &j : i) cin >> j;
}

void solve()
{
    dfs(0, 0);
    cout << ans;
}

int main() {
    input();
    solve();
    return 0;
}