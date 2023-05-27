/*****************************************************************//**
 * \file   Graphs.h
 * \brief  Declara��o das structs e fun��es para o Grafo
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
 * Adiciona uma Cidade(V�rtice) a uma lista de Cidades, ordenado por c�digo da Cidade
 */
Town* AddTown(Town* g, Town* new);

/**
 * Mostra a lista de Cidades(V�rtices)
 */
void ShowTowns(Town* g);

/**
 * A partir de uma lista de Ve�culos j� exstente, insere-os na lista de Ve�culos da respetica Cidade(V�rtice)
 */
Town* AddVehicleTown(Town* g, char* town, struct VehicleList* vList);

/**
 *  Mostra as Cidades(V�rtices) e respetivos caminhos(Adjac�ncias)
 */
void ShowGraph(Town* g);

/**
 * Procura por uma Cidade por nome no Grafo
 */
Town* SearchTown(Town* g, char* tName);

/**
 * Liberta a mem�ria usada tanto pelas Cidade(V�rticese) e
 * pelos Caminhos(Adjac�ncias)
 */
Town* DestroyGraph(Town* g);

/**
 * Carrega as Cidades(V�rtices) a partir de um ficheiro bin�rio
 */
Town* LoadGraph(Town* h, char* fileName);

/**
 * Grava as Cidades(V�rtices) e Caminhos(Adjac�ncias) em um ficheiro bin�rio
 */
int SaveGraph(Town* g, char* fileName);
#pragma endregion

#pragma region EDGES
/**
 * Cria um Caminho(Adjac�ncia)
 */
Path* CreatePath(int cod, char* dest, float dist);

/**
 * Verifica se o Caminho(Adjac�ncia) existe pelo seu c�digo
 */
bool CheckPath(Path* h, int cod);

/**
 * Adiciona um Caminho(Adjac�ncia) a uma lista de Caminhos
 */
Path* AddPath(Path* h, Path* new);

/**
 * Mostra a lista de Caminhos(Adjac�ncias)
 */
void ShowPaths(Path* h);

/**
 * Liberta a mem�ria usada pelos Caminhos(Adjac�ncias)
 */
Path* DestroyPaths(Path* h);

/**
 * Carrega os Caminhos(Adjac�ncias) a partir de um ficheiro bin�rio
 */
Town* LoadAdj(Town* g);

/**
 * Grava os Caminhos(Adjac�ncias) em um ficheiro bin�rio
 */
int SavePaths(Path* h, char* fileName, int cod);
#pragma endregion

#pragma region ALGORITIMOS
/**
 * Mostra a lista de Ve�culos de uma respetiva Cidade(V�rtice)
 */
void ShowTownVehicles(Town* g, char* town);

/**
 * Insere um Caminho(Adjac�ncia) � lista de Caminhos da respetiva Cidade(V�rtice)
 * definindo o destino e o peso do mesmo
 */
Town* AddPathToTown(Town* g, char* start, char* dest, float dist);

/**
 * Define uma lista de Ve�culos de um determinado tipo
 * dentro de um certo raio de dist�ncia de uma Cidade(V�rtice)
 */
VehicleList* VehicleTypeRadius(Town* g, char* start, char* type, float radius);
#pragma endregion

