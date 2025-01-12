#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define NMAX 200005

ll t,n,a,s;
vector<ll> v(NMAX);

void solve(){
    cin>>n;
    v.resize(n);
    v.clear();
    for (int i=0; i<n; i++){
        cin>>a;
        v.push_back(a);
    }
    sort(v.begin(),v.end());
    if(v[0]!=1){
        cout<<"NO\n";
        return;
    }
    s=1;
    for(int i=1;i<n;i++){
        if(s<v[i]){
            cout<<"NO\n";
            return;
        }
        s+=v[i];
    }
    cout<<"YES\n";
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
