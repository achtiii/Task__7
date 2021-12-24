
#include <iostream>
#include<string>
#include <sstream>
#include <fstream>

void Words(std::string str_, char symbol_);
void Nametxt(std::string& fileName_);
bool NameVal(std::string fileName_);
bool isExistFile(std::string fileName_);

int main()
{
	setlocale(LC_ALL, "Russian");
	std::string fileName = "";
	char symbol;
	std::cout << "Введите букву, на которую мы будем искать слова: ";
	std::cin >> symbol;
	Nametxt(fileName);
	// Открытие файла на чтение
	std::ifstream in(fileName);
	std::string str;
	while (!in.eof())
	{
		std::getline(in, str);
		Words(str, symbol);
	}

	system("pause");

	std::cout << "Введите строку: ";
	std::getline(std::cin, str);
	Words(str, symbol);

	return 0;
}

void Words(std::string str_, char symbol_)
{
	std::string word = "";
	int size = 255;
	std::string* arrWords = new std::string[size];
	std::stringstream words(str_);
	int i = 0;
	while (words >> word)
	{
		if (word[0] == symbol_)
		{
			arrWords[i] = word;
			i++;
		}
	}
	i = 0;
	int count = 0;
	while (i < size)
	{
		for (int j = 0; j < size; j++)
		{
			if (arrWords[i] == arrWords[j])
				count++;
		}
		if (count >= 0)
		{
			std::cout << arrWords[i] << "\n";
			i += count;
			count = 0;
		}
	}
}

void Nametxt(std::string& fileName_)
{
	std::cout << "Файл должен находиться в папке с проектом. Пример имени файла: fileName.txt" << std::endl;
	std::cout << "Введите имя файла: ";
	do
	{
		std::getline(std::cin, fileName_); // проверка корректности введенного
		bool isCheck = true;
		if (!NameVal(fileName_))
			isCheck = false;
		if (isCheck && !isExistFile(fileName_))
		{
			std::cout << "Файл с таким именем не найден. Введите имя файла еще раз.\n";
			fileName_ = "";
		}
		else
			std::cout << "Имя файла введено верно\n";
	} while (fileName_ == "");
}

// Проверка имени файла на корректность
bool NameVal(std::string fileName)
{
	char failWord[] = " /\\:?*<>|\"";
	int isCheck = false;
	int count = 0;
	if (fileName.length() < 1)
	{
		std::cout << "Не корректная длина имени файла. Введите еще раз." << "\n";
		return false;
	}
	for (int i = 0; i < fileName.length(); i++)
	{
		for (int j = 0; j < sizeof(failWord); j++)
		{
			if (fileName[i] == failWord[j])
			{
				std::cout << "Не корректное имя файла. Введите еще раз." << "\n";
				return false;
			}
		}
	}

	return true;
}

// Проверка на существование файла c введенным именем
//
bool isExistFile(std::string fileName_)
{
	std::ifstream in(fileName_);
	if (in.is_open())
	{
		in.close();
		return true;
	}
	else
		return false;
}

