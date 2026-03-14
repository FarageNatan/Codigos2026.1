package PucMinas.TrabalhoPratico;
import java.util.Scanner;

public class CiframentoCesar {
    
    public static String cifraString(String palavra, int chaveCifra){
        String cifrada = "";
        for(int i = 0; i < palavra.length(); i++){
            char modificado = palavra.charAt(i);
            if(modificado >= 'A' && modificado <= 'Z' || modificado >= 'a' && modificado <= 'z'){
                modificado = (char) (modificado + chaveCifra);
                cifrada += modificado;
            }else{
                cifrada += modificado;
            }
        }
        return cifrada;
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String palavra = sc.nextLine();
        
        while(palavra.length() != 3 || palavra.charAt(0) != 'F' && palavra.charAt(1) != 'I' && palavra.charAt(2) != 'M'){
            
            String cifrada = cifraString(palavra, 3);
            System.out.println(cifrada);
            palavra = sc.nextLine();

        }
        sc.close();
    }
}
