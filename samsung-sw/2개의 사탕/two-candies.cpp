#include <iostream>
#include <vector>
using namespace std;

#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
int n, m, ans;
vector<string> mp;

void input(void);
void solve(void);
void scene(int p);
int move(int di, vector<string> &t_mp);
bool out(int nx, int ny) {return nx < 0 || nx >= n || ny < 0 || ny >= m;}


int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void input(void)
{
    cin >> n >> m;
    mp.resize(n);
    for (auto &i : mp) cin >> i;
    ans = 987654321;
}

void solve(void)
{
    int MX = 1 << 20;
    for (int i = 0; i < MX; i++)
    {
        scene(i);
    }
    if(ans > 10) ans = -1;
    cout << ans;
}

void scene(int p)
{
    int tmp;
    vector<string> t_mp;
    t_mp = mp;
    int pre = -1;
    for (tmp = 1; tmp <= 10; tmp++)
    {
        int di = p % 4;
        if(pre == di) return;
        p /= 4;               
        int res = move(di, t_mp);
        if(res == 1) return;
        else if(res == 2) break;
        pre = di;
    }
    ans = min(ans, tmp);
}

int run(int di, int x, int y, vector<string> &t_mp)
{
    int cnt = 1;
    int nx, ny;
    while (1)
    {
        nx = cnt * dx[di] + x;
        ny = cnt * dy[di] + y;
        if(t_mp[nx][ny] == 'O') {
            t_mp[x][y] = '.';
            return 1;            
        }
        if(t_mp[nx][ny] != '.') break;
        cnt++;
    }
    cnt--;
    nx = cnt * dx[di] + x;
    ny = cnt * dy[di] + y;
    swap(t_mp[nx][ny], t_mp[x][y]);
    return 0;
}
int move(int di, vector<string> &t_mp)
{
    int rx, ry, bx, by;
    int b, r;
    for (int i = 0; i < n; i++)
    {
        int ty = t_mp[i].find('R');
        if(ty != -1)
        {
            rx = i;
            ry = ty;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int ty = t_mp[i].find('B');
        if(ty != -1)
        {
            bx = i;
            by = ty;
            break;
        }
    }
    switch (di)
    {
        case 0 :
        {
            if(bx < rx)
            {
                b = run(di, bx, by, t_mp);
                r = run(di, rx, ry, t_mp);
            }
            else
            {
                r = run(di, rx, ry, t_mp);
                b = run(di, bx, by, t_mp);
            }
            break;
        }
        case 1 :
        {
            if(bx > rx)
            {
                b = run(di, bx, by, t_mp);
                r = run(di, rx, ry, t_mp);
            }
            else
            {
                r = run(di, rx, ry, t_mp);
                b = run(di, bx, by, t_mp);                
            }
            break;
        }
        case 2 :
        {
            if(by < ry)
            {
                b = run(di, bx, by, t_mp);
                r = run(di, rx, ry, t_mp);
            }
            else
            {
                r = run(di, rx, ry, t_mp);
                b = run(di, bx, by, t_mp);                
            }
            break;
        }   
        case 3 :
        {
            if(by > ry)
            {
                b = run(di, bx, by, t_mp);
                r = run(di, rx, ry, t_mp);
            }
            else
            {
                r = run(di, rx, ry, t_mp);
                b = run(di, bx, by, t_mp);                
            }
            break;
        }
        default :
            break;
    }
    if (b) return 1;
    else if (r) return 2;
    else return 0;
}
int main() {
    fastio;
    input();
    solve();
    return 0;
}