#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
int n, m, h, k;
deque<int> board[105][105];
deque<int> tmpQ[105][105];
bool tree[105][105];

bool oob(int x, int y)
{
    return x < 1 || x > n || y < 1 || y > n;
}
vector<vector<int>> shape;
void makeShape()
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    int x = (n + 1) / 2;
    int y = (n + 1) / 2;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int k = 0; k < 2; k++)
        {
            cnt %= 4;
            for (int j = 0; j < i - 1; j++)
            {
                x = x + dx[cnt];
                y = y + dy[cnt];
                if (oob(x, y))
                    return;
                shape.push_back({x, y, cnt});
            }
            x = x + dx[cnt];
            y = y + dy[cnt];
            if (oob(x, y))
                return;
            int dir = (cnt + 1) % 4;
            shape.push_back({x, y, dir});
            cnt++;
        }
    }
}
int returnDir(int dir)
{
    if (dir == 0)
        return 2;
    else if (dir == 1)
        return 1;
    else if (dir == 2)
        return 0;
    else
        return 3;
}
void moving(int x, int y)
{
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (abs(x - i) + abs(j - y) > 3)
                continue;
            while (!board[i][j].empty())
            {
                auto dir = board[i][j].front();
                board[i][j].pop_front();
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (oob(nx, ny))
                {
                    dir = (dir + 2) % 4;
                    nx = i + dx[dir];
                    ny = j + dy[dir];
                }
                if (nx == x && ny == y)
                {
                    tmpQ[i][j].push_back(dir);
                }
                else
                {
                    tmpQ[nx][ny].push_back(dir);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            while (!tmpQ[i][j].empty())
            {
                board[i][j].push_back(tmpQ[i][j].front());
                tmpQ[i][j].pop_front();
            }
        }
    }
}
int solve(int x, int y, int d)
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    int nx = x;
    int ny = y;
    int ret = 0;
    for (int i = 0; i < 3; i++)
    {
        if (oob(nx, ny))
            break;
        if (!tree[nx][ny])
        {
            ret += board[nx][ny].size();
            board[nx][ny].clear();
        }
        nx += dx[d];
        ny += dy[d];
    }
    return ret;
}

void makeReverseShape()
{
    int x = 0;
    int y = 1;
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    int cnt = 0;
    for (int i = n; i >= 1; i--)
    {
        for (int k = 0; k < 2; k++)
        {
            cnt %= 4;
            if (i == n && k == 1)
                break;
            for (int j = 0; j < i - 1; j++)
            {
                x = x + dx[cnt];
                y = y + dy[cnt];
                shape.push_back({x, y, returnDir(cnt)});
            }
            x = x + dx[cnt];
            y = y + dy[cnt];
            if (x == (n + 1) / 2 && y == (n + 1) / 2)
            {
                shape.push_back({x, y, returnDir(2)});
                return;
            }
            int dir = (cnt + 1) % 4;
            shape.push_back({x, y, returnDir(dir)});
            cnt++;
        }
    }
}
int main()
{
    fastio;
    cin >> n >> m >> h >> k;
    for (int i = 0; i < m; i++)
    {
        int x, y, dir;
        cin >> x >> y >> dir;
        board[x][y].push_back(dir);
    }
    for (int i = 0; i < h; i++)
    {
        int x, y;
        cin >> x >> y;
        tree[x][y] = true;
    }
    makeShape();
    makeReverseShape();
    int idx = 0;
    int l = shape.size();
    int answer = 0;
    int x = (n + 1) / 2;
    int y = (n + 1) / 2;
    for (int t = 1; t <= k; t++)
    {
        idx %= l;
        moving(x, y);
        x = shape[idx][0];
        y = shape[idx][1];
        int d = shape[idx][2];
        answer += solve(x, y, d) * t;
        idx++;
    }
    cout << answer;
    return 0;
}