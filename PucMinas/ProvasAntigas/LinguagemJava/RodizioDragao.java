package PucMinas.ProvasAntigas.LinguagemJava;

import java.util.Scanner;

class Fila{
    String[] array;
    int n;

    public Fila(){
        array = new String[1000]; //Capacidade máxima da fila
        n = 0; //Dragoes na fila
    }

    public Fila(int tam){
        array = new String[tam];
        n = 0;
    }

    public void inserirFim(String nome){
        if(n >= array.length){
            //Fila cheia o dragao nao entra
        }else{  
            array[n] = nome;
            n++;
        }
    }

    public String removerInicio(){
        String resp = "Vazio";
        if(n > 0){
            resp = array[0];
            
            for(int i = 1; i < n; i++){
                array[i - 1] = array[i];
            }
            
            n--;
        }
        return resp;
    }

    public void mostrar(){
        for(int i = 0; i < n; i++){
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }
}

public class RodizioDragao {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int capacidade = sc.nextInt();
        int numEventos = sc.nextInt();
        
        Fila fila = new Fila(capacidade);
        int i = 0;
        while(i < numEventos){
            char eventos = sc.next().charAt(0);
            if(eventos == 'E'){
                fila.inserirFim(sc.next());
            }else if(eventos == 'V'){
                fila.removerInicio();
            }else if(eventos == 'B'){
                fila.mostrar();
            }
            i++;
        }  
        fila.mostrar();
        sc.close();
    }
}
