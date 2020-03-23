/// Dinic

struct Dinic {
	struct Edge {
		int flow, to, next;
	};
	vector <Edge> edges;
	vector <int> adia, at, dist;
	int S, D;

	void add_Edge(int from, int to, int cap) {
		edges.push_back({ cap, to, adia[from] });
		adia[from] = edges.size() - 1;
		edges.push_back({ 0, from, adia[to] });
		adia[to] = edges.size() - 1;
	}

	bool bfs() {
		queue <int> q;
		fill(dist.begin(), dist.end(), 1e9);
		dist[S] = 0;
		q.push(S);
		while (!q.empty()) {
			int x = q.front();
			q.pop();

			for (int i = adia[x]; i != -1; i = edges[i].next) {
				if (dist[edges[i].to] > dist[x] + 1 && edges[i].flow) {
					dist[edges[i].to] = 1 + dist[x];
					q.push(edges[i].to);
				}
			}
		}
		return dist[D] < 1e9;
	}
	int dfs(int nod, int fmax) {
		if (nod == D)
			return fmax;
		while (at[nod] != -1) {
			Edge& e = edges[at[nod]];
			int f;
			if (dist[e.to] == dist[nod] + 1 && e.flow && (f = dfs(e.to, min(fmax, e.flow)))) {
				e.flow -= f;
				edges[at[nod] ^ 1].flow += f;
				return f;
			}
			at[nod] = edges[at[nod]].next;
		}
		return 0;
	}

	int GetFlow() {
		int f = 0;
		while (bfs()) {
			at = adia;
			while (int x = dfs(S, 1e9))
				f += x;
		}
		return f;
	}
	Dinic(int n = 0, int s = 0, int d = 0) {
		S = s, D = d;
		at = dist = adia = vector <int>(n + 1, -1);
	}
};
