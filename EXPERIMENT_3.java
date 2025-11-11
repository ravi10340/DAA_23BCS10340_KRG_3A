// Find frequency of elements in a given array in O(n)

import java.util.*;

public class FrequencyOfElements {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements in the array: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.print("Enter elements in the array: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        LinkedHashMap<Integer, Integer> freq = new LinkedHashMap<>();

        for (int elmnt : arr) {
            freq.put(elmnt, freq.getOrDefault(elmnt, 0) + 1);
        }

        System.out.println("\nFrequency of elements:");
        for (Map.Entry<Integer, Integer> entry : freq.entrySet()) {
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
    }
}
