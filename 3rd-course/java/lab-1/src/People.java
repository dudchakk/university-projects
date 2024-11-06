import java.util.Arrays;
import java.util.Comparator;

abstract class Person {
  String name;
  int age;
  String gender;

  public Person(String name, int age, String gender) {
    this.name = name;
    this.age = age;
    this.gender = gender;
  }

  public String getName() {
    return name;
  }

  public abstract void displayInfo();
}

class Teacher extends Person {
  String position;
  int experience;

  public Teacher(String name, int age, String gender, String position, int experience) {
    super(name, age, gender);
    this.position = position;
    this.experience = experience;
  }

  public int getExperience() {
    return experience;
  }

  @Override
  public void displayInfo() {
    System.out.println("(Teacher) " + name + ", experience: " + experience);
  }
}

class Student extends Person {
  String faculty;
  double avg_progress;

  public Student(String name, int age, String gender, String faculty, double avg_progress) {
    super(name, age, gender);
    this.faculty = faculty;
    this.avg_progress = avg_progress;
  }

  public double getAvg_progress() {
    return avg_progress;
  }

  @Override
  public void displayInfo() {
    System.out.println("(Student) " + name + ", average progress: " + avg_progress);
  }
}

public class People {
  public static void main(String[] args) {
    Person[] people = {
      new Teacher("Ivan Ivanenko", 45, "male", "Professor", 15),
      new Student("Marta Koval", 20, "female", "Computer Science", 3.9),
      new Student("Andriy Shevchenko", 21, "male", "Physics", 3.8),
      new Teacher("Oksana Romanenko", 40, "female", "Assistant", 10)
    };

    Arrays.sort(people, Comparator.comparing(Person::getName));
    System.out.println("Sorted by name:");
    for (Person person : people) {
      person.displayInfo();
    }

    Teacher minExperienceTeacher = Arrays.stream(people)
      .filter(p -> p instanceof Teacher)
      .map(p -> (Teacher) p)
      .min(Comparator.comparingInt(Teacher::getExperience))
      .orElse(null);

    if (minExperienceTeacher != null) {
      System.out.println("\nTeacher with minimum experience:");
      minExperienceTeacher.displayInfo();
    }

    double maxGpa = Arrays.stream(people)
      .filter(p -> p instanceof Student)
      .map(p -> (Student) p)
      .mapToDouble(Student::getAvg_progress)
      .max()
      .orElse(0);

    System.out.println("\nStudents with maximum progress:");
    Arrays.stream(people)
      .filter(p -> p instanceof Student && ((Student) p).getAvg_progress() == maxGpa)
      .forEach(Person::displayInfo);
  }
}
