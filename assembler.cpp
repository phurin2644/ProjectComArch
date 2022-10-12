/* Assembler code fragment */

#include <iostream>
#include <bits/stdc++.h>
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
bool isNegative(int ) ;
string invertBits(int);
string DecimalToBin(char *,int);
long long int BinToDeci(string);
long long int Rtype(char *, char *, char *, char *);
long long int Itype(char *, char *, char *, char *,vector<string>,int);
long long int Jtype(char *, char *, char *);
long long int Otype(char *);
long long int filltype(char *,vector<string>);

int main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
        arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
    long long int s;
    std::vector<string> addressLabel;
    std::vector<long long int> machinecode ;

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
    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
    {
        /* code */
        if (std::find(addressLabel.begin(), addressLabel.end(), label) != addressLabel.end()&&strcmp(label, "")){
        /* same label */ 
                printf("error: already used %s as label\n",label);
                exit(1);
        }
        addressLabel.push_back(label);
    }
    // rewind(inFilePtr);
    rewind(inFilePtr);


    for (int n = 0; n < addressLabel.size(); n++){cout << n << " : "<< addressLabel[n] << "\n";}

    int ind = 0;


    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
    {
        /* code */
        if (!strcmp(opcode, "add"))
        {
            /* do whatever you need to do for opcode "add" */
            s = Rtype("000", arg2, arg1, arg0);

        }
        else if (!strcmp(opcode, "nand"))
        {
            /* do whatever you need to do for opcode "nand" */
            s = Rtype("001", arg2, arg1, arg0);
           
        }
        else if (!strcmp(opcode, "lw"))
        {
            /* do whatever you need to do for opcode "lw" */
            s = Itype("010", arg0, arg1, arg2,addressLabel,ind);
           
        }
        else if (!strcmp(opcode, "sw"))
        {
            /* do whatever you need to do for opcode "sw" */
            s = Itype("011", arg0, arg1, arg2,addressLabel,ind);
         
        }
        else if (!strcmp(opcode, "beq"))
        {
            /* do whatever you need to do for opcode "beq" */
            s = Itype("100", arg0, arg1, arg2,addressLabel,ind);
           
        }
        else if (!strcmp(opcode, "jalr"))
        {
            /* do whatever you need to do for opcode "beq" */
            s = Jtype("101", arg0, arg1);
          
        }
        else if (!strcmp(opcode, "halt"))
        {
            /* do whatever you need to do for opcode "beq" */
            s = Otype("110");
           
        }
        else if (!strcmp(opcode, "noop"))
        {
            /* do whatever you need to do for opcode "beq" */
            s = Otype("111");
        
        }
        else if(!strcmp(opcode, ".fill")){
            s = filltype(arg0,addressLabel);
        }
        else{
            printf("error: no %s opcode\n",opcode);
            exit(1);
        }
        machinecode.push_back(s);
        ind++ ;
    }

    /* print on output*/
    for (int n = 0; n < machinecode.size(); n++){
        fprintf(outFilePtr, "%d \n",machinecode[n]) ;
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
bool isNegative(int n){
    return n < 0 ;
}

string invertBits(int num)
{
    // calculating number of bits
    // in the number
    bitset<16> b(to_string(num));
    
 
    // Inverting the bits one by one
   b.flip();
    return b.to_string() ;
}
string DecimalToBin(char *demi , int index)
{
    int decimal = atoi(demi);
    bool isN = isNegative(decimal);
    if(isN){decimal = abs(decimal+1);}
    int binary = 0, remainder, product = 1;
    while (decimal != 0)
    {
        remainder = decimal % 2;
        binary = binary + (remainder * product);
        decimal = decimal / 2;
        product *= 10;
    }
    std::stringstream tmp;
    if(!isN){tmp << binary;
    }else{tmp << invertBits(binary);}

    string num_char = tmp.str();
    while (num_char.length() < index)
    {
        if(!isN){
            num_char = "0" + num_char ;
        }else{ 
            num_char = "1" + num_char ;
        }
    }
    return num_char;
}

long long int BinToDeci(string n)
{
    char *end;
    int j = 0;
    while (n[j] == '0')
    {
        ++j;
    }
    n.erase(0, j);
    int decimalNumber = 0;
    int base = 1;
    long long int temp = stoll(n, 0, 2);
    return temp;
}
long long int Rtype(char *opc, char *rA, char *rB, char *dR)
{
    std::string opcode(opc);
    std::string regA(DecimalToBin(rA,3));
    std::string regB(DecimalToBin(rB,3));
    std::string destReg(DecimalToBin(dR,3));
    string fields = "0000000" + opcode + regA + regB + "0000000000000" + destReg;
    return BinToDeci(fields);
}
long long int Itype(char *opc, char *rA, char *rB, char *offsField,vector<string> adr,int ind)
{
    int x ;
    if(!isNumber(offsField)){
        for (int n = 0; n < adr.size(); n++){
            if(!strcmp(adr[n].c_str(), offsField)){
                x = n ;
                break;
            }
        }
        if(x==NULL){
            printf("error: no %s label in this program\n",offsField);
            exit(1);
        } 
        if(!strcmp(opc, "100")){
            x = x-(ind+1) ;
        }
        std::string tmp = std::to_string(x);
        strcpy(offsField, tmp.c_str());
    }
    std::string opcode(opc);
    std::string regA(DecimalToBin(rA,3));
    std::string regB(DecimalToBin(rB,3));
    std::string offsetField(DecimalToBin(offsField,16));
    /*check if offsetField more than 16 bits*/
    if(offsetField.length()>16){
        printf("error: this offsetField too long\n");
        exit(1);
    }
    string fields = "0000000" + opcode + regA + regB + offsetField;
    return BinToDeci(fields);
}
long long int Jtype(char *opc, char *rA, char *rB)
{
    std::string opcode(opc);
    std::string regA(DecimalToBin(rA,3));
    std::string regB(DecimalToBin(rB,3));
    string fields = "0000000" + opcode + regA + regB + "0000000000000000";
    return BinToDeci(fields);
}
long long int Otype(char *opc)
{
    std::string opcode(opc);
    string fields = "0000000" + opcode + "0000000000000000000000";
    return BinToDeci(fields);
}
long long int filltype(char *num,vector<string> adr)
{
    long long int x;
    if(isNumber(num)){
        sscanf(num, "%d", &x);
    }else{
        for (int n = 0; n < adr.size(); n++){
            if(!strcmp(adr[n].c_str(), num))
            x = n ;
        }
        if(x==NULL){
            printf("error: no %s label in this program\n",num);
            exit(1);
        } 
    }
    return x;
}
