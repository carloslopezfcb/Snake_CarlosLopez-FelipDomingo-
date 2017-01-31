#pragma once
#include <stdio.h>
#include <iostream>				//Management of cin and cout
#include <fstream>				//Management of files
#include <cstdlib>				//Management of system functions such as pause
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include "Playerrankin.h"

using namespace std;

class Leaderboard
{
	int _numOfPlayers;
	PlayerR *arrayPlayers;

public:
	Leaderboard() {

		_numOfPlayers = 9;
		arrayPlayers = 0;

	}
	~Leaderboard() {

		delete[] arrayPlayers;
	}

	void CreateLeadBoard(int size) {
		arrayPlayers = new PlayerR[size];

		for (int i = 0; i < size; i++) {

			arrayPlayers[i] = PlayerR("", 0);
		}
	}

	void AddPlayer(char filename[100], std::string name, int score) {


		PlayerR p(name, score);
		int sizePerson = sizeof(PlayerR);
		std::fstream myInputOutputFile;

		//Create the file with a random population
		myInputOutputFile.open(filename, std::ios::in | std::ios::out | std::ios::binary);

		if (!myInputOutputFile.is_open()) {
			throw std::exception("[ChangePerson] System was not able to open the file");
		}
		//Move the get pointer in order to read the personID position
		//myInputOutputFile.seekg(sizePerson );

		//Move the put pointer in order to override the personID position
		arrayPlayers[0].UpdateScore(score);
		arrayPlayers[0].UpdateName(name);

		//const size_t sz = sizeof(arrayPlayers) / sizeof((Player)arrayPlayers[0].UpdateScore());
	
		Heapsort(arrayPlayers,10);

	
		for (int i = 0; i <= _numOfPlayers; i++) {
			myInputOutputFile.seekp(sizePerson * i/*NumOfPlayers*/);
			myInputOutputFile.write((char *)(&arrayPlayers[i]), sizePerson);
		}
		/*
		myInputOutputFile.seekp(sizePerson * 9;
		myInputOutputFile.write((char *)(&p), sizePerson);
		*/
		myInputOutputFile.close();

		cout << "\n";
		
	}

	void ShowScore(char filename[100] ) {

		std::ifstream myInputFile;
		std::streampos fileSize;
		PlayerR p;
		int sizePerson = sizeof(PlayerR);

		//Read the file with the random population
		myInputFile.open(filename, std::ios::in | std::ios::binary);
		if (!myInputFile.is_open()) {
			throw std::exception("ReadAndPrintPopulation] System was not able to open the file");
		}
		//Compute the filesize
		myInputFile.seekg(0, std::ios::end);
		fileSize = myInputFile.tellg();
		myInputFile.seekg(0, std::ios::beg);

		//Read the content
	

		for (int i = 0; i <= _numOfPlayers; i++) {
			myInputFile.read((char *)(&p), sizePerson);
			//std::cout << p << std::endl;
			arrayPlayers[i] = p;
		}

		
	}

	void CreateAPopulationFile(char filename[100]) {
		PlayerR p("empty", 0);

		int sizePerson = sizeof(PlayerR);
		std::ofstream myOutputFile;

		//Create the file with a random population
		myOutputFile.open(filename, std::ios::in | std::ios::trunc | std::ios::binary);

		if (!myOutputFile.is_open()) {
			throw std::exception("[CreateAPopulationFile] System was not able to open the file");
		}
		
		for (int i = 0; i <= _numOfPlayers; i++) {
			myOutputFile.write((char *)(&p), sizePerson * i);
		}
		
		myOutputFile.close();
	}

	int ReturnNumOfPlayers(){

		return _numOfPlayers;
	}

	PlayerR & ReturnPlayer(int id) {

		return arrayPlayers[id];
	}

	void swap(PlayerR * m, PlayerR * n)
	{
		PlayerR tmp;
		tmp = *m;
		*m = *n;
		*n = tmp;
	}


	void siftDown(PlayerR * a, int k, int N) {

		while (k * 2 + 1 < N) {
			
			int child = 2 * k + 1;

			
			if ((child + 1 < N) && (a[child].ReturnScore() < a[child + 1].ReturnScore())) child++;

			if (a[k].ReturnScore() < a[child].ReturnScore()) {   
				swap(&a[child], &a[k]);
			
				k = child;
			}
			else
				return;
		}
	}

	//Metodo de ordenación HeapsSort para ordenar el array

	void Heapsort(PlayerR a[], int N) {



		for (int k = N / 2; k >= 0; k--) {
			siftDown(a, k, N);
		}

		while (N - 1 > 0) {
		
			swap(&a[0], &a[N - 1]);
			
			siftDown(a, 0, N - 1);
	
			N--;

			for (int i = 0; i <= _numOfPlayers; i++) {
				std::cout <<"\n" << a[i];
			}
		}
	}
};

