//package java;

import java.util.Scanner;

public class InverterRecursivo {

    public static void inverter(String str, int i){
        if(i < str.length()){
            inverter(str, i + 1);
            System.out.print(str.charAt(i));
        }
    }

    public static boolean ehFim(String str){
        boolean resp = false;
        if(str.length() == 3 && str.charAt(0) == 'F' && str.charAt(1) == 'I' && str.charAt(2) == 'M'){
            resp = true;
        }
        return resp;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();

        while(!ehFim(linha)){

            inverter(linha, 0);
            System.out.println();

            linha = sc.nextLine();
        }

        sc.close();
    }
}