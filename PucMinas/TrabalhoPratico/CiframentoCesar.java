//package PucMinas.TrabalhoPratico;
import java.util.Scanner;

public class CiframentoCesar {
    
    public static String cifraString(String palavra, int chaveCifra){
        String cifrada = "";
        for(int i = 0; i < palavra.length(); i++){
            char original = palavra.charAt(i);
            char modificado = original;
            if(original >= 0 && original <= 127){
                modificado = (char) ((modificado + chaveCifra) % 128); 
                cifrada += modificado;
            }else{
                cifrada += original;
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
