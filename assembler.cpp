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
string Jtype(string,string,string);
string Otype(string);

int main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
        arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    string s ;
    
    printf("binnum: %s\n",DecimalToBin("20"));
    char *opc = "010";
    char *ra = "111";
    char *rb = "010";
    char *dr = "101";
    s = Itype(opc,ra,rb,dr);
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
    if (!strcmp(opcode, "add"))
    {
        /* do whatever you need to do for opcode "add" */
//        s = Rtype("000");
    }else if (!strcmp(opcode, "nand"))
    {
        /* do whatever you need to do for opcode "nand" */
        int opc = 001 ;
    }else if (!strcmp(opcode, "lw"))
    {
        /* do whatever you need to do for opcode "add" */
        int opc = 010 ;
    }else if (!strcmp(opcode, "sw"))
    {
        /* do whatever you need to do for opcode "add" */
        int opc = 011 ;
    }else if (!strcmp(opcode, "beq"))
    {
        /* do whatever you need to do for opcode "add" */
        int opc = 100 ;
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
	printf("Demical num is %d \n", demi);
	int decimal = atoi(demi);
	printf("Demical num is %d \n", decimal);
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
	std::string regA(rA);
	std::string regB(rB);
	std::string destReg(dR);
    string fields = "0000000"+opcode+regA+regB+"0000000000000"+destReg ;
    return fields ;
}
string Itype(char *opc,char *rA,char *rB,char *offsField){
	std::string opcode(opc);
	std::string regA(rA);
	std::string regB(rB);
	std::string offsetField(offsField);
	int i = 0 ;
	while(offsetField.length()<16){
		offsetField = "0"+offsetField ;
	}
    string fields = "0000000"+opcode+regA+regB+offsetField ;
    return fields ;
}
string Jtype(string opcode,string regA,string regB){
    string fields = "0000000"+opcode+regA+regB+"0000000000000000" ;
    return fields ;
}
string Otype(string opcode){
    string fields = "0000000"+opcode+"0000000000000000000000" ;
    return fields ;
}
