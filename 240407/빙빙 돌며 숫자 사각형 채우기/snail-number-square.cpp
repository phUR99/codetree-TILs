#include <bits/stdc++.h>
using namespace std;

int n, m;
bool inRange(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <=m ;
}
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int board[105][105];
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int cnt = 1;
    int x =1, y = 1;
    board[x][y] = cnt;
    int dir =0;
    while (cnt < n * m)
    {
        if(inRange(x + dx[dir], y + dy[dir]) && board[x+dx[dir]][y+dy[dir]] == 0){
            cnt++;
            x += dx[dir];
            y += dy[dir];
            board[x][y] = cnt; 
        }
        else{
            dir = (dir + 1) % 4;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for(int j = 1; j <=m; j++){
            cout<< board[i][j] << ' ';
        }
        cout << '\n';
    }
    


    return 0;    
}