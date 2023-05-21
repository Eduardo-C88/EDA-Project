/*****************************************************************//**
 * \file   Vehicle.h
 * \brief  Declaração da struct e funções para os Transportes
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/
#pragma warning(disable : 4996)

#ifndef VEHICLE
#define VEHICLE

#include "Globals.h"

#define TYPE_SIZE 20

typedef struct Vehicle{
	int id;
	char type[TYPE_SIZE];
	float battery;
	float price;                   //por distância
	char local[NAME_SIZE];
	//struct Vehicle* next;
}Vehicle;

typedef struct VehicleList {
	Vehicle vehicle;
	struct VehicleList* next;
}VehicleList;

/**
 * Carregar uma lista de Veículos de um ficheiro de texto
 */
VehicleList* LoadVehicles(char f[]);

/**
 * Gravar uma lista de Veículos para um ficheiro binário
 */
bool SaveVehiclesBin(VehicleList* h, char f[]);

/**
 * Inserir um Veículo a uma lista de Veículos, ordenada de ordem crescente por id
 */
VehicleList* AddVehicle(VehicleList* h, Vehicle* v);

/**
 * Remover um Veículo com um id definido de uma lista de Veículos
 */
VehicleList* RemoveVehicle(VehicleList* h, int id);

/**
 * Trocar um Veículo de uma lista de Veículos por um com o mesmo id
 */
bool EditVehicle(VehicleList* h, Vehicle* v);

/**
 * Mostrar todos os Veículos em uma lista de Veículos
 */
void ShowVehiclesList(VehicleList* h);

/**
 * Limpar/Libertar o espaço da memória ocupada por uma lista de Veículos
 */
bool ClearVehiclesList(VehicleList* h);

/**
 * Devolver um Veículo, com um geocódigo determinado, de um lista de Veículos
 */
VehicleList* SearchVehicle(VehicleList* h, char g[]);

/**
 * Inserir um Veículo a uma lista de Veículos, ordenada de ordem decrescente por autonomia
 */
VehicleList* AddVehicleAutDec(VehicleList* h, Vehicle* v);

/**
 * Listar os Veículos, de uma lista de Veículos já existente, com um determinado geocódigo 
 */
VehicleList* AddVehicleGeo(VehicleList* h, VehicleList* v, char* local);
#endif



