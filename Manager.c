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
Manager* LoadManagers(char fileName[]) {
	Manager* h = NULL;
	Manager* current = NULL;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		Manager* newManager = (Manager*)malloc(sizeof(Manager));
		if (newManager == NULL)return NULL;

		if (fscanf(fp, "%d;%[^;];%[^;];%[^;]", newManager->id, newManager->name, newManager->email, newManager->password)== 4) {
			newManager->next = NULL;

			if (h == NULL) {
				h = newManager;
				current = newManager;
			}
			else {
				current->next = newManager;
				current = newManager;
			}
		}
		else {
			free(newManager);
		}
	}
	fclose(fp);
	return h;
}

/**
 * Carregar uma lista de Gestores de um ficheiro binário
 *
 * \param fileName
 * \return
 */
Manager* LoadManagersBin(char fileName[]) {
	Manager* h = NULL;

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (fp == NULL)return NULL;

	Manager* aux;
	while (fread(&aux, 1, sizeof(Manager), fp)) {
		h = AddManager(h, &aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Gestores para um ficheiro de texto
 * 
 * \param h
 * \return 
 */
bool SaveManagers(Manager* h, char fileName[]) {
	FILE* fp;
	fp = fopen(fileName, "w");
	if (h == NULL) return false;
	if (fp == NULL)return false;

	Manager* current = h;

	while (current != NULL) {
		fprintf(fp, "%d;%s;%s;%s\n", current->id, current->name, current->email, current->password);
		current = current->next;
	}
	fclose(fp);
	return true;
}

/**
 * Gravar uma lista de Gestores para um ficheiro binário
 * 
 * \param h
 * \return 
 */
bool SaveManagersBin(Manager* h, char fileName[]) {
	if (h == NULL)return false;
	Manager* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;
	while (aux != NULL) {
		fwrite(aux, 1, sizeof(Manager), fp);
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
Manager* AddManager(Manager* h, Manager* m) {
	Manager* aux = (Manager*)malloc(sizeof(Manager));
	aux->next = NULL;

	if (h == NULL) {
		h = m;
		return h;
	}
	else {
		if (h->id > aux->id) {
			aux->next = h;
			h = m;
		}
		else {
			Manager* prev = h;
			Manager* current = h;
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
 * Remover um Gestor com um id definido de uma lista de Gestores
 * 
 * \param h
 * \param id
 * \return 
 */
Manager* RemoveManager(Manager* h, int id) {
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
 * Trocar um Gestor de uma lista de Gestores por um com o mesmo id
 * 
 * \param h
 * \param m
 * \return 
 */
bool EditManager(Manager* h, Manager* m){
	if (h == NULL || m == NULL)return false;
	Manager* aux = h;

	while (aux != NULL) {
		if (aux->id == m->id) {
			strcpy(aux->name, m->name);
			strcpy(aux->email, m->email);
			strcpy(aux->password, m->password);
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
void ShowManagerList(Manager* h){
	Manager* aux = h;
	while (aux != NULL) {
		printf("Manager\nID: %d\nName: %s\ne-mail: %s\nPassword: %s\n",aux->id, aux->name, aux->email, aux->password);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Gestores
 *
 * \param h
 * \return
 */
bool ClearManagerList(Manager* h) {
	if (h == NULL)return false;
	Manager* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}
