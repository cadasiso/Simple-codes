//Calculates a matrix determinant by Chio's Pivotal Condensation
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
    
    srand(time(NULL));

    int dimension, option;
    int boundary=0; //Controls de level of condensation we're in
    
    do{
        printf("Insert a natural number for the matrix order:\n");
        scanf("%d", &dimension);
    } while (dimension<1); //I think a do/while here is cleaner than a for
    
    float matrix[dimension][dimension];
    float indexFixer; //Easier than dividing the entire row by the index before starting the condensation
    float determinantModifier=1; //Stores the indexFixer adjustments and line swaps values
    
    printf("Insert 1 if you want to write each matrix value, insert anything else for a random one\n");
    scanf("%d", &option);
    if (option==1){
    for (int i=0; i<dimension; i++){
        for (int j=0; j<dimension; j++){
            printf("Insert the integer value of A[%d][%d]:\n", i+1, j+1);
            scanf("%f", &matrix[i][j]);
        }
    }
    } else if(option!=1){
        int randomValue;
        for (int i=0; i<dimension; i++){
            for (int j=0; j<dimension; j++){
                randomValue=rand()%199-99; //Generates integers from -99 to 99
                matrix[i][j]=(float)randomValue;
            }
        }
    }

    printf("Input matrix:\n");
    for (int i=0; i<dimension; i++){
        for (int j=0; j<dimension; j++){
            printf("%3.0lf ", matrix[i][j]);
        }
        printf("\n");
    }

    for (int r=0; r<dimension-1; r++){ //Stops when the matrix becomes a 1x1
        
        if (matrix[boundary][boundary]==0){ //If the index is 0,so that there are no 0/x for x!=0 cases, searches for a non-zero potential index in lower rows
            int nuleIndexCandidate=1;
            for (int i=boundary+1; i<dimension; i++){ 
                if (matrix[i][boundary]!=0){ //Swaps the row containing the suitable candidate for index with the one with the 0
                    for (int j=boundary; j<dimension; j++){
                        float rowStorage=matrix[boundary][j];
                        matrix[boundary][j]=matrix[i][j];
                        matrix[i][j]=rowStorage;
                    }
                    determinantModifier*=-1; //Row swap
                    break;
                } else {
                    nuleIndexCandidate++; //Counts the number of 0s in the boundary column
                }
            }
            if (nuleIndexCandidate==dimension-boundary){ //Since we're not creating new matrixes for each condensation, we have to count for the reduced number of rows of the condensated matrix we're currently leading with
                printf("Nule row encountered during reduction process!\nThe determinant is 0\n");
                return 0;
            }
        }

        indexFixer=1/matrix[boundary][boundary]; 
        determinantModifier*=matrix[boundary][boundary]; //If the index is 4, we multiply it by its inverse, 1/4, and do the opposite operation externally, that is, multiply by the very index value
        for (int i=boundary+1; i<dimension; i++){
            for (int j=boundary+1; j<dimension; j++){
                matrix[i][j]-=(matrix[i][boundary]*matrix[boundary][j]*indexFixer);
            }
        }
        boundary++;
    }

    float determinant=determinantModifier*matrix[dimension-1][dimension-1];
    printf("The matrix determinant is: %.4f\n", determinant);
    printf("End of Program");
    return 0;
}