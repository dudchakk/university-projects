class Program()
{
    public static void Main(string[] args)
    {
        Data data = new Data();

        //data.Load1("input/input1.xml");

        var res1 = data.Load1("input/input1.xml");
        var res2 = data.Load1("input/input2.xml");
        data.Receipts = res1.Concat(res2).ToList();

        //data.TaskA("output/output1.xml");
        data.TaskB("output/output2.xml");
        //data.TaskC("output/output3.xml");
    }
}
