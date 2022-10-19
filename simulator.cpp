/* instruction-level simulator */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <array>
using namespace std;

#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8       /* number of machine registers */
#define MAXLINELENGTH 1000

typedef struct stateStruct
{
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
int binaryToDecimal(int);
int *decimalToBinary(int);
int convertNum(int);

int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if (argc != 2)
    {
        cout << (argc);
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL)
    {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    /* read in the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL;
         state.numMemory++)
    {
        if (sscanf(line, "%d", state.mem + state.numMemory) != 1)
        {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    // initialize register to 0
    for (int i = 0; i < NUMREGS; i++)
    {
        state.reg[i] = 0;
    }

    bool halt = false;
    int count = 0;

    // simulation
    while (!halt && count < 65536)
    {
        //printState(&state);

        // pre-simulation
        int *curr_inst = decimalToBinary(state.mem[state.pc]);
        int opcode = curr_inst[24] * 100 + curr_inst[23] * 10 + curr_inst[22];

        int regA = binaryToDecimal(curr_inst[19] + curr_inst[20] * 10 + curr_inst[21] * 100); // bit 21-19
        int regB = binaryToDecimal(curr_inst[16] + curr_inst[17] * 10 + curr_inst[18] * 100); // bit 18-16
        int offset = convertNum(state.mem[state.pc] & (1 << 16) - 1);

        // read and simulate instruction (in-progress)
        if (opcode == 000)    //add instruction
        { 
            //for test
            //cout << "execute add instruction";
            int dest = binaryToDecimal(curr_inst[0] + curr_inst[1] * 10 + curr_inst[2] * 100); // bit 2-0
            state.reg[dest] = state.reg[regA] + state.reg[regB];
        }
        else if (opcode == 1)   //nand instruction
        { 
            //for test
            //cout << "execute nand instruction";
            int dest = binaryToDecimal(curr_inst[0] + curr_inst[1] * 10 + curr_inst[2] * 100); // bit 2-0
            state.reg[dest] = ~(state.reg[regA] & state.reg[regB]);
        }
        else if (opcode == 10)  //lw instruction
        { 
            //for test
            //cout << "execute lw instruction";
            state.reg[regB] = state.mem[offset + state.reg[regA]];
        }
        else if (opcode == 11)  //sw instruction
        { 
            //for test
            //cout << "execute sw instruction";
            state.mem[offset + state.reg[regA]] = state.reg[regB]; 
        }
        else if (opcode == 100)     //beq instruction
        { 
            //cout <<"execute beq instruction";
            if(state.reg[regA] == state.reg[regB]){
                state.pc = state.pc + offset;
            }
        }
        else if (opcode == 101)     //jalr instruction
        { 
            //for test
            //cout << "execute jalr instruction";
            state.reg[regB]=state.pc+1;
            state.pc=state.reg[regA]-1;
        }
        else if (opcode == 110)     //halt instruction
        { 
            //for test
            //cout << "execute halt instruction";
            halt = true;
        }

        count++;
        state.pc++;
        state.reg[0] = 0;
    }
    printf("machine halted\n");
    printf("total of %d instructions executed\n",count);
    printf("final state of machine:\n");
    printState(&state);

    return (0);
}

void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i = 0; i < statePtr->numMemory; i++)
    {
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");
    for (i = 0; i < NUMREGS; i++)
    {
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}

// convert binary to decimal function
int binaryToDecimal(int n)
{
    int decimalNumber = 0;
    int base = 1;
    int temp = n;
    while (temp)
    {
        int lastDigit = temp % 10;
        temp = temp / 10;
        decimalNumber += lastDigit * base;
        base = base * 2;
    }
    //cout << "Decimal form of " << n << " is " << decimalNumber << endl;
    ;
    return decimalNumber;
}

// convert decimal to binary function
int *decimalToBinary(int n)
{
    int *arr = new int[25];
    int i = 0, num = n;

    // initial all element to zero.
    for (int j = 0; j < 25; j++)
    {
        arr[j] = 0;
    }

    // Until the value of n becomes 0.
    while (n != 0)
    {
        arr[i] = n % 2;
        i++;
        n = n / 2;
    }
    //cout << num << " in Binary is ";

    // Printing the array in Reversed Order.
    // for (int j = i; j >= 0; j--)
    // {
    //     cout << arr[j];
    // }
    // cout << endl;
    return arr;
}

int convertNum(int num)
{

    /* convert a 16-bit number into a 32-bit integer */
    if (num & (1 << 15))
    {
        num -= (1 << 16);
    }

    return (num);
}