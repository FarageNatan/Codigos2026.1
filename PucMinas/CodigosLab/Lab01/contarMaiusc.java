package PucMinas.CodigosLab;

import java.util.Scanner;

public class contarMaiusc {

    private static int contMaiuscIterativo(String s, int pos){
        int cont = 0;
        for(int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if(c >= 'A' && c <= 'Z'){
                cont += 1;
            }
        }
        return cont;
    }

    public static int contMaiuscIterativo(String s){
        return contMaiuscIterativo(s, 0);
    }

    public static int contMaiuscRec(String s){
        return contMaiuscRec(s, 0);
    }

    private static int contMaiuscRec(String s, int pos){
        int cont = 0;
        if(pos < s.length()){
            char c = s.charAt(pos);
            if(c >= 'A' && c <= 'Z'){
                cont = 1 + contMaiuscRec(s, pos + 1);
            }else{
                cont = contMaiuscRec(s, pos + 1);
            }
        }
        return cont;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        String palavra = sc.nextLine();
        
        int resultado = contMaiuscRec(palavra);

        System.out.println("Quantidade: " + resultado);

        sc.close();
    }    
}