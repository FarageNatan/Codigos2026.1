import java.util.Scanner;

public class ValidacaoSenha{

	public static boolean confereSenha(String senha){
		boolean ehSenha = true;
		int minuscula = 0, maiuscula = 0, numero = 0, especial = 0;		

		if(senha.length() < 8){
			ehSenha = false;	
		} else {
			for(int i = 0; i < senha.length(); i++){
				if(senha.charAt(i) >= 'a' && senha.charAt(i) <= 'z'){
					minuscula++;
				}else if(senha.charAt(i) >= 'A' && senha.charAt(i) <= 'Z'){
					maiuscula++;
				}else if(senha.charAt(i) >= '0' && senha.charAt(i) <= '9'){
					numero++;
				}else if(senha.charAt(i) == '!' || senha.charAt(i) == '@' || senha.charAt(i) == '#' || senha.charAt(i) == '^' || senha.charAt(i) == '$'){
					especial++;
				}
			}//fim for
			if(minuscula == 0 || maiuscula == 0 || numero == 0 || especial == 0){
				ehSenha = false;
			}
		} //fim else
		
		return ehSenha;
	}//fim funcao

	public static void main(String[]args){
		Scanner sc = new Scanner(System.in);
		
		String senha = sc.nextLine();
		
		while(senha.length() != 3 || senha.charAt(0) != 'F' || senha.charAt(1) != 'I' || senha.charAt(2) != 'M'){
			boolean ehSenha = confereSenha(senha);
			if(ehSenha){
				System.out.println("SIM");
			}else{
				System.out.println("NAO");
			}
			senha = sc.nextLine();	
		}//fim while

		sc.close();
	}//fim main


}//fim class
