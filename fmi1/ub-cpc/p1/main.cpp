#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calc_max_min(const vector<int>& a, const vector<int>& b) {
    int m = a.size();
    int minim = 2147483647;
    for (int k = 0; k < m; ++k) {
        minim = min(minim,max(a[k],b[k]));
    }
    return minim;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> v[i][j];
        }
    }

    int maxs = -1;
    pair<int, int> pereche;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int mina = calc_max_min(v[i], v[j]);
            if (mina > maxs) {
                maxs = mina;
                pereche = {i + 1, j + 1};
            }
        }
    }

    cout << pereche.first << " " << pereche.second << endl;

    return 0;
}
