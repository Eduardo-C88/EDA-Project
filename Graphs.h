/*****************************************************************//**
 * \file   Graphs.h
 * \brief  ...
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
	char *dest;          //Destino
	float dist;			 //Peso
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
	struct Town* next;
	Path* paths;
}Town;

typedef struct TownFile {
	int cod;
	char geoCode[CODE_SIZE];
	char tName[NAME_SIZE];
}TownFile;

/**
 * 
 */
Town* CreateGraph();

/**
 * 
 */
Town* CreateTown(int cod, char town[], char geoCode[]);

/**
 * 
 */
Town* AddTown(Town* g, Town* new);

/**
 * 
 */
void ShowGraph(Town* g);

/**
 * .
 */
Town* SearchTown(Town* g, char* tName);

/**
 * .
 */
int SaveTowns(Town* g, char* fileName);

/**
 * .
 */
Path* CreatePath(int cod, char* dest, float dist);

/**
 * .
 */
bool CheckPath(Path* h, int cod);

/**
 * .
 */
Path* AddPath(Path* h, Path* new);

/**
 * 
 */
void ShowPaths(Path* h);

/**
 * .
 */
Town* AddPathToTown(Town* g, char* start, char* dest, float dist);

/**
 * .
 */
int SavePaths(Path* h, char* fileName, char* town);




