#pragma once
// assembly.h
// This header file includes code used in syntax.h to generate assembly instructions.
// Tyler Hatzenbuhler
// Anette Ulrichsen

/*
	The Symbol Table will collect all the variable names from the declaration list, essentially saving the variables in memory.
	Then, for the statements, instructions are created and added to the instruction vector, which actually holds the faux
	assembly code. Back patch function is used for JUMP / loop bases instructions.
*/

int memory_address = 10000; // Global staring address variable

class Symbol { // One instance of symbol, collected in vector;
public:
	string identifier;
	int memLocation;
	string type;

	Symbol(string a, int b, string c) {
		identifier = a;
		memLocation = b;
		type = c;
	}
	Symbol() {
		identifier = "";
		memLocation = 0;
		type = "";
	}
};

class Instr{ // One instance of an instruction, collected in vector
public:
	string Op;
	int operand;
	Instr(string a, int b) {
		Op = a;
		operand = b;
	}
	Instr() {
		Op = "";
		operand = 0;
	}
};

vector<Symbol> SymbolTable; // Global Symbol Table
vector<Instr> InstrTable; // Global Instruction Table

int get_address(string x) { // Checks symbol table for given id and returns address
	if (SymbolTable.size() == 0) {
		cout << "Error: table empty" << endl;
		exit(1);
	}
	for (int i = 0; i < SymbolTable.size(); i++) {
		if (SymbolTable[i].identifier == x) {
			return SymbolTable[i].memLocation;
		}
	}
	// If it reaches below code, id was not found in table
	cout << "Error: identifier not declared" << endl;
	exit(1);
}

void printST() { // Prints all stored symbols in symbol table
	if (SymbolTable.size() == 0) return;
	cout << "--------- Symbol Table ---------" << endl;
	for (int i = 0; i < SymbolTable.size(); i++) {
		cout << "Identifier: " << SymbolTable[i].identifier << "   Mem Location: " << SymbolTable[i].memLocation << "   Type: " << SymbolTable[i].type << endl;
	}
}

/*
Potentially add a printIT function instead of printST
*/

void add_symbol(string ins, int mem, string t) { // Adds identifier to vector
	Symbol input(ins, mem, t);
	SymbolTable.push_back(input);
}

void add_instr(string ins, int mem) { // Places an instruction into the vector
	Instr input(ins, mem);
	InstrTable.push_back(input);
}

void back_patch(int jump_addr) {
	// todo
}

// potentially more functions needed regarding jumps / backpatch
