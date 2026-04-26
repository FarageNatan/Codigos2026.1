//package PucMinas.TrabalhoPratico.TP02;

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

    
    public int comparar(Data outra) {
        int resultado = ano - outra.ano;

        if (resultado == 0) {
            resultado = mes - outra.mes;
        }

        if (resultado == 0) {
            resultado = dia - outra.dia;
        }

        return resultado;
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

    public void ordenarPorCidade() {
        for (int i = 1; i < tamanho; i++) {
            Restaurante chave = restaurantes[i];
            int j = i - 1;

            while (j >= 0 && (
                restaurantes[j].getCidade().compareTo(chave.getCidade()) > 0 ||
                (restaurantes[j].getCidade().compareTo(chave.getCidade()) == 0 &&
                 restaurantes[j].getId() > chave.getId())
            )) {
                restaurantes[j + 1] = restaurantes[j];
                j = j - 1;
            }

            restaurantes[j + 1] = chave;
        }
    }

    private void intercalar(int inicio, int meio, int fim) {
        Restaurante[] aux = new Restaurante[fim - inicio + 1];

        int esq = inicio;
        int dir = meio + 1;
        int k   = 0;

        while (esq <= meio && dir <= fim) {
            int cmpCidade = restaurantes[esq].getCidade().compareTo(restaurantes[dir].getCidade());
            int cmpNome   = restaurantes[esq].getNome().compareTo(restaurantes[dir].getNome());

            boolean escolheEsq = cmpCidade < 0 || (cmpCidade == 0 && cmpNome <= 0);

            if (escolheEsq) {
                aux[k] = restaurantes[esq];
                esq++;
            } else {
                aux[k] = restaurantes[dir];
                dir++;
            }
            k++;
        }

        while (esq <= meio) {
            aux[k] = restaurantes[esq];
            esq++;
            k++;
        }

        while (dir <= fim) {
            aux[k] = restaurantes[dir];
            dir++;
            k++;
        }

        for (int i = 0; i < aux.length; i++) {
            restaurantes[inicio + i] = aux[i];
        }
    }

    private void mergesort(int inicio, int fim) {
        if (inicio < fim) {
            int meio = (inicio + fim) / 2;
            mergesort(inicio, meio);
            mergesort(meio + 1, fim);
            intercalar(inicio, meio, fim);
        }
    }

    public void ordenarPorCidadeMergesort() {
        mergesort(0, tamanho - 1);
    }
    
    private void heapify(int n, int i) {
        int maior = i;
        int esq   = 2 * i + 1;
        int dir   = 2 * i + 2;

        if (esq < n) {
            int cmpData = restaurantes[esq].getDataAbertura().comparar(restaurantes[maior].getDataAbertura());
            int cmpNome = restaurantes[esq].getNome().compareTo(restaurantes[maior].getNome());

            if (cmpData > 0 || (cmpData == 0 && cmpNome > 0)) {
                maior = esq;
            }
        }

        if (dir < n) {
            int cmpData = restaurantes[dir].getDataAbertura().comparar(restaurantes[maior].getDataAbertura());
            int cmpNome = restaurantes[dir].getNome().compareTo(restaurantes[maior].getNome());

            if (cmpData > 0 || (cmpData == 0 && cmpNome > 0)) {
                maior = dir;
            }
        }

        if (maior != i) {
            Restaurante temp    = restaurantes[i];
            restaurantes[i]     = restaurantes[maior];
            restaurantes[maior] = temp;

            heapify(n, maior);
        }
    }

    public void ordenarPorDataAberturaHeapsort() {
        // Fase 1: constrói o heap máximo
        for (int i = tamanho / 2 - 1; i >= 0; i--) {
            heapify(tamanho, i);
        }

        for (int i = tamanho - 1; i > 0; i--) {
            Restaurante temp  = restaurantes[0];
            restaurantes[0]   = restaurantes[i];
            restaurantes[i]   = temp;

            heapify(i, 0);
        }
    }

    public boolean pesquisaSequencialPorNome(String nome) {
        boolean encontrado = false;

        for (int i = 0; i < tamanho; i++) {
            if (restaurantes[i].getNome().compareTo(nome) == 0) {
                encontrado = true;
            }
        }

        return encontrado;
    }

    public Restaurante buscarPorId(int id) {
        Restaurante encontrado = null;
 
        for (int i = 0; i < tamanho; i++) {
            if (restaurantes[i].getId() == id) {
                encontrado = restaurantes[i];
            }
        }
 
        return encontrado;
    }
}

class Lista {
    private int tamanho;
    private Restaurante[] lista;
 
    public Lista(int capacidade) {
        this.tamanho = 0;
        this.lista   = new Restaurante[capacidade];
    }
 
    public int getTamanho() { return tamanho; }
 
    // Insere na primeira posição, deslocando os demais para a direita
    public void inserirInicio(Restaurante restaurante) {
        for (int i = tamanho; i > 0; i--) {
            lista[i] = lista[i - 1];
        }
        lista[0] = restaurante;
        tamanho++;
    }
 
    // Insere na posição informada, deslocando os demais para a direita
    public void inserir(Restaurante restaurante, int posicao) {
        for (int i = tamanho; i > posicao; i--) {
            lista[i] = lista[i - 1];
        }
        lista[posicao] = restaurante;
        tamanho++;
    }
 
    // Insere na última posição
    public void inserirFim(Restaurante restaurante) {
        lista[tamanho] = restaurante;
        tamanho++;
    }
 
    // Remove e retorna o primeiro registro, deslocando os demais para a esquerda
    public Restaurante removerInicio() {
        Restaurante removido = lista[0];
        for (int i = 0; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
        return removido;
    }
 
    // Remove e retorna o registro na posição informada, deslocando os demais
    public Restaurante remover(int posicao) {
        Restaurante removido = lista[posicao];
        for (int i = posicao; i < tamanho - 1; i++) {
            lista[i] = lista[i + 1];
        }
        tamanho--;
        return removido;
    }
 
    // Remove e retorna o último registro
    public Restaurante removerFim() {
        tamanho--;
        return lista[tamanho];
    }
 
    // Retorna o restaurante na posição i
    public Restaurante getRestaurante(int i) { return lista[i]; }
 
    // Busca um restaurante pelo id e retorna sua referência (null se não encontrado)
    public Restaurante buscarPorId(int id) {
        Restaurante encontrado = null;
 
        for (int i = 0; i < tamanho; i++) {
            if (lista[i].getId() == id) {
                encontrado = lista[i];
            }
        }
 
        return encontrado;
    }
}

class FilaCircular {
    private int CAPACIDADE = 5;
    private Restaurante[] fila;
    private int inicio;   
    private int fim;      
    private int tamanho;  
 
    public FilaCircular() {
        this.fila    = new Restaurante[CAPACIDADE];
        this.inicio  = 0;
        this.fim     = 0;
        this.tamanho = 0;
    }
 
    public int getTamanho()    { return tamanho; }
    public boolean estaCheia() { return tamanho == CAPACIDADE; }
    public boolean estaVazia() { return tamanho == 0; }
 
    public Restaurante getRestaurante(int i) {
        return fila[(inicio + i) % CAPACIDADE];
    }
 
    public Restaurante remover() {
        Restaurante removido = fila[inicio];
        inicio  = (inicio + 1) % CAPACIDADE;
        tamanho--;
        return removido;
    }

    public void inserir(Restaurante restaurante) {
        if (estaCheia()) {
            Restaurante removido = remover();
            System.out.println("(R)" + removido.getNome());
        }
        fila[fim]  = restaurante;
        fim        = (fim + 1) % CAPACIDADE;
        tamanho++;
    }
 
    public int mediaAnoAbertura() {
        int soma = 0;
        for (int i = 0; i < tamanho; i++) {
            soma += getRestaurante(i).getDataAbertura().getAno();
        }
        return Math.round((float) soma / tamanho);
    }
}

public class Main {
 
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Restaurante[] todos = colecao.getRestaurantes();
 
        // ── Parte 1: lê IDs e insere ao final da Fila ──────────────────
        FilaCircular fila = new FilaCircular();
 
        int id = sc.nextInt();
        sc.nextLine();
        while (id != -1) {
            for (int i = 0; i < colecao.getTamanho(); i++) {
                if (todos[i].getId() == id) {
                    fila.inserir(todos[i]);
                    System.out.println("(I)" + fila.mediaAnoAbertura());
                }
            }
            id = sc.nextInt();
            sc.nextLine();
        }
 
        // ── Parte 2: lê e processa comandos I e R ──────────────────────
        int n = sc.nextInt();
        sc.nextLine();
 
        for (int i = 0; i < n; i++) {
            String linha    = sc.nextLine();
            String[] partes = Restaurante.divideCampo(linha, ' ');
            String comando  = partes[0];
 
            if (comando.compareTo("I") == 0) {
                int idInserir = Restaurante.converteInteiro(partes[1]);
                Restaurante r = colecao.buscarPorId(idInserir);
                fila.inserir(r);
                System.out.println("(I)" + fila.mediaAnoAbertura());
 
            } else if (comando.compareTo("R") == 0) {
                Restaurante removido = fila.remover();
                System.out.println("(R)" + removido.getNome());
            }
        }
 
        // ── Saída final: fila do primeiro ao último ─────────────────────
        for (int i = 0; i < fila.getTamanho(); i++) {
            System.out.println(fila.getRestaurante(i).formatar());
        }
 
        sc.close();
    }
}