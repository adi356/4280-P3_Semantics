#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <iostream>      
#include <string>        
#include <vector>        
#include "node.h"
#include "token.h"
using namespace std;

typedef struct symbol_table
{
	Token identifier;
	//Token value;
} SymbolTable;

class Semantics
{
	private:
		SymbolTable st_holder;
		vector<SymbolTable> st;

		void checkDeclare(Token tk);
		void checkDefined(Token tk);

	public:
		void validate(NodeT *node);
};

#endif