#include <bits/stdc++.h>
using namespace std;

namespace LinearSolver {

	int MOD = 1000000007;
	typedef vector <int> Poly;

	Poly mult(Poly a, Poly b)
	{
		Poly ans(a.size() + b.size() - 1);

		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < b.size(); j++)
				ans[i + j] = (ans[i + j] + 1LL * a[i] * b[j]) % MOD;
		return ans;
	}

	Poly modulo(Poly a, Poly m)
	{
		// returns a % m
		// m are ceoficientul maximal 1 ->> FF IMPORTANT
		assert(m.back() == 1);

		while (a.size() >= m.size()) {
			int mult = a.back(), dec = a.size() - m.size();
			for (int i = 0; i < m.size(); i++)
				a[i + dec] = (a[i + dec] - 1LL * mult * m[i]) % MOD;
			assert(a.back() == 0);
			a.pop_back();
		}
		return a;
	}

	Poly put(Poly a, int p, Poly m)
	{
		Poly ans = { 1 };
		while (p) {
			if (p & 1) {
				ans = mult(ans, a);
				ans = modulo(ans, m);
			}
			a = mult(a, a);
			a = modulo(a, m);
			p /= 2;
		}
		return ans;
	}

	vector <int> val, coef;

	int solve(int n, int k)
	{
		// vreau al k-lea termen, recurenta este de ordin n
		Poly m(n + 1);
		m.back() = 1;
		for (int i = 1; i <= n; i++)
			m[n - i] = -coef[i];

		Poly x = { 0, 1 };

		x = put(x, k, m);
		int ans = 0;
		for (int i = 0; i < x.size(); i++)
			ans = (ans + 1LL * x[i] * val[i]) % MOD;
		return (ans + MOD) % MOD;
	}

	int brut(int n, int k)
	{
		val.resize(k + 1);
		for (int i = n; i <= k; i++)
			for (int j = 1; j <= n; j++)
				val[i] = (val[i] + 1LL * coef[j] * val[i - j]) % MOD;
		return val[k];
	}

	int LinearSolver(vector <int> vals, vector <int> coefs, int k) {
		// primele n valori, cei n coeficienti
		// vals[k] = sum(vals[k - i]*coefs[i])

		// returneaza al k-lea termen (indexat de la 0)
		 // returneaza fix vals.back() )

		val = vals;
		coef = coefs;
		coef.insert(coef.begin(), 0);
		int n = val.size();

		int ans = solve(n, k);
		//assert(ans == brut(n, k));
		return ans;
	}
}

int main()
{
	vector <int> vals = { 0, 1 };
	vector <int> rec = { 1, 1 };

	int k;
	cin >> k;

	cout << "The k-th Fibbonaci term is ";
	cout << LinearSolver::LinearSolver(vals, rec, k) << '\n';
}