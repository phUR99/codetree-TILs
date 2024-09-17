#include <iostream>
#include <algorithm>

#define MAX_N 100000
#define MAX_R 200000

using namespace std;

// 변수 선언
int n;
int x1[MAX_N], x2[MAX_N];
int checked[MAX_R + 1];

int ans;

int main() {
    // 입력:
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> x1[i] >> x2[i];
    
    // 주어진 좌표의 범위가 작을 때에는
    // 배열을 이용하여 직접 각 칸에
    // +1 -1을 진행해도 무방합니다.
    for(int i = 0; i < n; i++) {
        checked[x1[i]]++;
        checked[x2[i]]--;
    }

    // 모든 곳을 조사해보며
    // 그 중 가장 많이 겹치는 횟수를 구합니다.
    // 겹치는 횟수는
    // 각 위치에 적혀있는 숫자들의 합을 누적해주면 구해집니다.
    int overlapped_cnt = 0;
    for(int i = 1; i <= MAX_R; i++) {
        overlapped_cnt += checked[i];
        ans = max(ans, overlapped_cnt);
    }
    
    cout << ans;
    return 0;
}