/* instruction-level simulator */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<iostream>    
#include<array> 
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
void binaryToDecimal(int);
int* decimalToBinary(int);

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

    // // yang mai sed
    // for(int i = 0;i<state.numMemory;i++){

    //     // if(state.mem[state.numMemory]==0){
    //     //     continue;
    //     // }

    //     decimalToBinary(state.mem[i]);

    // }

    //initialize register to 0
    for(int i = 0 ;i<NUMREGS;i++){
        state.reg[i] = 0;
    }

    bool halt = false;
    int pc = 0;
    printState(&state);
    while(halt == false){
        
        //pre-simulation
        int *curr_inst = new int[11];
        curr_inst = decimalToBinary(state.mem[pc]);
        int opcode = curr_inst[23]*100 + curr_inst[22]*10 + curr_inst[21];
        cout << opcode;

        //read and simulate instruction (in-progress)

        //post-simulation 
        halt = true;
        pc++;
    }
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
void binaryToDecimal(int n) {
   int decimalNumber = 0;
   int base = 1;
   int temp = n;
   while (temp) {
      int lastDigit = temp % 10;
      temp = temp/10;
      decimalNumber += lastDigit*base;
      base = base*2;
   }
   cout<<"Decimal form of "<<n<<" is "<<decimalNumber<<endl;;
}

// convert decimal to binary function
int* decimalToBinary(int n){
	int *arr = new int[11];
    int i = 0, num = n;

    //initial all element to zero.
    for(int j = 0;j<32;j++){
        arr[i] = 0;
    }
    
    // Until the value of n becomes 0.
	while(n != 0){
		arr[i] = n % 2;
		i++;
		n = n / 2;
	}
	cout << num << " in Binary is ";

	// Printing the array in Reversed Order.
	for(i = i - 1; i >= 0;i--){
		cout << arr[i];
	}
	cout << endl;
    return arr;
}