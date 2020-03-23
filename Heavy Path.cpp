
using Pii = pair <int, int>;

namespace HP {
	const int NMAX = 100010;
	int h[NMAX], link[NMAX], id[NMAX], tata[NMAX], g[NMAX], cnt;
	vector <int> adia[NMAX];

	int calc_g(int nod, int t) {
		g[nod] = 1;
		h[nod] = 1 + h[t];
		tata[nod] = t;
		for (auto i : adia[nod])
			if (i != t)
				g[nod] += calc_g(i, nod);
		return g[nod];
	}
	void calc_id(int nod) {
		int fmax = NMAX - 1;
		id[nod] = cnt++;
		for (auto i : adia[nod])
			if (i != tata[nod] && g[i] > g[fmax])
				fmax = i;
		if (fmax != NMAX - 1)
			link[fmax] = link[nod], calc_id(fmax);
		for (auto i : adia[nod])
			if (i != tata[nod] && i != fmax)
				link[i] = i, calc_id(i);
	}
	vector <Pii> get_intervs(int a, int b) {
		vector <Pii> ans;
		while (link[a] != link[b]) {
			if (h[link[a]] < h[link[b]])
				swap(a, b);
			ans.push_back({ id[link[a]], id[a] });
			a = tata[link[a]];
		}
		/// acum sunt neaparat pe ac lant
		if (h[a] < h[b])
			swap(a, b);
		ans.push_back({ id[b], id[a] });
		return ans;
	}
	void calc() {
		link[1] = 1;
		calc_g(1, 0);
		calc_id(1);
	}
}
