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
    public static void main(String args[]){
        
        
        int filas, columnas;
        float[] vector;
        // Entrada de datos
        System.out.println("Defina las dimensiones de la matriz sin tomar en cuenta el extendimiento: ");
        
        System.out.print("Filas: "); 
        filas = entrada.nextInt();
        
        System.out.print("Columnas: ");
        columnas = entrada.nextInt();
        
        // Se pregunta si la matriz es cuadrada
        if(filas != columnas){
            System.out.println("No se puede realizar un proceso de eliminacion gaussiana");
        } else {
            vector = eliminacionGaussiana(filas, columnas + 1);
            System.out.print("Vector Solucion:[");
            for (int i = 0; i < filas; i++){
                if (i == filas - 1){
                    System.out.print(formatoD.format(vector[i]));
                } else {
                    System.out.print(formatoD.format(vector[i]) + ";");
                }
                
            }
            System.out.println("]");
        }
        
        
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
    
    
    static float[] eliminacionGaussiana(int filas, int columnas){
        
        float[] vectorSolucion = new float[filas];
        // Llenando el vector solucion de 0
        for (int i = 0; i < filas; i++){
            vectorSolucion[i] = 0;
        }
        
        
        // Declaracion de la matriz
        // Se agrega una columna mas por el extendimiento
        float[][] matriz = new float[filas][columnas];
        
        // Llenado de la matriz
        System.out.println("Ingrese los datos de la matriz: ");
        for (int i = 0; i < filas; i++){
            for (int j = 0; j < columnas; j++){
                System.out.print("Ingrese el elemento A[" + (i+1) + "][" + (j+1) + "]: ");
                matriz[i][j] = entrada.nextFloat();
            }
        }
        
        impresionMatriz(matriz, filas, columnas);
        float factor = 0;
        float[] vectorAux = new float[columnas];
        
        // ============================ CICLO PRINCIPAL DE LA ELIMINACION GAUSSEANA ==================== ||
        // Notas:
        // 1- Siempre se llega a la penultima fila
        for (int i = 0; i < filas - 1; i++) {
            
            // 1- Comprobar que el elemento A[i][i] != 0
            if (matriz[i][i] == 0) {
                
                int cambio = 0;
                // En caso de ser 0, se requiere hacer un cambio con la filas que estén abajo
                // Recorremos las diferentes filas debajo de esta
                // Empieza el indice J siendo i + 1 porque empieza para la fila de de debajo
                // Para este caso, la i representa la columna y la j la fila
                for (int j = i + 1; cambio == 0 && j < filas; j++){
                    
                    // Si el elemento debajo de esta columna siguiente es diferente de 0
                    if (matriz[j][i] != 0){
                        
                        // Requerimos mandar a hacer un cambio de fila con la fila i y la fila j
                        matriz = cambioFila(filas, columnas, i, j, matriz);
                        System.out.println("Cambio de la fila: " + i + " con la fila: " + j);
                        impresionMatriz(matriz, filas, columnas);
                        cambio = 1;
                        
                    }
                }
                
                // No se pudo continuar
                if (cambio == 0){
                    System.out.println("No existe solucion unica");
                    return vectorSolucion;
                }
            }
            
            
            
            // 2 - Hacer 0 los elementos de la columna de debajo
            // Los elementos de debajo es aumentando la fila pero la columna es la i
            // J empieza desde la siguiente fila, por eso es i + 1 
            for (int j = i + 1; j < filas; j++){
                
                // Hay que hacer 0 el elemento matriz[j][i]
                // Usando para multiplicar el factor, el elemento de la matriz[i][i]
                
                // El factor de multiplicacion sera el elemento que se quiere hacer 0 
                // Dividido por el elemento de la diagonal principal
                // Y multiplicado por -1
                factor = (matriz[j][i] / matriz[i][i]) * (-1);
                System.out.println("Factor de multiplicacion: " + formatoD.format(factor));
                
                // Multiplicamos este factor por todos los elementos de la fila i
                // y los guardamos en el vector auxiliar
                
                for (int z = 0; z < columnas; z++){
                    vectorAux[z] = matriz[i][z] * factor;
                }
                
                // Imprimimos el resultado de este vector aux
                System.out.print("VectorAux = [");
                for (int z = 0; z < columnas; z++){
                    if (z != columnas - 2){
                        System.out.println(vectorAux[z] + ";");
                    } else {
                        System.out.println(vectorAux[z]);
                    }
                }
                System.out.println("]");
                
                // Hacemos la suma del vectorAux con la fila[j]
                // Esos seran los nuevos elementos de la fila J
                for (int z = 0; z < columnas; z++){
                    matriz[j][z] = vectorAux[z] + matriz[j][z];
                }
                
                // Mandamos a imprimir la matriz
                impresionMatriz(matriz, filas, columnas);
            }
            
            
        } // ============ TERMINO DE LA ELIMINACION GAUSSEANA ================ ||
        
        // =============== DESPEJE DE ECUACIONES ============================= ||
        
        // Empezamos para cada posicion del vector solucion
        // De atras hacia adelante
        for (int i = filas - 1; i >= 0; i--){
            
            if (matriz[i][i] == 0){
                System.out.println("No existe solucion unica");
                return vectorSolucion;
            }
            
            // Si el elemento de la matriz[i][i] es negativo, hay que multiplicar toda la fila por -1
            if (matriz[i][i] < 0){
                
                // Recorremos todas las columnas y multiplicamos los valores por -1
                for (int j = 0; j < columnas; j++){
                    matriz[i][j] *= -1;
                }
                
            }
            
            // Si es la ultima fila
            if (i == filas - 1){
                
                // En caso de ser la ultima fila
                // el valor de esta posicion del vector solucion
                // es la division entre el elemento M[i][i+1] / M[i][i]
                vectorSolucion[i] = matriz[i][i+1] / matriz[i][i];
                
            } else {
                
                // La variable de acumulado nos permitira ir sumando los valores
                // de la fila de la ecuacion a la vez que multiplicamos por las variables que conseguimos
                // para por ultimo hacer la division
                float acumulado = 0;
                
                for (int j = i + 1; j < columnas; j++){
                    
                    // Si el valor no es el de la ultima columna
                    // significa que se acumula su valor negativo porque se despeja
                    if (j < columnas - 1){
                        
                        // Para este caso, significa que ademas
                        // Hay que multiplicarle el valor anterior conseguido
                        float x = matriz[i][j] * (-1) * vectorSolucion[i+1];
                        acumulado += matriz[i][j] * (-1) * vectorSolucion[j];
                    }
                    else {
                        // Este es el valor "constante" asi que no hay que cambiarle signo
                        acumulado += matriz[i][j];
                    }
                    //System.out.println("Acumulado: " + acumulado);
                }
                
                // Al acumulado, hay que dividirle el valor de M[i][i]
                acumulado = acumulado / matriz[i][i];
                vectorSolucion[i] = acumulado;
                
            }
        } // ====== CIERRE DE LA SUSTITUCION HACIA ATRAS ============= ||
        return vectorSolucion;
    }
    
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
        
    }
}
