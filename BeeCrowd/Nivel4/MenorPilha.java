package Nivel4;

import java.io.IOException;
import java.util.Scanner;
 
class Celula{
    int elemento;
    Celula prox;
    
    public Celula(int elemento){
        this.elemento = elemento;
        prox = null;
    }
}
 
class Pilha{
    Celula topo;
    
    public Pilha(){
        topo = null;
    }
    
    public void push(int elemento){
        if(topo != null){
            Celula tmp = new Celula(elemento);
            tmp.prox = topo;
            topo = tmp;
        }else{
            topo = new Celula(elemento);
        }
    }
    
    public int pop(){
        int resp = 0;
        if(topo != null){
            Celula tmp = topo.prox;
            resp = topo.elemento;
            topo.prox = null;
            topo = tmp;
            tmp = null;
        }else{
            System.out.println("EMPTY");
        }
        return resp;
    }
    
    public int min(){
        int menor = 0;
        if(topo != null){
            Celula i = topo;
            menor = topo.elemento;
            while(i != null){
                if(menor > i.elemento){
                    menor = i.elemento;
                }
                i = i.prox;
            }
        }else{
            System.out.println("EMPTY");
        }
        return menor;
    }
}
 
public class MenorPilha {
 
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        int operacoes = sc.nextInt();
        int i = 0;
        int num = 0;
        Pilha p = new Pilha();
        while(i < operacoes){
            String op = sc.next();
            if(op.equals("PUSH")){
                num = sc.nextInt();
                p.push(num);
            }else if(op.equals("POP")){
                num = p.pop();
            }else if(op.equals("MIN")){
                int min = p.min();
                System.out.println(min);
            }
            i++;
        }
        sc.close();
    }
 
}




