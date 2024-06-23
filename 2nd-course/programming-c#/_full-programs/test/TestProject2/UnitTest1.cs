namespace TestProject2;

public class UnitTest1
{
    [Fact]
    public void Test1()
    {
        Patient test = new Patient(1, "TestName", new DateTime(2024, 12, 1));

        Assert.Equal(1, test.Id);

        // var patients = Read.ReadPatientsFromCSV("C:\\Projects\\university-projects\\2nd-course\\programming-c#\\_full-programs\\test\\input.csv");

        // Assert.Equal("Johnson", patients[1].Surname);

    }
}