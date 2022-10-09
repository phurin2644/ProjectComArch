/* Assembler code fragment */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
char const * DecimalToBin(char *);
string Rtype(char *,char *,char *,char *);
string Itype(char *,char *,char *,char *);
string Jtype(char *,char *,char *);
string Otype(char *);

int main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
        arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    string s ;
    
    printf("binnum: %s\n",DecimalToBin("20"));
    char *opc = "010";
    char ra[] = "5";
    char rb[] = "5";
    char dr[] = "5";
    s = Rtype(opc,ra,rb,dr);
    printf("code: %s\n",s.c_str());
    s = Itype(opc,ra,rb,dr);
    printf("code: %s\n",s.c_str());
    s = Jtype(opc,ra,rb);
    printf("code: %s\n",s.c_str());
    s = Otype(opc);
    printf("code: %s\n",s.c_str());

    if (argc != 3)
    {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
               argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL)
    {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL)
    {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    /* here is an example for how to use readAndParse to read a line from
        inFilePtr */
    if (!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
    {
        /* reached end of file */
    }

    /* this is how to rewind the file ptr so that you start reading from the
        beginning of the file */
    rewind(inFilePtr);

    /* after doing a readAndParse, you may want to do the following to test the
        opcode */
    if (!strcmp(opcode, "add")){
        /* do whatever you need to do for opcode "add" */
        s = Rtype("000",arg0,arg1,arg2);
    }else if (!strcmp(opcode, "nand")){
        /* do whatever you need to do for opcode "nand" */
        s = Rtype("001",arg0,arg1,arg2);
    }else if (!strcmp(opcode, "lw")){
        /* do whatever you need to do for opcode "lw" */
        s = Itype("010",arg0,arg1,arg2);
    }else if (!strcmp(opcode, "sw")){
        /* do whatever you need to do for opcode "sw" */
        s = Itype("011",arg0,arg1,arg2);
    }else if (!strcmp(opcode, "beq")){
        /* do whatever you need to do for opcode "beq" */
        s = Itype("100",arg0,arg1,arg2);
    }else if (!strcmp(opcode, "jalr")){
        /* do whatever you need to do for opcode "beq" */
        s = Jtype("101",arg0,arg1);
    }else if (!strcmp(opcode, "halt")){
        /* do whatever you need to do for opcode "beq" */
        s = Otype("110");
    }else if (!strcmp(opcode, "noop")){
        /* do whatever you need to do for opcode "beq" */
        s = Otype("111");
    }

    return (0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
                 char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL)
    {
        /* reached end of file */
        return (0);
    }

    /* check for line too long (by looking for a \n) */
    if (strchr(line, '\n') == NULL)
    {
        /* line too long */
        printf("error: line too long\n");
        exit(1);
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label))
    {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n ]%[^\t\n ]%*[\t\n ]%[^\t\n ]%*[\t\n ]%[^\t\n ]%*[\t\n ]%[^\t\n ]",
           opcode, arg0, arg1, arg2);
    return (1);
}

int isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return ((sscanf(string, "%d", &i)) == 1);
}

char const * DecimalToBin(char *demi){
	int decimal = atoi(demi);
	int binary = 0, remainder, product = 1;
	while (decimal != 0) {
    remainder = decimal % 2;
    binary = binary + (remainder * product);
    decimal = decimal / 2;
    product *= 10;
  }
  std::stringstream tmp;
    tmp << binary;

    char const *num_char = tmp.str().c_str();
	return num_char ;
}
int BinToHex(){

}
string Rtype(char *opc,char *rA,char *rB,char *dR){
	std::string opcode(opc);
	std::string regA(DecimalToBin(rA));
	std::string regB(DecimalToBin(rB));
	std::string destReg(DecimalToBin(dR));
	while(regA.length()<3){
		regA = "0"+regA ;
	}
	while(regB.length()<3){
		regB = "0"+regB ;
	}
	while(destReg.length()<3){
		destReg = "0"+destReg ;
	}
    string fields = "0000000"+opcode+regA+regB+"0000000000000"+destReg ;
    return fields ;
}
string Itype(char *opc,char *rA,char *rB,char *offsField){
	std::string opcode(opc);
	std::string regA(DecimalToBin(rA));
	std::string regB(DecimalToBin(rB));
	std::string offsetField(DecimalToBin(offsField));
	while(regA.length()<3){
		regA = "0"+regA ;
	}
	while(regB.length()<3){
		regB = "0"+regB ;
	}
	while(offsetField.length()<16){
		offsetField = "0"+offsetField ;
	}
    string fields = "0000000"+opcode+regA+regB+offsetField ;
    return fields ;
}
string Jtype(char *opc,char *rA,char *rB){
	std::string opcode(opc);
	std::string regA(DecimalToBin(rA));
	std::string regB(DecimalToBin(rB));
	while(regA.length()<3){
		regA = "0"+regA ;
	}
	while(regB.length()<3){
		regB = "0"+regB ;
	}
    string fields = "0000000"+opcode+regA+regB+"0000000000000000" ;
    return fields ;
}
string Otype(char *opc){
	std::string opcode(opc);
    string fields = "0000000"+opcode+"0000000000000000000000" ;
    return fields ;
}
