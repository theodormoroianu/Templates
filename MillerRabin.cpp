typedef long long i64;

namespace MillerRabin {
	inline i64 mult64(i64 a, i64 b, i64 mod) {
		i64 div = 1.L * a * b / mod;
		i64 ans = (a * b - div * mod) % mod;
		return (ans >= 0 ? ans : ans + mod);
	}
	inline i64 put64(i64 a, i64 p, i64 mod) {
		i64 ans = 1;
		while (p) {
			if (p & 1LL)
				ans = mult64(ans, a, mod);
			a = mult64(a, a, mod);
			p /= 2;
		}
		return ans;
	}
	bool fermat_test(i64 nr, i64 p) {
		i64 phi = p - 1;
		int nr2 = 0;
		while (!(phi & 1LL))
			phi /= 2, nr2++;
		nr = put64(nr, phi, p);

		while (nr2--) {
			i64 newnr = mult64(nr, nr, p);
			if (newnr == 1 && (nr != 1 && nr != p - 1))
				return false;
			nr = newnr;
		}
		return (nr == 1);
	}
	vector <int> to_test = { 2, 3, 5, 7, 11, 13, 17 }; /// for more safety of precision add or remove prime numbers
	bool is_prime(i64 x) {
		if (x == 1)
			return false;
		for (auto i : to_test) {
			if (i == x)
				return true;
			if (!fermat_test(i, x))
				return false;
		}
		return true;
	}
}
