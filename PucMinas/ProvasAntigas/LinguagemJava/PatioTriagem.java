import java.util.*;

class Celula {
    int elemento;
    Celula prox;

    public Celula(int x) {
        this.elemento = x;
        this.prox = null;
    }
}

class Lista {
    Celula primeiro;
    Celula ultimo;

    public Lista() {
        primeiro = ultimo = null;
    }

    public boolean vazia() {
        return primeiro == null;
    }

    public void inserirFim(int x) {
        Celula nova = new Celula(x);
        if (vazia()) {
            primeiro = nova;
            ultimo = nova;
        } else {
            ultimo.prox = nova;
            ultimo = nova;
        }
    }

    public int removerInicio() {
        if (vazia()) return -1;

        int resp = primeiro.elemento;
        Celula tmp = primeiro;
        primeiro = primeiro.prox;
        tmp.prox = null;

        if (primeiro == null) ultimo = null;

        return resp;
    }

    public void moverPrimeiroParaFim() {
        int val = removerInicio();
        inserirFim(val);
    }

    public boolean temPar() {
        for (Celula p = primeiro; p != null; p = p.prox) {
            if (p.elemento % 2 == 0) return true;
        }
        return false;
    }
}

public class PatioTriagem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            int N = sc.nextInt();
            int L = sc.nextInt();

            Lista lista = new Lista();
            for (int i = 0; i < N; i++) {
                lista.inserirFim(sc.nextInt());
            }

            Lista descarregados = new Lista();
            int count = 0;

            while (count < L && !lista.vazia()) {
                int frente = lista.primeiro.elemento;

                if (frente % 2 == 0) {
                    descarregados.inserirFim(lista.removerInicio());
                    count++;
                } else {
                    if (lista.temPar()) {
                        lista.moverPrimeiroParaFim();
                    } else {
                        descarregados.inserirFim(lista.removerInicio());
                        count++;
                    }
                }
            }

            System.out.print("Descarregados:");
            for (Celula c = descarregados.primeiro; c != null; c = c.prox) {
                System.out.print(" " + c.elemento);
            }
            System.out.println();

            System.out.print("Restantes:");
            for (Celula c = lista.primeiro; c != null; c = c.prox) {
                System.out.print(" " + c.elemento);
            }
            System.out.println();

            System.out.println();
        }

        sc.close();
    }
}