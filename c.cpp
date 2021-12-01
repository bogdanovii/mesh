#include<iostream>//std
#include<cstdlib>//sustem()
#include<fstream>
#include<vector>
#include"f.h"

class TriDeSetka{
	private:
		const std::string border_step_chyzlov_yacheek = "border_step_chyzlov_yacheek_setka";
		const std::string iskrivlenye = "iskrivlenye_setka";
		const std::string massiv_yzlov = "massiv_yzlov_setka";

		const std::vector<std::string> readFile(const std::string filename){

			// ifstream используется для чтения содержимого файла.
                        // Попытаемся прочитать содержимое файла SomeText.txt
                        std::ifstream inf(filename);

                        // Если мы не можем открыть этот файл для чтения его содержимого, 
                        if (!inf){
                                // то выводим следующее сообщение об ошибке и выполняем функцию exit()
                                std::cerr << "Не получается открыть файл на чтение!" << std::endl;
                                exit(1);
                        }

                        // Пока есть данные, которые мы можем прочитать,
                        std::vector<std::string> bscy_s;
                        while (inf){
                                // то перемещаем эти данные в строку, которую затем выводим на экран
                                std::string strInput;
                                inf >> strInput;
                                bscy_s.push_back(strInput);
                        }
			
			const std::vector<std::string> ret{bscy_s};
			return ret;
		}
		
		const std::string checkBSCY{"xStart =", "xFinish =", "yStart =", "yFinish =", "zStart =", "zFinish =", "StepX =", "StepY =", "StepZ ="};
		
		const bool writeFile(const std::string filename, const std::vector<std::string> zapis){
			// Класс ofstream используется для записи данных в файл.
			// Создаем файл SofilenameText.txt
			std::ofstream outf(filename);
 
			// Если мы не можем открыть этот файл для записи данных,
			if (!outf)
			{
				// то выводим сообщение об ошибке и выполняем функцию exit()
				std::cerr << "Uh oh, SomeText.txt could not be opened for writing!" << std::endl;
				return false;
			}
 
			// Записываем в файл следующие две строки
			for(int i = 0; i < zapis.size(); i++){
				outf << zapis.at(i) << std::endl;
			}

			return true;
		}

		void check_bscy(){
			// Пока есть данные, которые мы можем прочитать,
			const std::vector<std::string> bscy_s = 						readFile("border_step_chyzlov_yacheek");
			
			
			//анализируем, что прочитали
			//2*3 границы + 3 шага 3 число узлов + 1 число ячеек
			//итого 13 строк
			bool isNormal = false;
			if(bscy_s.size() <= 13){
				if((bscy_s.size() != 9) && (bscy_s.size() != 13)){
					isNormal = false;
				}
				else{
					for(int i = 0; i < 9; i++){
						if(bscy.at(0).rfind(checkBSCY.at(0)) != 0){
							isNormal = false;
							break;
						}
					}
					isNormal = true;//если не пройдут проверку , то вывести предупреждение
				}
			}
			else{
				isNormal = false;	
			}
			
			//в него будем писать уже
			std::vector<std::string> bscy_r{checkBSCY};

			if(isNormal == false){
				std::cout << "Проблемы с источником" << std::endl;
							

				for(int i = 0; i < bscy_r.size(); i++){
					if(i < 6){
						bscy_r.at(i) = bscy_r.at(i) + " 50*i";
					}
					else{
						bscy_r.at(i) = bscy_r.at(i) + " 10*i";
					}
				}
			
			}
			else{
				
				for(int i = 0; i < 9; i++){
					bscy_r.at(i) = std::stoi(bscy.at(i));
				}
			}
			
			//достраиваем оставшиеся две строки и готово
			//количество узлов вдоль каждой из осей
        		//Количество узлов вдоль каждой оси, ну если все узлы на ось
        		//спроецировать
        		const int N_x =  abs(std::stoi(bscy_r.at(0)) - std::stoi(bscy_r.at(1))) / std::stoi(bscy_r.at(6)) + 1;
        		const int N_y =  abs(std::stoi(bscy_r.at(2)) - std::stoi(bscy_r.at(3))) / std::stoi(bscy_r.at(7)) + 1;
        		const int N_z =  abs(std::stoi(bscy_r.at(4)) - std::stoi(bscy_r.at(5))) / std::stoi(bscy_r.at(8)) + 1;
        		//#Следует понимать, что в это число узловв мы не вклюичли 
        		//#Узел начала оси, поэтому общее число узлов:        
        		const int Number_of_nodes{N_x * N_y * N_z};
			//stoi
			//отладка принт 
			std::cout << Number_of_nodes << std::endl;

			bscy_r.push_back("N_x = " + std::to_string(N_x));
			bscy_r.push_back("N_y = " + std::to_string(N_y));
			bscy_r.push_back("N_z = " + std::to_string(N_z));
			bscy_r.push_back("Number_of_nodes = " + std::to_string(Number_of_nodes));



			//перезаписать файл
			const bool isGoodRes = writeFile("border_step_chyzlov_yacheek", bscy_r);



		}


	public:
		TriDeSetka(){
			//проверяем существование и содержание наших файлов с параметрами сетки
			check_bscy();


		}


};


int main(int argc, char *argv[]){
    
	const bool res_pu_scr = py_script("s.py"); 	
	
	TriDeSetka myMesh;

	//построить сетку, то есть сгенерировать все узлы и записать их в файл
	//const bool res_pu_scr1 = py_script("postroyka_setki.py");


	return 0;
}
