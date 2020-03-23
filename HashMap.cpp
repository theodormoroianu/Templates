
typedef unsigned long long i64;const int NMAX = 10000010;const int DIMMAX = 666013 * 13;
struct Hash {	int head[DIMMAX], cnt, val[NMAX], next[NMAX];	i64 h[NMAX];	int none = -1;
	void clear() {		for (int i = 0; i <= cnt; i++)			head[h[i] % DIMMAX] = 0;		cnt = 0;	}	inline int end() {		return -1;	}	int& find(i64 hs) {		for (int i = head[hs % DIMMAX]; i; i = next[i])			if (h[i] == hs)				return val[i];		return none;	}	int& insert(i64 hs) {		int& x = find(hs);		if (x != -1)			return x;		cnt++;		next[cnt] = cnt;		val[cnt] = 0;		h[cnt] = hs;		swap(next[cnt], head[hs % DIMMAX]);		return val[cnt];	}	int& operator[](i64 hs) {		return insert(hs);	}};
