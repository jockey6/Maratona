#define putc(c) putc((c), stdout)

struct __IO__ {
  char cur, buf[100];
  __IO__() : cur(' '), buf{} {}

  inline operator bool() { return cur; }

  inline static bool isblank(char c) { return c <= ' '; }
  inline static bool isdigit(char c) { return c <= '9' && c >= '0'; }
  inline char readc() { return cur = (char)getc(stdin); }
  inline void skipBlanks() { while (isblank(cur)) readc(); }

  inline __IO__ &operator >> (char &c) { skipBlanks(); c = cur; readc(); return *this; }

  inline __IO__ &operator >> (char* s) {
    skipBlanks();
    while (*s++ = cur, !isblank(readc()));
    *s = 0;
    return *this;
  }

  inline __IO__ &operator >> (string &s) {
    s.clear();
    skipBlanks();
    while (s.push_back(cur), !isblank(readc()));
    return *this;
  }

  inline __IO__ &operator >> (double &d) { *this >> buf; sscanf(buf, "%lf", &d); return *this; }
  inline __IO__ &operator >> (long double &d) { *this >> buf; sscanf(buf, "%Lf", &d); return *this; }

  template<class intType> inline __IO__ &operator >> (intType &n) {
    skipBlanks();
    int sign = +1;
    if (cur == '-') sign = -1, readc();
    n = cur - '0';
    while (isdigit(readc())) n = (n << 1) + (n << 3) + cur - '0';
    n *= sign;
    return *this;
  }

  inline __IO__ &operator << (bool x) { putc((x ? '1' : '0')); return *this; }
  inline __IO__ &operator << (char c) { putc(c); return *this; }
  inline __IO__ &operator << (char* s) { return *this << (const char*)s; }
  inline __IO__ &operator << (const char* s) { while (*s) putc(*s++); return *this; }
  inline __IO__ &operator << (const string &s) { return *this << s.data(); }

  inline char* toString(double d) { sprintf(buf, "%.9lf%c", d, '\0'); return buf; }
  inline char* toString(long double d) { sprintf(buf, "%.9Lf%c", d, '\0'); return buf; }

  template<class intType> inline char* toString(intType n) {
    char* p = buf + sizeof(buf) - 1;
    bool neg;
    if ((neg = (n < 0))) n = -n;
    *p = 0;
    while (*--p = (char)(n % 10 + '0'), n /= 10);
    if (neg) *--p = '-';
    return p;
  }

  template<class T> inline __IO__ &operator << (T x) { return *this << toString(x); }

  inline void sync_with_stdio(bool) {}
  inline void tie(void*) {}
};

static __IO__ __io__;

#define endl '\n'
#define cin __io__
#define cout __io__
