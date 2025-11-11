// Naive String Search
import java.util.*;

public class NaiveStringSearch {

    static List<Integer> findOccurrences(String text, String pattern) {
        List<Integer> positions = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        for (int i = 0; i <= n - m; i++) {
            int j;
            for (j = 0; j < m; j++) {
                if (text.charAt(i + j) != pattern.charAt(j))
                    break;
            }
            if (j == m)
                positions.add(i);
        }
        return positions;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter text: ");
        String text = sc.nextLine();

        System.out.print("Enter pattern: ");
        String pattern = sc.nextLine();

        List<Integer> result = findOccurrences(text, pattern);

        if (result.isEmpty())
            System.out.println("Pattern not found");
        else {
            System.out.print("Pattern found at indices: ");
            for (int pos : result)
                System.out.print(pos + " ");
            System.out.println();
        }

        sc.close();
    }
}
