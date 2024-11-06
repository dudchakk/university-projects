using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace ConsoleApp1
{
  internal class Program
  {
    static int MAX_VALUE = 10999;
    public static void PrintGraph(int[,] graph)
    {
      for (int i = 0; i < graph.GetLength(0); i++)
      {
        for (int j = 0; j < graph.GetLength(1); j++)
        {
          Console.Write(graph[i, j] + " ");
        }
        Console.WriteLine();
      }
      Console.WriteLine();
    }
    public static int[,] GenerateGraph(int vertexCount)
    {
      int[,] graph = new int[vertexCount, vertexCount];
      Random random = new Random();

      for (int i = 0; i < vertexCount; i++)
      {
        for (int j = 0; j < vertexCount; j++)
        {
          if (i == j) 
          {
            graph[i, j] = 0;
          } 
          else 
          {
            graph[i, j] = random.Next(1, 21);
            if (random.NextDouble() < 0.2)
            {
              graph[i, j] = MAX_VALUE;
            }
          }
        }
      }
      return graph;
    }

    public static (Stopwatch, int) SequentialFloydAlgorithm(int[,] graph, int a = 0, int b = 0)
    {
      int n = graph.GetLength(0);

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      int[,] resultDistances = new int[n, n];

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          resultDistances[i, j] = graph[i, j];
        }
      }
      
      for (int k = 0; k < n; k++)
      {
        for (int i = 0; i < n; i++)
        {
          for (int j = 0; j < n; j++)
          {
            if (resultDistances[i, k] + resultDistances[k, j] < resultDistances[i, j])
            {
              resultDistances[i, j] = resultDistances[i, k] + resultDistances[k, j];
            }
          }
        }
      }

      stopWatch.Stop();
      return (stopWatch, resultDistances[a, b]);
    }

    public static (Stopwatch, int) ParallelFloydAlgorithm(int[,] graph, int threadCount, int a = 0, int b = 0)
    {
      int n = graph.GetLength(0);

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      int[,] resultDistances = new int[n, n];

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          resultDistances[i, j] = graph[i, j];
        }
      }

      for (int k = 0; k < n; k++)
      {
        Parallel.For(0, n, new ParallelOptions { MaxDegreeOfParallelism = threadCount }, i =>
        {
          for (int j = 0; j < n; j++)
          {
            if (resultDistances[i, k] + resultDistances[k, j] < resultDistances[i, j])
            {
              resultDistances[i, j] = resultDistances[i, k] + resultDistances[k, j];
            }
          }
        });
      }

      stopWatch.Stop();
      return (stopWatch, resultDistances[a, b]);
    }

    static void Main(string[] args)
    {
      int n = 400;
      int k = 10;
      int a = 1;
      int b = 2;

      var graph = GenerateGraph(n);
      // PrintGraph(graph);

      Console.WriteLine($"n = {n}, a = {a}, b = {b}");

      var (seqTime, distS) = SequentialFloydAlgorithm(graph, a, b);
      Console.WriteLine($"Sequential time: {seqTime.ElapsedMilliseconds} ms, dist: {distS}");

      var (parlTime, distP) = ParallelFloydAlgorithm(graph, k, a, b);
      Console.WriteLine($"Parallel time: {parlTime.ElapsedMilliseconds} ms, threads: {k}, dist: {distP}");  

      var acceleration = seqTime.Elapsed / parlTime.Elapsed;
      var efficiency = acceleration / k;

      Console.WriteLine($"Acceleration: {acceleration}");
      Console.WriteLine($"Efficiency: {efficiency}");

    }
  }
}