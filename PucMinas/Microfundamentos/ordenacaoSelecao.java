package PucMinas.Microfundamentos;
import java.util.Scanner;

public class ordenacaoSelecao {
    public static void swap(int[] array, int i, int j){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void ordenarSelecao(int[] array, int tam){
        for(int i = 0; i < tam - 1; i++){
            int menor = i;
            for(int j = (i + 1); j < tam; j++){
                if(array[menor] > array[j]){
                    menor = j;
                }
            }
            swap(array, menor, i);
        }
    }

    public static void selecaoDecrescente(int[] array, int tam){
        for(int i = 0; i < tam - 1; i++){
            int menor = i;
            for(int j = (i + 1); j < tam; j++){
                if(array[menor] < array[j]){
                    menor = j;
                }
            }
            swap(array, i, menor);
        }
    }
    
    public static void preencheArray(int[] array, int tam){
        Scanner sc = new Scanner(System.in);
        for(int i = 0; i < tam; i++){
            array[i] = sc.nextInt();
        }
        sc.close();
    }

    public static void imprimeArray(int[] array, int tam){
        for(int i = 0; i < tam; i++){
            System.out.println(array[i]);
        }
    }

    public static void main(String[]args){
        Scanner sc = new Scanner(System.in);
        
        int tamanho = sc.nextInt();
        int[] array = new int[tamanho];

        preencheArray(array, tamanho);
        selecaoDecrescente(array, tamanho);

        System.out.println("Array Ordenado: ");
        imprimeArray(array, tamanho);
        
        sc.close();
    }    
}
