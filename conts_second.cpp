#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
using namespace std;

struct Entity {
	string Quary;
	float Frequency;
	Entity(string _q,float _f):Quary(_q),Frequency(_f){}
};

ostream& operator<<(ostream& os, const Entity& e) {
	os <<"{'"<< e.Quary << "', " << e.Frequency <<"}";
	return os;
}

//загрузка словаря из файла
multimap<string, Entity> load(const string& fname) {
	ifstream ins(fname);
	multimap<string, Entity> dict;
	if (ins.is_open()) {
		string f, s;
		float fg;
		while (!ins.eof()) {
			ins >> f >> s >> fg;
			dict.insert(pair<string,Entity>(f,Entity(s,fg)));
		}
	}
	else {
		cout << "Файл не найден!" << endl;
	}
	ins.close();
	return dict;
}

using Dict = multimap<string, Entity>;
vector<Entity> suggest(const Dict& d, const string& current_word) {
	vector<Entity> vec;
	auto it = find_if(d.begin(), d.end(), [current_word](const pair<string, Entity>& a) {return a.first == current_word; });
	while (it != d.end()) {
		vec.push_back(it->second);
		it = find_if(++it, d.end(), [current_word](const pair<string, Entity>& a) {return a.first == current_word; });
	}
	if (vec.size()) sort(vec.begin(), vec.end(), [](const Entity& a, const Entity& b) {return a.Frequency > b.Frequency; }); //сортируем по частоте
	return vec;
}

//для тестирования
int main() {

	multimap<string, Entity> dict = load("dictionary.txt");
	if (dict.size()) {
		cout << "Словарь полученный из файла dictionary.txt:" << endl;
		for (auto i : dict) {
			cout << i.first << " -> " << i.second << endl;
		}
	}
	else {
		cout << "Словарь пуст!" << endl;
	}
	cout << endl;

	vector<Entity> result = suggest(dict, "добрый");

	if (result.size()) {
		cout << "Результат предложения 'добрый' :" << endl;
		for (auto i : result) {
			cout << i <<"; ";
		}
		cout << endl;
	}
	else {
		cout << "Ничего нет по данному предложению..." << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}
