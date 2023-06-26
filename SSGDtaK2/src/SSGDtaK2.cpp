#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

int get_size(FILE *file);
string read_tag(FILE *file, int readloc, int size);
void read_data(FILE *file);

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
