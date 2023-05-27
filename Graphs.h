/*****************************************************************//**
 * \file   Graphs.h
 * \brief  Declaração das structs e funções para o Grafo
 * 
 * \author Eduardo
 * \date   April 2023
 *********************************************************************/
#pragma warning(disable : 4996)

#pragma once
#include "Globals.h"

#define MAX_LOCAL 6
#define CODE_SIZE 50
#define NAME_SIZE 50

typedef struct Path{
	int cod;
	char dest[NAME_SIZE];          //Destino
	float dist;			           //Peso
	struct Path* next;
}Path;

typedef struct PathFile {
	int cod;
	char* town;			    //Vertice
	char* dest;				//Destino
	float dist;
	//struct Path* next;
}PathFile;

typedef struct Town{
	int cod;
	char geoCode[CODE_SIZE];
	char tName[NAME_SIZE];
	struct VehicleList* vehicles;
	struct Town* next;
	Path* paths;
}Town;

typedef struct TownFile {
	int cod;
	char geoCode[CODE_SIZE];
	char tName[NAME_SIZE];
}TownFile;

#pragma region GRAPH
/**
 * Inicializa o Grafo
 */
Town* CreateGraph();

/**
 * Cria uma Cidade 
 */
Town* CreateTown(int cod, char town[], char geoCode[]);

/**
 * Adiciona uma Cidade(Vértice) a uma lista de Cidades, ordenado por código da Cidade
 */
Town* AddTown(Town* g, Town* new);

/**
 * Mostra a lista de Cidades(Vértices)
 */
void ShowTowns(Town* g);

/**
 * A partir de uma lista de Veículos já exstente, insere-os na lista de Veículos da respetica Cidade(Vértice)
 */
Town* AddVehicleTown(Town* g, char* town, struct VehicleList* vList);

/**
 *  Mostra as Cidades(Vértices) e respetivos caminhos(Adjacências)
 */
void ShowGraph(Town* g);

/**
 * Procura por uma Cidade por nome no Grafo
 */
Town* SearchTown(Town* g, char* tName);

/**
 * Liberta a memória usada tanto pelas Cidade(Vérticese) e
 * pelos Caminhos(Adjacências)
 */
Town* DestroyGraph(Town* g);

/**
 * Carrega as Cidades(Vértices) a partir de um ficheiro binário
 */
Town* LoadGraph(Town* h, char* fileName);

/**
 * Grava as Cidades(Vértices) e Caminhos(Adjacências) em um ficheiro binário
 */
int SaveGraph(Town* g, char* fileName);
#pragma endregion

#pragma region EDGES
/**
 * Cria um Caminho(Adjacência)
 */
Path* CreatePath(int cod, char* dest, float dist);

/**
 * Verifica se o Caminho(Adjacência) existe pelo seu código
 */
bool CheckPath(Path* h, int cod);

/**
 * Adiciona um Caminho(Adjacência) a uma lista de Caminhos
 */
Path* AddPath(Path* h, Path* new);

/**
 * Mostra a lista de Caminhos(Adjacências)
 */
void ShowPaths(Path* h);

/**
 * Liberta a memória usada pelos Caminhos(Adjacências)
 */
Path* DestroyPaths(Path* h);

/**
 * Carrega os Caminhos(Adjacências) a partir de um ficheiro binário
 */
Town* LoadAdj(Town* g);

/**
 * Grava os Caminhos(Adjacências) em um ficheiro binário
 */
int SavePaths(Path* h, char* fileName, int cod);
#pragma endregion

#pragma region ALGORITIMOS
/**
 * Mostra a lista de Veículos de uma respetiva Cidade(Vértice)
 */
void ShowTownVehicles(Town* g, char* town);

/**
 * Insere um Caminho(Adjacência) à lista de Caminhos da respetiva Cidade(Vértice)
 * definindo o destino e o peso do mesmo
 */
Town* AddPathToTown(Town* g, char* start, char* dest, float dist);

/**
 * Define uma lista de Veículos de um determinado tipo
 * dentro de um certo raio de distância de uma Cidade(Vértice)
 */
VehicleList* VehicleTypeRadius(Town* g, char* start, char* type, float radius);
#pragma endregion

