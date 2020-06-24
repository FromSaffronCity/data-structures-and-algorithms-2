package myPackage;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        SplayTree splayTree = new SplayTree();
        Scanner scanner = new Scanner(System.in);

        int choice, keyValue;

        while(true) {
            System.out.println("Options:");
            System.out.println("1. Print Splay Tree");
            System.out.println("2. Search Node");
            System.out.println("3. Insert Node");
            System.out.println("4. Delete Node");
            System.out.println("5. Exit");

            System.out.print("\n" + "Enter choice: ");
            choice = scanner.nextInt();

            if(choice == 5) {
                break;
            } else if(choice == 1) {
                System.out.println("");
                splayTree.print();
                System.out.println("");
            } else if(choice == 2) {
                System.out.print("\n" + "Enter key value: ");
                keyValue = scanner.nextInt();

                if(splayTree.search(keyValue) == true) {
                    System.out.println("Node found" + "\n");
                } else {
                    System.out.println("Node not found" + "\n");
                }
            } else if(choice == 3) {
                System.out.print("\n" + "Enter key value: ");
                keyValue = scanner.nextInt();

                splayTree.insert(keyValue);
                System.out.println("\n");
            } else if(choice == 4) {
                System.out.print("\n" + "Enter key value: ");
                keyValue = scanner.nextInt();

                splayTree.delete(keyValue);
                System.out.println("\n");
            } else {
                System.out.println("\n" + "Invalid Input" + "\n");
            }
        }

        return ;
    }
}
