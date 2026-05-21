import java.util.*;


public class VerificarExpressoes{
	public static boolean confere(String exp){
		boolean resp;
		int pa = 0;
		int pb = 0;
		int colA = 0, colB = 0;
		int chaA = 0, chaB = 0;
		for(int i = 0; i < exp.length(); i++){
			char c = exp.charAt(i);
			if(c == '('){
				pa++;
			}else if( c == ')'){
				pb++;
			}else if(c == '['){
				colA++;
			}else if(c == ']'){
				colB++;
			}else if(c == '{'){
				chaA++;
			}else if(c == '}'){
				chaB++;
			}	
		}
		if((pa - pb == 0) && (colA - colB == 0) && (chaA - chaB == 0)){
			resp = true;
		}else{
			resp = false;
		}

		return resp;
	}

	public static void main(String[]args){
		Scanner sc = new Scanner(System.in);
		
		while(sc.hasNextLine()){
			String expressao = sc.nextLine();
			
			boolean ehCerta = confere(expressao);
			if(ehCerta){
				System.out.println("correta");
			}else{
				System.out.println("incorreta");
			}
			
		}
		sc.close();
	}

}
