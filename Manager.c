/*****************************************************************//**
 * \file   Manager.c
 * \brief  Funções para a lista de Gestores
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Manager.h"

 /**
  * Carregar uma lista de Gestores de um ficheiro de texto
  *
  * \param fileName
  * \return
  */
ManagerList* LoadManagers(char fileName[]) {
	ManagerList* h = NULL;
	Manager* aux = (Manager*)malloc(sizeof(Manager));

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		fscanf(fp, "%d;%s;%s;%s\n", &aux->id, aux->name, aux->email, aux->password);
		h = AddManager(h, aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Gestores para um ficheiro binário
 * 
 * \param h
 * \return 
 */
bool SaveManagersBin(ManagerList* h, char fileName[]) {
	if (h == NULL)return false;
	ManagerList* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;

	while (aux != NULL) {
		fwrite(&aux, 1, sizeof(aux->manager), fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
 * Inserir um Gestor a uma lista de Gestores, ordenada por id
 * 
 * \param h
 * \param m
 * \return 
 */
ManagerList* AddManager(ManagerList* h, Manager* m) {
	ManagerList* aux = (ManagerList*)malloc(sizeof(ManagerList));
	aux->next = NULL;
	aux->manager = *m;

	if (h == NULL) {
		h = aux;
		return h;
	}
	else {
		if (h->manager.id > aux->manager.id) {
			aux->next = h;
			h = aux;
		}
		else {
			ManagerList* prev = h;
			ManagerList* current = h;
			while (current != NULL && current->manager.id < aux->manager.id) {
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
 * Remover um Gestor com um id definido de uma lista de Gestores
 * 
 * \param h
 * \param id
 * \return 
 */
ManagerList* RemoveManager(ManagerList* h, int id) {
	if (h == NULL) return NULL;

	ManagerList* aux = h;
	ManagerList* prev = NULL;

	while (aux != NULL && aux->manager.id != id) {
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
 * Trocar um Gestor de uma lista de Gestores por um com o mesmo id
 * 
 * \param h
 * \param m
 * \return 
 */
bool EditManager(ManagerList* h, Manager* m){
	if (h == NULL || m == NULL)return false;
	ManagerList* aux = h;

	while (aux != NULL) {
		if (aux->manager.id == m->id) {
			strcpy(aux->manager.name, m->name);
			strcpy(aux->manager.email, m->email);
			strcpy(aux->manager.password, m->password);
			return true;
		}
		aux = aux->next;
	}
	return false;
}

/**
 * Mostrar todos os Gestores em uma lista de Gestores
 * 
 * \param h
 */
void ShowManagersList(ManagerList* h){
	ManagerList* aux = h;
	while (aux != NULL) {
		printf("ID: %d\nName: %s\ne-mail: %s\nPassword: %s\n",aux->manager.id, aux->manager.name, aux->manager.email, aux->manager.password);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Gestores
 *
 * \param h
 * \return
 */
bool ClearManagersList(ManagerList* h) {
	if (h == NULL)return false;
	ManagerList* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}
