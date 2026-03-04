package PucMinas.CodigosLab.Lab02;
import java.util.Scanner;

public class sequenciaEspelho {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int inicio = sc.nextInt();
        int fim = sc.nextInt();

        String resultado = "";

        for (int i = inicio; i <= fim; i++) {
            resultado += i;
        }

        for (int i = fim; i >= inicio; i--) {
            String numero = String.valueOf(i);
            String invertido = "";

            for (int j = numero.length() - 1; j >= 0; j--) {
                invertido += numero.charAt(j);
            }

            resultado += invertido;
        }

        System.out.println(resultado);

        sc.close();
    }
}
