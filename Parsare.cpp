#include <bits/stdc++.h>
using namespace std;


class InputReader {
public:
	InputReader() {
		input_file = fopen(stdin, "r");
	}

	InputReader(const char* file_name) {
		input_file = fopen(file_name, "r");
	}

	inline InputReader& operator >>(int& n) {
		advance();
		while (buffer[cursor] < '0' || buffer[cursor] > '9')
			advance();

		n = 0;
		while ('0' <= buffer[cursor] && buffer[cursor] <= '9') {
			n = n * 10 + buffer[cursor] - '0';
			advance();
		}
		return *this;
	}
private:
	FILE* input_file;
	static const int SIZE = 1 << 17;
	int cursor = SIZE;
	char buffer[SIZE];

	inline void advance() {
		++cursor;
		if (cursor == SIZE) {
			cursor = 0;
			fread(buffer, SIZE, 1, input_file);
		}
	}
};
