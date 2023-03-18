/*****************************************************************//**
 * \file   Manager.h
 * \brief  
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef MANAGER
#define MANAGER

#include "Globals.h"

#define NAME_SIZE 20
#define E_SIZE 50
#define PW_SIZE 20

typedef struct Manager{
	int id;
	char name[NAME_SIZE];
	char email[E_SIZE];
	char password[PW_SIZE];
	struct Manager* next;
}Manager;

/**
 * .
 */
Manager* LoadManagers(char f[]);
/**
 * .
 */
Manager* LoadManagersBin(char fileName[]);
/**
 * .
 */
bool SaveManagers(Manager* h, char f[]);
/**
 * .
 */
bool SaveManagersBin(Manager* h, char f[]);
/**
 * .
 */
Manager* AddManager(Manager* h, Manager* m);
/**
 * .
 */
Manager* RemoveManager(Manager* h, int id);
/**
 * .
 */
bool EditManager(Manager* h, Manager* m);
/**
 * .
 */
void ShowManagerList(Manager* h);
/**
 * .
 */
bool ClearManagerList(Manager* h);

#endif // !MANAGER



