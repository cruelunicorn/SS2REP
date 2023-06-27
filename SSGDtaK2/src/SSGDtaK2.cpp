#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

// додаткова функція, яка створює рандомний масив чисел та сортує бульбашкою
int sort_function()
{
	srand (time(NULL));
	const int n = 40;
	int i, j, temp;
	int array[n];
	for(i = 0; i < n; i++)
		{
			array[i] = rand() % 100 + 1;
			cout << array[i] << " ";
		}
	cout << endl;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(array[j] < array[i]) {
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
	for(i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl << endl;
	return 0;
}

int get_size(FILE *file);
string read_tag(FILE *file, int readloc, int size);
void read_data(FILE *file);
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
	if (argc < 2)
	{
		char str[128];
		cout << "Введіть шлях до .mp3 файлу:" << endl;
		cin.ignore();
		cin.getline(str, 129);
		path = str;
	}
	else path = argv[1];

	if (path.length() <= 4 || path.substr(path.length() - 4, 4) != ".mp3")
	{
		cout << "Відбулася помилка. Вибраний вами файл не є формату .mp3. Натисніть Enter для завершення програми." << endl;
		cin.get();
		return 0;
	}

	FILE *file;
	file = fopen(argv[1], "r+");

	if (!file)
	{
		cout << "Відбулася помилка під час відкриття файлу. Натисніть Enter для завершення програми." << endl;
		cin.get();
		return 0;
	}

	int readloc = get_size(file) - 128;
	if (read_tag(file, readloc, 4).substr(0, 3) != "TAG")
	{
		cout << "Вдібулася помилка. Вибраний вами файл не відповідає стандарту тегів ID3v1. Натисніть Enter для завершення програми." << endl;
		fclose(file);
		cin.get();
		return 0;
	}

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

int get_size(FILE *file)
{
	int loc = ftell(file);
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, loc, SEEK_SET);
	return size;
}

string read_tag(FILE *file, int readloc, int size)
{
	char temp[size];
	fseek(file, readloc, SEEK_SET);
	fread(temp, 1, size, file);
	string str(temp);
	return str;
}

void read_data(FILE *file)
{
	int size = get_size(file);
	cout << "Назва: " << read_tag(file, size - 125, 30) << endl;
	cout << "Виконавець: " << read_tag(file, size - 95, 30) << endl;
	cout << "Альбом: " << read_tag(file, size - 65, 30) << endl;
	cout << "Рік: " << read_tag(file, size - 35, 4) << endl;
	cout << "Коментар: " << read_tag(file, size - 31, 30) << endl << endl;
	return;
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
