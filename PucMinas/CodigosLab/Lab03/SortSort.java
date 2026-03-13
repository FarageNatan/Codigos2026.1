package PucMinas.CodigosLab.Lab03;

import java.util.Scanner;

public class SortSort {

    public static void swap(int[] array, int menor, int i){
        int temp = array[menor];
        array[menor] = array[i];
        array[i] = temp;
    }

    public static void ordenaArray(int[] array, int N, int M){
        for(int i = 0; i < N - 1; i++){
            int menor = i;
            for(int j = (i + 1); j < N; j++){
                if(array[menor] % M > array[j] % M){
                    menor = j;
                }else if(array[menor] % M == array[j] % M){
                    menor = desempata(array, menor, j);
                }
            }
            swap(array, menor, i);
        }

    }

    public static int desempata(int[] array, int menor, int j){
        if(array[j]%2==1 && array[menor]%2==0){
			menor = j;
		} else if(array[j]%2==1 && array[menor]%2==1){
			if(array[j] > array[menor]){
				menor = j;
			}
		} else if(array[j]%2==0 && array[menor]%2==0){
			if(array[j] < array[menor]){
				menor = j;
			}
		}
		return menor;
    }

    public static void printarArray(int[] array, int N){
        for(int i = 0; i < N; i++){
            System.out.println(array[i]);
        }
    }

    public static void main(String[]args){
        Scanner sc = new Scanner(System.in);
        
        int N = sc.nextInt();
        int M = sc.nextInt();
        
        while(!(N == 0 && M == 0)){
            
            int[] array = new int[N];
            for(int i = 0; i < N; i++){
                array[i] = sc.nextInt();
            }
            ordenaArray(array, N, M);
            printarArray(array, N);
            N = sc.nextInt();
            M = sc.nextInt();
        }

        sc.close();
    }


}
