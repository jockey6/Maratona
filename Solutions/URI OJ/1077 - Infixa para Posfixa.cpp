#include <bits/stdc++.h>
using namespace std;

#ifdef BALLOONFIELD
__attribute__((destructor))static void __destroy__() {cerr << "\nElapsed: " << (double)clock() / CLOCKS_PER_SEC << "s.\n";}

void debug() {}
template<class t, class... u> void debug(const t &x, const u &...y) {cerr << ' ' << x, debug(y...);}
# define debug(x...) cerr<<"\x1b[91m"<<__LINE__<<" ["#x"] =",debug(x),cerr<<"\x1b[0m\n"
# define sleep(x) this_thread::sleep_for(chrono::milliseconds(x))
#else
# define assert(x) void(0)
# define debug(...) void(0)
# define freopen(...) void(0)
# define sleep(x) void(0)
#endif

template<class A, class B>ostream &operator<<(ostream &f, const pair<A, B> &x) {return f << '(' << x.first << ", " << x.second << ')';}

#define DEF1(_class...) ostream&operator<<(ostream&f,const _class&x){int b=0;f<<'[';for(auto&y:x){if(b++)f<<", ";f<<y;}return f<<']';}
#define DEF2(get,pop,_class...) ostream&operator<<(ostream&f,_class x){int b=0;f<<'[';while(x.size()){if(b++)f<<", ";f<<x.get();x.pop();}return f<<']';}
template<class T> DEF1(vector<T>) template<class T, class C> DEF1(set<T, C>) template<class T, class C> DEF1(multiset<T, C>) template<class K, class T, class C> DEF1(map<K, T, C>) template<class K, class T, class C> DEF1(multimap<K, T, C>)
template<class T> DEF2(front, pop, queue<T>) template<class T> DEF2(top, pop, stack<T>) template<class T, class V, class C> DEF2(top, pop, priority_queue<T, V, C>)

#define null nullptr
#define st first
#define nd second
#define inf 0x3f3f3f3f
#define infl 0x3f3f3f3f3f3f3f3f
#define mod 1000000007
#define maxn "abacate"

#define rand() uid(rng)
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count()); // ll = mt19937_64
uniform_int_distribution<int> uid(0, numeric_limits<int>::max());             // range for random

typedef long long ll;
typedef double lf;
typedef pair<int, int> ii;

int prior[256];

void init() {
  prior['+'] = prior['-'] = 1;
  prior['*'] = prior['/'] = 2;
  prior['^'] = 3;
  prior['('] = prior[')'] = 4;
}

string posfix(string s) {
  // debug(s);
  string eq;
  stack<char> op;
  for (char c : s) {
    debug(c, op, s, eq);
    if (isalnum(c)) {
      eq.push_back(c);
    } else if (c == ')') {
      while (op.top() != '(') {
        eq.push_back(op.top());
        op.pop();
      }
      op.pop();
    } else {
      while (!op.empty() && prior[c] <= prior[op.top()] && op.top() != '(') {
        eq.push_back(op.top());
        op.pop();
      }
      op.push(c);
    }
  }
  while (!op.empty()) {
    eq.push_back(op.top());
    op.pop();
  }
  return eq;
}

int main() {
  freopen("in", "r", stdin);
  cin.sync_with_stdio(0), cin.tie(0);

  init();

  int t;
  cin >> t;
  string s;
  while (t--) {
    cin >> s;
    cout << posfix(s) << '\n';
  }

  return 0;
}
