#include <iostream>
#include <vector>
#define LEFT(x) ((x -1 + 4) % 4)
#define TL 1
#define OK 0
using namespace std;
int n, m, x, y, dir;
vector<vector<int>> mp, visit;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void input();
void solve();
bool out(int nx, int ny) {return nx < 0 || nx >= n || ny < 0 || ny >=m;}

void input()
{
    cin >> n >> m >> x >> y >> dir;
    mp.resize(n, vector<int>(m));
    visit.resize(n, vector<int>(m, 0));
    visit[x][y] = 1;
    for (auto &i  : mp) for (auto &j : i) cin >> j;
}

int seq1(int &cx, int &cy, int &cd)
{    
    cd = LEFT(cd);    
    int nx = cx + dx[cd];
    int ny = cy + dy[cd];    
    if(visit[nx][ny] || mp[nx][ny]) return TL;
    cx = nx;
    cy = ny;

    visit[nx][ny] = 1;    
    return OK;
}
int seq3(int &cx, int &cy, int &cd)
{
    int nx = cx - dx[cd];
    int ny = cy - dy[cd];    
    if(mp[nx][ny]) return TL;
    cx = nx;
    cy = ny;
    return OK;
}

void solve()
{
    int cnt = 0;
    int ans = 0;
    while(1)
    {
        if(seq1(x, y, dir) == OK)
        {
            cnt = 0;
            continue;
        }
        cnt++;         
        if(cnt == 4)
        {
            if(seq3(x, y, dir) == TL) break;
            cnt = 0;
        }                 
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ans += (visit[i][j]);
        }
    }
    cout << ans;
}

int main() {
    input();
    solve();
    return 0;
}