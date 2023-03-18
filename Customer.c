/*****************************************************************//**
 * \file   Customer.c
 * \brief  Funções para a lista de Clientes
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Customer.h"

/**
 * Carregar uma lista de Clientes de um ficheiro de texto
 * 
 * \param fileName
 * \return 
 */
Customer* LoadCustomers(char fileName[]) {
	Customer* h = NULL;
	Customer* current = NULL;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
		if (newCustomer == NULL)return NULL;

		if (fscanf(fp, "%d;%[^;];%[^;];%[^;];%0.2f\n", newCustomer->id, newCustomer->name, newCustomer->nif, newCustomer->address, newCustomer->balance) == 5) {
			newCustomer->next = NULL;

			if (h == NULL) {
				h = newCustomer;
				current = newCustomer;
			}
			else {
				current->next = newCustomer;
				current = newCustomer;
			}
		}
		else {
			free(newCustomer);
		}
	}
	fclose(fp);
	return h;
}

/**
 * Carregar uma lista de Clientes de um ficheiro binário
 * 
 * \param fileName
 * \return 
 */
Customer* LoadCustomersBin(char fileName[]) {
	Customer* h = NULL;

	FILE* fp;
	fp = fopen(fileName, "rb");
	if (fp == NULL)return NULL;

	Customer* aux;
	while (fread(&aux, 1, sizeof(Customer), fp)) {
		h = AddCustomer(h, &aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Clientes para um ficheiro de texto
 * 
 * \param h
 * \param fileName
 * \return 
 */
bool SaveCustomers(Customer* h, char fileName[]) {
	FILE* fp;
	fp = fopen(fileName, "w");
	if (h == NULL) return false;
	if (fp == NULL)return false;

	Customer* current = h;

	while (current != NULL) {
		fprintf(fp,"%d;%s;%s;%s;%0.2f\n",current->id, current->name, current->nif, current->address, current->balance);
		current = current->next;
	}
	fclose(fp);
	return true;
}

/**
 * Gravar uma lista de Clientes para um ficheiro binário
 * 
 * \param h
 * \param fileName
 * \return 
 */
bool SaveCustomersBin(Customer* h, char fileName[]) {
	if (h == NULL)return false;
	Customer* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;
	while (aux != NULL) {
		fwrite(aux, 1, sizeof(Customer), fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
 * Inserir um Cliente a uma lista de Clientes, ordenada por id
 * 
 * \param h
 * \param c
 * \return 
 */
Customer* AddCustomer(Customer* h, Customer* c) {
	Customer* aux = (Customer*)malloc(sizeof(Customer));
	aux->next = NULL;

	if (h == NULL) {
		h = c;
		return h;
	}
	else {
		if (h->id > aux->id) {
			aux->next = h;
			h = c;
		}
		else {
			Customer* prev = h;
			Customer* current = h;
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
 * Remover um Cliente com um id definido de uma lista de Clientes 
 * 
 * \param h
 * \param id
 * \return 
 */
Customer* RemoveCustomer(Customer* h, int id) {
	if (h == NULL) return NULL;

	Customer* aux = h;
	Customer* prev = NULL;

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
 * Trocar um Cliente de uma lista de Clientes por um com o mesmo id
 * 
 * \param h
 * \param c
 * \return 
 */
bool EditCustomer(Customer* h, Customer* c) {
	if (h == NULL || c == NULL)return false;
	Customer* aux = h;

	while (aux != NULL) {
		if (aux->id == c->id) {
			strcpy(aux->name, c->name);
			strcpy(aux->nif, c->nif);
			strcpy(aux->address, c->address);
			aux->balance = c->balance;
			return true;
		}
		aux = aux->next;
	}
	return false;
}

/**
 * Mostrar todos os Clientes em uma lista de Clientes
 * 
 * \param h
 */
void ShowCustomerList(Customer* h) {
	Customer* aux = h;
	while (aux != NULL) {
		printf("Customer\nID: %d\nName: %s\nNIF: %s\nAddress: %s\nBalance: %0.2f\n",aux->id, aux->name, aux->nif, aux->balance, aux->balance);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Clientes
 * 
 * \param h
 * \return 
 */
bool ClearCustomerList(Customer* h) {
	if (h == NULL)return false;
	Customer* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}

