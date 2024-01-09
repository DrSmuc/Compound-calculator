#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<fstream>
#include<map>
#include<set>
using namespace std;

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

	string formula = "Y(UO2)3(SO4)2O(OH)3(H2O)7·7H2O";
	
	vector<pair<string, double>> vec;
	int counter = 0;
	int vec_pointer = 0;
	string element;
	double element_count;
	map<string, double> sums;


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


	while (1) {

		vec.clear();

		for (int i = 0; i < formula.length();) {
			char c = formula[i];
			if (c >= 'A' && c <= 'Z') {
				element = c;
				char c2 = formula[i + 1];
				i++;
				if (c2 >= 'a' && c2 <= 'z' && i + 1 < formula.length()) {
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
			else {
				cout << "kvadratic" << endl;
				continue;
			}
		}

		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].first << " " << vec[i].second << endl;


		set<string> exists;
		double sum = 0;

		for (int i = 0; i < vec.size(); i++) {
			if (exists.count(vec[i].first) > 0)
				sums[vec[i].first] += vec[i].second;
			else {
				sums[vec[i].first] = vec[i].second;
				exists.insert(vec[i].first);
			}
		}

		cout << endl;
		for (auto a : sums) {
			cout << a.first << "\t" << sums[a.first] << endl;
		}

		for (auto a : sums) {
			sums[a.first] *= mass[a.first];
			sum += sums[a.first];
		}

		cout << endl << endl << formula << endl;
		for (auto a : sums) {
			sums[a.first] /= sum;
			cout << a.first << "\t" << sums[a.first] * 100 << " %" << endl;
		}
		cout << endl << endl;

		break;
	}

	return 0;
}