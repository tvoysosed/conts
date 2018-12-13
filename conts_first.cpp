#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
using namespace std;

struct Student {
	string Name;
	string GroupId;
	map<string, int> Ratings;

	//небольшой конструктор для простоты
	Student(string _name,string _gr,map<string,int> _rtg)
		:Name(_name),
		 GroupId(_gr),
		 Ratings(_rtg){}
};

//перегруженный оператор вывода в поток (cout)
ostream& operator<<(ostream& os, const Student& st) {
	cout << st.Name << "; " << st.GroupId << "; ";
	cout << "Оценки: ";
	for (auto i : st.Ratings) {
		cout << i.first << ": " << i.second << "; ";
	}
	return os;
}

//считаем среднее значение
double calc(const map<string, int>& a) {
	int sum = 0;
	for (auto i : a) sum += i.second;
	return (double)sum / a.size();
}

//для тестирования
int main() {

	//предположим
	vector<Student> students = {
		Student("Ivan","1",{pair<string,int>("Math",5),pair<string,int>("Politic",4),pair<string,int>("Biology",5) }),
		Student("Andrey","2",{ pair<string,int>("Math",4),pair<string,int>("Politic",5),pair<string,int>("Biology",5) }),
		Student("Sasha","3",{ pair<string,int>("Math",4),pair<string,int>("Politic",2),pair<string,int>("Biology",4) }),
		Student("Kirill","4",{ pair<string,int>("Math",5),pair<string,int>("Politic",5),pair<string,int>("Biology",5) }),
		Student("Vadim","5",{ pair<string,int>("Math",5),pair<string,int>("Politic",3),pair<string,int>("Biology",2) })
	};

	cout << "Список студентов:" << endl;
	for (auto i : students) {
		cout << i <<endl;
	}
	cout << endl;

	//сортировка по имени
	sort(students.begin(), students.end(), [](const Student& a,const Student& b) {return a.Name.compare(b.Name) < 0; }); //в алфавитном

	cout << "Список студентов отсортированный по имени:" << endl;
	for (auto i : students) {
		cout << i << endl;
	}
	cout << endl;

	//сортировка студентов по средней оценке
	sort(students.begin(), students.end(), [](const Student& a,const Student& b) {
		return calc(a.Ratings) < calc(b.Ratings); });
	
	cout << "Список студентов отсортированный по средней оценке:" << endl;
	for (auto i : students) {
		cout << i << endl;
	}

	cout <<endl<< "Кол-во студентов имеющих неудовлетворительную оценку: ";
	cout << count_if(students.begin(), students.end(), [](const Student& a) {
		return (count_if(a.Ratings.begin(), a.Ratings.end(),[](const pair<string, int>& b) {return b.second == 2; }) > 0) ? true : false; }) << endl;

	cout << endl << "Кол-во студентов сдавших все экзамены на 5: ";
	cout << count_if(students.begin(), students.end(), [](const Student& a) {
		return (count_if(a.Ratings.begin(), a.Ratings.end(), [](const pair<string, int>& b) {return b.second == 5; }) == 3) ? true : false; }) << endl;

	vector<Student> exlents; //отличники
	
	copy_if(students.begin(), students.end(), back_inserter(exlents), [](const Student& a) {
		auto it = a.Ratings.find("Math");  
		if(it != a.Ratings.end()) {
			return (it->second == 5) ? true : false;
		}
		else return false;
	});

	cout <<endl<< "Список отличников по математике:" << endl;
	for (auto i : exlents) {
		cout << i << endl;
	}
	cout << endl;

	//выставляем отметку хорошо всем студентам по предмету Политология - Politic
	transform(students.begin(), students.end(), students.begin(), [](Student& a) {
		auto it = a.Ratings.find("Politic");
		if (it != a.Ratings.end()) {
			it->second = 5;
		}
		return a;
	});

	cout << "Измененный список студентов:" << endl;
	for (auto i : students) {
		cout << i << endl;
	}

	cout << endl;
	system("pause");
	return 0;
}
