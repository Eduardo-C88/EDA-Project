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
CustomerList* LoadCustomers(char fileName[]) {
	CustomerList* h = NULL;
	Customer* aux = (Customer*)malloc(sizeof(Customer));

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)return NULL;

	while (!feof(fp)) {
		fscanf(fp, "%d;%s;%s;%s;%0.2f\n", &aux->id, aux->name, aux->nif, aux->address, &aux->balance);
		h = AddCustomer(h, aux);
	}
	fclose(fp);
	return h;
}

/**
 * Gravar uma lista de Clientes para um ficheiro binário
 * 
 * \param h
 * \param fileName
 * \return 
 */
bool SaveCustomersBin(CustomerList* h, char fileName[]) {
	if (h == NULL)return false;
	CustomerList* aux = h;

	FILE* fp;
	fp = fopen(fileName, "wb");
	if (fp == NULL)return false;

	while (aux != NULL) {
		fwrite(&aux->customer, 1, sizeof(aux->customer), fp);
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
CustomerList* AddCustomer(CustomerList* h, Customer* c) {
	if (c == NULL)return h;
	CustomerList* aux = (CustomerList*)malloc(sizeof(CustomerList));
	aux->next = NULL;
	aux->customer = *c;

	if (h == NULL) {
		h = aux;
		return h;
	}
	else {	
		if (h->customer.id > aux->customer.id) {
			aux->next = h;
			h = aux;
		}
		else {
			CustomerList* prev = h;
			CustomerList* current = h;
			while (current != NULL && current->customer.id < aux->customer.id) {
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
CustomerList* RemoveCustomer(CustomerList* h, int id) {
	if (h == NULL) return NULL;

	CustomerList* aux = h;
	CustomerList* prev = NULL;

	while (aux != NULL && aux->customer.id != id) {
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
bool EditCustomer(CustomerList* h, Customer* c) {
	if (h == NULL || c == NULL)return false;
	CustomerList* aux = h;

	while (aux != NULL) {
		if (aux->customer.id == c->id) {
			strcpy(aux->customer.name, c->name);
			strcpy(aux->customer.nif, c->nif);
			strcpy(aux->customer.address, c->address);
			aux->customer.balance = c->balance;
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
void ShowCustomersList(CustomerList* h) {
	CustomerList* aux = h;
	while (aux != NULL) {
		printf("ID: %d\nName: %s\nNIF: %s\nAddress: %s\nBalance: %0.2f\n",aux->customer.id, aux->customer.name, aux->customer.nif, aux->customer.address, aux->customer.balance);
		aux = aux->next;
	}
}

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Clientes
 * 
 * \param h
 * \return 
 */
bool ClearCustomersList(CustomerList* h) {
	if (h == NULL)return false;
	CustomerList* aux;
	while (h != NULL) {
		aux = h->next;
		free(h);
		h = aux;
	}
	return true;
}

