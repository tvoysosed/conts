# STL
 ## Задание 1
Пусть есть структура `Student`
```cpp
struct Student
{
  std::string Name;
  std::string GroupId;
  std::map<std::string, unsigned> Ratings;
};
```
Поле `Ratings` представляет из себя словарь со списком предметов и оценок, полученнных по этому предмету.
 Предположим есть список студентов `std::vector<Student> students`.
 Выполните следующие действия с этим списком:
* отсортируйте всех студентов по именам;
* отсортируйте всех студентов по средней оценке;
* определите, сколько студентов имеют неудовлетворительную оценку хотя бы по одному предмету;
* определите, сколько студентов сдали все экзамены на 5.
* создайте массив `std::vector<Student> exlents`, в который войдут студенты имеющие отметку отлично, по предмету "Math";
* выставьте всем студентам отметку "хорошо" по предмету "Политология".
 Для выполнения этого задания воспрользуйтесь алгоритмами `count_if, transform, copy_if, sort` и лямбда функциями.
 ## Задание 2
Вы разрабатываете мобильную клавиатуру. Для пользователя важной характеристикой является скорость ввода сообщений. Поэтому вы решили сделать новый функционал: вы пытаетесь угадать следующее слово, которое хочет ввести пользователь. Например, пользователь уже ввел слово "Добрый", вы предполагаете, что скорее всего следующее слово, которое захочет ввести пользователь это "вечер". Почему именно "вечер"? Потому что аналитик исследовал все сообщения в интернете и знаете, что после слово "Добрый", слово "вечер" встречается в 10 случаях из 100, а слово "сок" в 7 случаях из 100 и т.д. Аналитик предоставил текстовый словарь, в котором написано предыдущее слово, последующее слово и частота
```
добрый сок 0.07
добрый вечер 0.1
добрый утро 0.01
добрый человек 0.02
спокойной ночи 0.21
спокойного сна 0.11
...
```
 Системный архитектор решил ввести в проект структуру `Entity`. В которой будет встрчаться слово, которое требудется подсказать пользователю и частота, которую предоставил аналитик.
```cpp
struct Entity
{
  std::string Query;
  float Frequency;
};
```
 Все `Entity` будут храниться в `std::multimap<std::string, Entity>`, где ключ, это текущее слово, а значение - соответсвующие этому слову `Entity`.
 ```cpp
std::multimap<std::string, Entity> dict;
dict["добрый"] = {"сок", 0.07};
dict["добрый"] = {"вечер", 0.1};
dict["добрый"] = {"утро", 0.01};
dict["добрый"] = {"человек", 0.02};
dict["спокойной"] = {"сок", 0.21};
dict["спокойного"] = {"сна", 0.11};
```
 Вам требуется реализовать функцию загрузки словаря из файла, который предоставил аналитик.
```cpp
std::multimap<std::string, Entity> load(const std::string& filename);
```
 Также необходимо реализовать фунцию, которая вернет отсортированный по частоте массив `Entity` по заданному ключу.
```cpp
using Dict = std::multimap<std::string, Entity>;
std::vector<Entity> suggest(const Dict&, const std::string& currentWord);
```
Пример
```cpp
auto dict = load("db.txt");
auto result = suggest(dict, "добрый");
// result == {"вечер", 0.1}, {"сок", 0.07}, {"человек", 0.02}, {"утро", 0.01}
```
