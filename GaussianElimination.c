//Limite de terminal para verificar o determinante com folder explorer fechado = 44, aberto = 35
//Limite de terminal p ver matriz reduzida com folder explorer fechado = 25, aberto = 20(recomendado 19)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    //Generates and exhibits the input matrix, 8-38
    int dms;
    do { //I think a do/while here looks cleaner and is simpler to understand
        printf("Enter a valid natural number for the matrix dimension: ");
        scanf("%d", &dms);
    } while (dms<1);
    int op;
    double matrix[dms][dms];
    printf("Choose an option to generate the matrix elements:\n1. Random values from -99 to 99\n2. Manually insert values\n");
    scanf("%d", &op);
    if (op==1){
        srand(time(NULL));
        for (int i=0; i<dms; i++){
            for (int j=0; j<dms; j++){
                matrix[i][j]=(double)(rand()%199-99); //-99 to 99, negatives for 0 to 98, 0 for 99, positives for 100 to 198
            }
        }
    } else {
        for (int i=0; i<dms; i++){
            for (int j=0; j<dms; j++){
                printf("Insert the value for A[%d][%d]: ", i+1, j+1);
                scanf("%lf", &matrix[i][j]);
            }
        }
    }
    printf("Input Matrix:\n");
    for (int i=0; i<dms; i++){
        for (int j=0; j<dms; j++){
            printf("%3.0lf ", matrix[i][j]);
        }
        printf("\n");
    }
    //Gaussian Elimination itself from 40-73
    int nuleClock=0; //Searches for suitable pivot candidate in r-1 rows and r column so that we don't incur in 0/0 or x/0 for x!=0 cases
    double pivot, modExDet=1;
    for (int r=0; r<dms; r++){
        pivot=matrix[r][r];
        nuleClock=0;
        if (pivot==0){
            for (int i=r+1; i<dms; i++){
                if (matrix[i][r]!=0){ //Swap rows when suitable non-zero [r][r] pivot candidate is found
                    for (int j=0; j<dms; j++){
                        double temp=matrix[r][j];
                        matrix[r][j]=matrix[i][j];
                        matrix[i][j]=temp;
                    }
                    modExDet*=-1; //External determinant modifier, inverts its signal when swapping rows
                    pivot=matrix[r][r];
                    break;
                }
            }
            if (pivot==0){
                nuleClock++;
            }
        }
        if (nuleClock==dms-r){ //This -r part is important because if during the reduction we find a nule column >below< the pivot, it also means the determinant is 0
            printf("Nule row encountered\nDeterminant: 0\n");
            return 0;
        }
        //Elimination itself
        for (int i=r+1; i<dms; i++){
            double factor=-matrix[i][r]/pivot;
            for (int j=r; j<dms; j++){
                matrix[i][j]+=factor*matrix[r][j];
            }
        }
    }
    //Exhibits matrix in row echelon form, calculates and exhibits the determinant, 75-89
    printf("Matrix in row echelon form:\n");
    for (int i=0; i<dms; i++){
        for (int j=0; j<dms; j++){
            printf("%6.0lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Keep in mind it only shows the integer part, so if you see, for example, a Det(M)=2 from a reduced 2x2 matrix of main diagonal 4 and 0,\nwhich would naturally be an absurd, you might actually be before 4 and 0.5 or 4.8 and 0,416667 truncated/rounded down pairs\n");
    //Once in the row echelon form, the determinant is the product of the elements of the main diagonal
    double determinant=1;
    for (int i=0; i<dms; i++){
        determinant*=matrix[i][i];
    }
    determinant*=modExDet;
    printf("Det(M)~=%.0lf\nFor gigantic determinants you might not be before a exact answer due to the dozens, hundreds or thousands of carried roundings,\nbut still a extremely precise answer (often in over 10 orders of magnitude, that is, for example, 1.00000000001245... or 0,9999999991457...)\nFor small determinants, though, you can expect the answer to be exact\nBut for really, really big exact determinants of hundreds of digits, then you might not even see all the digits, but still, very accurate first digits\n", determinant);
    return 0;
}