import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        AVLTree<Integer> tree = new AVLTree<>();

        Random random = new Random();
        ArrayList<Integer> array = new ArrayList<>();


//        for (int a = 0; a < 6; a++) {
//            Integer randomKey = random.nextInt() % 20;
//            array.add(randomKey);
//            tree.push(randomKey);
//        }

        Arrays.asList(1, 5, 2, 4, 7, 6).forEach(e -> {tree.push(e); array.add(e);});

        tree.print();
        System.out.println(tree.find(array.get(0)));


        System.out.println("All elements: ");
        array.forEach(e -> System.out.print(array.indexOf(e) + ":" + e + "  "));

        Scanner scanner = new Scanner(System.in);
        System.out.println("\nLet's removeNode: ");
        tree.remove(array.get(scanner.nextInt()));
        tree.print();

        System.out.println("\nLet's find prev min: ");
        System.out.println(tree.prev(scanner.nextInt()).key);

        System.out.println("\nLet's find next max: ");
        System.out.println(tree.next(scanner.nextInt()).key);

        System.out.println("NLR");
        tree.NLR();

        System.out.println("\nLNR");
        tree.LNR();

        System.out.println("\nLRN");
        tree.LRN();
    }
}
