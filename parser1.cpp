#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <bits/stdc++.h>
using namespace std;

int removeBlankSpace(int index, char line[]);
int sameStr(char str1[], char str2[]);
int opcodeRead(int* index, char line[], char word[]);
int printSpecDir(int* index, char line[], char word[]);
int opBlankSpace(int index, char line[]);
void readOperand (int* index, char line[], char word[]);
void readLastOp (int* index, char line[], char word[]);
int isInt(char word[]);
int isRegister(char word[]);
int isBracketed(char word[]);

char assCodes[][19] = {"LD", "LDi", "SD", "SDi", "ADD",							//Char arrays of ass(embly) codes
					"ADDi", "SUB", "SUBi", "MUL", "MULi",
					"DIV", "DIVi", "JMP", "JZ", "JNZ",
					"JGZ", "JGEZ", "JLZ", "JLEZ"};

int main (int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Error: Exactly 2 arguments required." << endl;
		return -1;
	}
	//Initialize all necessary variables
	char line[100] = {};
	int countLS = 0, countALU = 0, countCJ = 0, total = 0;
	int lineNum = 1;
	int codeNum = 0;
	//Open file
	ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open()) {
		cerr << "Error: Unable to open file: " << argv[1] << endl;
		return -1;
	}
	infile >> setw(100);
	while (infile.getline(line, 100)) {
		int index = 0;
		char word[100];
		for(int x=0; x<100; x++)
			word[x]=0;
		index = removeBlankSpace(index, line);
		//Now index is first non-blank char.
		int opNum = opcodeRead(&index, line, word);
		if (opNum==-1) {														//Unrecognized OpCode-> error message, go to next line.
			cerr << "Error on line " << lineNum << ": invalid opcode." << endl;
		}
		else if (opNum==20) {													//Blank line/comment-> no instructions required.
		}
		else {																	//Directives/Opcodes: Requires additional line checking.
			if (opNum==19) {													//Directives-> prints out the directive.	
				char dir1[6] = "Code:";
				char dir2[6] = "Data:";
				if (sameStr(word, dir1)) {
					index = removeBlankSpace(index, line);
					codeNum = printSpecDir(&index, line, word);
				}
				else if (sameStr(word, dir2)) {
					index = removeBlankSpace(index, line);
					int temp = printSpecDir(&index, line, word);
				}
				else {
					index = removeBlankSpace(index, line);
					cout << word << " " << codeNum << endl;
				}
			}
			if (opNum>=0&&opNum<=18) {											//Opcodes. GL Andrew you're gonna need it
				for (int x=0; x<100; x++)
					word[x]=0;
				bool valid = true;
				index = removeBlankSpace(index, line);		
				readOperand(&index, line, word);
				if (opNum==0) {
					if (!isInt(word)&&!isRegister) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;						
						readLastOp(&index, line, word);
						if (!isRegister(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}	
					}
				}
				if (opNum==1) {
					if (!isInt(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;						
						readLastOp(&index, line, word);
						if (!isRegister(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
					}
				}				
				if (opNum==2) {
					if (!isRegister(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;
						readLastOp(&index, line, word);
						if (!isInt(word)&&!isRegister(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
					}					
				}
				if (opNum==3) {
					if (!isInt(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;						
						readLastOp(&index, line, word);
						if (!isInt(word)&&!isRegister(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
					}
				}					
				if (opNum==4||opNum==6||opNum==8||opNum==10) {
					if (!isRegister(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;
						readOperand(&index, line, word);
						if (!isRegister(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
						else {
							index = opBlankSpace(index, line);
							for (int x=0; x<100; x++)
								word[x]=0;
							readLastOp(&index, line, word);
							if (!isRegister(word)) {
								valid = false;
								cout << "Error on line " << lineNum << ": Invalid operand" << endl;
							}
						}
					}
				}
				if (opNum==5||opNum==7||opNum==9||opNum==11) {
					if (!isRegister(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;
						readOperand(&index, line, word);
						if (!isInt(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
						else {
							index = opBlankSpace(index, line);
							for (int x=0; x<100; x++)
								word[x]=0;
							readLastOp(&index, line, word);
							if (!isRegister(word)) {
								valid = false;
								cout << "Error on line " << lineNum << ": Invalid operand" << endl;
							}
						}
					}					
				}
				if (opNum==12) {
					if (!isInt(word)&&!isBracketed(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
				}
				if (opNum>=13&&opNum<=18) {
					if (!isRegister(word)) {
						valid = false;
						cout << "Error on line " << lineNum << ": Invalid operand" << endl;
					}
					else {
						index = opBlankSpace(index, line);
						for (int x=0; x<100; x++)
							word[x]=0;
						readLastOp(&index, line, word);
						if (!isInt(word)&&!isBracketed(word)) {
							valid = false;
							cout << "Error on line " << lineNum << ": Invalid operand" << endl;
						}
					}
				}
				if (valid) {
					if (opNum>=0&&opNum<=3)
						countLS++;
					else if (opNum>=4&&opNum<=11)
						countALU++;
					else if (opNum>=12&&opNum<=18) {
						countCJ++;
					}
				}
			}

		//After any of these instructions MUST be a comment
		//or else it is invalid by definition. The following
		//code checks for this.
			int tempIndex = index;
			index = removeBlankSpace(index, line);
			if (index!=tempIndex) {
				for (int x = 0; x < 100; x++)
					word[x] = 0;
				int opNum2 = opcodeRead(&index, line, word);
				if (opNum2!=19&&opNum2!=20) {
					cerr << "Error on line " << lineNum << ": Extra data after instruction." << endl;
				}				
			}
		}
		if (opNum>=0&&opNum<=18) {
			codeNum++;

		}
		lineNum++;
	}
	
	//Final output
	total = countLS + countALU + countCJ;
	cout << "Total number of assembly instructions: " << total << endl;
	cout << "Number of Load/Store: " << countLS << endl;
	cout << "Number of ALU: " << countALU << endl;
	cout << "Number of Compare/Jump: " << countCJ << endl;
	return 0;
}
int removeBlankSpace(int index, char line[]) {								//Returns the index of the next non-blank character
	enum {BLANK, OPCODE};
	int state = BLANK;
	while (state!=OPCODE) {
		switch(state) {
			case BLANK:
				if (isspace(line[index])) {
					index++;
				}
				else
					state = OPCODE;
				break;
			default:
				break;
		}
	}
	return index;
}
int sameStr(char str1[], char str2[]) {										//Returns 1 (true) if the char arrays are the same. 0 if different
	/*THIS FUNCTION WORKS EVEN WITH LEADING BLANKSPACE!!!*/
	int i = 0;
	while (str1[i]!=0||str2[i]!=0) {
		if (str1[i]==0||str2[i]==0)
			return 0;
		else if (str1[i]!=str2[i])
			return 0;
		else
			i++;
	}
	return 1;
}
int opcodeRead(int* index, char line[], char word[]) {						//Returns a numerical value of the beginning OPCODE in the program
	//Note: This function also writes the
	//next word to the char array "word".
	int counter = 0;
	for(int x=*index; x<100; x++)
	{
		//if(line[x]==' ' || line[x]=='\n' || line[x]==0)
		if (isspace(line[x]))
			break;
		if (line[x]==':') {
			counter++;
			break;
		}
		counter++;
	}
	for(int x=*index; x<*index+counter; x++)
		word[x-*index] = line[x];
	//The char array "WORD" now contains the WORD in which it was used on.
	*index += counter;
	//comment or newline: 20
	if (word[0]=='\0'||word[0]=='#') {
		return 20;
	}
	//directives: 19
	if (word[counter-1]==':') {
		return 19;
	}
	//opcodes: 0 to 18
	for (int i = 0; i < 19; i++) {
		if (sameStr(word, assCodes[i]))
			return i;
	}
	//unrecognized stuff: -1
	return -1;
}
int printSpecDir(int* index, char line[], char word[]) {					//Prints the "Code/Data: <n>" directives
	int counter = 0;
	char codeChar[95];
	for (int x = *index; x < 94; x++) {
		if (line[x]==' '||line[x]=='\n'||line[x]==0) {
			break;
		}
		counter++;
	}

	for (int x = *index; x < *index+counter; x++)
		codeChar[x-*index] = line[x];
	int followInt = atoi (codeChar);
	
	//Checking to see if the value is actually an integer
	if (followInt!=0) {
		cout << word << " " << followInt << endl;
		return followInt;
	}
	else {
		if (codeChar[0]!=0) {
			cerr << "Error: Incorrect information entered for Code/Data directive." << endl;
			return 0;
		}
		else {
			cout << word << " " << followInt << endl;
			return followInt;
		}
	}
}
int opBlankSpace(int index, char line[]) {									//returns the index of the next non-blank character (excepting commas)
	enum {BLANK, OPERAND};
	int state = BLANK;
	while (state!=OPERAND) {
		switch (state) {
			case BLANK:
				if (isspace(line[index])||line[index]==',') {
					index++;
				}
				else
					state = OPERAND;
				break;
			default:
				break;
		}
	}
	return index;
}
void readOperand(int* index, char line[], char word[]) {					//Reads all but last operand. (stops at commas or spaces)
	int counter = 0;
	for (int x=*index; x<100; x++) {
		if (isspace(line[x])||line[x]==',')
			break;
		counter++;
	}
	for(int x=*index; x<*index+counter; x++)
		word[x-*index] = line[x];
	
	*index += counter;
}
void readLastOp(int* index, char line[], char word[]) {						//Reads last register (only stops at spaces)
	int counter = 0;
	for (int x=*index; x<100; x++) {
		if (isspace(line[x])||line[x]==0)
			break;
		counter++;
	}
	for(int x=*index; x<*index+counter; x++)
		word[x-*index] = line[x];
	*index += counter;	
}
int isInt(char word[]) {													//Returns 1 (true) if the char array is an int. 0 if not.
	for (int i = 0; i < 99; i++) {
		if (!isdigit(word[i])&&!isspace(word[i])&&word[i]!=0&&word[i]!='-') {
			return 0;
		}
	}
	return 1;
}
int isRegister(char word[]) {												//Returns 1 (true) if the char array is a valid register. 0 if not
	if (word[0]!='R') {
		return 0;
	}
	else {
		int counter = 0;
		char word2[99];
		for (int i = 0; i < 99; i++) {
			word2[i] = 0;
		}
		for (int x=0; x<100; x++) {
			if (word[x]==' '||word[x]=='\n'||word[x]==0)
				break;
			counter++;
		}
		for (int i = 0; i < counter; i++) {
			word2[i]=word[i+1];
		}
		if (isInt(word2)) {
			return 1;
		}
		else {
			return 0;
		}
	}
}
int isBracketed(char word[]) {												//Returns 1 (true) if the char array is enclosed in square brackets. 0 if not
	if (word[0]!='[') {
		return 0;
	}
	int counter = 0;
	for (int x=0; x<100; x++) {
		if (word[x]==' '||word[x]=='\n'||word[x]==0)
			break;
		counter++;
	}
	if (word[counter-1]!=']') {
		return 0;
	}
	return 1;
}
/**/