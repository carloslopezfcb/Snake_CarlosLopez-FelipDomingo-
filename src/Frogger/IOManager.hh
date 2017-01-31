

#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.h"
#include "Assert.hh"
#include "Resource.h"
#include <vector>
#include <XML/rapidxml_utils.hpp>
using namespace Logger;




namespace IOManager {

	// Base test function for XML purposes (TODO)
	
	int buffer_dificultats[15];

	




	void TestXML(std::string &&filename/*,std::string dificultat*/) {
		
		
	//llesim el fixer XML i printem per consola
		rapidxml::xml_document<> doc;
		std::ifstream file("XMLFile.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		

		std::cout << "Nombre de la raíz:" << doc.first_node()->name() << "\n";
		rapidxml::xml_node<> *pRoot = doc.first_node();
						int i = 0;		for ( rapidxml::xml_node<> *pNode = pRoot->first_node("dif"); pNode; pNode = pNode->next_sibling())		{
			rapidxml::xml_attribute<> *pAttr = pNode->first_attribute();			/*std::cout << pAttr->name() << '-' << pAttr->value() << '\n';*/

			
			for ( rapidxml::xml_node<>*pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
			{
				/*std::cout << pNodeI->name() << ':' << pNodeI->value() << '\n';*/
				
				int num = atoi(pNodeI->value());
				buffer_dificultats[i] = num;
				std::cout << pNodeI->name() << ':' << buffer_dificultats[i] << '\n';
				
				i++;

			}
		}
		






	}

	int LLegirXML(string difficulty,int q_volem ) {
		TestXML("XMLFile.xml");
		int val;
		
		if (difficulty == "easy")
			val = 1;
		else if (difficulty == "medium")
			val = 2;
		else if (difficulty == "hard")
			val = 3;
		
		switch (val)
		{

		case 1:
			if(q_volem==1)//caselles
				return  buffer_dificultats[0];
			else if(q_volem==2)//init pomes
				return  buffer_dificultats[3];
			else if (q_volem == 3)//v_inicial
				return  buffer_dificultats[1] ;
			else if (q_volem == 4)//murs
				return  buffer_dificultats[4];
			else if (q_volem == 5)//temps
				return  buffer_dificultats[2];
		case 2:
			if (q_volem == 1)
				return buffer_dificultats[5];
			else if (q_volem == 2)
				return  buffer_dificultats[8];
			else if (q_volem == 3)
				return  buffer_dificultats[6];
			else if (q_volem == 4)
				return  buffer_dificultats[9];
			else if (q_volem == 5)//temps
				return  buffer_dificultats[7];
		case 3:
			if (q_volem == 1)
				return buffer_dificultats[10];
			else if (q_volem == 2)
				return  buffer_dificultats[13];
			else if (q_volem == 3)
				return  buffer_dificultats[11] ;
			else if (q_volem == 4)
				return  buffer_dificultats[14];
			else if (q_volem == 5)//temps
				return  buffer_dificultats[12];
		default:
			break;
		}


	}
	///LLegeix la informacio del fixer on guarda l'inici, a la carpeta lvl hi ha un fixer, llegeix aquesta informacio per a l'escena aplicar-ho a la grid
	// Loader function that takes level info for a grid
	//Función de cargador que toma la información de nivel para una cuadrícula
	//no ho utilitzarem en cap moment ja que nosaltres ho llesim d'un fixer XML
	std::vector<std::vector<ObjectID>> LoadLevel(std::string &&filename, int &rows, int &cols) {
		std::ifstream fileData(RESOURCE_FILE(filename));
		ASSERT(fileData.good());
		//lvlData: vector de ObjectID
		std::vector<std::vector<ObjectID>> lvlData;
		std::string line;
		//get::line extrae la linea de fileData i la pone en el string line
		//si no hay lineas sales del while
			while (std::getline(fileData, line)) {

				std::istringstream strData(std::move(line));
				lvlData.emplace_back(std::istream_iterator<ObjectID>(std::move(strData)), std::istream_iterator<ObjectID>());
			}
		rows = int(lvlData.size()); cols = int(lvlData[0].size());
		//
		fileData.close();
		//printa per consola la grid amb 1 ,2,3,0.. depenen del candy 
#pragma region DEBUG_DATA
		Println("Level: ", filename);
			for (auto &r : lvlData) {
				for (auto &c : r) Print(c, ' ');
				Endln();
			}
#pragma endregion
		return std::move(lvlData);
	}

}
