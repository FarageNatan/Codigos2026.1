package Nivel1;

import java.util.Scanner;
import java.util.ArrayList;

public class AttackOnGasparini {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int x = scanner.nextInt();

        String titans = scanner.next();

        int p = scanner.nextInt();
        int m = scanner.nextInt();
        int g = scanner.nextInt();

        // ArrayList para armazenar dinamicamente a altura de cada muralha
        ArrayList<Integer> walls = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            char type = titans.charAt(i);
            int k = 0;
            if (type == 'P') k = p;
            else if (type == 'M') k = m;
            else if (type == 'G') k = g;

            boolean stopped = false;
            // O titã percorre a sequência de muralhas existentes
            for (int j = 0; j < walls.size(); j++) {
                if (walls.get(j) >= k) {
                    walls.set(j, walls.get(j) - k); // O titã destrói k metros e morre
                    stopped = true;
                    break;
                }
            }

            // Se nenhuma muralha existente barrou o titã, constrói uma nova
            if (!stopped) {
                walls.add(x - k);
            }
        }

        // Imprime a quantidade mínima de muralhas criadas
        System.out.println(walls.size());

        scanner.close();
    }
}