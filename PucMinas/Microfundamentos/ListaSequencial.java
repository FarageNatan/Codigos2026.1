package PucMinas.Microfundamentos;

import java.util.Scanner;

class Lista{
    int[] array;
    int n; //numero de elementos dentro da lista

    Lista(){
        array = new int[6]; //Poderia ser qualquer valor entre os colchetes, 6 é apenas um exemplo
        n = 0;  //Como a lista vai estar vazia, inicializa n com 0;
    }

    Lista(int tamanho){
        array = new int[tamanho]; //Limite da quantidade de elementos da lista estabelecido de acordo com o valor passado como parâmetro
        n = 0;
    }

    public void inserirInicio(int x) {
        if(n >= array.length) {
            System.out.println("Lista Cheia!");
        }

        for(int i = (n - 1); i >= 0; i--){
            array[i + 1] = array[i];
        }

        array[0] = x;
        n++;
    }

    /* Método Inserir Inicio do Slide 
    public void InserirInicio(int x){
        if(n >= array.length) {
            System.out.println("Lista Cheia!");
        }

        for(int i = n; i > 0; i--){
            array[i] = array[i - 1];
        }

        array[0] = x;
        n++;
    }
    */

    public void inserirFim(int x){
        if(n >= array.length){
            System.out.println("Lista Cheia");
        }

        array[n++] = x;
    }

    /* Método inserirFim do slide igual ao anterior */

    public void inserirPosicao(int x, int pos){
        if(n >= array.length || pos > n || pos < 0){ //Conferimos se a posicao eh maior que n, para evitar que fique espaços em branco na Lista
            System.out.println("Está Cheio ou Posicao Invalida");
        }
        
        for(int i = (n - 1); i >= pos; i--){
            array[i + 1] = array[i];
        }

        array[pos] = x;
        n++;
    }

    public int removerInicio(){
        if(n == 0){
            System.out.println("Lista Vazia");
            return 0;
        }
        int resp = array[0];
        for(int i = 1; i < n; i++){
            array[i - 1] = array[i];
        }
        n--;
        return resp;
    }

    public int removerFim(){
        if(n == 0){
            System.out.println("Lista Vazia");
            return 0;
        }
        return array[--n];
    }

    public int removerPos(int pos){
        if(n == 0 || pos < 0 || pos >= n){
            System.out.println("Lista vazia ou posição invalida");
        }

        int resp = array[pos];
        n--;
        
        for(int i = pos; i < n; i++){
            array[i] = array[i + 1];
        }
        return resp;
    }

    public void mostrar(){
        for(int i = 0; i < n; i++){
            System.out.print("[ " + array[i] + " ]");
        }
        System.out.println(); //Pula linha
    }

    /* Métodos Complementares propostos na atividade do Microfundamento */

    public int somaElementos(){
        int soma = 0;
        for(int i = 0; i < n; i++){
            soma += array[i];
        }
        return soma;
    }
}

public class ListaSequencial {
    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.println("Tamanho Lista: ");
        Lista lista = new Lista(sc.nextInt());
        
        System.out.println("Inserir inicio ");
        lista.inserirInicio(sc.nextInt());
        lista.mostrar();

        System.out.println("Inserir inicio ");
        lista.inserirInicio(sc.nextInt());
        lista.mostrar();
        
        System.out.println("Inserir Fim: ");
        lista.inserirFim(sc.nextInt());
        lista.mostrar();
        
        System.out.println("Remover Inicio");
        int x1 = lista.removerInicio();
        lista.mostrar();

        System.out.println("Inserir na posicao: ");
        lista.inserirPosicao(sc.nextInt(), 1);
        lista.mostrar();

        System.out.println("Remover Fim");
        int x2 = lista.removerFim();
        lista.mostrar();

        int soma = lista.somaElementos();

        System.out.println("Os elementos removidos da lista foram: " + x1 + " e " + x2);
        System.out.println("A lista final ficou assim: ");
        lista.mostrar();
        System.out.println("A soma dos elementos da lista eh igual a: " + soma);
        sc.close();
    }
}
