import java.util.Scanner;

public class ReverseWords {

  public static String reverseString(String str) {
    return new StringBuilder(str).reverse().toString();
  }

  
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    try {
      System.out.println("Enter words separated by commas:");
      String input = scanner.nextLine();

      String[] words = input.split(",");
      for (int i = 0; i < words.length; i++) {
        words[i] = reverseString(words[i].trim());
      }

      System.out.println("Reversed words: " + String.join(", ", words));
    } finally {
      scanner.close();
    }
  }
}
