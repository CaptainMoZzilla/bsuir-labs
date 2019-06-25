import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Read from: \n1)Keyboard\n2)File\n3)Close\n");


        ArrayList<ArrayList<Double>> matrix = new ArrayList<>();

        switch (sc.nextInt()) {
            case 1:
                System.out.println("Enter n: ");
                int rows = sc.nextInt();
                System.out.println("Enter m: ");
                int columns = sc.nextInt();

                for (int a = 0; a < rows; a++)
                    matrix.add(new ArrayList<Double>());

                System.out.println("Enter coefficients: ");
                for (ArrayList<Double> temp : matrix) {
                    for (int a = 0; a < columns; a++) {
                        temp.add(sc.nextDouble());
                    }
                }
            break;

            case 2:
                matrix = new ArrayList<>(Arrays.asList(
                        new ArrayList<Double>(Arrays.asList(4.855, 1.239, 0.272, 0.258, 1.192)),
                        new ArrayList<Double>(Arrays.asList(1.491, 4.954, 0.124, 0.236, 0.256)),
                        new ArrayList<Double>(Arrays.asList(0.456, 0.285, 4.354, 0.254, 0.852)),
                        new ArrayList<Double>(Arrays.asList(0.412, 0.335, 0.158, 2.874, 0.862))));

            break;

            default:
                return;
        }


        System.out.println("Before transformation:\u001B[34m");
        Gauss.showMatrix(matrix);


        ArrayList<ArrayList<Double>> triangleMatrix = Gauss.toTriangleMatrix(Gauss.cloneMatrix(matrix));
        System.out.println("\n\u001B[0mTriangle matrix:\u001B[34m");
        Gauss.showMatrix(triangleMatrix);


        ArrayList<Double> roots = Gauss.findRoots(triangleMatrix);

        if (Gauss.calculateDeterminant(triangleMatrix) == 0d ) {
            System.out.println("Нет решений");
            return;
        }
        System.out.println("\n\u001B[0mRoots:");
        roots.forEach(e -> System.out.println(e));

        triangleMatrix.stream().forEach(e -> e.remove(e.size() - 1));

        Double determinant = Gauss.calculateDeterminant(triangleMatrix);

        ArrayList<ArrayList<Double>> invertMatrix = Gauss.transposeMatrix(Gauss.matrixOfAlgebraicComponents(triangleMatrix));
        Gauss.invertMatrix(invertMatrix, determinant);

        System.out.println("\n\u001B[0mA^(-1):\u001B[34m");
        Gauss.showMatrix(invertMatrix);

        Gauss.calcError(matrix, roots, invertMatrix);
    }
}
