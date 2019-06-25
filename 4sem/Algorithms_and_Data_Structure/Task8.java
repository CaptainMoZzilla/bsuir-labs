import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        String buffer = scanner.nextLine();

        char[] array = buffer.toCharArray();
        char first = array[0];
        boolean checker = true;



        for (int a = 0; a < buffer.length(); a++) {
            if (first != array[a]) {
                checker = false;
                break;
            }
        }

        if (checker) {
            System.out.println(-1);
            return;
        }
        
        for (int a = 0, b = buffer.length() - 1; a < b; a++, b--){
            if (array[a] != array[b]) {
                System.out.println(buffer.length());
                return;
            }
        }
        System.out.println(buffer.length() - 1);
    }
}
