import java.util.Scanner;

public class EstacionamentoBizarro {

    public static class Motorista{
        private int ci;
        private int si;

        public void setCi(int ci){
            this.ci = ci;
        }

        public void setSi(int si){
            this.si = si;
        }

        public int getCi(){
            return ci;
        }

        public int getSi(){
            return si;
        }
    }

    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        
        while(sc.hasNextLine()){
            int N = sc.nextInt();
            int K = sc.nextInt();
            Motorista motoristas[] = new Motorista[N];
            boolean resp = true;

            if(!(N == K && K == 0)){
                for(int i = 0; i < N; i++){
                    motoristas[i] = new Motorista();
                    motoristas[i].setCi(sc.nextInt());
                    motoristas[i].setSi(sc.nextInt());
                    int tam = 0;

                    if(i >= 1 && resp == true){
                        for(int j = i - 1; j >= 0; j--){
                            if(motoristas[j].getSi() > motoristas[i].getCi()){tam++;}
                            if(tam == K || (motoristas[i].getCi() < motoristas[j].getSi() && motoristas[i].getSi() > motoristas[j].getSi())){resp = false;}
                        }
                    }

                }

                if(resp == true){System.out.println("Sim");}
                else{System.out.println("Nao");}
            }
        }

        sc.close();
    }
}