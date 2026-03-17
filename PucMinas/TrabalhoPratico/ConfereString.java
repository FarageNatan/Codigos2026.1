package PucMinas.TrabalhoPratico;
import java.util.Scanner;

public class ConfereString{
	
	public static boolean confereVogal(String palavra){
        System.out.println("Aqui1");
		boolean soVogal = true;
		for(int i = 0; i < palavra.length(); i++){
			char letra = palavra.charAt(i);
			if(letra != 'a' && letra != 'A' && letra != 'e' && letra != 'E' && letra != 'i' && letra != 'I' && letra != 'o' && letra != 'O' && letra != 'u' && letra != 'U'){
				soVogal = false;
				i = palavra.length();
			}
		}//fim for
		return soVogal;
	}//fim vogal

	public static boolean confereConsoante(String palavra){
        System.out.println("Aqui2");
		boolean soConsoante = true;
		for(int i = 0; i < palavra.length(); i++){
			char letra = palavra.charAt(i);
			if(letra == 'a' || letra == 'A' || letra == 'e' || letra == 'E' || letra == 'i' || letra == 'I' || letra == 'o' || letra == 'O' || letra == 'u' || letra == 'U'){
				soConsoante= false;
				i = palavra.length();
			}
		}//fim for
		return soConsoante;
	}//fim consoante

	public static boolean confereInteiro(String palavra){
        System.out.println("Aqui3");
		boolean ehInteiro = true;
		for(int i = 0; i < palavra.length(); i++){
			char letra = palavra.charAt(i);
			if(!(letra >= '0' && letra <= '9')){
				ehInteiro = false;
				i = palavra.length();
			}
		}//fim for
		return ehInteiro;
	}

	public static boolean confereReal(String palavra){
        System.out.println("Aqui4");
		boolean ehReal = true;
		int ponto = 0;
		for(int i = 0; i < palavra.length(); i++){
			char letra = palavra.charAt(i);
			if(letra == '.' || letra == ','){
				ponto++;
			}
			if((!(letra >= '0' && letra <= '9')) || ponto > 1){
				ehReal = false;
			}	

		}//fim for
		return ehReal;
	}


	public static void main(String[]args){
		
		Scanner sc = new Scanner(System.in);

		String palavra = sc.nextLine();
		
		while(!(palavra.length() == 3 || palavra.charAt(0) == 'F' && palavra.charAt(1) == 'I' && palavra.charAt(2) == 'M')){
            boolean soVogais = confereVogal(palavra);
		    boolean soConsoantes = confereConsoante(palavra);
		    boolean ehInteiro = confereInteiro(palavra);
		    boolean ehReal = confereReal(palavra);
			if(soVogais){
				System.out.print("SIM ");
			}else{
				System.out.print("NAO ");
			}
			if(soConsoantes){
				System.out.print("SIM ");
			}else{
				System.out.print("NAO ");
			}
			if(ehInteiro){
				System.out.print("SIM ");
			}else{
				System.out.print("NAO ");
			}
			if(ehReal){
				System.out.println("SIM");
			}else{
				System.out.println("NAO");
			}	
			palavra = sc.nextLine();
		}

		sc.close();
	}//fim main

}//fim class