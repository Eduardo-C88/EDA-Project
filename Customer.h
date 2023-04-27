/*****************************************************************//**
 * \file   Customer.h
 * \brief  Declaração da struct e funções para os Clientes
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef CUSTOMER
#define CUSTOMER

#include "Globals.h"

#define NAME_SIZE 20
#define NIF_SIZE 10
#define ADD_SIZE 30

typedef struct Customer {
	int id;
	char name[NAME_SIZE];
	char nif[NIF_SIZE];
	char address[ADD_SIZE];
	float balance;
	//struct Customer* next;
}Customer;

typedef struct CustomerList {
	Customer customer;
	struct CustomerList* next;
}CustomerList;

/**
 * Carregar uma lista de Clientes de um ficheiro de texto
 */
CustomerList* LoadCustomers(char f[]);

/**
 * Carregar uma lista de Clientes de um ficheiro binário
 */
//CustomerList* LoadCustomersBin(char f[]);

/**
 * Gravar uma lista de Clientes para um ficheiro de texto
 */
//bool SaveCustomers(CustomerList* h, char f[]);

/**
 * Gravar uma lista de Clientes para um ficheiro binário
 */
bool SaveCustomersBin(CustomerList* h, char f[]);

/**
 * Inserir um Cliente a uma lista de Clientes, ordenada por id
 */
CustomerList* AddCustomer(CustomerList* h, Customer* c);

/**
 * Remover um Cliente com um id definido de uma lista de Clientes 
 */
CustomerList* RemoveCustomer(CustomerList* h, int id);

/**
 * Trocar um Cliente de uma lista de Clientes por um com o mesmo id
 */
bool EditCustomer(CustomerList* h, Customer* c);

/**
 * Mostrar todos os Clientes em uma lista de Clientes
 */
void ShowCustomerList(CustomerList* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Clientes
 */
bool ClearCustomerList(CustomerList* h);

#endif


