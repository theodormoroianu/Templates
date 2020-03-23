#include <bits/stdc++.h>
using namespace std;

struct Dinic {
	struct Edge {
		int to, flow, next;
	};
	vector <Edge> edges;
	vector <int> head, act, h;
	int S, D;

	void AddEdge(int from, int to, int f, int rev_f = 0) {
		edges.push_back({ to, f, (int)edges.size() });
		swap(edges.back().next, head[from]);
		edges.push_back({ from, rev_f, (int)edges.size() });
		swap(edges.back().next, head[to]);
	} /// rev_f = ce flux pun pe muchia inversa, ca sa nu adaug dublu in mod inutil

	bool bfs() {
		fill(h.begin(), h.end(), -1);
		h[S] = 0;
		vector <int> q = { S };
		for (int it = 0; it < q.size() && h[D] == -1; it++) {
			int nod = q[it];
			for (int i = head[nod]; i != -1; i = edges[i].next)
				if (edges[i].flow && h[edges[i].to] == -1)
					h[edges[i].to] = 1 + h[nod], q.push_back(edges[i].to);
		}
		return h[D] != -1;
	}

	int dfs(int nod, int flow) {
		if (flow == 0 || nod == D)
			return flow;
		while (act[nod] != -1) {
			Edge& e = edges[act[nod]];
			int d;
			if (e.flow && h[e.to] == 1 + h[nod] && (d = dfs(e.to, min(flow, e.flow))) != 0) {
				e.flow -= d;
				edges[act[nod] ^ 1].flow += d;
				return d;
			}
			act[nod] = edges[act[nod]].next;
		}
		return 0;
	}

	int GetFlow() {
		int f = 0;
		while (bfs()) {
			act = head;
			int d;
			while ((d = dfs(S, 1e9)) != 0)
				f += d;
		}
		return f;
	}

	Dinic(int dim = 0, int s = 0, int d = 0) : head(dim + 1, -1), h(dim + 1), S(s), D(d) { }
};

struct FlowWithMinRestrictions {
	struct Edge {
		int from, to, flowmin, flowmax, id;
		/// id is used to check where it is placed in the dinic's edges
	};
	vector <Edge> edges;
	int S, D, n;

	void AddEdge(int from, int to, int flowmin, int flowmax) {
		edges.push_back({ from, to, flowmin, flowmax, 0 });
	}

	vector <int> Solve(bool& feasible, int& flow) {
		feasible = 1;
		flow = 0;

		int news = n + 1, newd = n + 2;
		Dinic first_flow(n + 2, news, newd);
		first_flow.AddEdge(D, S, 1e9);
		int s_minime = 0;

		for (auto& i : edges) {
			if (i.flowmax < i.flowmin) {
				feasible = 0;
				return vector <int> ();
			} /// imposibil

			s_minime += i.flowmin;
			i.id = first_flow.edges.size(); /// unde imi regasesc cat am folosit din muchie
			first_flow.AddEdge(i.from, i.to, i.flowmax - i.flowmin);
			first_flow.AddEdge(news, i.to, i.flowmin);
			first_flow.AddEdge(i.from, newd, i.flowmin);
			/// teleportez unitatile de flux cu care nu stiu ce sa fac
			/// ca fluxul maxim sa le forteze sa treaca prin sistem
		}

		if (first_flow.GetFlow() != s_minime) {
			feasible = 0;
			return vector <int>();
			/// nu a reusit sa teleporteze tot, deci nu exista solutie
		}

		Dinic curent_flow(n, S, D);

		for (auto& i : edges) {
			/// din muchia asta sigur am trecut i.flowmin
			int dif = i.flowmax - i.flowmin;
			int passed = dif - first_flow.edges[i.id].flow;
			/// passed e cate au trecut in plus de flowmin
			int nid = curent_flow.edges.size();
			curent_flow.AddEdge(i.from, i.to, first_flow.edges[i.id].flow, passed);
			i.id = nid;
		}

		curent_flow.GetFlow();

		vector <int> ans(edges.size());

		for (int i = 0; i < edges.size(); i++) {
			int cntflow = curent_flow.edges[edges[i].id ^ 1].flow + edges[i].flowmin;
			ans[i] = cntflow;
			if (edges[i].from == S)
				flow += cntflow;
			if (edges[i].to == S)
				flow -= cntflow;
		}
		return ans;
	}

	FlowWithMinRestrictions(int n = 0, int s = 0, int d = 0) : n(n), S(s), D(d) { }
};


///https://codeforces.com/contest/704/problem/D
