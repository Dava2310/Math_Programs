#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// Variables globales
const int MAX_ITER = 100; // Numero maximo de iteraciones

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
vector<double> baistrow(double polinomio[], double r, double s, double Es, int n);
vector<double> nuevoPolinomio(double b[], int n);
void imprimirDouble(double);
void imprimirDouble2(double);
vector<double> solucionDeltas(double c2, double c3, double b1, double c1, double b0);

int main() {
	
	// Variables de entrada
	double r = 0, s = 0, Es = 0;
	int n = 0;
	
	// Ingreso del grado del polinomio
	cout << "Ingrese el grado del polinomio: ";
	cin >> n;
	
	// Declaracion del polinomio
	double polinomio[n + 1];
	
	// Llenado de los datos del polinomio
	
    for (int i = 0; i < n + 1; i++) {

        cout << "Ingrese el elemento de grado " << i << ": ";
        cin >> polinomio[i];

    } // Finalizacion de entrada del polinomio
	
	// Ingreso de las variables de entrada
    cout << "Ingrese los valores de entrada: " << endl;
	cout << "r = "; cin >> r;
	cout << "s = "; cin >> s;
	cout << "Es = "; cin >> Es;
	
	vector<double> resultados = baistrow(polinomio, r, s, Es, n);
	
	system("pause");
	return 0;
}

vector<double> baistrow(double polinomio[], double r, double s, double Es, int n) {
	
	// Parametros de inicio R y S
	double errorR = 100, errorS = 100;

	// Vectores temporales
	vector<double> resultados;
	vector<double> temporal;

	// Arreglos de valores B y N
	double b[n + 1];
	double c[n + 1];

	// Valores Delta para R y S
	double DeltaR = 0.0, DeltaS = 0.0;
	
	bool condicion = false; // Si la condicion de error tolerable es verdadero o falso
	bool terminado = false; // Si el programa esta terminado
	int iteraciones = 0; // Cantidad de iteraciones
	double x = 0.0, x1 = 0.0;

	// Inicializacion de los arrays
	for (int i = 0;i < n + 1; i++) {
		b[i] = 0.0;
		c[i] = 0.0;
	}
	
	while (!terminado) {
		
		
		iteraciones++;
		cout << "\n\n==============Iteracion #" << iteraciones << "===========================" << endl;
		
		// Paso 1:
		condicion = false;
		cout << "PASO 1: El grado" << endl << endl;
		cout << "Grado n = " << n << endl << endl;
		
		// Paso 2 
		cout << "PASO 2: R,S, ES" << endl;
		cout << "R = "; imprimirDouble(r);	
		cout << "S = "; imprimirDouble(s);
		cout << "Es = "; imprimirDouble(Es);
		cout << endl << endl;
		
		// Paso 3
		cout << "PASO 3: Determinar valores de B y C" << endl << endl;
		
		b[n] = polinomio[n];
		b[n - 1] = polinomio[n - 1] + (r * b[n]);
		
		// Resto de los valores de bi
		for (int i = n - 2; i >= 0; i--) {
			
			b[i] = polinomio[i] + (r * b[i + 1]) + (s * b[i + 2]);
			
		}
		
		// Impresion de resultados
		
		cout << "Valores de B: " << endl << endl;
		for (int i = n; i >= 0; i--) {
			cout << "B[" << i << "] = "; 
			imprimirDouble(b[i]);
		}
		cout << endl << endl;
		
		c[n] = b[n];
		c[n - 1] = b[n - 1] + (r * c[n]);
		
		// Resto de los valores de ci
		for (int i = n - 2; i >= 1; i--) {
			
			c[i] = b[i] + (r * c[i + 1]) + (s * c[i + 2]);
			
		} 
		
		// Impresion de resultados
		cout << "Valores de C: " << endl << endl;
		for (int i = n; i >= 1; i--) {
			cout << "C[" << i << "] = "; 
			imprimirDouble(c[i]);
		}
		cout << endl << endl;
		
		// Paso 4 para calculo con computadora: 
		cout << "Paso 4 para el calculo de DeltaR y DeltaS: " << endl << endl;

		// Calculo de Delta R y Delta S
		vector<double> ecuacion = solucionDeltas(c[2], c[3], b[1], c[1], b[0]);
		DeltaR = ecuacion.at(0);
		DeltaS = ecuacion.at(1);
		
		cout << "DeltaR = ";

		imprimirDouble(DeltaR);
		
		cout << "DeltaS = ";
		imprimirDouble(DeltaS);
		
		cout << endl;
		// Paso 5
		
		// Calculo de nueva R y S
		r = r + DeltaR;
		s = s + DeltaS;
		
		// Impresion de resultados
		cout << "Paso 5: Calculo de R y S: " << endl << endl; 
		cout << "Nueva R = "; imprimirDouble(r); 
		cout << "Nueva S = "; imprimirDouble(s);
		
		cout << endl;

		// Paso 6
		errorR = (DeltaR / r) * 100;
		if (errorR < 0) {
			errorR *= -1;
		}
		
		errorS = (DeltaS / s) * 100;
		if (errorS < 0) {
			errorS *= -1;
		}
		
		// Impresion de resultados:
		cout << "Paso 6: Calculo de los errores." << endl;
		cout << "Error de R = "; imprimirDouble(errorR);
		cout << "Error de S = "; imprimirDouble(errorS);
		
		cout << endl;

		// Paso 7
		
		// Si alguno de los errores esta por encima del permitido, se va hacia la primera iteracion
		if (errorR >= Es || errorS >= Es) {
			condicion = false;
		} else {
			condicion = true;
		}
		
		cout << "Paso 7: Verificacion de los errores:" << endl;
		if (!condicion) {
			cout << "Uno de los errores o ambos estan por encima de lo permitido. Se devuelve al paso 1." << endl << endl;
		}
		
		// Resto de los pasos si ninguno de los errores esta por encima
		if (condicion) {
			
			system("pause");
			cout << "=========== Ha pasado del paso 7 ===========" << endl << endl;
			// Paso 8

			// Calculo de las nuevas raices

			// Verificacion si dan imaginarios

			double w = (r*r) + (4*s); 
			
			// Si lo de adentro es negativo
			if (w < 0 ){
				
				cout << "FIN DEL PROGRAMA, SE ENCONTRARON IMAGINARIOS" << endl;

				w *= -1;
				
				// Impresion de resultados reales
				for (int i = 0; i < resultados.size(); i++) {

					cout << "Raiz #" << i << " = " << resultados.at(i) << endl;

				}

				// Impresion de resultados imaginarios
				cout << "Primera raiz imaginaria: " << (r / 2) << " + " << sqrt(w) << "i" << endl; 
				cout << "Segunda raiz imaginaria: " << (r / 2) << " - " << sqrt(w) << "i" << endl;

				// Se le bajan 2 grados al polinomio primero
				//polinomio = nuevoPolinomio(b, polinomio, n);
				temporal = nuevoPolinomio(b, n);

				cout << "================ Polinomio Resultante:=============" << endl;
				for (int i = 0; i <= n - 2; i++) {
					cout << "i = " << i << endl;
					cout << "Polinomio[i] = " << polinomio[i] << endl;
				}

				return resultados;
			}


			x = (r + sqrt( (r*r) + (4*s) ) ) / 2;
			x1 = (r - sqrt( (r*r) + (4*s) ) ) / 2;

			resultados.push_back(x);
			resultados.push_back(x1);
			
			// Impresion del resultado
			cout << "Paso 8: Calculo des la Raices." << endl << endl;
			cout << "X = "; imprimirDouble(x);

			cout << endl;

			cout << "X1 = "; imprimirDouble(x1);
			cout << endl;
			
			// Paso 9
			/*
				Existen 3 posibilidades:
				1. Queda un polinomio de grado 3 o mas
				2. Queda un polinomio cuadratico
				3. Queda un polinomio de primer grado
				
			*/
			
			// Se le bajan 2 grados al polinomio primero
			//polinomio = nuevoPolinomio(b, polinomio, n);
			temporal = nuevoPolinomio(b, n);

			for (int i = n - 2; i >= 0; i--) {
				
				polinomio[i] = temporal.at(i);
				
			}

			cout << "================ Polinomio Resultante:=============" << endl;
			for (int i = 0; i <= n - 2; i++) {
				cout << "i = " << i << endl;
				cout << "Polinomio[i] = " << polinomio[i] << endl;
			}
			
			n = n - 2;
			
			if (n < 3) {
				
				cout << "Llego a un polinomio de grado 2 o 1" << endl;
				terminado = true;
				
			}
			
		}
		
	}
	cout << "FIN DEL PROGRAMA." << endl;
	for (long long unsigned int i = 0; i < resultados.size(); i++) {
		
		cout << "Raiz #" << i+1 << " = "; 
		imprimirDouble(resultados.at(i)); 
		cout << endl;
		
	}
	cout << endl;
}

vector<double> nuevoPolinomio(double b[], int n) {
	
	cout << "Haciendo nuevo polinomio: " << endl;

	// N = 5, Valores 6
	// N - 2 = 3, Valores 4
	
	vector<double> nuevoPolinomio; // [n - 2 + 1]; 
	
	for (int i = (n-2); i >= 0; i--) {
		
		nuevoPolinomio.push_back(b[n - i]);
		
	}
	return nuevoPolinomio;
}

void imprimirDouble(double resultado) {
	
	printf("%.8f\n", resultado);
	
}

void imprimirDouble2(double resultado) {
	
	printf("%.8f", resultado);
	
}

vector<double> solucionDeltas(double c2, double c3, double b1, double c1, double b0) {

	vector<double> deltas;

	double DeltaR = 0.0, DeltaS = 0.0;

	DeltaR = ((c3 * b0) - (c2 * b1)) / ((c2 * c2) - (c1 * c3));
	DeltaS = ((c1 * b1) - (c2 * b0)) / ((c2 * c2) - (c1 * c3));

	deltas.push_back(DeltaR);
	deltas.push_back(DeltaS);


	return deltas;
}

