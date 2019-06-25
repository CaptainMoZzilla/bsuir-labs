import java.util.ArrayList;
import java.util.Collections;

import static java.lang.Math.abs;

public class Gauss {

    public static ArrayList<ArrayList<Double>> toTriangleMatrix(ArrayList<ArrayList<Double>> a) {
        ArrayList<ArrayList<Double>> temp = new ArrayList<ArrayList<Double>>(a);
        int rows = a.size(), columns = a.get(0).size();

        for (int i = 0; i < rows - 1; i++) { //Для общего варианта
            if (temp.get(i).get(i) == 0) {
                int index = i + 1;
                while (temp.get(index).get(index) == 0 && index < rows)
                    index++;

                ArrayList<Double> t = temp.get(i);
                temp.set(i, temp.get(index));
                temp.set(index, t);
            }

            for (int i2 = i + 1; i2 < rows; i2++) {
                Double coefficient = temp.get(i2).get(i) / temp.get(i).get(i);
                for (int j = i; j < columns; j++) {
                    temp.get(i2).set(j, temp.get(i2).get(j) - (temp.get(i).get(j) * coefficient));
                }
            }
        }
        return temp;
    }

    public static ArrayList<Double> findRoots(ArrayList<ArrayList<Double>> matrix) {
        ArrayList<Double> roots = new ArrayList<>();

        for (int a = matrix.size() - 1; a >= 0; a--) {
            Double root = matrix.get(a).get(matrix.get(a).size() - 1);

            for (int bVector = 0; bVector < roots.size(); bVector++) {
                root -= roots.get(bVector) * matrix.get(a).get(matrix.get(a).size() - 2 - bVector);

            }
            root /= matrix.get(a).get(matrix.get(a).size() - 2 - roots.size());
            roots.add(root);
        }
        Collections.reverse(roots);
        return roots;
    }

    public static void showMatrix(ArrayList<ArrayList<Double>> matrix) {
        for (ArrayList<Double> t : matrix) {
            System.out.print("[");
            for (Double a : t) {
                System.out.print(String.format("  %2.15f  ", a));
            }
            System.out.print("]\n");
        }
    }

    public static double calculateDeterminant(ArrayList<ArrayList<Double>> matrix) {
        double result = 0.0;
        
        if (matrix.size() == 2) {
            result = matrix.get(0).get(0) * matrix.get(1).get(1) - matrix.get(1).get(0) * matrix.get(0).get(1);
        } else {
            int coefficient;
            for (int i = 0; i < matrix.size(); i++) {
                coefficient =  (i % 2 == 1) ? -1 : 1;
                result += coefficient * matrix.get(0).get(i) *
                        calculateDeterminant(getMinor(new ArrayList<ArrayList<Double>>(matrix), 0, i));
            }
        }
        return result;
    }

    public static ArrayList<ArrayList<Double>> getMinor(ArrayList<ArrayList<Double>> matrix, int row, int column) {

        ArrayList<ArrayList<Double>> minor = cloneMatrix(matrix);
        minor.stream().forEach(e -> e.remove(column));
        minor.remove(row);

        return minor;
    }

    public static ArrayList<ArrayList<Double>> cloneMatrix(ArrayList<ArrayList<Double>> matrix) {
        ArrayList<ArrayList<Double>> newMatrix = new ArrayList<>();
        matrix.forEach(e -> newMatrix.add(new ArrayList<Double>(e)));

        return newMatrix;
    }

    public static ArrayList<ArrayList<Double>> matrixOfAlgebraicComponents(ArrayList<ArrayList<Double>> matrix) {
        ArrayList<ArrayList<Double>> temp = new ArrayList<>();
        for (int a = 0; a < matrix.size(); a++) {
            ArrayList<Double> row = new ArrayList<>();
            for (int bVector = 0; bVector < matrix.get(0).size(); bVector++) {
                row.add(calculateDeterminant(getMinor(matrix, a, bVector)) * ((a + bVector) % 2 == 1 ? -1 : 1));
            }
            temp.add(row);
        }
        return temp;
    }

    public static ArrayList<ArrayList<Double>> transposeMatrix(ArrayList<ArrayList<Double>> matrix) {
        ArrayList<ArrayList<Double>> inverseMatrix = new ArrayList<>();

        matrix.stream().forEach(e -> inverseMatrix.add(new ArrayList<Double>()));

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                inverseMatrix.get(j).add(matrix.get(i).get(j));
            }
        }

        if (matrix.size() != matrix.get(0).size())
            for (int i = 0; i < matrix.size(); i++)
                inverseMatrix.get(i).add(matrix.get(i).get(matrix.get(i).size() - 1));

        return inverseMatrix;
    }

    public static void invertMatrix(ArrayList<ArrayList<Double>> matrix, Double determinant) {
        for (ArrayList<Double> t : matrix)
            for (int a = 0; a < t.size(); a++) {
                t.set(a, t.get(a)/determinant);
            }
    }

    public static void calcError(ArrayList<ArrayList<Double>> matrix, ArrayList<Double> roots, ArrayList<ArrayList<Double>> invertMatrix) {
        double normA = 0, normB = 0, normX = 0, normNegA = 0;
        double delX = 0, delB = 0.001;

        ArrayList<Double> bVector = new ArrayList<>();

        matrix.stream().forEach(e -> bVector.add(e.get(e.size() - 1)));
        matrix.stream().forEach(e -> e.remove(e.size() - 1));

        for (ArrayList<Double> a : matrix) {
            double sum = 0;
            for (Double d : a)
                sum += Math.abs(d);

            if (normA < sum) {
                normA = sum;
            }
        }

        normB = calcNorm(bVector);
        normX = calcNorm(roots);

        System.out.println("\n\u001B[0mОтносительная b погрешность: " + delB / normB);

        for (ArrayList<Double> a : invertMatrix) {
            Double norm = calcNorm(a);
            if (normNegA < norm) {
                normNegA = norm;
            }
        }
        delX = normNegA * delB;

        System.out.println("Относительная x погрешность: " + delX / normX);
        System.out.println(delX / normX + " <= " + normA * normNegA * delB / normB);
    }

    public static double calcNorm(ArrayList<Double> matrix) {
        return matrix.stream().max((a, b) -> abs(a) > abs(b) ? 1 : -1).get();
    }

}