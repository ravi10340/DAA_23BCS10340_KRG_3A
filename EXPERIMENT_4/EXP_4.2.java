// Circular Linked List (CLL)

import java.util.Scanner;

class CNode {
    int data;
    CNode next;

    CNode(int data) {
        this.data = data;
        this.next = null;
    }
}

public class CircularLinkedList {
    static CNode head = null;
    static Scanner sc = new Scanner(System.in);

    static void insertBegin(int val) {
        CNode newNode = new CNode(val);
        if (head == null) {
            head = newNode;
            newNode.next = head;
            return;
        }
        CNode temp = head;
        while (temp.next != head) temp = temp.next;
        newNode.next = head;
        temp.next = newNode;
        head = newNode;
    }

    static void insertEnd(int val) {
        CNode newNode = new CNode(val);
        if (head == null) {
            head = newNode;
            newNode.next = head;
            return;
        }
        CNode temp = head;
        while (temp.next != head) temp = temp.next;
        temp.next = newNode;
        newNode.next = head;
    }

    static void deleteBegin() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        if (head.next == head) {
            head = null;
            System.out.println("Deleted last node.");
            return;
        }
        CNode temp = head;
        while (temp.next != head) temp = temp.next;
        head = head.next;
        temp.next = head;
        System.out.println("Deleted from beginning.");
    }

    static void deleteEnd() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        if (head.next == head) {
            head = null;
            System.out.println("Deleted last node.");
            return;
        }
        CNode temp = head;
        while (temp.next.next != head) temp = temp.next;
        temp.next = head;
        System.out.println("Deleted from end.");
    }

    static void display() {
        if (head == null) {
            System.out.println("List is empty!");
            return;
        }
        CNode temp = head;
        System.out.print("Circular Linked List: ");
        do {
            System.out.print(temp.data + " ");
            temp = temp.next;
        } while (temp != head);
        System.out.println();
    }

    public static void main(String[] args) {
        int choice, val;
        do {
            System.out.println("\n--- Circular Linked List Menu ---");
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
