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
	struct Customer* next;
}Customer;

/**
 * Carregar uma lista de Clientes de um ficheiro de texto
 */
Customer* LoadCustomers(char f[]);

/**
 * Carregar uma lista de Clientes de um ficheiro binário
 */
Customer* LoadCustomersBin(char f[]);

/**
 * Gravar uma lista de Clientes para um ficheiro de texto
 */
bool SaveCustomers(Customer* h, char f[]);

/**
 * Gravar uma lista de Clientes para um ficheiro binário
 */
bool SaveCustomersBin(Customer* h, char f[]);

/**
 * Inserir um Cliente a uma lista de Clientes, ordenada por id
 */
Customer* AddCustomer(Customer* h, Customer* c);

/**
 * Remover um Cliente com um id definido de uma lista de Clientes 
 */
Customer* RemoveCustomer(Customer* h, int id);

/**
 * Trocar um Cliente de uma lista de Clientes por um com o mesmo id
 */
bool EditCustomer(Customer* h, Customer* c);

/**
 * Mostrar todos os Clientes em uma lista de Clientes
 */
void ShowCustomerList(Customer* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Clientes
 */
bool ClearCustomerList(Customer* h);

#endif


