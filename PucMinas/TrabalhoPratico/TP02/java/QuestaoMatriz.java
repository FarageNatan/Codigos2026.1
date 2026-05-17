import java.util.Scanner;

class Celula {
    public int elemento;
    public Celula inf, sup, esq, dir;

    public Celula() {
        this(0);
    }

    public Celula(int elemento) {
        this.elemento = elemento;
        this.inf = this.sup = this.esq = this.dir = null;
    }
}

class Matriz {
    private Celula inicio;
    private int linha, coluna;

    public Matriz(int linha, int coluna) {
        this.linha = linha;
        this.coluna = coluna;

        if (linha <= 0 || coluna <= 0) return;

        inicio = new Celula();
        Celula atualLinha = inicio;
        for (int j = 1; j < coluna; j++) {
            Celula nova = new Celula();
            atualLinha.dir = nova;
            nova.esq = atualLinha;
            atualLinha = nova;
        }

        Celula linhaAnterior = inicio;
        for (int i = 1; i < linha; i++) {
            Celula novaLinhaInicio = new Celula();
            linhaAnterior.inf = novaLinhaInicio;
            novaLinhaInicio.sup = linhaAnterior;

            Celula atualSup = linhaAnterior.dir;
            Celula atualInf = novaLinhaInicio;

            for (int j = 1; j < coluna; j++) {
                Celula nova = new Celula();
                atualInf.dir = nova;
                nova.esq = atualInf;

                atualSup.inf = nova;
                nova.sup = atualSup;

                atualSup = atualSup.dir;
                atualInf = nova;
            }
            linhaAnterior = novaLinhaInicio;
        }
    }

    public void ler(Scanner scanner) {
        Celula linhaAtual = inicio;
        while (linhaAtual != null) {
            Celula celulaAtual = linhaAtual;
            while (celulaAtual != null) {
                if (scanner.hasNextInt()) {
                    celulaAtual.elemento = scanner.nextInt();
                }
                celulaAtual = celulaAtual.dir;
            }
            linhaAtual = linhaAtual.inf;
        }
    }

    public Matriz somar(Matriz m) {
        if (this.linha != m.linha || this.coluna != m.coluna) {
            return null;
        }

        Matriz resultado = new Matriz(this.linha, this.coluna);
        
        Celula rLinha = resultado.inicio;
        Celula tLinha = this.inicio;
        Celula mLinha = m.inicio;

        while (rLinha != null) {
            Celula rCel = rLinha;
            Celula tCel = tLinha;
            Celula mCel = mLinha;

            while (rCel != null) {
                rCel.elemento = tCel.elemento + mCel.elemento;
                rCel = rCel.dir;
                tCel = tCel.dir;
                mCel = mCel.dir;
            }
            rLinha = rLinha.inf;
            tLinha = tLinha.inf;
            mLinha = mLinha.inf;
        }

        return resultado;
    }

    public Matriz multiplicar(Matriz m) {
        if (this.coluna != m.linha) {
            return null;
        }

        Matriz resultado = new Matriz(this.linha, m.coluna);

        Celula rLinha = resultado.inicio;
        Celula tLinhaA = this.inicio;

        while (rLinha != null) {
            Celula rCel = rLinha;
            Celula mColunaB = m.inicio;

            while (rCel != null) {
                int somaProd = 0;
                Celula tCel = tLinhaA;   
                Celula mCel = mColunaB;  

                while (tCel != null && mCel != null) {
                    somaProd += tCel.elemento * mCel.elemento;
                    tCel = tCel.dir;
                    mCel = mCel.inf;
                }

                rCel.elemento = somaProd;
                rCel = rCel.dir;
                mColunaB = mColunaB.dir;
            }
            rLinha = rLinha.inf;
            tLinhaA = tLinhaA.inf;
        }

        return resultado;
    }

    public void mostrarDiagonalPrincipal() {
        if (linha != coluna) return; 

        Celula atual = inicio;
        while (atual != null) {
            System.out.print(atual.elemento + " ");
            if (atual.dir != null) {
                atual = atual.dir.inf;
            } else {
                atual = null;
            }
        }
        System.out.println();
    }

    public void mostrarDiagonalSecundaria() {
        if (linha != coluna) return;

        Celula atual = inicio;
        while (atual.dir != null) {
            atual = atual.dir;
        }

        while (atual != null) {
            System.out.print(atual.elemento + " ");
            if (atual.esq != null) {
                atual = atual.esq.inf;
            } else {
                atual = null;
            }
        }
        System.out.println();
    }

    public void mostrar() {
        Celula linhaAtual = inicio;
        while (linhaAtual != null) {
            Celula celulaAtual = linhaAtual;
            while (celulaAtual != null) {
                System.out.print(celulaAtual.elemento + " ");
                celulaAtual = celulaAtual.dir;
            }
            System.out.println();
            linhaAtual = linhaAtual.inf;
        }
    }
}

public class QuestaoMatriz {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (!scanner.hasNextInt()) return;

        int numCasos = scanner.nextInt();

        for (int caso = 0; caso < numCasos; caso++) {
          
            int l1 = scanner.nextInt();
            int c1 = scanner.nextInt();
            Matriz m1 = new Matriz(l1, c1);
            m1.ler(scanner);

         
            int l2 = scanner.nextInt();
            int c2 = scanner.nextInt();
            Matriz m2 = new Matriz(l2, c2);
            m2.ler(scanner);

            m1.mostrarDiagonalPrincipal();

         
            m2.mostrarDiagonalSecundaria();

            
            Matriz soma = m1.somar(m2);
            if (soma != null) {
                soma.mostrar();
            }

            Matriz multiplicacao = m1.multiplicar(m2);
            if (multiplicacao != null) {
                multiplicacao.mostrar();
            }
        }
        scanner.close();
    }
}