//package PucMinas.TrabalhoPratico.TP02;

import java.util.Scanner;
import java.io.IOException;


class Celula {
    int valor;
    Celula direita;
    Celula abaixo;

    public Celula(int valor) {
        this.valor   = valor;
        this.direita = null;
        this.abaixo  = null;
    }
}

class Matriz {
    private int linhas;
    private int colunas;
    private Celula cabeca; 

    public Matriz(int linhas, int colunas) {
        this.linhas  = linhas;
        this.colunas = colunas;

        Celula[][] aux = new Celula[linhas][colunas];
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                aux[i][j] = new Celula(0);
            }
        }

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (j < colunas - 1) {
                    aux[i][j].direita = aux[i][j + 1];
                }
                if (i < linhas - 1) {
                    aux[i][j].abaixo = aux[i + 1][j];
                }
            }
        }

        cabeca         = new Celula(-1);
        cabeca.direita = aux[0][0];
    }

    public int getLinhas()  { return linhas; }
    public int getColunas() { return colunas; }

    private Celula getCelula(int i, int j) {
        Celula atual = cabeca.direita; // célula (0,0)

        for (int li = 0; li < i; li++) {
            atual = atual.abaixo;
        }
        for (int co = 0; co < j; co++) {
            atual = atual.direita;
        }

        return atual;
    }

    public int get(int i, int j) {
        return getCelula(i, j).valor;
    }

    public void set(int i, int j, int valor) {
        getCelula(i, j).valor = valor;
    }

    public Matriz somar(Matriz m) {
        Matriz resultado = new Matriz(linhas, colunas);
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                resultado.set(i, j, this.get(i, j) + m.get(i, j));
            }
        }
        return resultado;
    }

    public Matriz multiplicar(Matriz m) {
        Matriz resultado = new Matriz(this.linhas, m.colunas);
        for (int i = 0; i < this.linhas; i++) {
            for (int j = 0; j < m.colunas; j++) {
                int soma = 0;
                for (int k = 0; k < this.colunas; k++) {
                    soma += this.get(i, k) * m.get(k, j);
                }
                resultado.set(i, j, soma);
            }
        }
        return resultado;
    }

    public void mostrarDiagonalPrincipal() {
        for (int i = 0; i < linhas; i++) {
            if (i > 0) {
                System.out.print(" ");
            }
            System.out.print(get(i, i));
        }
        System.out.println();
    }

    public void mostrarDiagonalSecundaria() {
        for (int i = 0; i < linhas; i++) {
            if (i > 0) {
                System.out.print(" ");
            }
            System.out.print(get(i, colunas - 1 - i));
        }
        System.out.println();
    }

    public void mostrar() {
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (j > 0) {
                    System.out.print(" ");
                }
                System.out.print(get(i, j));
            }
            System.out.println();
        }
    }
}

public class QuestaoMatriz {

    public static String[] dividirPorEspaco(String s) {
        int count = 0;
        boolean emToken = false;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) != ' ' && !emToken) {
                count++;
                emToken = true;
            } else if (s.charAt(i) == ' ') {
                emToken = false;
            }
        }

        String[] partes = new String[count];
        int indice = 0;
        int inicio = -1;

        for (int i = 0; i <= s.length(); i++) {
            boolean espaco = (i == s.length() || s.charAt(i) == ' ');
            if (!espaco && inicio == -1) {
                inicio = i;
            } else if (espaco && inicio != -1) {
                char[] trecho = new char[i - inicio];
                for (int j = inicio; j < i; j++) {
                    trecho[j - inicio] = s.charAt(j);
                }
                partes[indice] = new String(trecho);
                indice++;
                inicio = -1;
            }
        }
        return partes;
    }

    public static int converteInteiro(String s) {
        int resultado = 0;
        for (int i = 0; i < s.length(); i++) {
            resultado = resultado * 10 + (s.charAt(i) - '0');
        }
        return resultado;
    }

    public static Matriz lerMatriz(Scanner sc) {
        String[] dim = dividirPorEspaco(sc.nextLine().trim());
        int l = converteInteiro(dim[0]);
        int c = converteInteiro(dim[1]);
        Matriz m = new Matriz(l, c);
        for (int i = 0; i < l; i++) {
            String[] vals = dividirPorEspaco(sc.nextLine().trim());
            for (int j = 0; j < c; j++) {
                m.set(i, j, converteInteiro(vals[j]));
            }
        }
        return m;
    }

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int casos = converteInteiro(sc.nextLine().trim());

        for (int t = 0; t < casos; t++) {
            Matriz a = lerMatriz(sc);
            Matriz b = lerMatriz(sc);

            a.mostrarDiagonalPrincipal();

            b.mostrarDiagonalSecundaria();

            Matriz soma = a.somar(b);
            soma.mostrar();

            Matriz produto = a.multiplicar(b);
            produto.mostrar();
        }

        sc.close();
    }
}