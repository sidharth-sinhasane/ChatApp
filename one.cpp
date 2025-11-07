#include <bits/stdc++.h>
using namespace std;

int fib(int n) {
    if(n <= 1) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}

int fib1(int n) {
    vector<int> res;
    int fibn , fibn1 = 0, fibn2 = 1;
    res.push_back(fibn1);
    res.push_back(fibn2);
    for(int i = 2; i<=n; i++) {
        fibn = fibn1 + fibn2;
        fibn1 = fibn2;
        fibn2 = fibn;
        res.push_back(fibn2);
    }
    for(int x : res) {
        cout<<x<<" ";
    }
    cout<<endl;
    return fibn;
}

int fibDp(int n) {
    vector<int> dp(n,1);

    for(int i = 2; i< n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n-1];
}


int main() {
    int n;
    cout<<"Enter the Number: ";
    cin>>n;

    cout<<fibDp(n);
}