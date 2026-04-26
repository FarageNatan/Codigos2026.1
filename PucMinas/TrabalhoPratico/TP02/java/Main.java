//package PucMinas.TrabalhoPratico.TP02.java;

import java.io.IOException;
import java.util.Scanner;
import java.io.File;

class Data {
    private int ano;
    private int mes;
    private int dia;

    public Data(int ano, int mes, int dia) {
        this.ano = ano;
        this.mes = mes;
        this.dia = dia;
    }

    public Data() {
        ano = 0;
        mes = 0;
        dia = 0;
    }

    public int getAno() { return ano; }
    public int getMes() { return mes; }
    public int getDia() { return dia; }

    public void setAno(int ano) { this.ano = ano; }
    public void setMes(int mes) { this.mes = mes; }
    public void setDia(int dia) { this.dia = dia; }

    // Retorna a data no formato DD/MM/YYYY — usando apenas format
    public String formatar() {
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }

    // Converte "YYYY-MM-DD" para Data — usando apenas charAt e length
    public static Data parseData(String s) {
        Data dataResultado = null;

        if (s != null && s.length() == 10) {
            int ano = 0;
            int mes = 0;
            int dia = 0;

            ano += (s.charAt(0) - '0') * 1000;
            ano += (s.charAt(1) - '0') * 100;
            ano += (s.charAt(2) - '0') * 10;
            ano += (s.charAt(3) - '0');

            mes += (s.charAt(5) - '0') * 10;
            mes += (s.charAt(6) - '0');

            dia += (s.charAt(8) - '0') * 10;
            dia += (s.charAt(9) - '0');

            dataResultado = new Data(ano, mes, dia);
        }

        return dataResultado;
    }
}

class Hora {
    private int hora;
    private int minuto;

    public Hora(int h, int min) {
        if (h < 0 || h > 23 || min < 0 || min > 59) {
            System.out.println("Valor de hora ou minuto invalido");
        } else {
            hora = h;
            minuto = min;
        }
    }

    public Hora() {
        hora = 0;
        minuto = 0;
    }

    public int getHora()   { return hora; }
    public int getMinuto() { return minuto; }

    public void setHora(int hora)     { this.hora = hora; }
    public void setMinuto(int minuto) { this.minuto = minuto; }

    // Retorna a hora no formato HH:mm — usando apenas format
    public String formatar() {
        return String.format("%02d:%02d", hora, minuto);
    }

    // Converte "HH:mm" para Hora — usando apenas charAt e length
    public static Hora parseHora(String s) {
        Hora resultado = null;

        if (s != null && s.length() == 5) {
            int hora   = (s.charAt(0) - '0') * 10 + (s.charAt(1) - '0');
            int minuto = (s.charAt(3) - '0') * 10 + (s.charAt(4) - '0');
            resultado  = new Hora(hora, minuto);
        }

        return resultado;
    }
}


class Restaurante {
    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinha;
    private int faixaPreco;
    private Hora horarioAbertura;
    private Hora horarioFechamento;
    private Data dataAbertura;
    private Boolean aberto;

    public Restaurante(int id, String nome, String cidade, int capacidade, double avaliacao,
                       String[] tiposCozinha, int faixaPreco,
                       Hora horarioAbertura, Hora horarioFechamento,
                       Data dataAbertura, Boolean aberto) {
        this.id                = id;
        this.nome              = nome;
        this.cidade            = cidade;
        this.capacidade        = capacidade;
        this.avaliacao         = avaliacao;
        this.tiposCozinha      = tiposCozinha;
        this.faixaPreco        = faixaPreco;
        this.horarioAbertura   = horarioAbertura;
        this.horarioFechamento = horarioFechamento;
        this.dataAbertura      = dataAbertura;
        this.aberto            = aberto;
    }

    
    public int      getId()                { return id; }
    public String   getNome()              { return nome; }
    public String   getCidade()            { return cidade; }
    public int      getCapacidade()        { return capacidade; }
    public double   getAvaliacao()         { return avaliacao; }
    public String[] getTiposCozinha()      { return tiposCozinha; }
    public int      getFaixaPreco()        { return faixaPreco; }
    public Hora     getHorarioAbertura()   { return horarioAbertura; }
    public Hora     getHorarioFechamento() { return horarioFechamento; }
    public Data     getDataAbertura()      { return dataAbertura; }
    public Boolean  getAberto()            { return aberto; }

    // Formato: [id ## nome ## cidade ## capacidade ## avaliacao ## [tipos] ## faixaPreco ## HH:mm-HH:mm ## DD/MM/YYYY ## aberto]
    public String formatar() {
        String tipos = "[";
        for (int i = 0; i < tiposCozinha.length; i++) {
            tipos = tipos + tiposCozinha[i];
            if (i < tiposCozinha.length - 1) {
                tipos = tipos + ",";
            }
        }
        tipos = tipos + "]";
        String preco = "";
        for (int i = 0; i < faixaPreco; i++) {
            preco = preco + "$";
        }

        return String.format("[%d ## %s ## %s ## %d ## %.1f ## %s ## %s ## %s-%s ## %s ## %b]",
            id,
            nome,
            cidade,
            capacidade,
            avaliacao,
            tipos,
            preco,
            horarioAbertura.formatar(),
            horarioFechamento.formatar(),
            dataAbertura.formatar(),
            aberto);
    }

    // Conta '$' na string para determinar faixa de preco (1 a 4)
    public static int converteFaixaPreco(String s) {
        int novaFaixa = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '$') {
                novaFaixa++;
            }
        }

        return novaFaixa;
    }

    // Divide uma string pelo separador
    public static String[] divideCampo(String s, char separador) {
        int count = 1;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == separador) {
                count++;
            }
        }

        String[] partes = new String[count];
        int indice = 0;
        int inicio = 0;

        for (int i = 0; i <= s.length(); i++) {
            boolean fimString   = (i == s.length());
            boolean ehSeparador = !fimString && s.charAt(i) == separador;

            if (fimString || ehSeparador) {
                char[] trecho = new char[i - inicio];
                for (int j = inicio; j < i; j++) {
                    trecho[j - inicio] = s.charAt(j);
                }
                partes[indice] = new String(trecho);
                indice++;
                inicio = i + 1;
            }
        }

        return partes;
    }

    // Converte "true"/"false" para booleano
    public static boolean converteBooleano(String s) {
        return s.compareTo("true") == 0;
    }

    // Converte string numerica inteira para int
    public static int converteInteiro(String s) {
        int resultado = 0;

        for (int i = 0; i < s.length(); i++) {
            resultado = resultado * 10 + (s.charAt(i) - '0');
        }

        return resultado;
    }

    // Converte string decimal para double
    public static double converteDouble(String s) {
        int pontoPos = -1;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '.') {
                pontoPos = i;
            }
        }

        double resultado = 0;

        if (pontoPos == -1) {
            resultado = converteInteiro(s);
        } else {
            for (int i = 0; i < pontoPos; i++) {
                resultado = resultado * 10 + (s.charAt(i) - '0');
            }
            double fator = 0.1;
            for (int i = pontoPos + 1; i < s.length(); i++) {
                resultado += (s.charAt(i) - '0') * fator;
                fator /= 10;
            }
        }

        return resultado;
    }

    // Lê uma linha CSV e retorna um Restaurante
    public static Restaurante lerRestaurante(String linha) {
        String[] campos = divideCampo(linha, ',');

        int      id           = converteInteiro(campos[0]);
        String   nome         = campos[1];
        String   cidade       = campos[2];
        int      capacidade   = converteInteiro(campos[3]);
        double   avaliacao    = converteDouble(campos[4]);
        String[] tiposCozinha = divideCampo(campos[5], ';');
        int      faixaPreco   = converteFaixaPreco(campos[6]);
        String[] horario      = divideCampo(campos[7], '-');
        Hora     abertura     = Hora.parseHora(horario[0]);
        Hora     fechamento   = Hora.parseHora(horario[1]);
        Data     dataAbertura = Data.parseData(campos[8]);
        boolean  aberto       = converteBooleano(campos[9]);

        return new Restaurante(id, nome, cidade, capacidade, avaliacao, tiposCozinha, faixaPreco, abertura, fechamento, dataAbertura, aberto);
    }
}


class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes(int tamanho) {
        this.tamanho      = tamanho;
        this.restaurantes = new Restaurante[tamanho];
    }

    // Retorna a quantidade de restaurantes da coleção
    public int getTamanho() { return tamanho; }

    // Retorna o arranjo com os restaurantes (ponteiros) da coleção
    public Restaurante[] getRestaurantes() { return restaurantes; }

    // Conta as linhas de dados no CSV (descontando o cabeçalho)
    private static int contarLinhas(String caminho) throws IOException {
        Scanner scanner = new Scanner(new File(caminho));
        int total = 0;

        scanner.nextLine();

        while (scanner.hasNextLine()) {
            scanner.nextLine();
            total++;
        }

        scanner.close();
        return total;
    }

    // Lê o arquivo CSV, cria os restaurantes e configura a coleção
    public void lerCsv(String path) throws IOException {
        int total = contarLinhas(path);
        this.tamanho = total;
        this.restaurantes = new Restaurante[total];

        Scanner scanner = new Scanner(new File(path));
        scanner.nextLine();

        int i = 0;
        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            restaurantes[i] = Restaurante.lerRestaurante(linha);
            i++;
        }

        scanner.close();
    }

    // Lê o dataset do arquivo CSV e retorna a coleção com os restaurantes
    public static ColecaoRestaurantes lerCsv() throws IOException {
        ColecaoRestaurantes colecao = new ColecaoRestaurantes(0);
        //colecao.lerCsv("./PucMinas/TrabalhoPratico/TP02/dataset/restaurantes.csv");
        colecao.lerCsv("/tmp/restaurantes.csv");
        return colecao;
    }
}


public class Main {

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Restaurante[] restaurantes = colecao.getRestaurantes();

        int id = sc.nextInt();
 
        while (id != -1) {
            for (int i = 0; i < colecao.getTamanho(); i++) {
                if (restaurantes[i].getId() == id) {
                    System.out.println(restaurantes[i].formatar());
                }
            }
            id = sc.nextInt();
        }

        sc.close();
    }
}