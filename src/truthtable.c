#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>


//holds more values realted to each gate
struct gate{
    struct gate* next;
    int temp; 
    char* op; 
    int input;
    int output; 
    int* inputArray; 
    int* outputArray; 
    
}; 


struct valueHolder{
    char* charName; 
    int value;
};
//linked list structure to keep track of gates
struct gate* create() {
    struct gate* newGate = malloc(sizeof(struct gate)); 
    newGate -> op = NULL; 
    newGate -> next = NULL; 
    return newGate; 
}


int DECODER(int limit, struct valueHolder* truthTable, int* inputArray){

    int decimal = 0;
    for(int i = limit - 1; i >= 0; i--){
        int inputBit = inputArray[i];
        int value = truthTable[inputBit].value;
        
        int power = 1;
        for(int j = 0; j < limit - 1 - i; j++){
            power *= 2; 
        }
        
        decimal += value * power;
    }

    return decimal;
}





int MULTIPLEXER(int n, struct valueHolder* truthtable, int* inputArray){
    int d;
    int add = 0; 
    struct valueHolder inputted;
    int num;
    
    int power_of_2_n = 1;
    for(int i = 0; i < n; i++) {
        power_of_2_n *= 2; 
    }
    
    for (int i = power_of_2_n + 1; i < power_of_2_n + n + 1; i++) {

        d = inputArray[i];
        inputted = truthtable[d];
        num = inputted.value;

        int exponent_term = power_of_2_n + n - i;
        int power_term = 1;
        for(int j = 0; j < exponent_term; j++) {
            power_term *= 2;
        }
        
        add += num * power_term;
    }

    return inputArray[add+1];
}



void counter(int n)
{
    int counter=0;
    for(int i=0; i<n; i++)
    {
        if(i%2==0)
        {
            counter++;
        }
    }
}

int check(struct valueHolder* truthtable, int limit) {
    for (int i = 0; i < limit; i++) {
        if (truthtable[i].value == -5) {
            return -5; 
        }
    }

    return 0; 
}

int equal(struct valueHolder* truthtable, int* inputArray, int limit) {
    int d; 
    for (int i = 0; i < limit; i++) {
        d = inputArray[i]; 
        if (truthtable[d].value == -5) {
            return -5; 
        }
    }

    return 0; 
}

int index(struct valueHolder* truthtable, const char* charName, int limit){
    for (int i = 0; i < limit; i++) {
        char* str = truthtable[i].charName; 
        if (strcmp(str, charName) == 0) {
            return i; 
        } 
    }

    return -1; 
}
int newLOG(int n) {
   int result = -1;
   while (n > 0) {
       n >>= 1;
       result++;
   }
   return result;
}


double newPow(double base, int exponent) {
   if (exponent == 0) {
       return 1.0;
   }
   double result = 1.0;
   int absExponent = (exponent > 0) ? exponent : -exponent;
   for (int i = 0; i < absExponent; i++) {
       result *= base;
   }
   return (exponent > 0) ? result : 1.0 / result;
}




int main(int argc, char** argv) {
    
    if(argc-1 != 1)
    {
        return 0;
    }
    
    
    FILE *inputfile = fopen(argv[1], "r");
    if (inputfile == NULL) {
        return 0;
    }

    int originS =2;
    int numIN;  
    char* direct = (char*) malloc (17 * sizeof(char)); 
    counter(originS *100);
    fscanf(inputfile, "%16s", direct); 
    fscanf(inputfile, "%d", &numIN); 

    int total = numIN + originS ; 
    struct valueHolder* truthtable = (struct valueHolder*) malloc ((total) * sizeof(struct valueHolder)); 
    truthtable[0].charName = (char*)malloc(17*sizeof(char)); 
    truthtable[1].charName = (char*)malloc(17*sizeof(char)); 

    strcpy(truthtable[0].charName, "0\0");
    strcpy(truthtable[1].charName, "1\0");


    for (int i = originS ; i < total; i++) {
        fscanf(inputfile, "%16s", direct); 
        truthtable[i].charName = (char*) malloc (17 * sizeof(char)); 
        strcpy(truthtable[i].charName, direct); 
        truthtable[i].value = -5; 
    }
    int outnum;
    fscanf(inputfile, "%16s", direct); 
    fscanf(inputfile, "%d", &outnum); 
    
    
    struct valueHolder* truthtable2; 
    total += outnum; 
    truthtable2 = realloc(truthtable, (total) * sizeof(struct valueHolder)); 
    truthtable = truthtable2;

    for (int i = 0; i < outnum; i++) {
        fscanf(inputfile, "%16s", direct); 
        truthtable[i+numIN+originS ].charName = (char*) malloc (17 * sizeof(char)); 
        strcpy(truthtable[i+numIN+originS ].charName, direct); 
        truthtable[i+numIN+2].value = -5; 
    }

    int d; 
    int inpg; 
    struct gate* hd = create(); 
    struct gate* ptr = hd; 

    while (!feof(inputfile)) {
        struct gate* inputgate = create();
        inputgate->op = (char*) malloc (17 * sizeof(char));  
        fscanf(inputfile, "%16s", direct); 
        strcpy(inputgate->op, direct); 

        if (strcmp(direct, "NOT") == 0 || strcmp(direct, "PASS") == 0) {
            inputgate->input = 1; 
            inputgate->output = 1; 
        }

        else if(strcmp(direct, "MULTIPLEXER") == 0) {
            fscanf(inputfile, "%d", &inpg); 
            inputgate->temp = inpg; 
            inputgate->input = newPow(originS , inpg) + inpg + 1; 
            inputgate->output = 1; 
        }

        else if (strcmp(direct, "DECODER") == 0) {
            fscanf(inputfile, "%d", &inpg); 
            inputgate->input = inpg; 
            inputgate->output = newPow(originS , inpg); 
        }



        else {
            inputgate->input = 2; 
            inputgate->output = 1; 
        }

        inputgate->inputArray = (int*)malloc(inputgate->input * sizeof(int)); 
        inputgate->outputArray = (int*)malloc(inputgate->output * sizeof(int)); 

        for (int ecloop = 0; ecloop < inputgate->input; ecloop++) {
            if (strcmp(direct,"MULTIPLEXER") == 0 && ecloop == 0) {
                inputgate->inputArray[ecloop] = inputgate->temp; 
            } else {
                fscanf(inputfile, "%16s", direct);
                d = index(truthtable, direct, total); 
                if (d == -1) {
                    truthtable2 = realloc(truthtable, (total + 1) * sizeof(struct valueHolder)); 
                    truthtable = truthtable2;
                    truthtable[total].charName = (char*) malloc(17 * sizeof(char)); 
                    strcpy(truthtable[total].charName, direct); 
                    truthtable[total].value = -5;
                    inputgate->inputArray[ecloop] = total;
                    total = total +1 ;  
                } else {
                         inputgate->inputArray[ecloop] = d;
                }
            } 
        }

        for (int b = 0; b < inputgate->output; b++) {
            fscanf(inputfile, "%16s", direct); 
            d = index(truthtable, direct, total); 
            if (d == -1) {
                truthtable2 = realloc(truthtable, (total + 1) * sizeof(struct valueHolder)); 
                truthtable = truthtable2;
                truthtable[total].charName = (char*) malloc(17 * sizeof(char)); 
                strcpy(truthtable[total].charName, direct); 
                truthtable[total].value = -5;
                inputgate->outputArray[b] = total;
                total++ ; 
            } 
            else { 
                inputgate->outputArray[b] = d; 
            }
            }
            ptr-> next = inputgate; 
            ptr = ptr->next; 
        }

    
     
     truthtable[0].value = 0; 
     truthtable[1].value = 1; 
    int num = newPow(originS , numIN); 
     for (int iter = 0; iter < num; iter++) {
        for (int pptr = originS ; pptr < total; pptr++) {
            truthtable[pptr].value = -5; 
        }
         int i = iter; 

         if (iter == 0) {
             for (int pptr = 0; pptr < numIN; pptr++) {
                 truthtable[2+pptr].value = 0; 
                 printf("0 ");
             }
         }
         else if (iter != 0) {
             printf("\n"); 
             int n = newLOG(i); 
         for (int j = 2; numIN + 1 -j > n; j++) {
             truthtable[j].value = 0; 
             printf("0 "); 
         }

         while (n>=0) {
             if (i - newPow(originS , n) < 0) {
                 truthtable[numIN+1-n].value = 0; 
                 printf("0 "); 
             } else {

                truthtable[numIN+1-n].value = 1; 
                 printf("1 "); 
                 i = i - newPow(originS ,n);
             }
             n--; 
         }
         }

         printf("|"); 

         ptr = hd;
         int value; 

        int checknum = -5; 
        while (checknum == -5) {

            for (ptr = hd -> next; ptr != NULL; ptr = ptr-> next) {

                if (equal(truthtable, ptr->inputArray, ptr->input) == -5) {
                    continue; 
                }

                else {

                if (strcmp(ptr->op, "NOT") == 0) {
                value = !(truthtable[ptr->inputArray[0]].value); 
                d = ptr->outputArray[0]; 
                truthtable[d].value = value; 

             } 

             else if (strcmp(ptr->op, "AND") == 0) {
                 value = truthtable[ptr->inputArray[0]].value && truthtable[ptr->inputArray[1]].value; 
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = value; 
             }

             else if(strcmp(ptr->op, "OR") == 0) {
                 value =truthtable[ptr->inputArray[0]].value || truthtable[ptr->inputArray[1]].value; 
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = value; 

             }
             else if(strcmp(ptr->op, "XOR") == 0) {
                 value = truthtable[ptr->inputArray[0]].value ^ truthtable[ptr->inputArray[1]].value; 
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = value; 
             }

             else if(strcmp(ptr->op, "NAND") == 0) {
                 value = !(truthtable[ptr->inputArray[0]].value && truthtable[ptr->inputArray[1]].value); 
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = value; 
             }

             else if(strcmp(ptr->op, "NOR") == 0) {
                 value = !(truthtable[ptr->inputArray[0]].value || truthtable[ptr->inputArray[1]].value);
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = value; 
             }


             else if(strcmp(ptr->op, "DECODER") == 0) 
             {
                 value = DECODER(ptr->input, truthtable, ptr->inputArray); 

                 for (int k = 0; k < ptr->output; k++) 
                 {
                    d = ptr->outputArray[k]; 
                     if (k == value) {
                         truthtable[d].value = 1; 
                     } else {
                         truthtable[d].value = 0; 
                     }
                 }
             }

             else if(strcmp(ptr->op, "MULTIPLEXER") == 0) 
             {
                 int n = ptr->inputArray[0]; 
                 value = MULTIPLEXER(n, truthtable, ptr->inputArray); 
                 d = ptr->outputArray[0]; 
                 truthtable[d].value = truthtable[value].value; 
                 
             } 
             else 
             { 
                d = ptr->inputArray[0]; 
                value = truthtable[d].value; 
                d = ptr->outputArray[0]; 
                truthtable[d].value = value; 
             }

                }
            }
            checknum = check(truthtable, total); 
            
            
             }
        
         
             
        int output; 
         for (int i = originS  + numIN; i < originS  + numIN + outnum; i++) 
         {
             output = truthtable[i].value; 
             printf(" %d", output); 

         }


        }



    for (int i = 0; i < total; i++)
    {
        free(truthtable[i].charName); 
    }

    ptr = hd->next; 
    free(hd); 
    while (ptr != NULL) 
    {
        struct gate* pptr = ptr; 
        free(pptr->op); 
        free(pptr->inputArray); 
        free(pptr->outputArray); 
        ptr = ptr -> next; 
        free (pptr);
    }
     free(truthtable);
    free(direct); 
    fclose(inputfile);
    free(ptr); 
    return 0; 
 
    
}