package PucMinas.CodigosLab.LabBicolor;
import java.util.Scanner;


class NoAN{
    int elemento;
    boolean cor;
    NoAN dir;
    NoAN esq;

    public NoAN(int elemento){
        this.elemento = elemento;
        dir = esq = null;
        cor = true;
    }

    public NoAN(){
        elemento = 0;
        dir = esq = null;
        cor = true;
    }

    public boolean isNoTipoQuatro(){
        return (esq != null && dir != null && esq.cor == true && dir.cor == true);
    }
    
}

class ArvoreBicolor{
    NoAN raiz;
    public ArvoreBicolor(){ raiz = null; }
    
    private void fragmentar(NoAN i){
        boolean ehTipoQuatro = i.isNoTipoQuatro();
        if(ehTipoQuatro){
            fragmentar(null, null, null, i);
        }
    }
    
    private void fragmentar(NoAN bisavo, NoAN avo, NoAN pai, NoAN i){
        
    }



}





public class RoteiroBicolor {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);




        sc.close();
    }
}
