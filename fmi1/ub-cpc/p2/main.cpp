#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define NMAX 1e9

ll lcm(ll x,ll y){
    return 1LL*(x*y/gcd(x,y));
}

ll t,n,a,l;
set<ll> rez, s;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 

    cin>>t;
    while(t--){
        cin>>n;
        rez.clear();
        s.clear();
        for (int i=0; i<n; i++){
            cin>>a;
            set<ll> temp;
            temp.insert(a);
            rez.insert(a);
            for (auto x: s) {
                l=lcm(x, a);
                if (l<NMAX){
                    temp.insert(l);
                    rez.insert(l);
                }
            }
            s=temp;
        }
        int x=1;
        while(rez.count(x)){
            x++;
        }
        cout<<x<<'\n';
    }

    return 0;
}
