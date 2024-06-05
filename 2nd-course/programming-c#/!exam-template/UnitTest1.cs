using System.Text.RegularExpressions;

namespace TestProject1
{
    public class TaskResultsProjectTests : IClassFixture<Data>
    {
        Data fixture;

        public TaskResultsProjectTests(Data fixture)
        {
            this.fixture = fixture;
            fixture.Load1("input/input1.xml");
            fixture.Load2("input/input2.xml");
            fixture.Load3("input/input3.xml");
        }

        [Fact]
        public void TestA()
        {
            var expected = new List<string>
            {
                "Group1 Furman Y. Subject1 9",
                "Group1 Klakovych M. Subject1 5",
                "Group1 Klakovych M. Subject1 10"

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
                "Group1 Subject1 Furman Y. 9",
                "Group1 Subject1 Klakovych M. 15"   
            };

            var result = fixture.TaskB("");

            Assert.Equal(expected.Count, result.Count);
            for (var i = 0; i < expected.Count; i++)
            {
                Assert.Equal(expected[i], result[i]);
            }
        }

        [Fact]
        public void TestC()
        {
            var expected = new List<string>
            {
                "Group1 Furman Y. 9",
                "Group1 Klakovych M. 15"
            };

            var result = fixture.TaskC("");

            Assert.Equal(expected.Count, result.Count);
            for (var i = 0; i < expected.Count; i++)
            {
                Assert.Equal(expected[i], result[i]);
            }
        }

    }
}
