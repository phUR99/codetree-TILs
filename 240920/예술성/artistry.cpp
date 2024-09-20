#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
int n;
int board[30][30];
int group[30][30];
int solve();
void rotate();
int find(int c1, int c2)
{
    int dx[] = {1, 0};
    int dy[] = {0, 1};
    int ret = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int dir = 0; dir < 2; dir++)
            {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                    continue;
                if ((group[i][j] == c1 && group[nx][ny] == c2) || (group[i][j] == c2 && group[nx][ny] == c1))
                {
                    ret++;
                }
            }
        }
    }
    return ret;
}
void squareRot(int x, int y, int l)
{
    vector<vector<int>> tmpBoard(l, vector<int>(l, 0)), rotBoard(l, vector<int>(l, 0));
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            tmpBoard[i][j] = board[i + x][j + y];
        }
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            rotBoard[j][l - 1 - i] = tmpBoard[i][j];
        }
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            board[i + x][j + y] = rotBoard[i][j];
        }
    }
}
void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void rotate()
{
    int l = (n - 1) / 2;
    squareRot(0, 0, l);
    squareRot(0, l + 1, l);
    squareRot(l + 1, 0, l);
    squareRot(l + 1, l + 1, l);
    vector<int> row, col;
    for (int i = 0; i < 5; i++)
    {
        row.push_back(board[i][l]);
        col.push_back(board[l][i]);
    }
    reverse(col.begin(), col.end());
    for (int i = 0; i < 5; i++)
    {
        board[l][i] = row[i];
        board[i][l] = col[i];
    }
    // print();
}
int solve()
{
    int ret = 0;

    memset(group, -1, sizeof(group));
    queue<pair<int, int>> q;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int cnt = 0;
    vector<pair<int, int>> groupCnt;
    map<int, int> groupNum;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (group[i][j] != -1)
                continue;
            q.push({i, j});
            int m = board[i][j];
            int c = 1;
            groupNum[cnt] = m;
            group[i][j] = cnt;
            while (!q.empty())
            {
                auto cur = q.front();
                q.pop();
                int x = cur.first;
                int y = cur.second;
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                        continue;
                    if (group[nx][ny] != -1 || board[nx][ny] != m)
                        continue;
                    q.push({nx, ny});
                    group[nx][ny] = cnt;
                    c++;
                }
            }
            groupCnt.push_back({cnt, c});
            cnt++;
        }
    }

    for (int i = 0; i < groupCnt.size(); i++)
    {
        for (int j = i + 1; j < groupCnt.size(); j++)
        {
            int cnt1 = groupCnt[i].second;
            int cnt2 = groupCnt[j].second;
            int g1 = groupCnt[i].first;
            int g2 = groupCnt[j].first;
            int cur = find(g1, g2) * groupNum[g1] * groupNum[g2] * (cnt1 + cnt2);
            ret += cur;
        }
    }
    return ret;
}

int main()
{
    fastio;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> board[i][j];
        }
    }
    int answer = 0;
    for (int i = 0; i < 4; i++)
    {
        answer += solve();
        rotate();
    }
    cout << answer;

    return 0;
}