/*****************************************************************//**
 * \file   Vehicle.h
 * \brief  Declara��o da struct e fun��es para os Transportes
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
	float price;                   //por dist�ncia
	char local[NAME_SIZE];
	//struct Vehicle* next;
}Vehicle;

typedef struct VehicleList {
	Vehicle vehicle;
	struct VehicleList* next;
}VehicleList;

/**
 * Carregar uma lista de Ve�culos de um ficheiro de texto
 */
VehicleList* LoadVehicles(char f[]);

/**
 * Gravar uma lista de Ve�culos para um ficheiro bin�rio
 */
bool SaveVehiclesBin(VehicleList* h, char f[]);

/**
 * Inserir um Ve�culo a uma lista de Ve�culos, ordenada de ordem crescente por id
 */
VehicleList* AddVehicle(VehicleList* h, Vehicle* v);

/**
 * Remover um Ve�culo com um id definido de uma lista de Ve�culos
 */
VehicleList* RemoveVehicle(VehicleList* h, int id);

/**
 * Trocar um Ve�culo de uma lista de Ve�culos por um com o mesmo id
 */
bool EditVehicle(VehicleList* h, Vehicle* v);

/**
 * Mostrar todos os Ve�culos em uma lista de Ve�culos
 */
void ShowVehiclesList(VehicleList* h);

/**
 * Limpar/Libertar o espa�o da mem�ria ocupada por uma lista de Ve�culos
 */
bool ClearVehiclesList(VehicleList* h);

/**
 * Devolver um Ve�culo, com um geoc�digo determinado, de um lista de Ve�culos
 */
VehicleList* SearchVehicle(VehicleList* h, char g[]);

/**
 * Inserir um Ve�culo a uma lista de Ve�culos, ordenada de ordem decrescente por autonomia
 */
VehicleList* AddVehicleAutDec(VehicleList* h, Vehicle* v);

/**
 * Listar os Ve�culos, de uma lista de Ve�culos j� existente, com um determinado geoc�digo 
 */
VehicleList* AddVehicleGeo(VehicleList* h, VehicleList* v, char* local);
#endif



