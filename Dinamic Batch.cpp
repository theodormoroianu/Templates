/// NOT FULLY TESTED -> TO TEST ON AT LEAST A PROBLEM :)

const int order = -1; /// -1 if minimum, 1 if maximum
#define inf 1e18
struct Line {
	double a, b, intersect; /// Line is y = a * x + b
	bool enabled;
	Line(double a, double b) : a(a), b(b), enabled(1), intersect(inf) { }
	Line(double a) : intersect(a), enabled(0) { }
	double val(double x) const { return a * x + b; }
	bool operator< (const Line& l) const {
		if (!enabled || !l.enabled)
			return intersect < l.intersect;
		if (a == l.a)
			return b * order < l.b * order;
		return a * order < l.a * order;
	}
	double cross(const Line & l, bool replace = 0) const {
		double loc = (b - l.b) / (l.a - a);
		if (replace)
			const_cast <Line*> (this)->intersect = loc;
		return loc;
	}
};

struct Batch : set <Line> {
	double Query(double loc) {
		iterator it = lower_bound(loc);
		if (it == end()) {
			cerr << "No line :(\n";
			assert(0);
		}
		return it->val(loc);
	}
	void Add(double a, double b) {
		Line l(a, b);
		iterator it = insert(l).first;
		if (next(it) != end() && next(it)->a == a || bad(it)) {
			erase(it);
			return;
		}
		if (it != begin() && prev(it)->a == a)
			erase(prev(it));
		while (it != begin() && bad(prev(it)))
			erase(prev(it));
		while (next(it) != end() && bad(next(it)))
			erase(next(it));
		if (it != begin())
			prev(it)->cross(*it, 1);
		if (next(it) != end())
			it->cross(*next(it), 1);
		else
			const_cast <Line&>(*it).intersect = inf;
	}
	bool bad(iterator it) {
		/// if line it is bad. It is bad if it's neither the first and the last, and the
		/// intersection between prev(it) and next(it) <= prev(it) and it
		return it != begin() && next(it) != end() && it->cross(*prev(it)) >= prev(it)->cross(*next(it));
	}
};
