#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void interpolacionLineal();
void interpolacionCuadratica();
void interpolacionPolinomial(int);
double evaluacionFuncion(double x);
double diferenciaCuadrados(double[], int);
int main(int argc, char** argv) {
	
	int grado_Interpolacion = 0;
	
	cout << "Ingrese el grado de Interpolacion: ";
	cin >> grado_Interpolacion;
	
	if (grado_Interpolacion == 1) {
		
		interpolacionLineal();
		
	}
	
	if (grado_Interpolacion == 2) {
		
		interpolacionCuadratica();
	}
	
	if (grado_Interpolacion >= 3) {
		
		interpolacionPolinomial(grado_Interpolacion);
	
	}
	
	system("pause");
	return 0;
}

double evaluacionFuncion(double x)
{
	
	double resultado = 0;
	
	// CAMBIAR ESTA FUNCION DEPENDIENDO DEL EJERCICIO
	resultado = log(x);
	// resultado = log10(x);
	return resultado;
		
}


void interpolacionLineal() {

	double x0 = 0.0, x1 = 0.0;
	double fx0 = 0.0, fx1 = 0.0;
	double x = 0.0;
	double resultado = 0.0;
	double valorVerdadero = 0.0;
	
	// Paso 1: Los puntos X0 y X1
	cout << "Paso 1: Definicion de los puntos X0 y X1." << endl << endl;
	cout << "Ingrese X0 = "; cin >> x0;
	cout << "Ingrese X1 = "; cin >> x1;
	cout << endl;
	
	// Paso 2: Fx0 y Fx1
	
	fx0 = evaluacionFuncion(x0);
	fx1 = evaluacionFuncion(x1);
	
	cout << "Paso 2: Evaluacion de X0 y X1 en la funcion." << endl << endl;
	cout << "F(X0) = " << fx0 << endl;
	cout << "F(X1) = " << fx1 << endl;
	cout << endl;
	
	// Paso 3: Definicion de X y el Intervalo
	cout << "Paso 3: Verificacion del Intervalo de X0 < X < X1." << endl << endl;
	cout << "Ingrese X = "; cin >> x;
	cout << endl;
	
	// Proceso de verificacion
	if (!(x > x0 && x < x1)){
		
		cout << "La condicion X0 < X < X1 no se cumple" << endl << endl;
		return;
	}
	
	// Paso 4: Calculo de F1(x)
	resultado = fx0 + (( (fx1 - fx0) / (x1 - x0) ) * (x - x0));
	
	cout << "================== IMPRESION DE RESULTADO ===============" << endl << endl;
	cout << "F1(" << x << ") = " << resultado << endl;
	
	cout << "\n================== CALCULO DEL ERROR ===============" << endl << endl; 
	cout << "Ingrese el valor verdadero: "; cin >> valorVerdadero;
	cout << "Valor del Error: " << (abs(valorVerdadero - resultado) * 100) << "%" << endl << endl;
}

void interpolacionCuadratica() {
	
	double x0 = 0.0, x1 = 0.0, x2 = 0.0;
	double fx0 = 0.0, fx1 = 0.0, fx2 = 0.0;
	double x = 0.0;
	double resultado = 0.0;
	double valorVerdadero = 0.0;
	double b0 = 0.0, b1 = 0.0, b2 = 0.0;
	
	
	// Paso 1: Los puntos X0 y X1
	cout << "Paso 1: Definicion de los puntos X0, X1, X2." << endl << endl;
	cout << "Ingrese X0 = "; cin >> x0;
	cout << "Ingrese X1 = "; cin >> x1;
	cout << "Ingrese X2 = "; cin >> x2;
	cout << endl;
	
	// Paso 2: Fx0 y Fx1
	
	fx0 = evaluacionFuncion(x0);
	fx1 = evaluacionFuncion(x1);
	fx2 = evaluacionFuncion(x2);
	
	cout << "Paso 2: Evaluacion de X0 y X1 en la funcion." << endl << endl;
	cout << "F(X0) = " << fx0 << endl;
	cout << "F(X1) = " << fx1 << endl;
	cout << "F(X2) = " << fx2 << endl;
	cout << endl;
	
	// Paso 3 y 4: Definicion de X y el Intervalo
	cout << "Paso 3 y 4: Definicion de X y Verificacion del Intervalo de X0 < X < X2 && X Distinto de X1." << endl << endl;
	cout << "Ingrese X = "; cin >> x;
	cout << endl;
	
	// Proceso de verificacion
	if (!( (x > x0 && x < x2) && (x != x1) ) ){
	
		cout << "La condicion X0 < X < X2 y/o X Diferente de X1 no se cumple" << endl << endl;
		return;
	}
	
	// Paso 5: Calculo de B0
	
	b0 = fx0;
	
	cout << "Paso 5: Calculo de B0." << endl;	
	cout << "B0 = " << b0 << endl << endl;
	
	// Paso 6: Calculo de b1
	
	b1 = ( (fx1 - fx0) / (x1 - x0) );
	
	cout << "Paso 6: Calculo de B1." << endl;	
	cout << "B1 = " << b1 << endl << endl;
	
	// Paso 7: Calculo de B2
	
	b2 = ( ( (fx2 - fx1) / (x2 - x1)  ) -  b1 ) / (x2 - x1);
	
	cout << "Paso 7: Calculo de B2." << endl;	
	cout << "B2 = " << b2 << endl << endl;
	
	// Paso 8: Imprimir la ecuacion
	cout << b0 << " + " << b1 << "(X - " << x0 << ") + " << b2 << "(X - " << x0 << ")(X - " << x1 << ")" << endl << endl; 
	
	// Paso 9: Calculo del Resultado
	
	resultado = b0 + (  b1 * (x - x0) ) + ( b2 * (x - x0) * (x - x1) );
	
	cout << "================== IMPRESION DE RESULTADO ===============" << endl << endl;
	cout << "F2(" << x << ") = " << resultado << endl;
	
	cout << "\n================== CALCULO DEL ERROR ===============" << endl << endl; 
	cout << "Ingrese el valor verdadero: "; cin >> valorVerdadero;
	cout << "Valor del Error: " << (abs(valorVerdadero - resultado) * 100) << "%" << endl << endl;
	
}

void interpolacionPolinomial(int grado) {
	
	double array_puntos[grado + 1];
	double array_F_puntos[grado + 1];
	double b[grado + 1];
	double x;
	double xMin = 0.0, xMax = 0.0;
	int n = grado + 1;
	double resultado = 0.0;
	double valorVerdadero = 0.0;
	
	// Llenado del arreglo
	for (int i = 0; i < n; i++) {
		
		cout << "Ingrese X[" << i << "] = ";
		cin >> array_puntos[i];
		cout << endl;
		
	}
	
	// Evaluacion de la funcion en cada punto
	for (int i = 0; i < n; i++) {
		
		array_F_puntos[i] = evaluacionFuncion(array_puntos[i]);
		cout << "F(X" << i << ") = " << array_F_puntos[i] << endl;
		cout << endl;
	}
	
	// Ingreso de X
	cout << "Ingrese el valor de X = ";
	cin >> x;
	cout << endl;
	
	// Hallar XMIN y XMAX
	xMin = array_puntos[0];
	xMax = array_puntos[0];
	
	// Hallar xMin
	for (int i = 1; i < n; i++) {
		
		if (array_puntos[i] < xMin) {
			
			xMin = array_puntos[i];
			
		}
		
	}
	
	// Hallar xMax
	for (int i = 1; i < n; i++) {
		
		if (array_puntos[i] > xMax) {
			
			xMax = array_puntos[i];
			
		}
		
	}
	
	cout << "Xmin = " << xMin << endl;
	cout << "Xmax = " << xMax << endl;
	
	// Verificacion I Parte
	if (!(x > xMin && x < xMax)) {
		
		cout << "X no esta dentro del rango de: Xmin < X < Xmax" << endl;
		return;
		
	}
	
	// Verificacion II parte
	for (int i = 0; i < n; i++) {
		
		if (!(x != array_puntos[i])) {
			
			cout << "X no es diferente de X[" << i << "]" << endl;
			return;
		}
		
	}
	
	// Impresion del polinomio
	for (int i = 0; i < n; i++) {
		
		if (i >= 1){
			
			cout << "b" << i;
			for (int j = 0; j < i; j++) {
				
				cout << "(X - X" << j << ")";
				
			}
			if (i != n - 1) {
				cout << "+";
			}
			
			
		} else {
			
			cout << "b0 + ";
			
		}
		
	}
	cout << endl;
	
	// Calculo de B0 
	b[0] = array_F_puntos[0];
	
	cout << "B0 = " << b[0] << endl;
	
	double array[2];
	array[0] = array_puntos[1];
	array[1] = array_puntos[0];
	
	// Calculo de b1
	b[1] = diferenciaCuadrados(array, 2);
	cout << "B1 = " << b[1] << endl;
	
	double array2[3];
	array2[0] = array_puntos[2];
	array2[1] = array_puntos[1];
	array2[2] = array_puntos[0];
	
	// Calculo de B2
	b[2] = diferenciaCuadrados(array2, 3);
	cout << "B2 = " << b[2] << endl;
	
	// Calculo de los bn
	for (int i = 3; i < n; i++) {
		
		// B3 tiene 4 elementos
		double arrayTemp[i + 1];
		
		for (int j = 0; j < i + 1; j++) {
			
			arrayTemp[j] = array_puntos[i - j];
			
		}
		
		b[i] = diferenciaCuadrados(arrayTemp, i + 1);
		cout << "B" << i << "= " << b[i] << endl;
	
	}
	
	double resultadoTemp = 0.0;
	double valorAMultiplicar = 0.0;
	for (int i = 0; i < n; i++) {
		
		cout << "I = " << i << endl; 

		if (i != 0) {
			
			resultadoTemp = 1;
			resultadoTemp *= b[i];

			// cout << "Resultado Temp 1 (solo el valor de la b) = " << resultadoTemp << endl;

			for (int j = i; j > 0; j--) {
				
				valorAMultiplicar = (x - array_puntos[j - 1]);
				// cout << "Valor A Multiplicar: " << valorAMultiplicar << endl;
				resultadoTemp *= valorAMultiplicar;
				// cout << "El resultado temp 1 multiplicado por eso: " << resultadoTemp << endl;
			}
			
			// cout << "Resultado Temp 2 Resumen (multiplicado con las X) = " << resultadoTemp << endl;

			resultado += resultadoTemp;
			// cout << "Agregando eso al resultado: " << resultado << endl;
			
		} else {
			
			resultado += b[i];
			
		}

		// cout << "Resultado actual: " << resultado << endl;
		
	}
	
	cout << "================== IMPRESION DE RESULTADO ===============" << endl << endl;
	cout << "F3(" << x << ") = " << resultado << endl;

	cout << "\n================== CALCULO DEL ERROR ===============" << endl << endl; 
	cout << "Ingrese el valor verdadero: "; cin >> valorVerdadero;
	cout << "Valor del Error: " << (abs(valorVerdadero - resultado) * 100) << "%" << endl << endl;
}

double diferenciaCuadrados(double x[], int n) {
	
	double resultado = 0.0;
	if (n == 2){
		
		resultado = (evaluacionFuncion(x[0]) - evaluacionFuncion(x[1])) / (x[0] - x[1]);
		return resultado;
	}
	
	double x2_1[n - 1];
	
	for (int i = 0; i < n - 1; i++) {
		
		x2_1[i] = x[i];
		
	}
	
	double x2_2[n - 1];
	
	for (int i = 1, pos = 0; i < n; i++) {
		
		x2_2[pos] = x[i];
		pos++;
	}
	
	resultado = diferenciaCuadrados(x2_1, n - 1) - diferenciaCuadrados(x2_2, n - 1);
	resultado /= x[0] - x[n - 1];
	return resultado;
}
