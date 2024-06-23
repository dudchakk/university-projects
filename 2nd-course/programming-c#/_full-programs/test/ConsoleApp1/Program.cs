class Program()
{
    public static void Main(string[] args)
    {
        Data data = new Data();

        data.ReadPatientsFromCSV("input/input.csv");

        data.GenerateOutput("output/output1.xml");
    }
}