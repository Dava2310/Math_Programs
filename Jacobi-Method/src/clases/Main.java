/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package clases;

import java.text.DecimalFormat;
import java.util.Scanner;

/**
 *
 * @author Daniel Vetencourt
 */
public class Main {
    static Scanner entrada = new Scanner(System.in);
    static DecimalFormat formatoD = new DecimalFormat("###0.00000000");
    
    // Metodo main
    public static void main(String args[]){
        
        int filas, columnas;
        float[] vectorSolucion;
        
        System.out.println("Bienvenido al programa Gauss-Jacobi");
        System.out.println("Ingrese las dimensiones de la matriz extendida.");
        
        System.out.print("Filas: ");
        filas = entrada.nextInt();
        
        System.out.print("Columnas: ");
        columnas = entrada.nextInt();
        
        // Verificacion de las dimensiones de la matriz
        if (filas == (columnas - 1)){
            
            float[][] matriz = ingresoMatriz(filas, columnas);
            System.out.print("Ingrese la cantidad de error: ");
            float error = entrada.nextFloat();
            System.out.println("");
            
            // Se puede realizar el proceso de Gauss-Seidel
            
            vectorSolucion = gaussSeidel(matriz, filas, columnas, error);
            System.out.println("");
            System.out.print("Vector Solucion Definitivo:[");
            for (int i = 0; i < filas; i++){
                if (i == filas - 1){
                    System.out.print(formatoD.format(vectorSolucion[i]));
                } else {
                    System.out.print(formatoD.format(vectorSolucion[i]) + ";     ");
                }
                
            }
            System.out.println("]");
            
        } else {
            System.out.println("No se puede trabajar con esta matriz");
        }
        
    }
    
    // Pedida de datos de una matriz
    static float[][] ingresoMatriz(int filas, int columnas){
        
        float matriz[][] = new float[filas][columnas];
        
        // Llenado de datos por entrada de usuario
        for (int i = 0; i < filas; i++){
            
            for (int j = 0; j < columnas; j++){
                
                System.out.print("Ingrese el elemento a[" + (i+1) + "][" + (j+1) + "] = ");
                matriz[i][j] = entrada.nextFloat();
            }
            
        }
        
        
        return matriz;
    }
     
    // Impresion de una matriz
    static void impresionMatriz(float[][] matriz, int filas, int columnas){
        
        System.out.println("");
        for (int i = 0; i < filas; i++){
            System.out.print("[");
            for (int j = 0; j < columnas; j++) {
                
                if (matriz[i][j] == 0){
                    System.out.print("0,00000000" + "      ");
                } else {
                    if (j != columnas - 1){
                        System.out.print(formatoD.format(matriz[i][j]) + "      ");
                    } else {
                        System.out.print("|   " + formatoD.format(matriz[i][j]));
                    }
                }
            }
            System.out.println("]");
        }
        System.out.println("");
    }
    
    static float[] gaussSeidel(float[][] matriz, int filas, int columnas, float error){
        
        float[] vectorSolucion = new float[filas];
        float[] vectorSolucionAnterior = new float[filas];
        // Para las primeras iteraciones, el valor de las variables son 0
        // Por tanto, se llenara el vector solucion de 0
        
        for (int i = 0; i < filas; i++){
            vectorSolucion[i] = 0;
            vectorSolucionAnterior[i] = 0;
        }
        
        // ============= HACER LA MATRIZ DOMINANTE ==================
        
        System.out.println("Matriz sin revision dominante: ");
        impresionMatriz(matriz, filas, columnas);
        
        matriz = matrizDominante(matriz, filas, columnas);
        
        System.out.println("Matriz dominante: ");
        impresionMatriz(matriz, filas, columnas);
        
        // ============ PROCESO GAUSS SEIDEL ========================
        // El proceso siguiente se hara dependiendo de la cantidad de iteraciones
        int n = 0;
        boolean condicion = false;
        do{
            n++;
            // Para cada ecuacion
            for (int i = 0; i < filas; i++){
                
                float acumulado = 0;
                for (int j = 0; j < columnas; j++){
                    
                    // Para el elemento solucion Xi
                    // No se puede tomar la matriz con la columna i
                    
                    if (j != i){
                        
                        if (j < columnas -1 ){
                            acumulado += matriz[i][j] * (-1) * vectorSolucionAnterior[j];
                        } else {
                            acumulado += matriz[i][j];
                        }
                    }
                    
                }
                
                acumulado = acumulado / matriz[i][i];
                vectorSolucion[i] = acumulado;
            }
            
            // Escribir el valor de las variables
            
            System.out.println("Vector Solucion en la Iteracion: " + n);
            
            System.out.print("[");
            for (int A = 0; A < filas; A++){
                
                if (A == filas - 1){
                    System.out.print(formatoD.format(vectorSolucion[A]));
                } else {
                    System.out.print(formatoD.format(vectorSolucion[A]) + ";     ");
                }
                
            }
            System.out.println("]\n");
            
            // Colocar ahora en el vector solucion anterior, el resultado de esta iteracion
            for (int Z = 0; Z < filas; Z++)
            {
                vectorSolucionAnterior[Z] = vectorSolucion[Z];
            }
            
            // Verificacion de salida
            condicion = verificacionSalida(vectorSolucion, error, filas, columnas, matriz);
            
        }while(!condicion);
        
        return vectorSolucion;
        
    }
    
    // Verificacion de la condicion de salida
    static boolean verificacionSalida(float[] vectorActual, float error, int filas, int columnas, float[][] matriz){
        
        for (int i = 0; i < filas; i++)
        {
            float acumulado = 0;
            for (int j = 0; j < columnas - 1; j++) 
            {
                acumulado += matriz[i][j] * vectorActual[j];
            }
            
            if ( Math.abs(acumulado - matriz[i][columnas - 1])> error)
            {
                return false;
            }
        }
        
        return true;
    }
    
    static float[][] matrizDominante(float[][] matriz, int filas, int columnas){
        
        for (int Z = 0; Z < filas -1; Z++){
           
            int cambio = 1;
            while (cambio != 0){
                
                cambio = 0;
                for (int i = Z; i < filas - 1; i++){
                    
                    // Si el elemento de la fila siguiente es mayor al actual
                    if (Math.abs(matriz[i][Z]) < Math.abs(matriz[i+1][Z])){
                        
                        // Se tiene que hacer un cambio con ambas filas
                        System.out.println("Cambio de la Fila: " + (i) + " con la Fila: " + (i+1));
                        matriz = cambioFila(filas, columnas, i, i+1, matriz);
                        cambio = 1;
                        impresionMatriz(matriz, filas, columnas);
                    }
                    
                }
                
            }
            
            
        }
        
        return matriz;
    }
    
    static float[][] cambioFila(int filas, int columnas, int filaA, int filaB, float[][] matriz){
        
        float[] vectorAux = new float[columnas];
        
        // Ingresar la filaA en el vectorAux
        for (int j = 0; j < columnas; j++){
            
            vectorAux[j] = matriz[filaA][j];
            
        }
        
        // Ingresar la filaB en la filaA
        for (int j = 0; j < columnas; j++){
            
            matriz[filaA][j] = matriz[filaB][j];
            
        }
        
        // Ingresar en la filaB, el vector Aux
        for (int j = 0; j < columnas; j++){
            
            matriz[filaB][j] = vectorAux[j];
            
        }
        
        return matriz;
    }
    
}