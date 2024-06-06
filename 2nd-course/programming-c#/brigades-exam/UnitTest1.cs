using System.Text.RegularExpressions;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace TestProject1
{
    public class TaskResultsProjectTests : IClassFixture<Data>
    {
        Data fixture;

        public TaskResultsProjectTests(Data fixture)
        {
            this.fixture = fixture;
            var res1 = fixture.Load1("input/input1.xml");
            var res2 = fixture.Load1("input/input2.xml");
            fixture.Receipts = res1.Concat(res2).ToList();
        }

        [Fact]
        public void TestA()
        {
            var expected = new List<string>
            {
                "Brigade1 Dudynets 75",
                "Brigade1 Furman 60",
                "Brigade2 Urbanskyi 20"

            };

            var result = fixture.TaskA("");

            Assert.Equal(expected.Count, result.Count);
            for (var i = 0; i < expected.Count; i++)
            {
                Assert.Equal(expected[i], result[i]);
            }
        }

        [Fact]
        public void TestB()
        {
            var expected = new List<string>
            {
                "Prystryi 1 5",
                "Prystryi 2 2"
            };

            var result = fixture.TaskB("");

            Assert.Equal(expected.Count, result.Count);
            for (var i = 0; i < expected.Count; i++)
            {
                Assert.Equal(expected[i], result[i]);
            }
        }

    }
}