package PucMinas.ProvasAntigas.LinguagemJava;
import java.util.*;


class Carro{
	String placa, modelo, tipo, chassi;

	void ler(String linha){
		String[] partes = linha.split(",");
		placa = partes[0];
		modelo = partes[1];
		tipo = partes[2];
		chassi = partes[3];
	}

	void imprimir(){
		System.out.println(placa + " " + modelo + " " + tipo + " " + chassi);
	}
}


class No{
	Carro carro;
	No esq;
	No dir;
	
	public No(Carro car){
		this.carro = car;
		esq = dir = null;
	}
}

class Arvore{
	No raiz;
	
	public Arvore(){
		raiz = null;
	}

	public void inserirCarro(Carro car){
		raiz = inserirCarroRec(car, raiz);
	}

	public No inserirCarroRec(Carro car, No i){
		if(i == null){
			i = new No(car);
		}else if(i.carro.placa.compareTo(car.placa) > 0){
			i.esq = inserirCarroRec(car, i.esq);
		}else{
			i.dir = inserirCarroRec(car, i.dir);
		}
		return i;
	}

	public int getAltura(){
		return getAltura(raiz);
	}

	public int getAltura(No i){
		if(i == null) return -1;
		return 1 + Math.max(getAltura(i.esq), getAltura(i.dir));
	}

	public int getNos(){
		return getNos(raiz);
	}
	
	public int getNos(No i){
		if(i == null) return 0;
		return 1 + getNos(i.dir) + getNos(i.esq);
	}

	public int getFolhas(){
		return getFolhas(raiz);
	}

	public int getFolhas(No i){
		int cont = 0;
		if(i == null){
			cont += 0;
		}else if(i.esq == null && i.dir == null){
			cont += 1;
		}else{
			cont += getFolhas(i.dir) + getFolhas(i.esq);
		}
		return cont;
	}

	public void mostrarCresc(){
		mostrarCrescRec(raiz);	
	}

	public void mostrarCrescRec(No i){
		if(i != null){
			mostrarCrescRec(i.esq);
			System.out.print(i.carro.placa + " ");
			mostrarCrescRec(i.dir);
		}
	}
}//fim class

public class RelatorioABP{
	
	public static void main(String[]args){
		Scanner sc = new Scanner(System.in);

		Arvore arvore = new Arvore();

        int i = 0;
		while(i < 5){
			Carro carro = new Carro();
			String infos = sc.nextLine();
            carro.ler(infos);
			arvore.inserirCarro(carro);
            i++;					
		}

		System.out.println(arvore.getAltura());
		System.out.println(arvore.getNos());
		System.out.println(arvore.getFolhas());
		
		arvore.mostrarCresc();

        sc.close();
	}
}
