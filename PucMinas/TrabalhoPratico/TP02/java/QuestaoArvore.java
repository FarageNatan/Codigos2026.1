import java.io.*;

class Data {

    private int ano;
    private int mes;
    private int dia;

    public static Data parseData(String s) {

        Data d = new Data();

        int i = 0;

        while (s.charAt(i) != '-') {
            d.ano = d.ano * 10 + (s.charAt(i) - '0');
            i++;
        }

        i++;

        while (s.charAt(i) != '-') {
            d.mes = d.mes * 10 + (s.charAt(i) - '0');
            i++;
        }

        i++;

        while (i < s.length()) {
            d.dia = d.dia * 10 + (s.charAt(i) - '0');
            i++;
        }

        return d;
    }

    public String formatar() {

        return Restaurante.doisDigitos(dia) + "/" +
               Restaurante.doisDigitos(mes) + "/" +
               Restaurante.quatroDigitos(ano);
    }
}

class Hora {

    private int hora;
    private int minuto;

    public static Hora parseHora(String s) {

        Hora h = new Hora();

        int i = 0;

        while (s.charAt(i) != ':') {
            h.hora = h.hora * 10 + (s.charAt(i) - '0');
            i++;
        }

        i++;

        while (i < s.length()) {
            h.minuto = h.minuto * 10 + (s.charAt(i) - '0');
            i++;
        }

        return h;
    }

    public String formatar() {

        return Restaurante.doisDigitos(hora) + ":" +
               Restaurante.doisDigitos(minuto);
    }
}

class Restaurante {

    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;

    private String[] tipos = new String[20];
    private int qtdTipos;

    private int faixaPreco;

    private Hora abertura;
    private Hora fechamento;

    private Data dataAbertura;

    private boolean aberto;

    public int getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public static int parseInt(String s) {

        int resp = 0;

        int inicio = 0;

        boolean negativo = false;

        if (s == null || s.length() == 0) {
            return 0;
        }

        if (s.charAt(0) == '-') {
            negativo = true;
            inicio = 1;
        }

        for (int i = inicio; i < s.length(); i++) {

            char c = s.charAt(i);

            if (c >= '0' && c <= '9') {
                resp = resp * 10 + (c - '0');
            }
        }

        if (negativo) {
            resp = resp * -1;
        }

        return resp;
    }

    public static double parseDouble(String s) {

        double resp = 0;

        double decimal = 0.1;

        boolean ponto = false;

        for (int i = 0; i < s.length(); i++) {

            char c = s.charAt(i);

            if (c == '.') {

                ponto = true;

            } else if (c >= '0' && c <= '9') {

                if (!ponto) {

                    resp = resp * 10 + (c - '0');

                } else {

                    resp += (c - '0') * decimal;

                    decimal /= 10;
                }
            }
        }

        return resp;
    }

    public static boolean igual(String a, String b) {

        if (a.length() != b.length()) {
            return false;
        }

        for (int i = 0; i < a.length(); i++) {

            if (a.charAt(i) != b.charAt(i)) {
                return false;
            }
        }

        return true;
    }

    public static int compararString(String a, String b) {

        int i = 0;

        while (i < a.length() && i < b.length()) {

            if (a.charAt(i) < b.charAt(i)) {
                return -1;

            } else if (a.charAt(i) > b.charAt(i)) {
                return 1;
            }

            i++;
        }

        if (a.length() == b.length()) {

            return 0;

        } else if (a.length() < b.length()) {

            return -1;

        } else {

            return 1;
        }
    }

    public static String doisDigitos(int n) {

        if (n < 10) return "0" + n;

        return "" + n;
    }

    public static String quatroDigitos(int n) {

        if (n < 10) return "000" + n;

        if (n < 100) return "00" + n;

        if (n < 1000) return "0" + n;

        return "" + n;
    }

    public static String umaCasa(double valor) {

        int inteiro = (int) valor;

        int decimal =
            (int)((valor - inteiro) * 10 + 0.5);

        return inteiro + "." + decimal;
    }

    public static Restaurante parseRestaurante(String s) {

        Restaurante r = new Restaurante();

        String[] campos = new String[10];

        int c = 0;

        String atual = "";

        for (int i = 0; i < s.length(); i++) {

            if (s.charAt(i) == ',') {

                campos[c++] = atual;

                atual = "";

            } else {

                atual += s.charAt(i);
            }
        }

        campos[c] = atual;

        r.id = parseInt(campos[0]);

        r.nome = campos[1];

        r.cidade = campos[2];

        r.capacidade = parseInt(campos[3]);

        r.avaliacao = parseDouble(campos[4]);

        String tipoAtual = "";

        for (int i = 0; i < campos[5].length(); i++) {

            if (campos[5].charAt(i) == ';') {

                r.tipos[r.qtdTipos++] = tipoAtual;

                tipoAtual = "";

            } else {

                tipoAtual += campos[5].charAt(i);
            }
        }

        r.tipos[r.qtdTipos++] = tipoAtual;

        r.faixaPreco = campos[6].length();

        String h1 = "";

        String h2 = "";

        int i = 0;

        while (campos[7].charAt(i) != '-') {

            h1 += campos[7].charAt(i);

            i++;
        }

        i++;

        while (i < campos[7].length()) {

            h2 += campos[7].charAt(i);

            i++;
        }

        r.abertura = Hora.parseHora(h1);

        r.fechamento = Hora.parseHora(h2);

        r.dataAbertura =
            Data.parseData(campos[8]);

        r.aberto =
            igual(campos[9], "true");

        return r;
    }

    public String formatar() {

        String tiposStr = "[";

        for (int i = 0; i < qtdTipos; i++) {

            tiposStr += tipos[i];

            if (i < qtdTipos - 1) {
                tiposStr += ",";
            }
        }

        tiposStr += "]";

        String faixa = "";

        for (int i = 0; i < faixaPreco; i++) {
            faixa += "$";
        }

        return "[" + id +
               " ## " + nome +
               " ## " + cidade +
               " ## " + capacidade +
               " ## " + umaCasa(avaliacao) +
               " ## " + tiposStr +
               " ## " + faixa +
               " ## " + abertura.formatar() +
               "-" + fechamento.formatar() +
               " ## " + dataAbertura.formatar() +
               " ## " + (aberto ? "true" : "false") +
               "]";
    }
}

class ColecaoRestaurantes {

    private Restaurante[] restaurantes =
        new Restaurante[2000];

    private int tamanho;

    public int getTamanho() {
        return tamanho;
    }

    public Restaurante[] getRestaurantes() {
        return restaurantes;
    }

    public void lerCsv(String path)
        throws Exception {

        BufferedReader br =
            new BufferedReader(
                new FileReader(path));

        String linha;

        tamanho = 0;

        br.readLine();

        while ((linha = br.readLine()) != null) {

            restaurantes[tamanho++] =
                Restaurante.parseRestaurante(linha);
        }

        br.close();
    }

    public static ColecaoRestaurantes lerCsv()
        throws Exception {

        ColecaoRestaurantes c =
            new ColecaoRestaurantes();

        c.lerCsv("/tmp/restaurantes.csv");

        return c;
    }
}

class No {

    public Restaurante restaurante;
    public No esq;
    public No dir;

    public No(Restaurante restaurante) {

        this.restaurante = restaurante;

        this.esq = null;
        this.dir = null;
    }
}

class ArvoreBinaria {

    private No raiz;

    public int comparacoes;

    public ArvoreBinaria() {

        raiz = null;

        comparacoes = 0;
    }

    public void inserir(Restaurante restaurante) {

        raiz =
            inserir(restaurante, raiz);
    }

    private No inserir(Restaurante restaurante,
                       No i) {

        if (i == null) {

            i = new No(restaurante);

        } else {

            int cmp =
                Restaurante.compararString(
                    restaurante.getNome(),
                    i.restaurante.getNome()
                );

            if (cmp < 0) {

                i.esq =
                    inserir(restaurante,
                            i.esq);

            } else if (cmp > 0) {

                i.dir =
                    inserir(restaurante,
                            i.dir);
            }
        }

        return i;
    }

    public boolean pesquisar(String nome) {

        System.out.print("raiz ");

        return pesquisar(nome, raiz);
    }

    private boolean pesquisar(String nome,
                              No i) {

        boolean resp;

        if (i == null) {

            resp = false;

        } else {

            comparacoes++;

            int cmp =
                Restaurante.compararString(
                    nome,
                    i.restaurante.getNome()
                );

            if (cmp == 0) {

                resp = true;

            } else if (cmp < 0) {

                System.out.print("esq ");

                resp =
                    pesquisar(nome,
                              i.esq);

            } else {

                System.out.print("dir ");

                resp =
                    pesquisar(nome,
                              i.dir);
            }
        }

        return resp;
    }

    public void caminharCentral() {

        caminharCentral(raiz);
    }

    private void caminharCentral(No i) {

        if (i != null) {

            caminharCentral(i.esq);

            System.out.println(
                i.restaurante.formatar());

            caminharCentral(i.dir);
        }
    }
}

public class QuestaoArvore {

    public static Restaurante buscar(
        ColecaoRestaurantes c,
        int id) {

        for (int i = 0;
             i < c.getTamanho();
             i++) {

            if (c.getRestaurantes()[i]
                .getId() == id) {

                return c.getRestaurantes()[i];
            }
        }

        return null;
    }

    public static void criarLog(
        String matricula,
        int comparacoes,
        double tempo)
        throws Exception {

        String nomeArquivo =
            matricula +
            "_arvore_binaria.txt";

        PrintWriter pw =
            new PrintWriter(
                new FileWriter(nomeArquivo));

        pw.println(
            matricula + "\t" +
            comparacoes + "\t" +
            tempo
        );

        pw.close();
    }

    public static void main(String[] args)
        throws Exception {

        BufferedReader br =
            new BufferedReader(
                new InputStreamReader(System.in));

        ColecaoRestaurantes c =
            ColecaoRestaurantes.lerCsv();

        ArvoreBinaria arvore =
            new ArvoreBinaria();

        String linha =
            br.readLine();

        while (linha != null) {

            int id =
                Restaurante.parseInt(linha);

            if (id == -1) {

                linha = null;

            } else {

                Restaurante r =
                    buscar(c, id);

                if (r != null) {

                    arvore.inserir(r);
                }

                linha = br.readLine();
            }
        }

        linha = br.readLine();

        while (linha != null &&
               !Restaurante.igual(
                   linha,
                   "FIM")) {

            boolean resp =
                arvore.pesquisar(linha);

            if (resp) {

                System.out.println("SIM");

            } else {

                System.out.println("NAO");
            }

            linha = br.readLine();
        }

        arvore.caminharCentral();

        br.close();
    }
}