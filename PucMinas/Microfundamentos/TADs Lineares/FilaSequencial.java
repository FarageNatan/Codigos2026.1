package PucMinas.Microfundamentos;

import java.util.Scanner;

class Fila{
    int[] array;
    int n;

    Fila(){
        array = new int[6];
        n = 0;
    }

    Fila(int tamanho){
        array = new int[tamanho];
        n = 0;
    }

    /* Métodos Inserir e Remover da Fila
        Os métodos desse TAD são correspondentes a uma fila de pessoas no caixa por exemplo.
        A primeira pessoa que entrar na fila vai ser a primeira a sair, da mesma forma que a ultima a entrar vai ser a ultima a sair
        Em uma fila de caixa, "removemos" a pessoa mais a frente, ou seja, a do inicio.
        Da mesma forma, a pessoa entra na fila pelo final, ja que é errado furar a fila, ou seja, "inserimos" no final   
        
        Podemos usar os mesmos métodos da lista, porém com as restrições citadas acima.
    */

    public void inserirFim(int x){
        if(n >= array.length){
            System.out.println("Fila está cheia");
        }

        array[n] = x;
        n++;
    }

    public int removerInicio(){
        if(n == 0){
            System.out.println("Lista vazia");
        }
        int resp = array[0];

        for(int i = 1; i < n; i++){
            array[i - 1] = array[i];
        }

        n--;
        return resp;
    }

    public void mostrar(){
        for(int i = 0; i < n; i++){
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }
}


public class FilaSequencial {
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Tamanho da fila: ");
        int tamanho = sc.nextInt();
        Fila fila = new Fila(tamanho);

        for(int i = 0; i < tamanho; i++){
            System.out.println("Inserir no fim: ");
            fila.inserirFim(sc.nextInt());
        }

        System.out.println("Fila completa: ");
        fila.mostrar();

        sc.close();    
    }
    
}
