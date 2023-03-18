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
Vehicle* LoadVehicles(char fileName[]) {
	Vehicle* h = NULL;
	Vehicle* current = NULL;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		Vehicle* newVehicle = (Vehicle*)malloc(sizeof(Vehicle));
		if (newVehicle == NULL)return NULL;

		if (fscanf(fp, "%d;%[^;];%0.2f;%0.2f;%[^;]\n", newVehicle->id, newVehicle->type, newVehicle->battery, newVehicle->price, newVehicle->geoCode) == 5) {
			newVehicle->next = NULL;

			if (h == NULL) {
				h = newVehicle;
				current = newVehicle;
			}
			else {
				current->next = newVehicle;
				current = newVehicle;
			}
		}
		else {
			free(newVehicle);
		}
	}
	fclose(fp);
	return h;
}

/**
 * Carregar uma lista de Transportes de um ficheiro binário
 *
 * \param fileName
 * \return
 */
Vehicle* LoadVehiclesBin(char fileName[]) {
	Vehicle* h = NULL;

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (fp == NULL)return NULL;

	Vehicle* aux;
	while (fread(&aux, 1, sizeof(Vehicle), fp)) {
		h = AddVehicle(h, &aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Transportes para um ficheiro de texto
 * 
 * \param h
 * \return 
 */
bool SaveVehicle(Vehicle* h, char fileName[]) {
	FILE* fp;
	fp = fopen(fileName, "w");
	if (h == NULL) return false;
	if (fp == NULL)return false;

	Vehicle* current = h;

	while (current != NULL) {
		fprintf(fp, "%d;%s;%0.2f;%0.2f;%s\n", current->id, current->type, current->battery, current->price, current->geoCode);
		current = current->next;
	}
	fclose(fp);
	return true;
}

/**
 * Gravar uma lista de Transportes para um ficheiro binário
 * 
 * \param h
 * \return 
 */
bool SaveVehicleBin(Vehicle* h, char fileName[]) {
	if (h == NULL)return false;
	Vehicle* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;
	while (aux != NULL) {
		fwrite(aux, 1, sizeof(Vehicle), fp);
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
Vehicle* AddVehicle(Vehicle* h, Vehicle* v){
	Vehicle* aux = (Vehicle*)malloc(sizeof(Vehicle));
	aux->next = NULL;

	if (h == NULL) {
		h = v;
		return h;
	}
	else {
		if (h->id > aux->id) {
			aux->next = h;
			h = v;
		}
		else {
			Vehicle* prev = h;
			Vehicle* current = h;
			while (current != NULL && current->id < aux->id) {
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
Vehicle* RemoveVehicle(Vehicle* h, int id) {
	if (h == NULL) return NULL;

	Manager* aux = h;
	Manager* prev = NULL;

	while (aux != NULL && aux->id != id) {
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
bool EditVehicle(Vehicle* h, Vehicle* v){
	if (h == NULL || v == NULL)return false;
	Vehicle* aux = h;

	while (aux != NULL) {
		if (aux->id == v->id) {
			strcpy(aux->type, v->type);
			aux->battery = v->battery;
			aux->price = v->price;
			strcpy(aux->geoCode, v->geoCode);
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
void ShowVehicleList(Vehicle* h) {
	Vehicle* aux = h;
	while (aux != NULL) {
		printf("Vehicle\nID: %d\nType: %s\nBattery usage: %0.2f\nPrice: %0.2f\nGeoCode: %s\n",aux->id, aux->type,aux->battery,aux->price,aux->geoCode);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Transportes
 *
 * \param h
 * \return
 */
bool ClearVehicleList(Vehicle* h) {
	if (h == NULL)return false;
	Vehicle* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}

/**
 * Devolver um Transporte, de tipo definido, de um lista de Transportes 
 * 
 * \param h
 * \param type
 * \return 
 */
Vehicle* SearchVehicle(Vehicle* h, char type[]) {
	if (h == NULL) return h;
	Vehicle* aux = h;
	while (aux != NULL) {
		if (strcmp(aux->type, type) == 0)return aux;
		aux = aux->next;
	}
	return NULL;
}
