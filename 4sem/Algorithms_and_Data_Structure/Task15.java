import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

public class Main {
    static long[] array;
    static int n;
    static int index = 0, tempVal;
    static BufferedReader scanner = new BufferedReader(new InputStreamReader(System.in));

    static boolean isMin(long prev, long cur, long next){
        return cur < prev && cur < next;
    }

    static boolean isMax(long prev, long cur, long next){
        return cur > prev && cur > next;
    }

    static boolean isEnd(int iter, int n){
        return iter == n - 1;
    }

    static void fillArray() throws IOException {
        String[] line = scanner.readLine().split(" ");
        for(int i = 0; i < array.length; i++){
            tempVal = Integer.parseInt(line[i]);
            if(index == 0 || array[index - 1] != tempVal) {
                array[index] = tempVal;
                index++;
            }
            else {
                n--;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        n = Integer.parseInt(scanner.readLine());
        array = new long[n];

        fillArray();

        long minimum, max;
        minimum = array[0];
        max = array[0];

        long result = 0;
        for (int i = 1; i < n; i++){
            if(isEnd(i, n)){
                if(array[i] > array[i - 1] && array[i] >= max)
                    result += (array[i] - minimum);
                else if(array[i] > array[i - 1] && array[i] < max)
                    result += (max - minimum);
                else
                    result += (max - array[i]);
                break;
            }

            else if(isMin(array[i - 1], array[i], array[i + 1])){
                minimum = array[i];
            }

            else if(isMax(array[i - 1], array[i], array[i + 1])){
                result += (array[i] - minimum);
                max = (max < array[i]) ? array[i] : max;
            }
        }

        System.out.println(result);
    }
}
