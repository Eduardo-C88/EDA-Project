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
	Vehicle* aux = (Vehicle*)malloc(sizeof(Vehicle));

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		fscanf(fp,"%d;%s;%0.2f;%0.2f;%s\n", &aux->id, aux->type, &aux->battery, &aux->price, aux->local);
		h = AddVehicle(h, aux);
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
	VehicleList* aux = (VehicleList*)malloc(sizeof(VehicleList));
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
			strcpy(aux->vehicle.local, v->local);
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
		printf("ID: %d\nType: %s\nBattery usage: %0.2f\nPrice: %0.2f\nLocation: %s\n",aux->vehicle.id, aux->vehicle.type,aux->vehicle.battery,aux->vehicle.price,aux->vehicle.local);
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
VehicleList* SearchVehicle(VehicleList* h, char local[]) {
	if (h == NULL) return h;
	VehicleList* aux = h;
	while (aux != NULL) {
		if (strcmp(aux->vehicle.local, local) == 0)return aux;
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

	VehicleList* aux = (VehicleList*)malloc(sizeof(VehicleList));
	aux->next = NULL;
	aux->vehicle = *v;

	if (h == NULL) {
		h = aux;
		return h;
	}
	else {
		if (h->vehicle.battery < aux->vehicle.battery) {
			aux->next = h;
			h = aux;
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
VehicleList* AddVehicleGeo(VehicleList* h, char* local){
	if (h == NULL)return NULL;

	VehicleList* aux = h;
	VehicleList* final = NULL;

	while (aux != NULL) {
		if (strcmp(aux->vehicle.local, local) == 0) {
			final = AddVehicle(final, &aux->vehicle);
		}
		aux = aux->next;
	}
	return final;
}


/**
 * Listar os Veículos, de uma lista de Veículos já existente, com um determinado tipo
 *
 * \param h
 * \param v
 * \param geoCode
 * \return
 */
VehicleList* AddVehicleType(VehicleList* h, char* type) {
	if (h == NULL)return NULL;

	VehicleList* aux = h;
	VehicleList* final = NULL;

	while (aux != NULL) {
		if (strcmp(aux->vehicle.type, type) == 0) {
			final = AddVehicle(final, &aux->vehicle);
		}
		aux = aux->next;
	}
	return final;
}