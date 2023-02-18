#include <iostream>
#include <conio.h>
using namespace std;

// Declaracion de prototipos de procedimientos y funciones
void mostrarMatriz(float **matriz, int rows, int col);
float *gauusJordan(float **matriz, int rows, int col);
float **cambioFila(float **matriz, int rows, int col, int A, int B);
void mostrarVector(float vector[], int col);

int main()
{
    // Filas y columnas de la matriz
    int rows, col;

    cout << "Bienvenido al programa de GAUSS-JORDAN" << endl;
    cout << "Ingrese las dimensiones de la matriz extendida: " << endl;

    cout << "Filas: ";
    cin >> rows;

    cout << "Columnas: ";
    cin >> col;

    // Definicion de la matriz
    float **matriz;
    matriz = new float *[rows];

    for (int i = 0; i < rows; i++){
        matriz[i] = new float[col];
    }

    // Definicion del vector resultante
    float *solucion;

    // Llenado de los datos de la matriz
    cout << "Ingrese en orden de las variables respectivas, los coeficientes de la matriz extendida." << endl;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < col; j++)
        {
            // Ingreso de datos
            cout << "Matriz (" << i << "," << j << ") = ";
            cin >> matriz[i][j];
        }
    }

    // Impresion de la matriz por primera vez
    mostrarMatriz(matriz, rows, col);
    
    // Ingreso de la matriz en el proceso de Gauss Jordan
    solucion = gauusJordan(matriz, rows, col);

    // Escribir la solucion
    cout << "Vector Solucion: [";
    for (int i = 0; i < rows; i++)
    {
        if (i != rows - 1)
        {
            printf("%-12.8f;", solucion[i]);
        } 
        else {
            printf("%-12.8f]\n", solucion[i]);
        }
        
    }
	
	getch();
    return 0;
}

// Procedimiento para imprimir matrices
void mostrarMatriz(float **matriz, int rows, int col)
{
    for (int i = 0; i < rows; i++){
        printf("[");
        for (int j  = 0; j < col; j++)
        {
            if (j != col - 1)
            {
                printf("%-12.8f     ", matriz[i][j]);
            }
            else 
            {
                printf("|     %-12.8f     ", matriz[i][j]);
            }
        }
        printf("]\n");
    }
	cout << endl << endl;
}

void mostrarVector(float vector[], int col)
{
    printf("Vector Auxiliar = [");
    for (int i = 0; i < col; i++)
    {
        if (i != col - 1)
        {
            printf("%12.8f;", vector[i]);
        }
        else 
        {
            printf("%12.8f", vector[i]);
        }
    }
    printf("]\n");
    cout << endl << endl;
}

float *gauusJordan(float **matriz, int rows, int col)
{
    // Vector solucion
    float *vector = new float[rows];

    // Vector auxiliar
    float auxiliar[col];

    float factor = 0;
    for (int i = 0; i < rows; i++)
    {   
        //cout << "Hola" << endl;
        vector[i] = 0;
    }

    // Inicio del proceso de Gauus Jordan

    // ============ HACER 0s la Triangular Inferior ================= |
    for (int i = 0; i < rows - 1; i++)
    {

        // Comprobar que el elemento a[i][i] sea diferente de 0
        if (matriz[i][i] == 0)
        {
            int cambio = 0;
            // En caso de ser 0, se requiere hacer un cambio con la filas que estén abajo
            // Recorremos las diferentes filas debajo de esta
            // Empieza el indice J siendo i + 1 porque empieza para la fila de de debajo
            // Para este caso, la i representa la columna y la j la fila

            for (int j = i + 1; cambio == 0 && j < rows; j++)
            {
                // Si el elemento debajo de esta misma fila es diferente de 0
                if (matriz[j][i] != 0)
                {
                    // Requerimos mandar a hacer un cambio de fila con la fila i y la fila j
                    matriz = cambioFila(matriz, rows, col, i, j);
                    cout << "Intercambio de las filas: " << i << " <-> " << j << endl;
                    mostrarMatriz(matriz, rows, col);
                    cambio++;
                } 

            }

            // Si despues de esto, no se hizo ningun cambio
            // basicamente no hay solucion para el problema
            if (cambio == 0)
            {
                cout << "No existe solucion unica." << endl;
                return vector;
            }
        
        }

        // Debemos hacer 0 los elementos de la columna de debajo
        // Los elementos de debajo es aumentando la fila pero la columna es la misma i
        // J empieza desde la siguiente fila, por eso es i + 1

        for (int j = i+1; j < rows; j++)
        {
            // Hay que hacer 0 el elemento matriz[j][i]
            // Usando para multiplicar el factor, el elemento de la matriz[i][i]
                
            // El factor de multiplicacion sera el elemento que se quiere hacer 0 
            // Dividido por el elemento de la diagonal principal
            // Y multiplicado por -1

            factor = (matriz[j][i] / matriz[i][i]) * (-1);
            printf("Factor de multiplicacion: %.8f\n", factor);

            // Multiplicamos este factor por todos los elementos de la fila i
            // y los guardamos en el vector auxiliar

            for (int z = 0; z < col; z++)
            {
                auxiliar[z] = matriz[i][z] * factor;
            }

            // Mandamos a imprimir este vector auxiliar
            mostrarVector(auxiliar, col);

            // Hacemos la suma del vector auxiliar con la fila[j]
            // Esos seran los nuevos elementos de la fila J
            for (int z = 0; z < col; z++)
            {
                matriz[j][z] = auxiliar[z] + matriz[j][z];
            }

            // Mandamos a imprimir la matriz actual
            mostrarMatriz(matriz, rows, col);
        }

    } // ======== TERMINO DE HACER 0 LA TRIANGULAR INFERIOR =============

    // Ahora hay que hacer 0s la triangular inferior

    for (int i = col - 2; i >= 1; i--)
    {
        // Comprobar que el elemento a[i][i] != 0

        // Ya para este momento, no es posible hacer cambios de fila
        // asi que si alguna vez esto da verdadero
        // no se puede seguir con el proceso
        if (matriz[i][i] == 0)
        {
            return vector;
        }

        // Una vez verificado esto, se usa la misma logica del factor
        // Hay que hacer 0s los elemento de las columnas de arriba
        // Los elementos de arriba son la columna i, y la fila va disminuyendo
        // La primera fila por encima es i - 1

        for (int j = i - 1; j >= 0; j--)
        {
            factor = (matriz[j][i] / matriz[i][i]) * (-1);
            printf("Factor de multiplicacion: %.8f\n", factor);

            for (int z = 0; z < col; z++)
            {
                auxiliar[z] = matriz[i][z] * factor;
            }

            // Mandamos a imprimir este vector auxiliar
            mostrarVector(auxiliar, col);

            // Hacemos la suma del vector auxiliar con la fila[j]
            // Esos seran los nuevos elementos de la fila J
            for (int z = 0; z < col; z++)
            {
                matriz[j][z] = auxiliar[z] + matriz[j][z];
            }

            // Mandamos a imprimir la matriz actual
            mostrarMatriz(matriz, rows, col);
        }

    } // ======== TERMINO DE HACER 0 LA TRIANGULAR SUPERIOR =============

    // CALCULO DE LAS SOLUCIONES
    /*
        Para hacer el calculo de las soluciones
        Se necesita hacer lo siguiente:
        1- 
           Dividir los elementos A[i][i] por si mismos
           Asi como tambien, dividir el valor A[i][col-1] (el valor de la columna extendida)
           Por el valor del elemento A[i][i]
        2- Los valores de la columna J = col - 1, yendo desde la fila i = 0 hasta i = row - 1
           Son los que forman el vector solucion
    */

    // 1- Diviendo los valores de la diagonal principal por si mismos
    for (int i = 0; i < rows; i++)
    {

        matriz[i][col - 1] /= matriz[i][i]; 
        matriz[i][i] /= matriz[i][i];
        
    }

    mostrarMatriz(matriz, rows, col);

    // 2- Formando el vector solucion
    for (int i = 0; i < rows; i++)
    {
        vector[i] = matriz[i][col-1];
    }

    return vector;
}

float **cambioFila(float **matriz, int rows, int col, int A, int B)
{
    float vectorAux[col];

    // Ingresar la fila A en el vector Auxiliar
    for (int j = 0; j < col; j++)
    {
        vectorAux[j] = matriz[A][j];
    }

    // Ingresar la fila B en la fila A
    for (int j = 0; j < col; j++)
    {
        matriz[A][j] = matriz[B][j];
    }

    // Ingresar en la fila B, el vector Aux
    for (int j = 0; j < col; j++)
    {
        matriz[B][j] = vectorAux[j];
    }

    return matriz;
}
