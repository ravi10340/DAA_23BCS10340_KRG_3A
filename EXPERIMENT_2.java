// Power function in O(log n) time complexity

import java.util.Scanner;

public class PowerFunction {

    static int power(int x, int y) {
        int result = 1;

        while (y > 0) {
            if (y % 2 == 1) {
                result *= x;
            }
            x = x * x;
            y = y / 2;
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter Base value: ");
        int base = sc.nextInt();

        System.out.print("Enter Exponent value: ");
        int exponent = sc.nextInt();

        int ans = power(base, exponent);

        System.out.println("Result (base^exponent): " + ans);
    }
}
