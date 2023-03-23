/*****************************************************************//**
 * \file   Manager.h
 * \brief  Declaração da struct e funções para os Gestores
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
 * Carregar uma lista de Gestores de um ficheiro de texto
 */
Customer* LoadManagersII(char fileName[]);
/**
 * Carregar uma lista de Gestores de um ficheiro de texto
 */
Manager* LoadManagers(char f[]);

/**
 * Carregar uma lista de Gestores de um ficheiro binário
 */
Manager* LoadManagersBin(char fileName[]);

/**
 * Gravar uma lista de Gestores para um ficheiro de texto
 */
bool SaveManagers(Manager* h, char f[]);

/**
 * Gravar uma lista de Gestores para um ficheiro binário
 */
bool SaveManagersBin(Manager* h, char f[]);

/**
 * Inserir um Gestor a uma lista de Gestores, ordenada por id
 */
Manager* AddManager(Manager* h, Manager* m);

/**
 * Remover um Gestor com um id definido de uma lista de Gestores
 */
Manager* RemoveManager(Manager* h, int id);

/**
 * Trocar um Gestor de uma lista de Gestores por um com o mesmo id
 */
bool EditManager(Manager* h, Manager* m);

/**
 * Mostrar todos os Gestores em uma lista de Gestores
 */
void ShowManagerList(Manager* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Gestores
 */
bool ClearManagerList(Manager* h);

#endif // !MANAGER



