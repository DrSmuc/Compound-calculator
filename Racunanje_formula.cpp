#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<fstream>
#include<map>
#include<set>
#include<iomanip>
#include<locale>
using namespace std;

class CommaDecimalSeparator : public std::numpunct<char> {
protected:
	char do_decimal_point() const override {
		return ',';
	}
};

double count(string str, int& i) {
	double count = 0;
	int dec_place = 0;
	bool decimal = false;
	for (; i < str.length(); i++) {
		char c = str[i];
		if (c >= '0' && c <= '9') {
			if (decimal) {
				count += ((c - '0') / pow(10, dec_place++));
			}
			else
				count = count * 10 + c - '0';
		}
		else if (c == '+' || c == '-') {
			decimal = false;
			count = 0;
		}
		else if (c == '.') {
			decimal = true;
			dec_place = 1;
		}
		else
			break;
	}
	if (count == 0) return 1;
	return count;
}

int main() {
	vector<pair<string, double>> vec;
	string element;
	double element_count;

	fstream mase;
	mase.open("files/elementi_mase.txt", ios::in);
	map<string, double> mass;
	
	while (1) {
		string x;
		double y;
		mase >> x;
		if (x == "zz") break;
		mase >> y;
		mass[x] = y;
	}
	mase.close();

	fstream input;
	fstream output;
	input.open("files/input.txt", ios::in);
	output.open("files/output.txt", ios::out);
	output.imbue(std::locale(output.getloc(), new CommaDecimalSeparator));

	cout << "Write formulas in 'files' -> input.txt" << endl << endl;

	string focus;
	cout << "Enter element to filter (or 'skip'): ";
	cin >> focus;

	bool skip = false;
	while (1) {
		string formula;
		vec.clear();
		if (!getline(input, formula)) {
			break;
		}

		for (int i = 0; i < formula.length();) {
			char c = formula[i];
			if (c >= 'A' && c <= 'Z') {
				element = c;
				char c2 = formula[i + 1];
				i++;
				if (c2 >= 'a' && c2 <= 'z' && i + 1 <= formula.length()) {
					element += c2;
					i++;
				}
				element_count = count(formula, i);
				vec.push_back({ element, element_count });
			}

			else if (c == '{' || c == '[' || c == '(') {
				vec.push_back({ "x", 0 });
				i++;
			}

			else if (c == '}' || c == ']' || c == ')') {
				i++;
				element_count = count(formula, i);
				int counter = vec.size() - 1;
				for (; vec[counter].first != "x"; counter--)
					vec[counter].second *= element_count;
				vec.erase(vec.begin() + counter);
			}

			else if (c == '·') {
				i++;
				element_count = count(formula, i);
				vec.push_back({ "H", element_count * 2 });
				vec.push_back({ "O", element_count });
				break;
			}

			else if (c==',' || c == '?' || c == 'x' || (c == 'n' && !(formula[i - 1] >= 'A' && formula[i - 1] <= 'Z'))) {
				output << "error" << endl;
				skip = true;
				break;
			}
			else
				i++;
		}

		if (skip) {
			skip = false;
			continue;
		}
		
		/*
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].first << " " << vec[i].second << "\t";
		cout << endl;
		*/
		
		set<string> exists;
		map<string, double> sums;
		double sum = 0;

		for (int i = 0; i < vec.size(); i++) {
			if (exists.count(vec[i].first) > 0)
				sums[vec[i].first] += vec[i].second;
			else {
				sums[vec[i].first] = vec[i].second;
				exists.insert(vec[i].first);
			}
		}

		/*
		cout << endl;
		for (auto a : sums) {
			//cout << a.first << "\t" << sums[a.first] << endl;
		}
		cout << endl;
		*/

		for (auto a : sums) {
			sums[a.first] *= mass[a.first];
			sum += sums[a.first];
		}

		bool focus_active=false;
		for (auto a : sums) {
			sums[a.first] = sums[a.first] * 100 / sum;
			if (focus != "skip" && a.first == focus) {
				output << fixed << setprecision(6) << sums[a.first] << "\t";
				//cout << sums[a.first] << endl;
				focus_active = true;
			}
		}
		if (!focus_active && focus != "skip")
			output << " - " << "\t";

		for (auto a : sums) {
			if (focus_active && a.first == focus)
				continue;
			output << fixed << setprecision(6) << a.first << " " << sums[a.first] << " %\t";
		}
		output << endl;
	}
	cout << endl << "Go to 'files' -> output.txt, copy contents into Excel" << endl;
	input.close();
	output.close();

	return 0;
}