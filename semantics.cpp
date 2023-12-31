/*
author: Andrew Irvine
P3 code
*/
#include "semantics.h"

/* check if the given token is already in the symbol table. Append if not. Error if so. */
void Semantics::checkDeclare(Token tk) {
	//Find the given variable in the symbol table. If exist, then it is already declare and should error
	static int is_declared = -1;
	for(unsigned int i = 0; i < st.size(); i++) {
		if(st[i].identifier.value == tk.value && st[i].identifier.id == tk.id) {
			if(st[i].identifier.blockNum == tk.blockNum) {
				is_declared = i;
				break;
			}
		}
	}

	//If positive, then the variable is already declared
	if(is_declared > -1) {
		cout << ">>: SEMANTICS ERROR the variable " << tk.value << " on line (" << tk.line_number <<
		") -> has already been declared on line (" << st[is_declared].identifier.line_number << ")" << endl;
		exit(EXIT_FAILURE);  //Comment this out to continue semantic check
	} else {
		st_holder.identifier = tk;
		st.push_back(st_holder);
	}
}


/* check if the given token is defined in the symbol table. Error if not*/
void Semantics::checkDefined(Token tk) {
	//Find the given variable in the symbol table. If exist, then it is already declare and should error
	int is_declared = -1;
	for(unsigned int i = 0; i < st.size(); i++) {
		if((st[i].identifier.value == tk.value)) {
			is_declared = i;
			break;
		}
	}

	//If positive, then the variable is declared. If not, then should error
	if(is_declared < 0) {
		cout << ">>: SEMANTICS ERROR the variable " << tk.value << " on line (" << tk.line_number <<
		") -> is not on the stack and not yet been declared" << endl;
		exit(EXIT_FAILURE);  //Comment this out to continue semantic check
	}
}


/* check for any violations of the static semantics.*/
void Semantics::validate(NodeT *node) {
	if(node == NULL) {
		return;
	}

	//Check for <vars> label
	if(node->label == "<vars>") {
		for(unsigned int i = 0; i < node->tokens.size(); i++) {
			if(node->tokens[i].id == IDENT_tk && node->tokens[i].value != "EMPTY") {
				checkDeclare(node->tokens[i]);
			}
		}
	}
	//Check for other label (whether identifier is defined or not)
	else {
		vector<string> labels = { "<R>", "<in>", "<assign>", "<label>", "<goTo>" };
		for(unsigned int i = 0; i < labels.size(); i++) {
			if(node->label == labels[i]) {		
				for(unsigned int ii = 0; ii < node->tokens.size(); ii++) {
					if(node->tokens[ii].id == IDENT_tk) {
						checkDefined(node->tokens[ii]);
					}
				}
			}
		}
	}

	validate(node->c1);
	validate(node->c2);
	validate(node->c3);
	validate(node->c4);
}