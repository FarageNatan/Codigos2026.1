package PucMinas.Microfundamentos.TADsFlexiveis;

class Celula{
    int elemento;
    Celula prox;

    public Celula(){
        elemento = 0;
        prox = null;
    }

    public Celula(int x){
        elemento = x;
        prox = null; 
    }
}


class Lista{
    Celula primeiro;
    Celula ultimo;

    public Lista(){
        primeiro = ultimo = new Celula();
    }

}



public class MainLista {
    
}
