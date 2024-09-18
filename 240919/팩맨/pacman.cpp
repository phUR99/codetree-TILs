#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
deque<int> cur_q[5][5], tmp_q[5][5];
int t, m;
pair<int, int> packMan;
int board[5][5];
vector<vector<int>> seq;
void printQ();
bool oob(int x, int y)
{
    return x < 1 || x > 4 || y < 1 || y > 4;
}
void copy()
{
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            for (auto e : cur_q[i][j])
            {
                tmp_q[i][j].push_back(e);
            }
        }
    }
}
void takeMove()
{
    deque<int> nxt_q[5][5];
    // ↑, ↖, ←, ↙, ↓, ↘, →, ↗
    int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            while (!cur_q[i][j].empty())
            {
                int dir = cur_q[i][j].front();
                cur_q[i][j].pop_front();
                int nx = i;
                int ny = j;
                int nxt = -1;
                for (int dd = 0; dd < 8; dd++)
                {
                    nx = i + dx[(dd + dir) % 8];
                    ny = j + dy[(dd + dir) % 8];
                    int px = packMan.first;
                    int py = packMan.second;
                    if (oob(nx, ny))
                        continue;
                    if (nx == px && ny == py)
                        continue;
                    if (board[nx][ny])
                        continue;
                    nxt = dd;
                    break;
                }
                if (nxt == -1)
                {
                    nxt_q[i][j].push_back(dir);
                    continue;
                }
                nx = i + dx[(nxt + dir) % 8];
                ny = j + dy[(nxt + dir) % 8];
                nxt_q[nx][ny].push_back({(nxt + dir) % 8});
            }
        }
    }
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            for (auto e : nxt_q[i][j])
            {
                cur_q[i][j].push_back(e);
            }
        }
    }
}

void packManMove()
{
    vector<vector<int>> ret;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    bool visited[5][5];
    for (auto ar : seq)
    {
        int x = packMan.first;
        int y = packMan.second;
        int sum = 0;
        memset(visited, 0, sizeof(visited));
        bool notMatched = false;
        for (auto dir : ar)
        {
            x += dx[dir];
            y += dy[dir];
            if (oob(x, y))
            {
                notMatched = true;
                break;
            }
            if (visited[x][y])
                continue;
            visited[x][y] = true;
            sum += cur_q[x][y].size();
        }
        if (notMatched)
            continue;
        ret.push_back({-sum, ar[0], ar[1], ar[2]});
    }
    sort(ret.begin(), ret.end());

    vector<int> &f = ret[0];
    int &px = packMan.first;
    int &py = packMan.second;
    for (int i = 1; i < f.size(); i++)
    {
        px += dx[f[i]];
        py += dy[f[i]];
        if (!cur_q[px][py].empty())
            board[px][py] = 3;
        cur_q[px][py].clear();
    }
}
void print()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void printQ()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            cout << cur_q[i][j].size() << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void decayed()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            board[i][j] = max(0, board[i][j] - 1);
        }
    }
}
void load()
{
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            for (auto e : tmp_q[i][j])
            {
                cur_q[i][j].push_back(e);
            }
            tmp_q[i][j].clear();
        }
    }
}
int main()
{
    fastio;
    cin >> m >> t;
    cin >> packMan.first >> packMan.second;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                seq.push_back({i, j, k});
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        int r, c, d;
        cin >> r >> c >> d;
        d--;
        cur_q[r][c].push_back(d);
    }
    for (int i = 0; i < t; i++)
    {
        copy();
        takeMove();
        packManMove();
        load();
        decayed();
    }
    int answer = 0;
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            answer += cur_q[i][j].size();
        }
    }
    cout << answer;
    return 0;
}