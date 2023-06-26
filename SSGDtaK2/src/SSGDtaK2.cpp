#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

void write_tag(FILE *file, int offset, char str[]);
void write_artist(FILE *file, char artist[]);
void write_title(FILE *file, char title[]);
void write_album(FILE *file, char album[]);
void write_year(FILE *file, char year[]);
void write_comment(FILE *file, char comment[]);

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string path = "";
	for (int item = 1; item > 0;)
	{
		cout << "========================================" << endl;
		cout << "0: Закінчити роботу програми." << endl;
		cout << "1. Редагувати Назву." << endl;
		cout << "2. Редагувати Виконавця." << endl;
		cout << "3. Редагувати Альбом." << endl;
		cout << "4. Редагувати Рік." << endl;
		cout << "5. Редагувати Коментар." << endl;
		cout << "6. Продивитись усі теги файлу." << endl << endl;
		cout << "Введіть номер з вищенаведених операцій: ";
		cin >> item;
		char input[31];
		switch (item)
		{
			case 0:
				break;
			case 1:
				cout << "Введіть Назву треку: " << endl;
				cin.ignore();
				cin.getline(input, 31);
				write_title(file, input);
				break;
			case 2:
				cout << "Введіть Виконавця: " << endl;
				cin.ignore();
				cin.getline(input, 31);
				write_artist(file, input);
				break;
			case 3:
				cout << "Введіть Назву альбому: " << endl;
				cin.ignore();
				cin.getline(input, 31);
				write_album(file, input);
				break;
			case 4:
				cout << "Введіть Рік випуску: " << endl;
				cin.ignore();
				cin.getline(input, 5);
				write_year(file, input);
				break;
			case 5:
				cout << "Введіть Коментар до треку: " << endl;
				cin.ignore();
				cin.getline(input, 31);
				write_comment(file, input);
				break;
			case 6:
				cout << endl;
				read_data(file);
				break;
			default:
				cout << "Даного номера немає у списку операцій. Спробуйте ще раз." << endl;
				item = 1;
				break;
		}
	}
	fclose(file);
	cin.get();
	return 0;
}

void write_tag(FILE *file, int offset, char str[])
{
	int writeloc = get_size(file) + offset;
	fseek(file, writeloc, SEEK_SET);
	fwrite(str, 1, 30, file);
}

void write_title(FILE *file, char title[])
{
	write_tag(file, -125, title);
	cout << "Назву треку було змінено на " << title << endl << endl;
}

void write_artist(FILE *file, char artist[])
{
	write_tag(file, -95, artist);
	cout << "Виконавця було змінено на " << artist << endl << endl;
}

void write_album(FILE *file, char album[])
{
	write_tag(file, -65, album);
	cout << "Назву альбома було змінено на " << album << endl << endl;
}

void write_year(FILE *file, char year[])
{
	write_tag(file, -35, year);
	cout << "Рік випуску було змінено на " << year << endl << endl;
}

void write_comment(FILE *file, char comment[])
{
	write_tag(file, -31, comment);
	cout << "Коментар було змінено на " << comment << endl << endl;
}
