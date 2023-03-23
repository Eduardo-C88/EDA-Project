/*****************************************************************//**
 * \file   Vehicle.h
 * \brief  Declaração da struct e funções para os Transportes
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma once
#pragma warning(disable : 4996)

#ifndef VEHICLE
#define VEHICLE

#include "Globals.h"

#define TYPE_SIZE 15
#define CODE_SIZE 20

typedef struct Vehicle{
	int id;
	char type[TYPE_SIZE];
	float battery;
	float price;
	char geoCode[CODE_SIZE];
	struct Vehicle* next;
}Vehicle;

/**
 * Carregar uma lista de Transportes de um ficheiro de texto
 */
Vehicle* LoadVehiclesII(char fileName[]);
/**
 * Carregar uma lista de Transportes de um ficheiro de texto
 */
Vehicle* LoadVehicles(char f[]);

/**
 * Carregar uma lista de Transportes de um ficheiro binário
 */
Vehicle* LoadVehiclesBin(char f[]);

/**
 * Gravar uma lista de Transportes para um ficheiro de texto
 */
bool SaveVehicle(Vehicle* h, char f[]);

/**
 * Gravar uma lista de Transportes para um ficheiro binário
 */
bool SaveVehicleBin(Vehicle* h, char f[]);

/**
 * Inserir um Transporte a uma lista de Transportes, ordenada por id
 */
Vehicle* AddVehicle(Vehicle* h, Vehicle* v);

/**
 * Remover um Transporte com um id definido de uma lista de Transportes
 */
Vehicle* RemoveVehicle(Vehicle* h, int id);

/**
 * Trocar um Transporte de uma lista de Transportes por um com o mesmo id
 */
bool EditVehicle(Vehicle* h, Vehicle* v);

/**
 * Mostrar todos os Transportes em uma lista de Transportes
 */
void ShowVehicleList(Vehicle* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Transportes
 */
bool ClearVehicleList(Vehicle* h);

/**
 * Devolver um Transporte, de tipo definido, de um lista de Transportes
 */
Vehicle* SearchVehicle(Vehicle* h, char t[]);


#endif


