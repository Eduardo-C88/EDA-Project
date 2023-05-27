/*****************************************************************//**
 * \file   Program.c
 * \brief  Função main para correr o codigo
 * 
 * \author Eduardo
 * \date   March 2023
 *********************************************************************/

#include "Globals.h"

int main() {
#pragma region FASE 1
	int cTot = 1;
	int mTot = 1;
	int vTot = 1;

	CustomerList* cHeader = LoadCustomers("Customers.txt");
	ManagerList* mHeader = LoadManagers("Managers.txt");
	VehicleList* vHeader = LoadVehicles("Vehicles.txt");
	VehicleList* autList = NULL;
	VehicleList* geoList = NULL;

	Customer c1 = { cTot++, "Carlos", "267543512", "Rua dos Robalos", 10654.57 };
	Customer c2 = { cTot++, "Otavio", "237523415", "Travessa dos Robalos", 106.57 };

	Manager m1 = { mTot++, "Rodrigo", "rodrisantos@gmail.pt", "yessir123" };

	Vehicle v1 = { vTot++, "Bicycle", 54.3, 26.48, "Barcelos"};
	Vehicle v2 = { vTot++, "Scooter", 42.74, 22.56, "Braga" };
	Vehicle v3 = { vTot++, "Bicycle", 46.54, 24.31, "Braga" };
	
	//cHeader = NULL;
	//mHeader = NULL;
	//vHeader = NULL;

	cHeader = AddCustomer(cHeader, &c1);
	cHeader = AddCustomer(cHeader, &c2);
	mHeader = AddManager(mHeader, &m1);
	vHeader = AddVehicle(vHeader, &v1);
	vHeader = AddVehicle(vHeader, &v2);
	vHeader = AddVehicle(vHeader, &v3);

	autList = AddVehicleAutDec(autList, &v1);
	autList = AddVehicleAutDec(autList, &v2);
	autList = AddVehicleAutDec(autList, &v3);

	geoList = AddVehicleGeo(vHeader, "Braga");

	
	ShowVehiclesList(autList);
	printf("\n");
	ShowVehiclesList(geoList);
	printf("\n");

	cHeader = RemoveCustomer(cHeader, 2);

	printf("Customers:\n");
	ShowCustomersList(cHeader);
	printf("\nManagers:\n");
	ShowManagersList(mHeader);
	printf("\nVehicles:\n");
	ShowVehiclesList(vHeader);

	bool cSave = SaveCustomersBin(cHeader, "CustomersSave.bin");
	bool mSave = SaveManagersBin(mHeader, "ManagersSave.bin");
	bool vSave = SaveVehiclesBin(vHeader, "vehiclesSave.bin");

#pragma endregion
	printf("-----------------------------------\n");	
#pragma region FASE 2
	Town* graph = CreateGraph();
	int townTot = 1;

	Town* newTown = CreateTown(townTot++, "Barcelos", "///movement.mambo.camcorder");
	if (newTown != NULL) {
		graph = AddTown(graph, newTown);
	}

	newTown = CreateTown(townTot++, "Braga", "///car.capibara.recorder");
	if (newTown != NULL) {
		graph = AddTown(graph, newTown);
	}

	newTown = CreateTown(townTot++, "Porto", "///motorcycle.canibal.dice");
	if (newTown != NULL) {
		graph = AddTown(graph, newTown);
	}

	//RentList* rHeader = NULL;

	//Date d1 = { 12, 6, 2022 };
	//Date d2 = { 25, 8, 2022 };
	//Rent* newRent = CreateRent(&c1, &v1, d1, d2);
	//if (newRent != NULL) {
	//	rHeader = AddRent(rHeader, newRent);
	//}

	int pathTot = 1;
	Path* newPath = CreatePath(pathTot++, "Braga", 30.26);
	graph = AddPathToTown(graph, "Barcelos", newPath->dest, newPath->dist);

	newPath = CreatePath(pathTot++, "Porto", 42.31);
	graph = AddPathToTown(graph, "Barcelos", newPath->dest, newPath->dist);

	newPath = CreatePath(pathTot++, "Porto", 42.31);
	graph = AddPathToTown(graph, "Braga", newPath->dest, newPath->dist);

	newPath = CreatePath(pathTot++, "Braga", 42.31);
	graph = AddPathToTown(graph, "Porto", newPath->dest, newPath->dist);

	ShowTowns(graph);
	printf("\n---------------------------------\n");
	ShowGraph(graph);

	bool clear = ClearCustomersList(cHeader);
	clear = ClearManagersList(mHeader);
	clear = ClearVehiclesList(vHeader);
	clear = ClearVehiclesList(autList);
	clear = ClearVehiclesList(geoList);
#pragma endregion
}
