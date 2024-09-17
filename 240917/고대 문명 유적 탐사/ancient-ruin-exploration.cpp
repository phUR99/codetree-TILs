#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
int board[5][5];
int k, m;
queue<int> legacy;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void rot(int i, int j);
int bfs();
bool cmp(vector<int> &a, vector<int> &b)
{
    if (a[0] == b[0])
    {
        if (a[1] == b[1])
        {
            if (a[3] == b[3])
            {
                return a[2] < b[2];
            }
            return a[3] < b[3];
        }
        return a[1] < b[1];
    }
    return b[0] < a[0];
}
bool cmp2(pair<int, int> &a, pair<int, int> &b)
{
    if (a.second == b.second)
        return b.first < a.first;
    return a.second < b.second;
}

int find()
{
    vector<vector<int>> arr;

    for (int l = 1; l <= 3; l++)
    {
        for (int i = 1; i < 4; i++)
        {
            for (int j = 1; j < 4; j++)
            {
                for (int o = 1; o <= l; o++)
                {
                    rot(i, j);
                }
                int cnt = bfs();
                arr.push_back({cnt, l, i, j});
                for (int o = 1; o <= 4 - l; o++)
                {
                    rot(i, j);
                }
            }
        }
    }
    sort(arr.begin(), arr.end(), cmp);
    int x = arr[0][2];
    int y = arr[0][3];
    int t = arr[0][1];
    for (int i = 1; i <= t; i++)
    {
        rot(x, y);
    }

    return arr[0][0];
}
void del()
{
    bool visited[5][5];
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (visited[i][j])
                continue;
            visited[i][j] = true;
            queue<pair<int, int>> q;
            q.push({i, j});
            vector<pair<int, int>> trace;
            trace.push_back({i, j});
            int num = board[i][j];
            while (!q.empty())
            {
                auto cur = q.front();
                int x = cur.first;
                int y = cur.second;
                q.pop();
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
                        continue;
                    if (visited[nx][ny] || board[nx][ny] != num)
                        continue;
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                    trace.push_back({nx, ny});
                }
            }
            if (trace.size() < 3)
                continue;
            for (auto e : trace)
            {
                int x = e.first;
                int y = e.second;
                board[x][y] = 0;
            }
        }
    }
}
int bfs()
{
    int ret = 0;
    queue<pair<int, int>> q;
    bool visited[5][5];
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (visited[i][j])
                continue;
            visited[i][j] = true;
            q.push({i, j});
            int cnt = 1;
            int num = board[i][j];
            while (!q.empty())
            {
                auto cur = q.front();
                int x = cur.first;
                int y = cur.second;
                q.pop();
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5)
                        continue;
                    if (visited[nx][ny] || board[nx][ny] != num)
                        continue;
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                    cnt++;
                }
            }
            if (cnt < 3)
                cnt = 0;
            ret += cnt;
        }
    }

    return ret;
}
void rot(int i, int j)
{
    int tmpBoard[3][3], rotBoard[3][3];
    memset(tmpBoard, 0, sizeof(tmpBoard));
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
            tmpBoard[x - (i - 1)][y - (j - 1)] = board[x][y];
        }
    }
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            rotBoard[y][2 - x] = tmpBoard[x][y];
        }
    }

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            board[x + i - 1][y + j - 1] = rotBoard[x][y];
        }
    }
}
void fill()
{
    vector<pair<int, int>> arr;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == 0)
                arr.push_back({i, j});
        }
    }
    sort(arr.begin(), arr.end(), cmp2);
    for (auto e : arr)
    {
        int x = e.first;
        int y = e.second;
        int c = legacy.front();
        legacy.pop();
        board[x][y] = c;
    }
}

int main()
{
    fastio;
    cin >> k >> m;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int t;
        cin >> t;
        legacy.push(t);
    }
    for (int i = 0; i < k; i++)
    {
        int answer = 0;
        answer += find();

        del();

        fill();

        while (bfs() != 0)
        {
            answer += bfs();

            del();

            fill();
        }
        if (answer == 0)
            break;
        cout << answer << ' ';
    }

    return 0;
}