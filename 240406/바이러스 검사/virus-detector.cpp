#include <iostream>
using namespace std;

long long ans = 0;
long long arr[1000005];
int n, a, b;

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++){
        cin >> arr[i];
    }
    cin >> a >> b;
    for (int i = 0; i < n; i ++){
        int cnt = 1;
        if (arr[i] > a){
            cnt += ((arr[i] - a) % b == 0) ? (arr[i] - a) / b + 1 : (arr[i] - a) / b;
        }
        ans += cnt;
    }
    cout << ans;
    return 0;
}