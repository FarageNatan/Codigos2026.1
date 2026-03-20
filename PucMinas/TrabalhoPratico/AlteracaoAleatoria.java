import java.util.Random;
import java.util.Scanner;

public class AlteracaoAleatoria {
    
    public static char sortearLetra(Random gerador){
        return (char)('a' + Math.abs(gerador.nextInt()) % 26);
    }

    public static String alterar(String palavra, char l1, char l2){
        String p2 = "";
        for(int i = 0; i < palavra.length(); i++){
            if(palavra.charAt(i) == l1){
                p2 += l2;
            }else{
                p2 += palavra.charAt(i);                
            }
        }
        return p2;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Random gerador = new Random();
        gerador.setSeed(4);
        char letra1 = sortearLetra(gerador);
        char letra2 = sortearLetra(gerador);

        String palavra = sc.nextLine();
        while(palavra.length() != 3 || palavra.charAt(0) != 'F' && palavra.charAt(1) != 'I' && palavra.charAt(2) != 'M'){
            
            String resultado = alterar(palavra, letra1, letra2);
            System.out.println(resultado);
            palavra = sc.nextLine();
            
        }

        sc.close();
    }
}
