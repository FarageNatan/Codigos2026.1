package PucMinas.TrabalhoPratico.TP02;

class Data{
    int ano;
    int mes;
    int dia;
}

class Hora{
    int hora;
    int minuto;

    public Hora(int h, int min){
        if(h < 0 || h > 23 || min < 0 || min > 59){
            System.out.println("Valor de hora ou minuto invalido");
        }else{
            hora = h;
            minuto = min;
        }
    }

    public Hora(){
        hora = 0;
        minuto = 0;
    }

}


class Restaurante{
    int id;
    String nome;
    String cidade;
    int capacidade;
    double avaliacao;
    String[] tiposCozinha;
    int faixaPreco;

}


public class Main {



}
