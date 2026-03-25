package PucMinas.Microfundamentos;

import java.util.Scanner;

class Pilha{
    int[] array;
    int n;
    
    public Pilha(){
        array = new int[6];
        n = 0;
    }

    public Pilha(int tamanho){
        array = new int[tamanho];
        n = 0;
    }

    /*
        A Pilha eh outro tipo de TAD linear que tem características específicas podemos pensar que é uma pilha de pratos.
        Na pilha de pratos, inserimos no topo da pilha, ou seja, no final dela.
        E para facilitar, removemos o ultimo prato(elemento) colocado, ou seja, remoção no final.

        Existe a pilha que remove e insere no inicio, porem ambos os metodos nao sao eficientes.
    */

    public void inserirFim(int x){
        if(n >= array.length){
            System.out.println("Lista cheia");
        } else{
            array[n] = x;
            n++;
        }
    }
    
    public int removerFim(){
        int resp = 0;
        if(n == 0){
            System.out.println("Lista vazia");
        } else {
            resp = array[--n];             
        }
        return resp;
    }

    public void mostrar(){
        if(n == 0){
            System.out.println("Pilha Vazia");
        } else {
            System.out.println("Lista do topo para a base: ");
            for(int i = n - 1; i >= 0; i--){
                System.out.print(array[i] + " ");
                System.out.println();
            }
        }
    }


}

public class PilhaSequencial {
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Tamanho pilha: ");
        int tamanho = sc.nextInt();
        Pilha pilha = new Pilha(tamanho);

        System.out.println("Inserir: ");
        pilha.inserirFim(sc.nextInt());
        pilha.mostrar();
        System.out.println("Inserir: ");
        pilha.inserirFim(sc.nextInt());
        pilha.mostrar();
        System.out.println("Inserir: ");
        pilha.inserirFim(sc.nextInt());
        pilha.mostrar();
        System.out.println("Inserir: ");
        pilha.inserirFim(sc.nextInt());
        pilha.mostrar();
        int x1 = pilha.removerFim();
        pilha.mostrar();
        int x2 = pilha.removerFim();
        pilha.mostrar();
        System.out.println("Os elementos removidos foram: " + x1 + " " + x2);
        
        sc.close();
    }
}
