
using i64 = int;
const i64 INFINIT = 1e9;

struct Graph {
	struct Edge {
		int to, cost, flow;
	};
	vector <Edge> edges;
	vector <vector <int>> adia;
	vector <int> tata;
	vector <int> d;
	int S, D, n;

	inline bool bellman() {
		d = vector <int>(n, INFINIT);
		tata[S] = tata[D] = -1;
		d[S] = 0;
		vector <int> Q = { S };
		vector <bool> in_queue(n, 0);
		in_queue[S] = 1;

		for (int q = 0; q < Q.size(); q++) {
			int nod = Q[q];
			if (nod == D)
				continue;
			for (auto i : adia[nod]) {
				if (edges[i].flow && d[edges[i].to] > d[nod] + edges[i].cost) {
					d[edges[i].to] = d[nod] + edges[i].cost;
					tata[edges[i].to] = i;
					if (!in_queue[edges[i].to])
						in_queue[edges[i].to] = 1, Q.push_back(edges[i].to);
				}
			}
			in_queue[nod] = 0;
		}
		return (tata[D] != -1);
	}

	bool dijkstra() {
		/// costul unei muchii (a, b) de cost c o sa fie d[a] - d[b] + c care e mereu >= 0
		vector <int> newd(n, INFINIT);
		tata[S] = tata[D] = -1;
		newd[S] = 0;
		priority_queue <pair <i64, int>> pq;
		pq.push({ 0, S });
		while (!pq.empty()) {
			auto x = pq.top();
			pq.pop();
			int nod = x.second;
			if (newd[nod] != -x.first)
				continue;
			i64 c = newd[nod] + d[nod];
			for (auto i : adia[nod]) {
				if (edges[i].flow && newd[edges[i].to] > c + edges[i].cost - d[edges[i].to]) {
					newd[edges[i].to] = c + edges[i].cost - d[edges[i].to];
					tata[edges[i].to] = i;
					pq.push({ -newd[edges[i].to], edges[i].to });
				}
			}
		}
		for (int i = 0; i < n; i++)
			d[i] += newd[i];
		return (tata[D] != -1);
	}

	inline void add_edge(int a, int b, int cap, int cost) {
		adia[a].push_back(edges.size());
		edges.push_back({ b, cost, cap });
		adia[b].push_back(edges.size());
		edges.push_back({ a, -cost, 0 });
	}

	pair <i64, i64> get_flow() {
		tata = vector <int>(n);
		i64 ans = 0, cost = 0;
		bellman();
		while (dijkstra()) {
			int cap = 1e9;
			for (int i = tata[D]; ~i; i = tata[edges[i ^ 1].to])
				cap = min(cap, edges[i].flow);
			for (int i = tata[D]; ~i; i = tata[edges[i ^ 1].to]) {
				cost += 1LL * cap * edges[i].cost;
				edges[i].flow -= cap;
				edges[i ^ 1].flow += cap;
			}
			ans += cap;
		}
		return make_pair(ans, cost);
	}

	Graph() { }
	Graph(int n, int s, int d) : S(s), D(d), n(n + 1), adia(n + 1) { }
} G;
