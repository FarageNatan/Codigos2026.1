import java.util.Scanner;

public class RecSomaDigitos {
    
    public static int somaDigitos(int num){
        int sum = 0;
        if(num > 0){
            sum += (num % 10 + somaDigitos(num / 10));
        }
        return sum;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        
        while(sc.hasNext()){
            int numero = sc.nextInt();

            int resp = somaDigitos(numero);
            
            System.out.println(resp);
        }

        sc.close();
    }
}
