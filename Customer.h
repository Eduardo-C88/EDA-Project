/*****************************************************************//**
 * \file   Customer.h
 * \brief  
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
 * .
 */
Customer* LoadCustomers(char f[]);
/**
 * .
 */
Customer* LoadCustomersBin(char f[]);
/**
 * .
 */
bool SaveCustomers(Customer* h, char f[]);
/**
 * .
 */
bool SaveCustomersBin(Customer* h, char f[]);
/**
 * .
 */
Customer* AddCustomer(Customer* h, Customer* c);
/**
 * .
 */
Customer* RemoveCustomer(Customer* h, int id);
/**
 * .
 */
bool EditCustomer(Customer* h, Customer* c);
/**
 * .
 */
void ShowCustomerList(Customer* h);
/**
 * .
 */
bool ClearCustomerList(Customer* h);

#endif


