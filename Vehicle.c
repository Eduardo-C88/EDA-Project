/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  Funções para a lista de Transportes
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Vehicle.h"

 /**
  * Carregar uma lista de Transportes de um ficheiro de texto
  *
  * \param fileName
  * \return
  */
VehicleList* LoadVehicles(char fileName[]) {
	VehicleList* h = NULL;
	VehicleList* aux;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof) {
		fscanf(fp, "%d;%s;%0.2f;%0.2f;%s\n", aux->vehicle.id, aux->vehicle.type, aux->vehicle.battery, aux->vehicle.price, aux->vehicle.geoCode);
		h = AddVehicle(h, &aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Transportes para um ficheiro binário
 * 
 * \param h
 * \return 
 */
bool SaveVehiclesBin(VehicleList* h, char fileName[]) {
	if (h == NULL)return false;
	VehicleList* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;

	while (aux != NULL) {
		aux->next = NULL;
		fwrite(aux, 1, sizeof(aux->vehicle), fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
 * Inserir um Transporte a uma lista de Transportes, ordenada por id
 * 
 * \param h
 * \param v
 * \return 
 */
VehicleList* AddVehicle(VehicleList* h, Vehicle* v){
	VehicleList* aux = (Vehicle*)malloc(sizeof(Vehicle));
	aux->next = NULL;
	aux->vehicle = *v;

	if (h == NULL) {
		h = aux;
		return h;
	}
	else {
		if (h->vehicle.id > aux->vehicle.id) {
			aux->next = h;
			h = aux;
		}
		else {
			VehicleList* prev = h;
			VehicleList* current = h;
			while (current != NULL && current->vehicle.id < aux->vehicle.id) {
				prev = current;
				current = current->next;
			}
			aux->next = current;
			prev->next = aux;
		}
	}
	return h;
}

/**
 * Remover um Transporte com um id definido de uma lista de Transportes
 * 
 * \param h
 * \param id
 * \return 
 */
VehicleList* RemoveVehicle(VehicleList* h, int id) {
	if (h == NULL) return NULL;

	VehicleList* aux = h;
	VehicleList* prev = NULL;

	while (aux != NULL && aux->vehicle.id != id) {
		prev = aux;
		aux = aux->next;
	}

	if (aux == NULL) {
		// Customer with the given id was not found
		return h;
	}

	if (prev == NULL) {
		// Removing the first node
		h = aux->next;
	}
	else {
		prev->next = aux->next;
	}

	free(aux);
	return h;
}

/**
 * Trocar um Transporte de uma lista de Transportes por um com o mesmo id
 * 
 * \param h
 * \param v
 * \return 
 */
bool EditVehicle(VehicleList* h, Vehicle* v){
	if (h == NULL || v == NULL)return false;
	VehicleList* aux = h;

	while (aux != NULL) {
		if (aux->vehicle.id == v->id) {
			strcpy(aux->vehicle.type, v->type);
			aux->vehicle.battery = v->battery;
			aux->vehicle.price = v->price;
			strcpy(aux->vehicle.geoCode, v->geoCode);
			return true;
		}
		aux = aux->next;
	}
	return false;
}

/**
 * Mostrar todos os Transportes em uma lista de Transportes
 * 
 * \param h
 */
void ShowVehiclesList(VehicleList* h) {
	VehicleList* aux = h;
	while (aux != NULL) {
		printf("Vehicle\nID: %d\nType: %s\nBattery usage: %0.2f\nPrice: %0.2f\nGeoCode: %s\n",aux->vehicle.id, aux->vehicle.type,aux->vehicle.battery,aux->vehicle.price,aux->vehicle.geoCode);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Transportes
 *
 * \param h
 * \return
 */
bool ClearVehiclesList(VehicleList* h) {
	if (h == NULL)return false;
	VehicleList* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}

/**
 * Devolver um Transporte, com um geocódigo determinado, de um lista de Transportes 
 * 
 * \param h
 * \param type
 * \return 
 */
Vehicle* SearchVehicle(VehicleList* h, char geocode[]) {
	if (h == NULL) return h;
	VehicleList* aux = h;
	while (aux != NULL) {
		if (strcmp(aux->vehicle.geoCode, geocode) == 0)return aux;
		aux = aux->next;
	}
	return NULL;
}

/**
 * Inserir um Veículo a uma lista de Veículos, ordenada de ordem decrescente por autonomia
 * 
 * \param h
 * \param v
 * \return 
 */
VehicleList* AddVehicleAutDec(VehicleList* h, Vehicle* v) {
	VehicleList* aux = (Vehicle*)malloc(sizeof(Vehicle));
	aux->next = NULL;
	aux->vehicle = *v;

	if (h == NULL) {
		h = v;
		return h;
	}
	else {
		if (h->vehicle.battery < aux->vehicle.battery) {
			aux->next = h;
			h = v;
		}
		else {
			VehicleList* prev = h;
			VehicleList* current = h;
			while (current != NULL && current->vehicle.battery > aux->vehicle.battery) {
				prev = current;
				current = current->next;
			}
			aux->next = current;
			prev->next = aux;
		}
	}
	return h;
}

/**
 * Listar os Veículos, de uma lista de Veículos já existente, com um determinado geocódigo 
 * 
 * \param h
 * \param v
 * \param geoCode
 * \return 
 */
VehicleList* AddVehicleGeo(VehicleList* h, VehicleList* l, char* geoCode){
	if (h == NULL)return l;

	VehicleList* aux = h;

	while (aux->next != NULL) {
		if (strcmp(aux->vehicle.geoCode, geoCode) == 0) {
			l = AddVehicle(l, &aux->vehicle);
		}
		aux = aux->next;
	}
	return l;
}
