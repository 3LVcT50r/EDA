#include <iostream>
#include <vector>
using namespace std;

int fusiona(vector<int> &a, int e, int m, int d) {
    int inv = 0;
    vector<int> aux(d-e+1);
    int i = e;
    int j = m+1;
    int k = 0;
    while (i <= m and j <= d) {
        if (a[i] <= a[j]) {
            aux[k] = a[i];
            ++i;
            ++k;
        } else {
            aux[k] = a[j];
            ++j;
            ++k;
            inv = inv + (m-i+1);
        }
    }
    while (i <= m) {
        aux[k] = a[i]; ++i; ++k;
    }
    while (j <= d) {
        aux[k] = a[j]; ++j; ++k;
    }

    for (k = 0; k < (d-e+1); ++k) a[e+k] = aux[k];

    return inv;
}

int inversions(vector<int> &v, int e, int d) {
    
    if (e >= d) return 0;
    int inv = 0;
    int m = (e+d)/2;
    int inv_e = inversions(v, e, m);
    int inv_d = inversions(v, m+1, d);
    int inv_f = fusiona(v, e, m, d);
    return inv_e + inv_d + inv_f;
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];

        int inv = inversions(v, 0, n-1);

        cout << inv << endl;
    }
}