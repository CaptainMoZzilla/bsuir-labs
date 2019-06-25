import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLUE = "\u001B[34m";

    public static void main(String[] args) {
        ArrayList<ArrayList<Double>> matrix2, matrix, matrix3, inverseMatrix = new ArrayList<>();

        matrix = new ArrayList<>(Arrays.asList(
                new ArrayList<Double>(Arrays.asList(4.855, 1.239, 0.272, 0.258, 1.192)),
                new ArrayList<Double>(Arrays.asList(1.491, 4.954, 0.124, 0.236, 0.256)),
                new ArrayList<Double>(Arrays.asList(0.456, 0.285, 4.354, 0.254, 0.852)),
                new ArrayList<Double>(Arrays.asList(0.412, 0.335, 0.158, 2.874, 0.862))));


        System.out.println(ANSI_BLUE);
        Gauss.showMatrix(matrix);
        System.out.println(ANSI_RESET);

        matrix2 = Gauss.cloneMatrix(matrix);
        matrix3 = Gauss.transposeMatrix(matrix2);
        matrix3 = Matrix.multiply(matrix, matrix3);

        System.out.println("После трансформации" + ANSI_BLUE);
        Gauss.showMatrix(matrix3);


        System.out.println(ANSI_RESET + "\n\nМатрица U: " + ANSI_BLUE);
        ArrayList<ArrayList<Double>> matrixU = Matrix.makeT(matrix3), matrixUT, matrixUTBack;
        Gauss.showMatrix(matrixU);

        matrixUT = Gauss.transposeMatrix(matrixU);
        matrixUTBack = Gauss.cloneMatrix(matrixUT);


        for (int a = 0; a < matrix3.size(); a++) {
            matrixUT.get(a).add(matrix3.get(a).get(matrix3.get(0).size() - 1));
            matrixU.get(a).add(matrix3.get(a).get(matrix3.get(0).size() - 1));
        }


        System.out.println(ANSI_RESET + "\n\nВектор y: " + ANSI_BLUE);
        ArrayList<Double> y = Matrix.calcYVector(matrixUT);
        y.forEach(e -> System.out.println("[ " + e + " ]"));

        for (int a = 0; a < y.size(); a++)
            matrixU.get(a).set(matrixU.get(a).size() - 1, y.get(a));

        System.out.println(ANSI_RESET + "\n\nКорни: ");
        Gauss.findRoots(matrixU).forEach(e -> System.out.print(e + " "));


        matrix2 = Gauss.cloneMatrix(matrix);
        matrix2.forEach(e -> e.remove(e.size() - 1));
        double determinant = Gauss.calculateDeterminant(matrix3);
        System.out.println("\n\nОпределитель матрицы: " + determinant);


        //Обратная
        matrix.forEach(e -> inverseMatrix.add(new ArrayList<>()));

        for (int b = 0 ; b < matrixUTBack.size(); b++) {

            for (int a = 0; a < matrix3.size(); a++) {
                if (a == b) {
                    matrixUT.get(a).set(matrixUT.get(0).size() - 1,1d);
                    matrixU.get(a).set(matrixUT.get(0).size() - 1,1d);
                } else {
                    matrixUT.get(a).set(matrixUT.get(0).size() - 1,0d);
                    matrixU.get(a).set(matrixUT.get(0).size() - 1,0d);
                }
            }
            y = Matrix.calcYVector(matrixUT);

            for (int a = 0; a < y.size(); a++)
                matrixU.get(a).set(matrixU.get(a).size() - 1, y.get(a));

            ArrayList<Double> roots = Gauss.findRoots(matrixU);

            for (int a = 0; a < roots.size(); a++)
                inverseMatrix.get(a).add(roots.get(a));

        }
        System.out.println("\n\nA^-1 :" + ANSI_BLUE);

        Gauss.showMatrix(inverseMatrix);

        System.out.println(ANSI_RESET + "\n\nA^-1 * A :" + ANSI_BLUE);
        Gauss.showMatrix(Matrix.multiply(matrix3, inverseMatrix));

    }
}
