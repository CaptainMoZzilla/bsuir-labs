import java.util.ArrayList;

public class Seidel {

    public static void toSIMForm (ArrayList<ArrayList<Double>> matrix) {
        for (int a = 0; a < matrix.size(); a++) {
            Double coefficient = matrix.get(a).get(a);

            for (int b = 0; b < matrix.get(a).size(); b++) {
                if (b !=  matrix.get(a).size() - 1)
                    matrix.get(a).set(b, (-1 * matrix.get(a).get(b)) / coefficient);
                else
                    matrix.get(a).set(b, (matrix.get(a).get(b)) / coefficient);
            }
        }

        for (int a = 0; a < matrix.size(); a++) {
            matrix.get(a).set(a, 0d);
        }
    }

    public static ArrayList<Double> SIM(ArrayList<ArrayList<Double>> matrix, int count) {
        ArrayList<Double> roots = new ArrayList<>(), roots2 = new ArrayList<>();

        for (ArrayList<Double> a : matrix) {
            roots.add(a.get(a.size() - 1));
            roots2.add(a.get(a.size() - 1));
        }


        for (; count > 0; count--) {
            roots.clear();
            roots2.stream().forEach(e -> roots.add(e));

            for (int a = 0; a < matrix.size(); a++) {
                double x = 0;

                for (int b = 0; b < matrix.get(a).size(); b++) {
                    if (b != matrix.get(a).size() - 1) {
                        x += roots.get(b) * matrix.get(a).get(b);
                    } else {
                        x += matrix.get(a).get(b);
                    }
                }
                roots2.set(a, x);
            }
        }
        return roots;
    }

    public static Double calcMatrixNorm(ArrayList<ArrayList<Double>> matrix) {
        double normA = 0;

        for (int a = 0; a < matrix.size(); a++) {
            double sum = 0;

            for (int b = 0; b < matrix.get(a).size() - 1;b++) {
                sum += Math.abs(matrix.get(a).get(b));
            }
            if (normA < sum) {
                normA = sum;
            }
        }
        return normA;
    }

    public static Double calcVectorNorm(ArrayList<ArrayList<Double>> matrix) {
        double normA = 0;

        for (ArrayList<Double> a : matrix) {
            if (Math.abs(a.get(a.size() - 1)) > normA)
                normA = Math.abs(a.get(a.size() - 1));
        }
        return normA;
    }

    public static ArrayList<Double> getRoots(ArrayList<ArrayList<Double>> matrix, int count) {
        ArrayList<Double> roots = new ArrayList<>(),
                          roots2 = new ArrayList<>();

        for (ArrayList<Double> a : matrix) {
            roots.add(a.get(a.size() - 1));
        }

        for (; count > 0; count--) {
            roots2 = new ArrayList<>(roots);

            for (int a = 0; a < matrix.size(); a++) {
                double x = 0;

                for (int b = 0; b < matrix.get(a).size(); b++) {
                    if (b != matrix.get(a).size() - 1) {
                        x += roots.get(b) * matrix.get(a).get(b);

                    } else {
                        x += matrix.get(a).get(b);
                    }
                }
                roots.set(a, x);
            }
        }
        return roots;
    }

    public static Boolean checkConditions(ArrayList<ArrayList<Double>> matrix) {
        for (int a = 0; a < matrix.size(); a++) {
            double d = Math.abs(matrix.get(a).get(a));
            for (int b = 0; b < matrix.get(a).size() - 1; b++) {
                if (b == a)
                    continue;
                else
                    d -= Math.abs(matrix.get(a).get(b));
            }
            if (d < 0)
                return false;
        }
        return true;
    }
}
