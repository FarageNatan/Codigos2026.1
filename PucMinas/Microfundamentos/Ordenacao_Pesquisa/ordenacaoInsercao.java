package PucMinas.Microfundamentos.Ordenacao_Pesquisa;

import java.util.Random;

public class ordenacaoInsercao {

    public static void ordenar(int[] array){
        int n = array.length;
        int comparacoes = 0;
        for(int i = 1; i < n; i++){
            int tmp = array[i];
            int j = i - 1;
            while((j >= 0) && (array[j] > tmp)){
                comparacoes++;
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = tmp;
        }
        System.out.println("Quantidade de comparacoes: " + comparacoes);
    }

    public static void main(String[] args) {
        int[] array = new int[100];
        
        Random r = new Random();
        for(int i = 0; i < array.length; i++){
            array[i] = r.nextInt(100);
        }
        
        //Desordenado
        for(int i = 0; i < array.length; i++){
            System.out.print(array[i] + " ");
        }

        System.out.println();
        ordenar(array);

        //Ordenado
        for(int i = 0; i < array.length; i++){
            System.out.print(array[i] + " ");
        }
    }
}
