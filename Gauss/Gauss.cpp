
#include <iostream>
#include <vector>
using namespace std;
// debug
void ReplaceRows(vector <vector<double>> A, vector <vector<double>> B, int row1, int row2) {
    vector <double> bufA =  A[row1];
    A[row1] = A[row2];
    A[row2] = bufA;

    vector <double> bufB = B[row1];
    B[row1] = B[row2];
    B[row2] = bufB;



}

int main()
{
    // Запись по строкам, чтобы было лечге менять их и вычитать 
    vector <vector <double>> A;
    vector <vector <double>> B;
    vector <vector <double>> C;

    // Считываем из файла


}
