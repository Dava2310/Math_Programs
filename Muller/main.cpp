#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const int MAX_ITER = 100; // Numero maximo de iteraciones
const double TOL = 1; // Tolerancia del error

double evaluacionVariable(double polinomio[], double variable, int n);
vector<double> metodoMuller(double polinomio[], double& x0, double& x1, double& x2, int n);

int main() {

    // Variables de raices
    double x0 = 0, x1 = 0, x2 = 0, x3 = 0;

    // Variables de funcioens
    double fx0 = 0, fx1 = 0 ,fx2 = 0;

    // Condicion de error
    bool condicion = true;

    // Grado del polinomio
    int n;

    cout << "Ingrese el grado del polinomio: ";
    cin >> n;

    // Declaracion del polinomio (vector)
    double polinomio[n + 1]; // N + 1 porque si el grado es 3, puede tener AX3,AX2,AX1,AX0
	
    for (int i = 0; i < n + 1; i++) {

        cout << "Ingrese el elemento de grado " << i << ": ";
        cin >> polinomio[i];

    } // Finalizacion de entrada del polinomio

    int iteraciones = 0;

    // Ingreso de las variables de entrada
    cout << "Ingrese los valores de entrada: " << endl;
    cout << "X0 = "; cin >> x0;
    cout << "X1 = "; cin >> x1;
    cout << "X2 = "; cin >> x2;

    metodoMuller(polinomio, x0, x1, x2, n);
	system("pause");
	return 0;
	
}

double evaluacionVariable(double polinomio[], double variable, int n) {

    double resultado = 0.0;
    for (int i = 0; i < n + 1; i++) {

        resultado += polinomio[i] * pow(variable, i);

    }
    return resultado;

}

vector<double> metodoMuller(double polinomio[], double& x0, double& x1, double& x2, int n) {

    vector<double> resultados;

    double x3 = 0.0;
    double fx0 = 0.0, fx1 = 0.0, fx2 = 0.0;
    double h0 = 0.0, h1 = 0.0, d0 = 0.0, d1 = 0.0;
    double a = 0.0, b = 0.0, c = 0.0;
    double w = 0;

    // Para el paso 6
    double suma = 0.0, resta = 0.0;
    bool positivo = false, negativo = false;

    int iteraciones = 0;
    double error = 100;
    // Ciclo de iteraciones

    // En primera instancia, el error siempre sera mayor
    while (error > TOL) {
        iteraciones++;

        cout << "Inicio de la iteracion #" << iteraciones << endl;

        // Impresion de los parametros de inicio
        cout << "Parametros de inicio de la iteracion: #" << iteraciones << endl;
        cout << "X0 = " << x0 << endl;
        cout << "X1 = " << x1 << endl;
        cout << "X2 = " << x2 << endl;

        positivo = false;
        negativo = false;

        // Evaluacion de variables
        fx0 = evaluacionVariable(polinomio, x0, n);
        fx1 = evaluacionVariable(polinomio, x1, n);
        fx2 = evaluacionVariable(polinomio, x2, n); 

        // Impresion de resultados
        cout << "PASO 1: Evaluacion de X0,X1,X2: " << endl;
        cout << "F(X0) = " << fx0 << endl;
        cout << "F(X1) = " << fx1 << endl;
        cout << "F(X2) = " << fx2 << endl;
        cout << endl;

        // Formulas del paso 2
        h0 = x1 - x0;
        h1 = x2 - x1;
        d0 = (fx1 - fx0) / (x1 - x0);
        d1 = (fx2 - fx1) / (x2 - x1);

        // Impresion de resultados
        cout << "PASO 2: Encontrar H0,H1,D0,D1: " << endl;
        cout << "H0 = " << h0 << endl;
        cout << "H1 = " << h1 << endl;
        cout << "D0 = " << d0 << endl;
        cout << "D1 = " << d1 << endl;
        cout << endl;

        // Calculo de A,B,C
        a = (d1 - d0) / (h1 + h0);
        b = (a * h1) + d1;
        c = fx2;

        // Impresion de resultados
        cout << "PASO 3: Encontrar a,b,c: " << endl;
        cout << "A = " << a << endl;
        cout << "B = " << b << endl;
        cout << "C = " << c << endl;
        cout << endl;
        
        // Calculo del determinante
        if ( (b*b) - (4 * a * c) < 0) {
        	
			cout << "PASO 4: Se ha encontrado en el determinante, un numero imaginario." << endl;
			double determinante = (b*b) - (4 * a * c);
			
			cout << "Determinante antes de cambiar el signo: " << determinante << endl;
			
			determinante *= -1;
			
			cout << "Determinante: " << determinante << endl << endl; 
			
			x3 = sqrt(determinante);
			
			// Impresion de resultados
			cout << "FIN DEL PROCEDIMIENTO. Resultados de las raices: " << endl;
		    cout << "X1 = " << x1 << endl;
		    cout << "X2 = " << x2 << endl;
		    cout << "X3 = " << x3 << "i"<< endl;
            
            return resultados;
        }

        w = sqrt((b*b) - (4 * a * c));

        // Impresion de resultados
        cout << "PASO 4: Calculo del determinante: " << endl;
        cout << "W = " << w << endl;
        cout << endl;
        
        // Paso 5:
        suma = abs(b + w);
        resta = abs(b - w);

        // Impresion de resultados
        cout << "PASO 5: Verificacion del +- del denominador." << endl;
        cout << "Suma = " << suma << endl;
        cout << "Resta = " << resta << endl;

        // Verificacion del signo
        if (suma > resta) {
            positivo = true;
            cout << "Se usara el positivo" << endl;
        } else {
            negativo = true;
            cout << "Se usara el negativo" << endl;
        }
        cout << endl;

        // Paso 6: Calculo de X3
        if (positivo) {
            x3 = x2 + ( (-2*c) / (b + sqrt((b*b) - (4 * a * c))) );

            /*
            double numerador = (-2 * c);
            cout << "Numerador X3 = " << numerador << endl;

            double denominador = b + sqrt((b*b) - (4 * a * c));
            cout << "Denominador X3 = " << denominador << endl;

            x3 = numerador / denominador;
            cout << "X3 sin sumar X2 = " << x3;

            x3 = x3 + x2;
            cout << "X3 final = " << x3 << endl;
            */ 
        } else if (negativo) {
            x3 = x2 + ( (-2*c) / (b - sqrt((b*b) - (4 * a * c))) );
            
            /*
            double numerador = (-2 * c);
            cout << "Numerador X3 = " << numerador << endl;

            double denominador = b - sqrt((b*b) - (4 * a * c));
            cout << "Denominador X3 = " << denominador << endl;

            x3 = numerador / denominador;
            cout << "X3 sin sumar X2 = " << x3;

            x3 = x3 + x2;   
            cout << "X3 final = " << x3 << endl; 
            */
        }
        
        cout << "Paso 6: Calculo de X3." << endl;
        cout << "X3 = " << x3 << endl;

        // Paso 7: Calculo del error
        //error = abs((x3 - x2) / x3) * 100;
		error = ((x3 - x2) / x3) * 100;
		if (error < 0) {
			error *= -1;
		}
	
        // Impresion del resultado
        cout << "PASO 7: Calculo del Error Estimado o Aproximado." << endl;
        cout << "Ea = " << error << endl << endl; 

        // Verificacion del error
        if (error > TOL) {

            x0 = x1;
            x1 = x2;
            x2 = x3;

        }
    } // Cierre del procedimiento

    // Impresion de resultados
    cout << "FIN DEL PROCEDIMIENTO. Resultados de las raices: " << endl;
    cout << "X1 = " << x1 << endl;
    cout << "X2 = " << x2 << endl;
    cout << "X3 = " << x3 << endl;

    return resultados;
}
