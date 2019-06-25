import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLUE = "\u001B[34m";

    public static void main(String[] args) {
        ArrayList<ArrayList<Double>> matrix2, matrix, matrix3;
        double eps = 0.01;
        Double count = 100d;

        matrix = new ArrayList<>(Arrays.asList(
                                 new ArrayList<Double>(Arrays.asList(-3000d, -1d, -1d, 1000d)),
                                 new ArrayList<Double>(Arrays.asList(-1d, -4000d, -1d, -1000d)),
                                 new ArrayList<Double>(Arrays.asList(-1d, -1d, -5000d, 1000d))));
                             //    new ArrayList<Double>(Arrays.asList(0.412, 0.335, 0.158, 2.874, 0.862))));


        matrix2 = Gauss.cloneMatrix(matrix);

        System.out.println(ANSI_BLUE);
        Gauss.showMatrix(matrix2);
        Seidel.toSIMForm(matrix2);
        System.out.println(ANSI_RESET);


        System.out.println("\n\nПосле преобразований" + ANSI_BLUE);
        Gauss.showMatrix(matrix2);
        matrix3 = Gauss.cloneMatrix(matrix2);

        Double normB = Seidel.calcMatrixNorm(matrix2);

        if (normB < 1d) {
            System.out.println(ANSI_GREEN + "\n\nУсловия сходимости метода простых итераций выполнены" + ANSI_RESET);
            System.out.println("Норма матрицы: " + normB + " < 1");
            count = Math.log((1 - normB) * eps / Seidel.calcVectorNorm(matrix))/ Math.log(normB);

            System.out.println("Кол-во итераций: >= " + count);

            System.out.println("\nКорни:");
            Seidel.SIM(matrix2, count.intValue() + 1).forEach(e -> System.out.print(e + "   "));

        }
        else
            System.out.println(ANSI_RED + "\n\nНе удовлетворяет условиям сходимости МПИ (Норма матрицы: " + normB + ")" + ANSI_RESET);



        if (Seidel.checkConditions(matrix)) {
            System.out.println(ANSI_GREEN + "\n\nУсловия сходимости метода Зейделя выполнены" + ANSI_RESET);
            System.out.println("Корни по Зейделю:");

            Seidel.getRoots(matrix3, count.intValue() + 1)
                    .stream()
                    .forEach(e -> System.out.print(e + "   "));
        } else {
            System.out.println(ANSI_RED + "\n\nУсловия сходимости метода Зейделя не выполнены" + ANSI_RESET);
        }
    }
}
