// Doubly Linked List (DLL)

import java.util.Scanner;

class Node {
    int data;
    Node prev, next;

    Node(int data) {
        this.data = data;
        this.prev = null;
        this.next = null;
    }
}

public class DoublyLinkedList {
    static Node head = null;
    static Scanner sc = new Scanner(System.in);

    static void insertBegin(int val) {
        Node newNode = new Node(val);
        if (head != null) {
            newNode.next = head;
            head.prev = newNode;
        }
        head = newNode;
    }

    static void insertEnd(int val) {
        Node newNode = new Node(val);
        if (head == null) {
            head = newNode;
            return;
        }
        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = newNode;
        newNode.prev = temp;
    }

    static void deleteBegin() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        head = head.next;
        if (head != null) head.prev = null;
        System.out.println("Deleted from beginning.");
    }

    static void deleteEnd() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        if (head.next == null) {
            head = null;
            System.out.println("Deleted from end.");
            return;
        }
        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.prev.next = null;
        System.out.println("Deleted from end.");
    }

    static void display() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        Node temp = head;
        System.out.print("Doubly Linked List: ");
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int choice, val;
        do {
            System.out.println("\n--- Doubly Linked List Menu ---");
            System.out.println("1. Insert at Beginning");
            System.out.println("2. Insert at End");
            System.out.println("3. Delete at Beginning");
            System.out.println("4. Delete at End");
            System.out.println("5. Display");
            System.out.println("6. Exit");
            System.out.print("Enter choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1 -> {
                    System.out.print("Enter value: ");
                    val = sc.nextInt();
                    insertBegin(val);
                }
                case 2 -> {
                    System.out.print("Enter value: ");
                    val = sc.nextInt();
                    insertEnd(val);
                }
                case 3 -> deleteBegin();
                case 4 -> deleteEnd();
                case 5 -> display();
                case 6 -> System.out.println("Exiting...");
                default -> System.out.println("Invalid choice!");
            }
        } while (choice != 6);
    }
}
