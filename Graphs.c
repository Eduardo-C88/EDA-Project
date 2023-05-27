/*****************************************************************//**
 * \file   Graphs.c
 * \brief  ...
 * 
 * \author Eduardo
 * \date   May 2023
 *********************************************************************/

#include "Graphs.h"

#pragma region GRAPH
/**
 * Inicializa o Grafo
 * 
 * \return 
 */
Town* CreateGraph() {
	return NULL;
}

/**
 * Cria uma Cidade(Vértice)
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
	new->vehicles = NULL;
	new->next = NULL;
	new->paths = NULL;

	return new;
}
	
/**
 * Adiciona uma Cidade(Vértice) ao Grafo, ordenado por código da Cidade
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

		while (aux != NULL && aux->cod < new->cod) {  //ordenar por código
			prev = aux;
			aux = aux->next;
		}
		if (aux == g) {
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
 * Mostra as Cidades(Vértices) e respetivos caminhos(Adjacências)
 * 
 * \param g
 */
void ShowGraph(Town* g){
	if (g == NULL)return;

	Town* aux = g;
	printf("Town: %s\n\tGeoCode: %s\n\tCode: %d\n",aux->tName, aux->geoCode, aux->cod);
	
	ShowPaths(aux->paths);
	ShowGraph(aux->next);
}

/**
 * Mostra a lista de Cidades(Vértices)
 *
 * \param g
 */
void ShowTowns(Town* g) {
	if (g == NULL)return;

	Town* aux = g;
	printf("Town: %s\n\tGeoCode: %s\n\tCode: %d\n", aux->tName, aux->geoCode, aux->cod);

	ShowGraph(aux->next);
}

/**
 * Procura por uma Cidade(Vértice) por nome no Grafo
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
 * A partir de uma lista de Veículos já exstente, insere-os na lista de Veículos da respetica Cidade(Vértice)
 * 
 * \param t
 * \param vList
 * \return 
 */
Town* AddVehicleTown(Town* g, char* town, VehicleList* vList) {
	if (g == NULL)return NULL;
	if (vList == NULL)return g;

	Town* aux = g;

	Town* temp = SearchTown(aux, town);
	temp->vehicles = AddVehicleGeo(vList, town);

	return temp;	
}

/**
 * Liberta a memória usada tanto pelas Cidade(Vérticese) e
 * pelos Caminhos(Adjacências)
 * 
 * \param g
 * \return		
 */
Town* DestroyGraph(Town* g) {
	if (g == NULL) return NULL;
	Town* aux = NULL;
	while (g) {
		if (g->next)
			aux = g->next;
		g->paths = DestroyAdj(g->paths);
		free(g);
		g = aux;
		aux = NULL;
	}
	return g;
}

/**
 * Carrega as Cidades(Vértices) a partir de um ficheiro binário
 * 
 * \param h
 * \param fileName
 * \return 
 */
Town* LoadGraph(Town* h, char* fileName) {
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) return NULL;
	TownFile aux;
	Town* new;
	while (fread(&aux, 1, sizeof(TownFile), fp)) {
		new = CreateTown(aux.cod, aux.tName, aux.geoCode);
		h = AddTown(h, new);
	}
	fclose(fp);
	return h;
}

/**
 * Grava as Cidades(Vértices) e Caminhos(Adjacências) em um ficheiro binário
 * 
 * \param g
 * \param fileName
 * \return 
 */
int SaveGraph(Town* g, char* fileName) {
	if (g == NULL) return -1;
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL) return 0;
	int r;

	Town* aux = g;
	TownFile tFile;
	while (aux != NULL) {
		tFile.cod = aux->cod;
		strcpy(tFile.tName, aux->tName);
		strcpy(tFile.geoCode, aux->geoCode);
		fwrite(&tFile, sizeof(tFile), 1, fp);
		if (aux->paths != NULL) {
			r = SavePaths(aux->paths, aux->tName, aux->cod);
		}
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}
#pragma endregion

#pragma region EDGES
/**
 * Cria um Caminho(Adjacência)
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
 * Verifica se o Caminho(Adjacência) existe pelo seu código
 * 
 * \param h
 * \param cod
 * \return 
 */
bool CheckPath(Path* h, int cod) {
	if (h == NULL)return false;
		
	if (h->cod == cod) return true;

	return CheckPath(h->next, cod);
}

/**
 * Adiciona um Caminho(Adjacência) a uma lista de Caminhos
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
	new->next = h;
	h = new;

	return h;
}

/**
 * Mostra a lista de Caminhos(Adjacências)
 * 
 * \param h
 */
void ShowPaths(Path* h) {
	if (h == NULL)return;

	Path* aux = h;
	printf("\tDestination: %s - Distance: %0.2f - Code:%d\n", aux->dest, aux->dist, aux->cod);
	ShowPaths(aux->next);
}

/**
 * Liberta a memória usada pelos Caminhos(Adjacências)
 * 
 * \param h
 * \return 
 */
Path* DestroyPaths(Path* h) {
	if (h == NULL) return NULL;
	Path* aux = NULL;
	while (h) {
		if (h->next != NULL)
			aux = h->next;
		free(h);
		h = aux;
		aux = NULL;
	}
	return h;
}

/**
 * Carrega os Caminhos(Adjacências) a partir de um ficheiro binário
 * 
 * \param g
 * \return 
 */
Town* LoadAdj(Town* g) {
	FILE* fp;

	PathFile aux;
	Town* auxGraph = g;
	while (auxGraph) {
		fp = fopen(auxGraph->tName, "rb");
		if (fp != NULL) {
			while (fread(&aux, 1, sizeof(PathFile), fp)) {
				g = AddPathToTown(g, aux.town, aux.dest, aux.dist);
			}
			fclose(fp);
		}
		auxGraph = auxGraph->next;
	}
	return g;
}

/**
 * Grava os Caminhos(Adjacências) em um ficheiro binário
 * 
 * \param h
 * \param fileName
 * \param verCode
 * \return 
 */
int SavePaths(Path* h, char* fileName, int cod) {
	//if (h == NULL) return -1;

	//FILE* fp;
	//fp = fopen(fileName, "wb");
	//if (fp == NULL) return 0;
	//
	//Path* aux = h;
	//PathFile pFile; 
	//while (aux != NULL) {
	//	pFile.cod = aux->cod;
	//	strcpy(pFile.town, town);
	//	strcpy(pFile.dest, aux->dest);
	//	pFile.dist = aux->dist;
	//	fwrite(&pFile, sizeof(pFile), 1, fp);
	//	aux = aux->next;
	//}
	//fclose(fp);
	//return 1;
}
#pragma endregion

#pragma region ALGORITIMOS

/**
 * Mostra a lista de Veículos de uma respetiva Cidade(Vértice)
 *
 * \param g
 * \param town
 */
void ShowTownVehicles(Town* g, char* town) {
	if (g == NULL)return;

	Town* aux = g;
	Town* temp = SearchTown(aux, town);
	if (temp == NULL)return;

	ShowVehiclesList(temp->vehicles);
}

/**
 * Insere um Caminho(Adjacência) à lista de Caminhos da respetiva Cidade(Vértice)
 * definindo o destino e o peso do mesmo
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
	return aux;
}

/**
 * Define uma lista de Veículos de um determinado tipo
 * dentro de um certo raio de distância de uma Cidade(Vértice)
 *
 * \param g
 * \param start
 * \param type
 * \param radius
 * \return
 */
VehicleList* VehicleTypeRadius(Town* g, char* start, char* type, float radius) {
	if (g == NULL)return NULL;

	float totalDist = 0;
	VehicleList* final = NULL;

	Town* aux = SearchTown(g, start);
	if (aux == NULL)return NULL;

	Path* paths = aux->paths;
	while (paths != NULL && totalDist <= radius) {
		Town* t = SearchTown(g, paths->dest);
		totalDist += paths->dist;

		final = AddVehicleType(t->vehicles, type);

		paths = paths->next;
	}
	return final;
}
#pragma endregion

