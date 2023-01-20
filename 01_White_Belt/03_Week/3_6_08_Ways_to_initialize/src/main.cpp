class Incognizable {
public:
	Incognizable() {
		i={};
		j={};
	}

	Incognizable(int _i) {
		i = _i;
		j={};
	}
	Incognizable(int _i, int _j) {
		i=_i;
		j=_j;
	}
private:
	int i, j;

};

int main() {
	Incognizable a;
	Incognizable b = { };
	Incognizable c = { 0 };
	Incognizable d = { 0, 1 };
	return 0;
}
