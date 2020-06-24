package myPackage;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        RandomWordGenerator object = new RandomWordGenerator();

        String[] wordList = new String[10000];

        for(int i=0; i<10000; i++) {
            wordList[i] = object.getWord();
            /* index of a word(key) is its sequence number of generation to be used as (value) */
        }

        System.out.print("Enter the length of hash table: ");
        int N = scanner.nextInt();

        /* methodOpt = 0(separate chaining)/ 1(double hashing)/ 2(custom hashing) */
        HashTable ht1 = new HashTable(N, 0, true);
        HashTable ht2 = new HashTable(N, 0, false);
        HashTable ht3 = new HashTable(N, 1, true);
        HashTable ht4 = new HashTable(N, 1, false);
        HashTable ht5 = new HashTable(N, 2, true);
        HashTable ht6 = new HashTable(N, 2, false);

        int[] collision = new int[6];
        int[] hits = new int[6];

        for(int i=0; i<6; i++) {
            collision[i] = hits[i] = 0;
        }


        /* inserting words */
        for(int i=0; i<wordList.length; i++) {
            collision[0] += ht1.insert(wordList[i], i+1);
            collision[1] += ht2.insert(wordList[i], i+1);
            collision[2] += ht3.insert(wordList[i], i+1);
            collision[3] += ht4.insert(wordList[i], i+1);
            collision[4] += ht5.insert(wordList[i], i+1);
            collision[5] += ht6.insert(wordList[i], i+1);
        }


        /* searching words */
        for(int i=0; i<10000; i+=5) {
            hits[0] += ht1.search(wordList[i]);
            hits[1] += ht2.search(wordList[i]);
            hits[2] += ht3.search(wordList[i]);
            hits[3] += ht4.search(wordList[i]);
            hits[4] += ht5.search(wordList[i]);
            hits[5] += ht6.search(wordList[i]);
        }


        /* process the report */
        System.out.println("\n");

        System.out.println("Hash1:");
        System.out.println("for Chaining Method: #Collision = " + collision[0] + "/ Average Hit = " + hits[0]/1000.0);
        System.out.println("for Double Hashing: #Collision = " + collision[2] + "/ Average Hit = " + hits[2]/1000.0);
        System.out.println("for Custom Hashing: #Collision = " + collision[4] + "/ Average Hit = " + hits[4]/1000.0);

        System.out.println("");

        System.out.println("Hash2:");
        System.out.println("for Chaining Method: #Collision = " + collision[1] + "/ Average Hit = " + hits[1]/1000.0);
        System.out.println("for Double Hashing: #Collision = " + collision[3] + "/ Average Hit = " + hits[3]/1000.0);
        System.out.println("for Custom Hashing: #Collision = " + collision[5] + "/ Average Hit = " + hits[5]/1000.0);

        return ;
    }
}
