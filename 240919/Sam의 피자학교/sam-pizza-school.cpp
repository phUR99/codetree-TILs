#include <bits/stdc++.h>
#define fastio                       \
    ios_base::sync_with_stdio(NULL); \
    cin.tie(NULL);                   \
    cout.tie(NULL)
using namespace std;
int arr[105];
int board[105][105];
int k;
int n;
void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(2) << setfill('0') << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void roll()
{

    memset(board, -1, sizeof(board));
    for (int i = 0; i < n; i++)
    {
        board[0][i] = arr[i];
    }
    int h = 1;
    int cnt = 1;
    while (true)
    {
        int L = 0;
        for (int i = 0; i <= n; i++)
        {
            if (board[0][i] == -1)
                break;
            L++;
        }
        if (L < 2 * (h))
            return;
        h += (cnt % 2);
        cnt++;

        vector<vector<int>> seq;
        for (int i = 0; i < h - 1; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < n; j++)
            {
                if (board[j][i] == -1)
                    break;
                tmp.push_back(board[j][i]);
                board[j][i] = -1;
            }
            seq.push_back(tmp);
        }
        reverse(seq.begin(), seq.end());
        for (int i = 0; i < h - 1; i++)
        {
            for (int j = 0; j < seq[i].size(); j++)
            {
                board[i + 1][j + h - 1] = seq[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                swap(board[i][j], board[i][j + h - 1]);
            }
        }
    }
}
void rollHalf()
{
    memset(board, -1, sizeof(board));
    for (int i = 0; i < n; i++)
    {
        board[0][i] = arr[i];
    }
    int nn = n;
    for (int t = 0; t < 2; t++)
    {
        nn /= 2;
        vector<vector<int>> seq;
        for (int i = 0; i < nn; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < n; j++)
            {
                if (board[j][i] == -1)
                    break;
                tmp.push_back(board[j][i]);
                board[j][i] = -1;
            }
            reverse(tmp.begin(), tmp.end());
            seq.push_back(tmp);
        }
        reverse(seq.begin(), seq.end());
        for (int i = 0; i < seq.size(); i++)
        {
            for (int j = 0; j < seq[i].size(); j++)
            {
                board[j + t + 1][i + nn] = seq[i][j];
            }
        }

        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                swap(board[j][k], board[j][k + nn]);
            }
        }
    }
}
void compress()
{
    int tmpBoard[100][100];
    memset(tmpBoard, 0, sizeof(tmpBoard));
    int dx[] = {1, 0};
    int dy[] = {0, 1};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == -1)
                continue;
            for (int dir = 0; dir < 2; dir++)
            {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                    continue;
                if (board[nx][ny] == -1)
                    continue;
                int div = (board[i][j] - board[nx][ny]) / 5;
                div = -div;
                tmpBoard[i][j] += div;
                tmpBoard[nx][ny] -= div;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] += tmpBoard[i][j];
        }
    }
    vector<int> ret;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[j][i] == -1)
                continue;
            ret.push_back(board[j][i]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = ret[i];
    }
}
int main()
{
    fastio;
    cin >> n >> k;
    memset(arr, -1, sizeof(arr));
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int cnt = 0;
    while (true)
    {
        int m = *min_element(arr, arr + n);
        int M = *max_element(arr, arr + n);
        if (M - m <= k)
            break;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == m)
                arr[i]++;
        }
        roll();
        // print();
        compress();
        rollHalf();
        // print();
        compress();
        cnt++;
    }
    cout << cnt;

    return 0;
}