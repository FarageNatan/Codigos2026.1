package Java;

//QuestaoDozeTP

import java.util.Scanner;


class No{
	String nome;
	No esq;
	No dir;

	public No(String nome){
		this.nome = nome;
		esq = dir = null;
	}
}


class ArvoreBinaria{
	No raiz;
	
	public ArvoreBinaria(){
		raiz = null;
	}

	public void inserir(String nome){
		raiz = inserirRec(nome, raiz);
	}

	private No inserirRec(String name, No i){
		if(i == null){
			i = new No(name);
		}else if(i.nome.compareTo(name) > 0){
			i.esq = inserirRec(name, i.esq);
		}else if(i.nome.compareTo(name) < 0){
			i.dir = inserirRec(name, i.dir);
		}else{
			System.out.println("Elemento já inserido");
		}
		return i;
	} 

	public boolean pesquisar(String name){
		return pesquisarRec(name, raiz, 0, ' ');
	}
	
	private boolean pesquisarRec(String name, No i, int nivel, char direcao){
		boolean resp = false;
		if(i == null){
			return false;
		}
		if(nivel == 0) System.out.print("Raiz\n");
		else{ 
			System.out.print(direcao);
			System.out.println();
 		}
		if(i.nome.compareTo(name) == 0){
			resp = true;
		}else if(i.nome.compareTo(name) > 0){
			resp = pesquisarRec(name, i.esq, nivel + 1, 'E');
		}else if(i.nome.compareTo(name) < 0){
			resp = pesquisarRec(name, i.dir, nivel + 1, 'D');
		}
		return resp;
	}
}


public class QuestaoDozeTP {
    	
	public static void main(String[]args){
		Scanner sc = new Scanner(System.in);
		ArvoreBinaria ab = new ArvoreBinaria();

		for(int i = 0; i < 10; i++){
			String nome = sc.nextLine();
			ab.inserir(nome);
		}

		String nome1 = "Natan";
		String nome2 = "Sofia";
		String nome3 = "Fabiola";
		String nome4 = "Jose";

		boolean found1 = ab.pesquisar(nome1);
		if(found1) System.out.println("SIM");
		else{ System.out.println("NAO"); } 
		boolean found2 = ab.pesquisar(nome2);
		if(found2) System.out.println("SIM");
		else{ System.out.println("NAO"); }
		boolean found3 = ab.pesquisar(nome3);
		if(found3) System.out.println("SIM");
		else{ System.out.println("NAO"); }
		boolean found4 = ab.pesquisar(nome4);
		if(found4) System.out.println("SIM");
		else{ System.out.println("NAO"); }

		sc.close();
	}



}


