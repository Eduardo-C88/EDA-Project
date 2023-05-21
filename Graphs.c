/*****************************************************************//**
 * \file   Graphs.c
 * \brief  ...
 * 
 * \author Eduardo
 * \date   May 2023
 *********************************************************************/

#include "Graphs.h"

#pragma region GRAPHS
/**
 * ...
 * 
 * \return 
 */
Town* CreateGraph() {
	return NULL;
}

/**
 * ...
 * 
 * \param town
 * \param geoCode
 * \return 
 */
Town* CreateTown(int cod, char town[], char geoCode[]) {
	Town* new = (Town*)malloc(sizeof(Town));
	if (new == NULL) return NULL;

	new->cod = cod;
	strcpy(new->geoCode, geoCode);
	strcpy(new->tName, town);
	new->next = NULL;
	new->paths = NULL;

	return new;
}

/**
 * ...
 * 
 * \param g
 * \param 
 * \return 
 */
Town* AddTown(Town* g, Town* new) {
	if (new == NULL)return g;

	if (g == NULL) {
		g = new;
		return g;
	}
	else{ 
		Town* aux = g;
		Town* prev = aux;

		while (aux != NULL && strcmp(aux->tName, new->tName) < 0) {  //ordenar alfabeticamente
			prev = aux;
			aux = aux->next;
		}
		if (aux = g) {
			new->next = g;
			g = new;
		}
		else {
			new->next = aux;
			prev->next = new;
		}
	}
	return g;
}

/**
 * ...
 * 
 * \param g
 */
void ShowGraph(Town* g){
	if (g == NULL)return;

	printf("Town: %s\n\tGeoCode: %s\n\tCode: %d\n",g->tName, g->geoCode, g->cod);
	
	ShowPaths(g->paths);
	ShowGraph(g->next);
}

/**
 * ...
 * 
 * \param g
 * \param tName
 * \return 
 */
Town* SearchTown(Town* g, char* tName) {
	if (g == NULL) return NULL;
	if (strcmp(g->tName, tName) == 0) return g;
	return(SearchTown(g->next, tName));
}

/**
 * ...
 * 
 * \param g
 * \param fileName
 * \return 
 */
int SaveTowns(Town* g, char* fileName) {
	if (g == NULL) return -1;
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL) return 0;

	Town* aux = g;
	TownFile tFile;
	while (aux != NULL) {
		tFile.cod = aux->cod;
		strcpy(tFile.tName, aux->tName);
		strcpy(tFile.geoCode, aux->geoCode);
		fwrite(&tFile, sizeof(tFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}
#pragma endregion

#pragma region EDGES
/**
 * ...
 * 
 * \param cod
 * \param dest
 * \param dist
 * \return 
 */
Path* CreatePath(int cod, char* dest, float dist) {
	Path* new = (Path*)malloc(sizeof(Path));
	if (new == NULL) return NULL;

	new->cod = cod;
	strcpy(new->dest, dest);
	new->dist = dist;
	new->next = NULL;

	return new;
}

/**
 * ...
 * 
 * \param h
 * \param cod
 * \return 
 */
bool CheckPath(Path* h, int cod) {
	if (h == NULL)return false;
	
	Path* aux = h;
	while (aux != NULL) {
		if (aux->cod == cod)return true;
		aux = aux->next;
	}
	return false;
}

/**
 * ...
 * 
 * \param h
 * \param 
 * \return 
 */
Path* AddPath(Path* h, Path* new) {
	if (new == NULL)return h;
	if (CheckPath(h, new->cod))return h;
	if (h == NULL) {
		h = new;
		return h;
	}
	else {
		Path* aux = h;
		Path* prev = aux;
		while (aux != NULL && strcmp(aux->dest, new->dest) < 0) {
			prev = aux;
			aux = aux->next;
		}
		if (aux == h) {
			new->next = aux;
			h = new;
		}
		else {
			new->next = aux;
			prev->next = new;
		}
	}
	return h;
}

/**
 * ...
 * 
 * \param h
 */
void ShowPaths(Path* h) {
	if (h == NULL)return;
	printf("\tDestination: %s - Distance: %0.2f - Code:%d\n", h->dest, h->dist, h->cod);
	ShowPaths(h->next);
}

/**
 * ...
 * 
 * \param g
 * \param start
 * \param dest
 * \param dist
 * \return 
 */
Town* AddPathToTown(Town* g, char* start, char* dest, float dist) {
	if (g == NULL)return NULL;

	Town* aux = SearchTown(g, start);
	Town* d = SearchTown(g, dest);

	if (aux == NULL || d == NULL) return g;
	if (CheckPath(aux->paths, d->cod))return g;

	Path* newPath = CreatePath(d->cod, dest, dist);
	aux->paths = AddPath(aux->paths, newPath);
	return g;
}

/**
 * ...
 * 
 * \param h
 * \param fileName
 * \param verCode
 * \return 
 */
int SavePaths(Path* h, char* fileName, char* town) {
	if (h == NULL) return -1;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL) return 0;
	 
	Path* aux = h;
	PathFile pFile;
	while (aux != NULL) {
		pFile.cod = aux->cod;
		strcpy(pFile.town, town);
		strcpy(pFile.dest, aux->dest);
		pFile.dist = aux->dist;
		fwrite(&pFile, sizeof(pFile), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}
#pragma endregion
