#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void printMatrix(int** matrix , int m  , int n) {
    cout << "\n   A B C D\n";
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** makeMatrix(int m, int n) {
    int** matrix = new int* [m];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    return matrix;
}

void readMatrix(int** matrix , fstream& myFile , int m , int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            myFile >> matrix[i][j];
        }
    }
}

void printArr(int* arr , int size) {
    cout << "\nA B C D\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int** getNeedMatrix(int** allocMat, int** maxMat, int n, int m){
    int **needMat = makeMatrix(m,n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            needMat[i][j] = maxMat[i][j] - allocMat[i][j];
        }
    }
    return needMat;
}

bool checkSafe(int** allocMat, int** maxMat, int** needMat, int* reqArr, int* availArr, int m, int n){
    int* workArr = availArr;
    int* finishArr = new int[n];
    for (int i =0; i< n; i++){
        finishArr[i] = 0;
    }
    int* safeArr = new int[n];
    bool isFound;
    for (int i = 0; i < n;){
        isFound = false;
        for(int j = 0; j< n; j++){
            if(finishArr[j] == 0){
                for(int p = 0; p<m;p++){
                    if(needMat[j][p] > workArr[p]){
                        break;
                    }
                }
                if ( j == m){
                    for (int k = 0; i < m; i++){
                        workArr[k] = workArr[k] + allocMat[j][k];
                    }
                    safeArr[i++] = j;
                    finishArr[j] = 1;
                    isFound = true;
                    
                }
            }
        }
        if(isFound){
            cout<<"\nSystem is in safe state";
        }
        else{
            cout<<"\nSystem is not in safe state";
        }
    }
    return isFound;
}
int main(int argc, char* argv[]) {
    string filename = argv[1];
    fstream myFile(filename);

    int n = 0, m = 0;
    myFile >> n >> m;
    cout << "\nThere are " << n << " processes in the system.";
    cout << "\nThere are " << m << " resources types.";

    int** allocMat = makeMatrix(m, n);
    readMatrix(allocMat, myFile, m, n);
    cout<<"\nThe Allocation Matrix is:";
    printMatrix(allocMat, m, n);

    int** maxMat = makeMatrix(m, n);
    readMatrix(maxMat, myFile, m, n);
    cout<<"\nThe Maximum Matrix is:";
    printMatrix(maxMat, m, n);

    int** needMat = getNeedMatrix(allocMat, maxMat, n, m);
    cout<<"\nThe Need Matrix is:";
    printMatrix(needMat, m, n);

    int* availArr = new int[m];
    for (int i = 0; i < m; i++) {
        myFile >> availArr[i];
    }

    int* reqArr = new int[m];
    for (int i = 0; i < m; i++) {
        if (i == 0){
            char str[100];
            myFile >> str;
            char *ptr; // declare a ptr pointer  
            ptr = strtok(str, ":");
            while(ptr != NULL){
                // cout<<"\n!!!"<<ptr<<"!!!";
                ptr = strtok(NULL, ":");
            }

        }
        else
            myFile >> reqArr[i];
    }

    cout<<"\nAvailable Vector is:";
    printArr(availArr, m);
    bool safeAns = checkSafe(allocMat, maxMat, needMat, reqArr, availArr, m, n);
    if (safeAns){
        cout<<"\n\nThe request can be granted.\n";
    }
    else{
        cout<<"\n\nThe request can't be granted.\n";
    }
    cout<<"\nRequest Vector is:\n";
    printArr(reqArr,m);

    if (safeAns){
        cout<<"\nThe new available vector is:\n";
        for(int i = 0; i<m;i++){
            availArr[i] = availArr[i] - reqArr[i];
        }
        printArr(availArr,m);
    }
    myFile.close();
	return 0;
}

