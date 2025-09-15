
#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <iomanip>
using namespace std;

class GaussMetod {
private:
    int nCol;
    vector <vector <double>> A;
    vector <double> B;
    vector <vector <double>> C;

public:
    GaussMetod(vector <vector <double>> A, vector <double> B, vector <vector <double>> C, int nCol) {
        this->nCol = nCol;
        this->A = A;
        this->B = B;
        this->C = C;
    }
    void substractCol(int col1, int col2) {
        for (size_t i = 0; i < nCol; i++)
        {
            A[col1][i] = A[col1][i] - A[col2][i];
        }
        B[col1] = B[col1] - B[col2];
    }

    void multCol(int col1, double mult) {
        for (size_t i = 0; i < nCol; i++)
        {
            A[col1][i] = A[col1][i] * mult;
        }
        B[col1] = B[col1] * mult;
    }

    void ReplaceRows(int row1, int row2) {
        vector <double> bufA = A[row1];
        A[row1] = A[row2];
        A[row2] = bufA;

        double bufB = B[row1];
        B[row1] = B[row2];
        B[row2] = bufB;
    }

    // Ставим ведущий элемент на верх
    void prepareMatrix(int cur) {
        // Ищем Max по модулю
        double max = A[cur][cur];
        int num = cur;
        for (size_t i = cur+1; i < nCol; i++)
        {
            if (abs(A[i][cur]) > max)
            {
                max = A[cur][i];
                num = i;
            }
        }

        // Ставим наверх лучшую строку
        if (num != cur )
            ReplaceRows(cur, num);
    }

    void getZerosInColumn(int numCol) {

        double coef;
        vector <double> bufA;
        double bufB;
        for (size_t i = numCol + 1; i < nCol; i++)
        {
            // Вычисляем коэффициент
            coef = A[i][numCol] /  A[numCol][numCol];
            // Сохраняем начальную строку
            bufA = A[numCol];
            bufB = B[numCol];
            // Выполняем преобразования прямо в матрице
            multCol(numCol, coef);
            substractCol(i, numCol);
            // Возвращяем начальную строку
            A[numCol] = bufA;
            B[numCol] = bufB;
            // Устанавливаем главный коэффициент в единицу, понадобиться позже 
            multCol(numCol, 1 / A[numCol][numCol]);
        }
    }

    void getOneCoef(int numCol) {
        multCol(numCol, 1 / A[numCol][numCol]);
    }

    void getZerosInColumnReverse(int numCol) {

        double coef;
        vector <double> bufA;
        double bufB;
        for (int i = numCol-1; i >= 0; i--)
        {
            // Вычисляем коэффициент
            coef = A[i][numCol] / A[numCol][numCol];
            // Сохраняем начальную строку
            bufA = A[numCol];
            bufB = B[numCol];
            // Выполняем преобразования прямо в матрице
            multCol(numCol, coef);
            substractCol(i, numCol);
            // Возвращяем начальную строку
            A[numCol] = bufA;
            B[numCol] = bufB;
        }
    }

    void getTriangle() {
        // Приводим к треуголному виду
        cout << "Начнём приводить к треугольному виду\n";
        cout << "Начальная матрица\n";
        printAB();
        for (size_t i = 0; i < nCol; i++)
        {
            cout << "Столбец номер " << i + 1 << endl;
            prepareMatrix(i);
            cout << "После переставления строк\n";
            printAB();
            getZerosInColumn(i);
            cout << "После приведения столбца\n";
            printAB();
            getOneCoef(i);
            cout << "После приведения к единичным коэффициентам\n";
            printAB();
            cout << endl;
        }  

        cout << "Приведение к треугольному виду и единичный коэффициентам на главной диагонали завершено"  << endl;
    }

    vector <double> reversePath() {
        // Матрицы уже должны быть подготовлены, теперь получаем корни
        vector <double> C;
        double sum;
        double cur;
        for (int i = nCol-1; i >= 0; i--)
        {
            sum = B[i];
            for (int j = nCol-1; j > i; j--)
            {
                sum -= A[i][j] * C[nCol - 1 - j];
            }
            cur = sum / A[i][i];
            C.push_back(cur);
        }

        return C;
    }

    void completeIdentityMatrix() {
        cout << "Начинаем приводить матрицу к единичной\n";
        cout << "Начальная матрица: \n";
        printAB();
        for (int i = nCol - 1; i >= 0; i--)
        {
            
            getZerosInColumnReverse(i);
            cout << "После приведения столбца " << i+1 << endl;
            printAB();
        }
        cout << "Приведение к единичной завершено.\n";
    }

    void getFullAnswer(vector <double> c1, vector <double> c2) {
        // Приводим к треугольному виду
        getTriangle();
        // Обратный ход и получаем ответы
        c1 = reversePath();
        reverse(c1.begin(), c1.end());
        // Завершаем преобразование матрицы к единичной
        completeIdentityMatrix();
        // Получаем ответы из матрицы B
        c2 = B;
        printRez(c1,c2);
       
    }


    void printAB() {
        cout << endl;
        for (size_t i = 0; i < nCol; i++)
        {
            for (size_t j = 0; j < nCol; j++)
            {
                if ((A[i][j] < 0.0005) && (A[i][j] > -0.00005))
                    A[i][j] = 0;
                cout << setw(5) << A[i][j] << " ";
            }
            cout <<"\t|\t";
            cout << B[i] << endl;
        }
        cout << endl;
    }

    void printRez(vector <double> c1, vector <double> c2) {
        cout << "Ответ методом Гаусса: ";
        for (size_t i = 0; i < nCol; i++)
        {
            cout << c1[i] << " ";
        }
        cout << endl;

        cout << "Ответ методом Гаусса - Жордана: ";
        for (size_t i = 0; i < nCol; i++)
        {
            cout << c2[i] << " ";
        }
        cout << endl;
    }

    
};



int main()
{
    // Запись по строкам, чтобы было лечге менять их и вычитать 
    int nCol;
    vector <vector <double>> A;
    vector <double> B;
    vector <vector <double>> C;

    setlocale(LC_ALL, "Rus");

    // Считываем из файла
    ifstream in("Matrix.txt");
    if (in.is_open())
    {
        in >> nCol;

        vector  <double> line;
        double bufNum;
        // Матрица А
        for (size_t i = 0; i < nCol; i++)
        {
            line.clear();
            for (size_t i = 0; i < nCol; i++)
            {
                in >> bufNum;
                line.push_back(bufNum);
            }
            A.push_back(line);
        }

        // Матрица B
        for (size_t i = 0; i < nCol; i++)
        {
            line.clear();
            in >> bufNum;
            B.push_back(bufNum);
        }

        in.close();
    }
    else 
        return -1;

    GaussMetod Meth(A, B, C, nCol);
    vector <double> c1, c2;

    Meth.getFullAnswer(c1, c2);
    int a;






    

    



}
