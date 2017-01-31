

#pragma once
#include <string>

// Define path to store our resources (images, fonts, lvl data, audio,...)
//Primerament definim que RESOURCE_PATH anira fins la carpeta res
#define RESOURCE_PATH "../../res/"
//Aqui sumem el RESOURCE_PATH + filename que es dintre del res on volem accedir. 
#define RESOURCE_FILE(filename) (RESOURCE_PATH + (filename)).c_str()