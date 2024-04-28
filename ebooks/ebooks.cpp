#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>


using namespace std;


struct Place {
	int stellazh = 0, shkaf = 0, shelf = 0;

	void print() {
		if (stellazh != 0)
			cout << stellazh << "-й стеллаж, ";
		if (shkaf != 0)
			cout << shkaf << "-й шкаф, ";
		cout << shelf << "-я полка" << endl;
	}
	bool operator == (Place const& place) const{
		if ((this->shelf == place.shelf) && (this->shkaf == place.shkaf) && (this->stellazh == place.stellazh))
			return true;
		else return false;
	}

};

struct Book
{
	string id;
	string author;
	string name;
	int year = 0;
	Place place;
	void print()
	{
		cout << id << "	" << author << "\t" << name << "\t" << year << "\t";
		place.print();
	}
	bool operator == (const Book& book) const {
		if ((this->author == book.author) &&
			(this->name == book.name) &&
			(this->year == book.year) &&
			(this->place == book.place))
			return true;
		else return false;
	}

};

void Show(vector<Book> Obj) {
	system("cls");
	cout << "№ " << "Автор\t\t" << "Название\t" << "Год издания\t" << "Местоположение книги";
	cout << "\n============================================\n" << endl;
	for (int i = 0; i < Obj.size(); i++)
	{
		Obj[i].print();
		cout << endl;
	};
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}


Book GetBook(vector<Book> v, string a, string name) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].author.find(a) != string::npos && v[i].name.find(name) != string::npos) {
			cout << endl << "Местоположение книги: ";
			v[i].place.print();
			return v[i];
		}
	}
	cout << "\nТаких книг нет\n";
	Book n;
	return n;
}

vector<Book> GetBook(vector<Book> v, string a) {
	int count = 0;
	vector<Book> find(0);

	for (int i = 0; i < v.size(); i++) {
		if (v[i].author.find(a) != string::npos) {
			count++;
			cout << endl << count << "	";
			find.push_back(v[i]);
			v[i].print();
		}
	}
	if (count == 0)
		cout << "\n Такого автора нет\n";
	return find;
}

vector<Book> GetBook(vector<Book> v, int year) {
	int count = 0;
	vector<Book> find(0);
	for (int i = 0; i < v.size(); i++) {
		if (v[i].year >= year) {
			count++;
			cout << endl;
			cout << count << "	";
			v[i].print();
		}
	}
	if (count == 0)
		cout << "\nТаких книг нет\n";
	return find;
}

bool remove_line(int index) {
	std::vector<std::string> vec;
	std::ifstream file("../ebooks.txt");
	if (file.is_open())
	{
		std::string str;
		while (std::getline(file, str))
			vec.push_back(str);
		file.close();
		// если строк в файле меньше чем индекс удаляемой
		if (vec.size() < index)
			return false;
		//удаление
		vec.erase(vec.begin() + index);
		std::ofstream outfile("../ebooks.txt");
		if (outfile.is_open())
		{
			std::copy(vec.begin(), vec.end(),
				std::ostream_iterator<std::string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}

vector<Book> Delete(vector<Book> v, vector<Book> del) {
	bool ok = false;
	for (int i = 0; i < v.size(); i++) {
		if (find(del.begin(), del.end(), v[i]) != del.end()) {
			if (remove_line(i)) {
				v.erase(v.begin() + i);
				cout << "\nУдаление прошло успешно";
			}
			else
				cout << "\nНе удалось удалить";

		}
	}
	return v;
}

vector<Book> read() {
	ifstream fin("../ebooks.txt");
	if (!fin.is_open()) {
		cout << "Невозможно открыть файл";
	};

	int booksAmount = 0;
	int counter = 0;
	vector <Book> books(0);
	string line = "";
	string temp = "";
	int index;
	Book b;
	while (getline(fin, line)) {
		stringstream ss(line);
		while (getline(ss, temp, '|')) {
			switch (counter) {
			case 0:
				temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
				b.id = temp;
				break;
			case 1:
				b.author = temp;
				break;
			case 2:
				b.name = temp;
				break;
			case 3:
				b.year = stoi(temp);
				break;
			case 4:
				index = temp.find_last_of(',', temp.length());
				b.place.shelf = stoi(temp.substr(index + 1));
				b.place.stellazh = stoi(temp.substr(0, temp.find_first_of(',')));
				b.place.shkaf = stoi(temp.substr(temp.find_first_of(',') + 1, temp.find_last_of(',') - temp.find_first_of(',')));
				break;
			default:
				cout << "Ошибка";
				break;
			}
			counter++;
		}
		counter = 0;	
		books.push_back(b);
	}
	return books;
}


int main(int argc, char* argv[]) {
	string name, author, buf;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	/*_setmode(_fileno(stdout), _O_U16TEXT);
	wcout.imbue(locale("rus_rus.65001"));
	wcin.imbue(locale("rus_rus.65001"));*/

	
	vector<Book> books = read();

	//1 местонахождение книги по автору и названию
	//2 список книг автора 
	//3 список шифр которых начинается с char и изданных после какого-то года
menu:
	int choice;

	int year = 0;
	cout << "\n=================================\n\n";
	cout << "Выберите опцию:\n\n";
	cout << "0 - Выход\n\n";
	cout << "1 - Местоположение книги\n\n";
	cout << "2 - Список книг автора\n\n";
	cout << "3 - Список книг, изданных не позднее заданного года\n\n";
	cout << "4 - Показать полный список книг\n\n";
	cout << "5 - Добавить книгу\n\n";
	cout << "6 - Удалить книгу(-и автора)\n\n";
	cin >> choice;
	cout << "\n";
	Book b;
	string add_file = "     " + to_string(books.size() + 1) + " | ";
	vector <Book> books_to_delete(0);
	ofstream fout;
	string temp;
	int index;

	switch (choice) {
	case 0:
		exit(0);
		break;
	case 1:
		cin.sync();
		cout << "\nАвтор: ";
		getline(cin >> ws, author);
		cout << "\nНазвание книги: ";
		cin.sync();
		getline(cin >> ws, name);
		GetBook(books, author, name);
		break;
	case 2:
		cin.sync();
		cout << "\nАвтор: ";
		getline(cin >> ws, author);
		GetBook(books, author);
		break;
	case 3:
		cout << "\nГод издания: ";
		cin >> year;
		GetBook(books, year);
		break;
	case 4:
		books = read();
		Show(books);
		break;
	case 5:
		cin.sync();
		cout << "\nАвтор: ";
		getline(cin >> ws, b.author);
		cout << "\nНазвание книги: ";
		cin.sync();
		getline(cin >> ws, b.name);
		add_file = add_file + b.author + " | ";
		add_file = add_file + b.name + " | ";

		cout << "\nГод издания: ";
		cin.sync();
		cin >> b.year;
		add_file = add_file + to_string(b.year) + " | ";

		cout << "\nМесто:";
		cin.sync();
		getline(cin >> ws, temp);
		add_file = add_file + temp;
		index = temp.find_last_of(',', temp.length());
		b.place.shelf = stoi(temp.substr(index + 1));
		b.place.stellazh = stoi(temp.substr(0, temp.find_first_of(',')));
		b.place.shkaf = stoi(temp.substr(temp.find_first_of(',') + 1, temp.find_last_of(',') - temp.find_first_of(',')));
		books.push_back(b);
		fout.open("../ebooks.txt", ios::app);
		if (fout.is_open()) {
			fout << add_file << endl;
		}
		fout.close();

		break;
	case 6:
		
		cout << "\nАвтор: ";
		cin.sync();
		getline(cin >> ws, b.author);
		cout << "\nНазвание (- если удалить все книги автора) : ";
		cin.sync();
		getline(cin >> ws, b.name);
		if (b.name == "-") {
			books_to_delete = GetBook(books, b.author);
		}
		else {
			books_to_delete.push_back(GetBook(books, b.author, b.name));
		}
		books = Delete(books, books_to_delete);
		break;

	default:
		cout << "Такой опции нет\n";
	}
	goto menu;
}