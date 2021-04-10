#include <bits/stdc++.h>

using namespace std;

int lsOne(int n) {
  return n & -n;
}

// Update Fenwick tree
void update(int idx, int val, vector<int>& ft) {
  idx++;
  while (idx <= ft.size()) {
    ft[idx] += val;
    idx += lsOne(idx);
  }
}

int query(int idx, vector<int>& ft) {
  idx++;
  int s = 0;
  while (idx > 0) {
    s += ft[idx];
    idx -= lsOne(idx);
  }
  return s;
}

int main() {

  //cout << "hello world" << "\n";
  
  int N;
  cin >> N;

  // Variables
  vector<int> ft(N + 100, 0);
  vector<int> last_occ(N + 100, -1);

  long long ans = 0;

  for (int i = 0; i < N; i++) {
    //cout << "i: " << i << "\n";
    int el;
    cin >> el;

    if (last_occ[el] != -1) {
      //cout << el << " ";
      update(last_occ[el], -1, ft);

      // Get unique elements
      int unique = query(i, ft) - query(last_occ[el], ft);
      //cout << unique << "\n";
      ans += unique;
    }
    update(i, 1, ft);

    last_occ[el] = i;
  }

  // After that, we want to go from last occurence till the end
  for (int i = 1; i <= N; i++) {
    if (last_occ[i] == -1) continue;

    int unique = query(N - 1, ft) - query(last_occ[i], ft);
    ans += unique;
  }

  cout << ans << "\n";
  return 0;
}