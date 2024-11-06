import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class MatrixFibonacci {

  public static boolean isFibonacciNumber(int num) {
    int a = 0, b = 1;
    while (b < num) {
      int temp = b;
      b = a + b;
      a = temp;
    }
    return b == num || num == 0;
  }

  public static List<Integer> findMinFibonacciInRows(int[][] matrix) {
    List<Integer> result = new ArrayList<>();
    for (int[] row : matrix) {
      int minFib = Integer.MAX_VALUE;
      for (int num : row) {
        if (isFibonacciNumber(num) && num < minFib) {
          minFib = num;
        }
      }
      result.add(minFib == Integer.MAX_VALUE ? -1 : minFib);
    }
    return result;
  }
  
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    try {
      System.out.println("Enter number of rows and columns:");
      int rows = scanner.nextInt();
      int cols = scanner.nextInt();
      int[][] matrix = new int[rows][cols];

      System.out.println("Enter matrix elements:");
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          matrix[i][j] = scanner.nextInt();
        }
      }

      List<Integer> minFibs = findMinFibonacciInRows(matrix);
      System.out.println("Minimum Fibonacci numbers in each row: " + minFibs);
    } finally {
      scanner.close();
    }
  }
}
