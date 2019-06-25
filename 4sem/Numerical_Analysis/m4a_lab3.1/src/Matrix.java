import java.util.ArrayList;

public class Matrix {
    public static ArrayList<ArrayList<Double>> multiply(ArrayList<ArrayList<Double>> a, ArrayList<ArrayList<Double>> b) {
        ArrayList<ArrayList<Double>> result = new ArrayList<>();

        int rows = a.size();
        int columns = b.get(0).size();

        a.forEach(e -> result.add(new ArrayList<>()));

        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.get(0).size()- (rows != columns ? 1 : 0); j++) {
                double res = 0;
                for (int k = 0; k < b.get(0).size() - (rows != columns ? 1 : 0); k++) {
                    res += a.get(i).get(k) * b.get(k).get(j);
                }
                result.get(i).add(res);
            }
        }

        if (rows != columns)
        for (int i = 0; i < b.size(); i++) {
            double res = 0;
            for (int j = 0; j < b.get(0).size() - 1; j++) {
                res += b.get(i).get(j) * a.get(j).get(a.get(0).size() - 1);
            }
            result.get(i).add(res);
        }
        return result;
    }

    public static ArrayList<ArrayList<Double>> makeT(ArrayList<ArrayList<Double>> matrix) {
        ArrayList<ArrayList<Double>> matrixT = new ArrayList<>();
        matrix.forEach(e -> matrixT.add(new ArrayList<>()));

        for (ArrayList<Double> a : matrixT)
            matrix.forEach(e ->  a.add(0d));

        matrixT.get(0).set(0, Math.sqrt(matrix.get(0).get(0)));

        for (int a = 0; a < matrix.size(); a++) {
            for (int b = 0; b < matrix.size(); b++) {
                if (a > b)
                    continue;

                if (a == b) {
                    double res = 0;
                    for (int c = 0; c < a; c++) {
                        res += matrixT.get(c).get(a) * matrixT.get(c).get(a);
                    }
                    matrixT.get(a).set(b, Math.sqrt(matrix.get(a).get(b) - res));
                }
                else {
                    double res = 0;
                    for (int c = 0; c < a; c++) {
                        res += matrixT.get(c).get(a) * matrixT.get(c).get(b);
                    }

                    matrixT.get(a).set(b, (matrix.get(a).get(b) - res) / matrixT.get(a).get(a));
                }
            }
        }
        return matrixT;
    }

    public static ArrayList<Double> calcYVector(ArrayList<ArrayList<Double>> matrixUT) {
        ArrayList<Double> roots = new ArrayList<>();

        for (int a = 0; a < matrixUT.size(); a++) {
            Double root = matrixUT.get(a).get(matrixUT.get(a).size() - 1);

            for (int bVector = 0; bVector < roots.size(); bVector++) {
                root -= roots.get(bVector) * matrixUT.get(a).get(bVector);
            }
            root /= matrixUT.get(a).get(a);
            roots.add(root);
        }

        return roots;
    }

}
