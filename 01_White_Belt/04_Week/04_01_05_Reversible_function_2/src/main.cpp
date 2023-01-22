#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FunctionPart {
public:
	FunctionPart(char new_operation, double new_value) {
		operation = new_operation;
		value = new_value;
	}
	double Apply(double source_value) const {
		if (operation == '+') {
			source_value += value;
		} else if (operation == '-') {
			source_value -= value;
		} else if (operation == '*') {
			source_value *= value;
		} else if (operation == '/') {
			source_value /= value;
		}
		return source_value;
	}
	void Invert() {
		if (operation == '+') {
			operation = '-';
		} else if (operation == '-') {
			operation = '+';
		} else if (operation == '*') {
			operation = '/';
		} else if (operation == '/') {
			operation = '*';

		}
	}

private:
	char operation;
	double value;
}
;

class Function {
public:
	void AddPart(char operation, double value) {
		parts.push_back( { operation, value });
	}

	double Apply(double source_value) const {
		for (const auto &item : parts) {
			source_value = item.Apply(source_value);
		}
		return source_value;
	}

	void Invert() {
		for (auto &item : parts) {
			item.Invert();
		}
		reverse(parts.begin(), parts.end());
	}

private:
	vector<FunctionPart> parts;
};
/*
struct Param {
	int p1;
	int p2;
};

struct Obj {
	int a;
	int b;
};

Function makeFoo(const Param &par, const Obj &obj) {
	Function foo;
	foo.AddPart('+', par.p1 * obj.b);
	foo.AddPart('-', par.p2);
	return foo;
}

double FooFrom_A(const Param &par, const Obj &obj) {
	Function foo = makeFoo(par, obj);
	return foo.Apply(obj.a);
}

double BarFor_A(const Param &par, const Obj &obj, double fooRez) {
	Function foo = makeFoo(par, obj);
	foo.Invert();
	return foo.Apply(fooRez);;
}

int main() {

	Param par1 = { 5, 9 };
	Obj obj1 = { 3, 6 };

	cout << FooFrom_A(par1, obj1) << endl;
	cout << BarFor_A(par1, obj1, 15) << endl;

	return 0;
}
*/struct Image {
	  double quality;
	  double freshness;
	  double rating;
	};

	struct Params {
	  double a;
	  double b;
	  double c;
	};

	Function MakeWeightFunction(const Params& params,
	                            const Image& image) {
	  Function function;
	  function.AddPart('*', params.a);
	  function.AddPart('-', image.freshness * params.b);
	  function.AddPart('+', image.rating * params.c);
	  return function;
	}

	double ComputeImageWeight(const Params& params, const Image& image) {
	  Function function = MakeWeightFunction(params, image);
	  return function.Apply(image.quality);
	}

	double ComputeQualityByWeight(const Params& params,
	                              const Image& image,
	                              double weight) {
	  Function function = MakeWeightFunction(params, image);
	  function.Invert();
	  return function.Apply(weight);
	}

	int main() {
	  Image image = {10, 2, 6};
	  Params params = {4, 2, 6};
	  cout << ComputeImageWeight(params, image) << endl;
	  cout << ComputeQualityByWeight(params, image, 52) << endl;
	  return 0;
	}
