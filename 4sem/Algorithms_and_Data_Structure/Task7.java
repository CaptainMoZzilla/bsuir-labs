import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int n, m, x1, y1, x2, y2;
        Scanner scanner = new Scanner(System.in);


        n = scanner.nextInt();
        m = scanner.nextInt();

        x1 = scanner.nextInt();
        y1 = scanner.nextInt();
        x2 = scanner.nextInt();
        y2 = scanner.nextInt();

        if (x1 - x2 == y1 - y2 || x1 - x2 == -(y1 -y2))
            System.out.println("NO");
        else
            System.out.println("YES");

    }
}
