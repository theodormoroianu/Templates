#include <bits/stdc++.h>
using namespace std;

/*
	Works with prime modulo p = 2^k * c, where 2^k >= N, N being the size of the polinomial to be multiplied
*/

#define MOD 998244353
#define root 3

int put(int x, int p)
{
	int ans = 1;
	while (p) {
		if (p & 1)
			ans = 1LL * ans * x % MOD;
		p /= 2;
		x = 1LL * x * x % MOD;
	}
	return ans;
}

void NTT(int* v, int n, int inv = 1)
{
	int r = (inv == 1 ? root : put(root, MOD - 2));

	for (int i = 0, j = 0; i < n; i++) {
		if (i < j)
			swap(v[i], v[j]);
		for (int k = n / 2; (j ^= k) < k; k /= 2)
			;
	}

	for (int l = 2; l <= n; l *= 2) {
		int k = put(r, MOD / l); /// <=> (mod - 1) / l

		for (int i = 0; i < n; i += l) {
			for (int j = 0, k0 = 1; j < l / 2; j++, k0 = 1LL * k0 * k % MOD) {
				int a = v[i + j], b = 1LL * k0 * v[i + j + l / 2] % MOD;
				v[i + j] = (a + b) % MOD;
				v[i + j + l / 2] = (a - b + MOD) % MOD;
			}
		}
	}

	if (inv == -1) {
		int mult = put(n, MOD - 2);
		for (int i = 0; i < n; i++)
			v[i] = 1LL * v[i] * mult % MOD;
	}
}

vector <int> NTT(vector <int> a, vector <int> b)
{
	int l = a.size() + b.size();

	while ((l & -l) != l)
		l += (l & -l);
	a.resize(l), b.resize(l);

	NTT(a.data(), l);
	NTT(b.data(), l);

	for (int i = 0; i < l; i++)
		a[i] = 1LL * a[i] * b[i] % MOD;

	NTT(a.data(), l, -1);

	return a;
}


int main()
{
	int a, b;
	cin >> a >> b;
	vector <int> v1(a), v2(b);

	for (auto& i : v1)
		cin >> i;
	for (auto& i : v2)
		cin >> i;

	auto ans = NTT(v1, v2);

	for (auto i : ans)
		cout << i << ' ';

	return 0;
}