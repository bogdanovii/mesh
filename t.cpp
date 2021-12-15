#include <iostream>
#include <cstdlib> // для использования функции exit()
#include <fstream>
 
int main()
{
	using namespace std;
 
	// Передаем флаг ios:app, чтобы сообщить fstream, что мы собираемся добавить свои данные к уже существующим данным файла.
	// Мы не собираемся перезаписывать файл.
	// Нам не нужно передавать флаг ios::out, поскольку ofstream по умолчанию работает в режиме ios::out
	
	//добавление в конец
	//ofstream outf("SomeText.txt", ios::app);
 
	//gперезапись
	ofstream outf("SomeText.txt", ios::out);

	// Если мы не можем открыть файл для записи данных,
	if (!outf)
	{
		// то выводим следующее сообщение об ошибке и выполняем функцию exit()
		cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
		exit(1);
	}
 
	outf << "See line #3!" << endl;
	outf << "See line #4!" << endl;
 
	return 0;
 
	// Когда outf выйдет из области видимости, то деструктор класса ofstream автоматически закроет наш файл
}
