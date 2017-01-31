

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
	
	void TestXML(std::string &&filename/*,std::string dificultat*/) {
		
		
	//llesim el fixer XML i printem per consola
		rapidxml::xml_document<> doc;
		std::ifstream file("XMLFile.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		int buffer_dificultats[15];

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
