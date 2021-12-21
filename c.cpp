#include<iostream>//std
#include<cstdlib>//sustem()
#include<fstream>
#include<vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem.hpp>
#include<boost/lexical_cast.hpp>
#include <regex>
#include <unistd.h>

#include"f.h"
#include "class.h"



//пишем по аджайлу, добавляем приписки с дефектом функционала
int main(int argc, char *argv[]){

	//const bool res_pu_scr = py_script("s.py");
	//эта фигня загружает данные из файла и строит сетку
	std::cerr << "Внимание. в данной програмее надо задавать по всем осям одинакове длины и шаг. так как гдето написанно для симметрии и сейчас нет времени искать эту строчку с ошибкой" << std::endl;
	TriDeSetka myMesh;

	//отправляем нашу сетку в принтер,ч тобыон сгенериовалвтк файл
	Printer myPrinter(&myMesh);

	//вызываем метод печати, как параллепипед
	const bool res{myPrinter.print_Paralepip("cppMyX_Y_Z.vtk")};

	//построить сетку, то есть сгенерировать все узлы и записать их в файл
	//дважды запускать, чтобы это сработало
	//const bool res_pu_scr1 = py_script("mp.py");

	//когда сетка потроена, вызвать принтер передав в него сетку , в классе сетка должен быть тип сетки


	/**************************Тестовая область***********/




	return 0;
}/*main*/
