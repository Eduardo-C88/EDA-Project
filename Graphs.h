/*****************************************************************//**
 * \file   Graphs.h
 * \brief  
 * 
 * \author Eduardo
 * \date   April 2023
 *********************************************************************/
#pragma warning(disable : 4996)

#pragma once
#include "Globals.h"

typedef struct Adj {


}Adj;

typedef struct Vertex{
	Customer customer;
	Vehicle vehicle;

	struct Vertex* next;
}Vertex;
