class Program()
{
    public static void Main(string[] args)
    {
        Data data = new Data();

        data.Load1("input/input1.xml");
        data.Load2("input/input2.xml");
        data.Load3("input/input3.xml");

        //data.TaskA("output/output1.xml");
        //data.TaskB("output/output2.xml");
        //data.TaskC("output/output3.xml");
    }
}