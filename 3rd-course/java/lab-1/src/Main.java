import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    try {
      System.out.println("Select task:");
      System.out.println("1. Matrix Fibonacci");
      System.out.println("2. Reverse words");
      System.out.println("3. People sorting");
      int choice = scanner.nextInt();

      switch (choice) {
        case 1:
          MatrixFibonacci.main(args);
          break;
        case 2:
          ReverseWords.main(args);
          break;
        case 3:
          People.main(args);
          break;
        default:
          System.out.println("Invalid choice");
      }
    } finally {
      scanner.close();
    }
  }
}
