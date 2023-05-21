/*****************************************************************//**
 * \file   Manager.h
 * \brief  Declaração da struct e funções para os Gestores
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma warning(disable : 4996)

#ifndef MANAGER
#define MANAGER

#include "Globals.h"

#define NAME_SIZE 50
#define E_SIZE 50
#define PW_SIZE 16

typedef struct Manager{
	int id;
	char name[NAME_SIZE];
	char email[E_SIZE];
	char password[PW_SIZE];
	//struct Manager* next;
}Manager;

typedef struct ManagerList {
	Manager manager;
	struct ManagerList* next;
}ManagerList;

/**
 * Carregar uma lista de Gestores de um ficheiro de texto
 */
ManagerList* LoadManagers(char f[]);

  /**
   * Gravar uma lista de Gestores para um ficheiro binário
   */
bool SaveManagersBin(ManagerList* h, char f[]);

/**
 * Inserir um Gestor a uma lista de Gestores, ordenada por id
 */
ManagerList* AddManager(ManagerList* h, Manager* m);

/**
 * Remover um Gestor com um id definido de uma lista de Gestores
 */
ManagerList* RemoveManager(ManagerList* h, int id);

/**
 * Trocar um Gestor de uma lista de Gestores por um com o mesmo id
 */
bool EditManager(ManagerList* h, Manager* m);

/**
 * Mostrar todos os Gestores em uma lista de Gestores
 */
void ShowManagersList(ManagerList* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Gestores
 */
bool ClearManagersList(ManagerList* h);

#endif // !MANAGER



