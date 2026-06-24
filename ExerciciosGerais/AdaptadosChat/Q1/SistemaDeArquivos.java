package ExerciciosGerais.AdaptadosChat.Q1;

import java.util.Scanner;

/*
Contexto:
Você está desenvolvendo o módulo de indexação de pastas de um novo sistema operacional chamado IceOS. Cada pasta criada recebe um nome único (String). Para otimizar a busca, o IceOS armazena os nomes das pastas em uma Árvore Binária de Busca (BST) conforme elas são criadas.O grande problema é que, se a árvore ficar muito desbalanceada, o sistema operacional começa a travar. O diretor técnico pediu para você criar um relatório que mostre a altura da árvore após a inserção de uma série de pastas e que liste os nomes das pastas em ordem alfabética reversa (decrescente).
Entrada:
A primeira linha da entrada contém um inteiro $N$ ($1 \le N \le 1000$), representando a quantidade de pastas que serão criadas. As $N$ linhas seguintes contêm, cada uma, uma String (sem espaços) com o nome da pasta.
Saída: 
Na primeira linha, imprima a mensagem Altura: X, onde X é a altura da árvore (considere altura da árvore com apenas o nó raiz como 0).Nas linhas seguintes, imprima os nomes das pastas inseridas, um por linha, em ordem alfabética decrescente.
*/

class No{
    String pasta;
    No esq;
    No dir;

    public No(String nome){
        this.pasta = nome;
        dir = esq = null;
    }
}

class ArvorePastas{
    No raiz;
    public ArvorePastas(){
        raiz = null;
    }

    public void inserirPasta(String nome){
            raiz = inserirPastaRec(nome, raiz);
    }

    public No inserirPastaRec(String nome, No i){
        if(i == null){
            i = new No(nome);
        }else if(i.pasta.compareTo(nome) > 0){
            i.esq = inserirPastaRec(nome, i.esq);
        }else if(i.pasta.compareTo(nome) < 0){
            i.dir = inserirPastaRec(nome, i.dir);
        }else{
            System.out.println("Elemento ja inserido");
        }
        return i;
    }   

    public int alturaArvore(){
        return getAltura(raiz, 0);
    }

    private int getAltura(No i, int altura){
      if(i == null){
         altura--;
      } else {
         int alturaEsq = getAltura(i.esq, altura + 1);
         int alturaDir = getAltura(i.dir, altura + 1);
         altura = (alturaEsq > alturaDir) ? alturaEsq : alturaDir;
      }
      return altura;
    }  

    public void alfabeticaContraria(){
        alfabeticaContrariaRec(raiz);
    }

    private void alfabeticaContrariaRec(No i){
        if(i != null){
            alfabeticaContrariaRec(i.dir);
            System.out.println(i.pasta);
            alfabeticaContrariaRec(i.esq);
        }
    }
}


public class SistemaDeArquivos {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int qtdInsercao = sc.nextInt();
        sc.nextLine();
        ArvorePastas ab = new ArvorePastas();
        
        for(int i = 0; i < qtdInsercao; i++){
            String pasta = sc.nextLine();
            ab.inserirPasta(pasta);
        }

        int altura = ab.alturaArvore();
        System.out.println("Altura: " + altura);

        ab.alfabeticaContraria();

        sc.close();
    }
}
