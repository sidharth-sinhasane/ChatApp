#include <bits/stdc++.h>
using namespace std;

struct item {
    int value, weight;
};

bool compare(item a, item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<item>& arr) {
    sort(arr.begin(), arr.end(),compare);

    double finalValue = 0.0;
    int currentWeight = 0;

    for(auto& item : arr) {
        if(currentWeight + item.weight <= W) {
            currentWeight += item.weight;
            finalValue += item.value;
            cout<<"value: "<<finalValue<<"  weight: "<<currentWeight<<endl;
        } else {
            int remain = W - currentWeight;
            finalValue += (double)item.value * ((double)remain / item.weight);
            break;
        }
    }
    return finalValue;
}

double fractionalKnapsackDp(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i = 1; i<=n; i++) {
        for(int j = 1; j<=W; j++) {
            if(wt[i-1] <= j) {
                dp[i][j] = max(val[i-1] + dp[i-1][j-wt[i-1]], dp[i-1][j]);
                cout<<dp[i][j]<<" ";
            } else {
                dp[i][j] = dp[i-1][j];
                cout<<dp[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    return dp[n][W];
}

int main() {
    int n, W;
    cout<<"Enter number of items: ";
    cin>>n;
    cout<<"Enter knapsack capacity: ";
    cin>>W;

    /*vector<item> arr(n);
    cout<<"Enter value and weight of each item:"<<endl;
    for(int i = 0; i<n; i++) {
        cin>>arr[i].value >>arr[i].weight;
    }*/

    vector<int> value;
    vector<int> weight;
    for(int i = 0; i<n; i++) {
        int v, w;
        cin>>v>>w;
        value.push_back(v);
        weight.push_back(w);
    }

    double maxvalue = fractionalKnapsackDp(W, weight, value, n);
    cout<<"Maximun value we can obtain = "<<maxvalue<<endl;

    return 0;
}