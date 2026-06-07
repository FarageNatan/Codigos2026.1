package Java;

class No{
    int elemento;
    No dir;
    No esq;

    public No(int elemento){
        this.elemento = elemento;
        esq = dir = null;
    }

    public No(){
        elemento = -1;
        esq = dir = null;
    }
}

class Arvore{
    No raiz;

    public Arvore(){
        raiz = null;
    }

    public void inserir(int x)throws Exception{
        raiz = inserirRec(x, raiz);
    }

    public No inserirRec(int x, No i) throws Exception{
        if(i == null){
            i = new No(x);
        }else if(x > i.elemento){
            i.dir = inserirRec(x, i.dir);
        }else if(x < i.elemento){
            i.esq = inserirRec(x, i.esq);
        }else{
            throw new Exception("Elemento repetido");
        }
        return i;
    }

    public boolean pesquisar(int x){
        return pesquisarRec(x, raiz);        
    }

    public boolean pesquisarRec(int x, No i){
        boolean resp = false;
        if(i == null){
            resp = false;
        }else if(x == i.elemento){
            resp = true;
        }else if(x > i.elemento){
            resp = pesquisarRec(x, i.dir);
        }else if(x < i.elemento){
            resp = pesquisarRec(x, i.esq);
        }
        return resp;
    }

    public void caminharPre(No i){
        if(i != null){
            System.out.println(i.elemento);
            caminharPre(i.esq);
            caminharPre(i.dir);
        }
    }

    public void caminharCentral(No i){
        if(i != null){
            caminharCentral(i.esq);
            System.out.println(i.elemento);
            caminharCentral(i.dir);
        }
    }

    public void caminharPos(No i){
        if(i != null){
            caminharPos(i.esq);
            caminharPos(i.dir);
            System.out.println(i.elemento);
        }
    }
}


public class ABP{

    public static void main(String[] args) throws Exception{
        Arvore a = new Arvore();
        
        a.inserir(3);
        a.inserir(1);
        a.inserir(5);
        a.inserir(2);
        a.inserir(4);
        a.inserir(8);
        a.inserir(7);
        a.inserir(6);
        
        a.caminharPre(a.raiz);
        
        boolean encontrou = a.pesquisar(4);
        if(encontrou){
            System.out.println("Achou");
        }else{
            System.out.println("Nao achou");
        }

        boolean opa = a.pesquisar(64);
        if(opa){
            System.out.println("Achou");
        }else{
            System.out.println("Nao achou");
        }

    }

}
