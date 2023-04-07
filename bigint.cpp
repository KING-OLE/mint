#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<long> s {290797};
  int m {1000003};
  long v=s[0];
  for (int i=1; i<m; i++) {
    long newv=(v*v)%50515093;
    v=newv;
    s.push_back(v);
  }

  cout << s.size() << endl;

  vector<long long> r {0,0,0};

  for (long i=0; i<(m-1); i++) {
    for (long j=(i+1); j<m; j++) {
      long long sisj = s[i]*s[j];
      if (sisj < 479000000000000) {
        r[0]+=1;
      } else if (sisj < 481000000000000) {
        r[1]+=1;
      } else {
        r[2]+=1;
      }
    }
    cout << i << ' ' << r[0] << ' ' << r[1] << ' ' << r[2] << endl;
  }


  return 0;
}
