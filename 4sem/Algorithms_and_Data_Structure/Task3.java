import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Scanner;

public class Main {

    static final long mod = 1000000007;

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        int n, k;

        n = scanner.nextInt();
        k = scanner.nextInt();

        ArrayList<Long> arrayList = new ArrayList<>(n);

        while (n-- != 0) {
            arrayList.add(scanner.nextLong());
        }

        Collections.sort(arrayList);

        long current = 1, temp;
        int i = 0, j = arrayList.size() - 1;


        if (k % 2 != 0) {
            current *= arrayList.get(arrayList.size() - 1) % mod;
            j--;
            k--;
        }

        long left, right;

        while (k != 0) {
            left = arrayList.get(i) * arrayList.get(i + 1);
            right = arrayList.get(j) * arrayList.get(j - 1);
            if (left > right && current > 0 || left <= right && current <= 0 ) {
                    current *= left % mod;
                    current %= mod;

                    i += 2;
            } else {
                current *= right % mod;
                current %= mod;

                j -= 2;
            }
            k -= 2;
        }

        if (current >= 0)
            System.out.println(current);
        else
            System.out.println(current + mod);
    }
}
