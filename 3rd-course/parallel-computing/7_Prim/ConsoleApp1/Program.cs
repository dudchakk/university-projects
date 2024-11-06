using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;
using System.Reflection;

namespace ConsoleApp1
{
  internal class Program
  {
    private static Dictionary<int, Dictionary<int, int>> GenerateGraph(int vertexCount)
    {
      Random random = new Random();
      var graph = new Dictionary<int, Dictionary<int, int>>();

      for (int i = 0; i < vertexCount; i++)
      {
        graph[i] = new Dictionary<int, int>();
        int edgeCount = random.Next(1, 21);

        for (int j = 0; j < edgeCount; j++)
        {
          int randomVertex = random.Next(vertexCount);
          if (randomVertex != i && !graph[i].ContainsKey(randomVertex))
          {
            int weight = random.Next(1, 91);
            graph[i][randomVertex] = weight;
          }
        }
      }

      return graph;
    }

    public static void PrintGraph(Dictionary<int, Dictionary<int, int>> graph)
    {
      foreach (var vertex in graph)
      {
        Console.Write($"Vertex {vertex.Key}: ");
        foreach (var edge in vertex.Value)
        {
          Console.Write($"(Vertex {edge.Key}, weight {edge.Value}) ");
        }
        Console.WriteLine();
      }
    }

    public static void PrintResults(Dictionary<int, int> parents)
    {
      foreach (var parent in parents)
      {
        if (parent.Value == int.MaxValue)
        {
          Console.WriteLine($"Not possible to reach {parent.Key}.");
        }
        else
        {
          Console.WriteLine($"From {parent.Key} to {parent.Value}");
        }
      }
    }

    public static Stopwatch SequentialPrimaAlgorithm(Dictionary<int, Dictionary<int, int>> graph, int nodeA)
    {
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      Dictionary<int, int> parents = new Dictionary<int, int>();
      Dictionary<int, int> keys = new Dictionary<int, int>();
      HashSet<int> unvisitedNodes = new HashSet<int>();
      
      foreach (int vertex in graph.Keys)
      {
        keys[vertex] = int.MaxValue;
        unvisitedNodes.Add(vertex);
      }
      keys[nodeA] = 0;
      
      while (unvisitedNodes.Count > 0)
      {
        int u = -1;
        foreach (int current in unvisitedNodes)
        {
          if (u == -1 || keys[current] < keys[u])
          {
            u = current;
          }
        }
        unvisitedNodes.Remove(u);
        foreach (var neighbor in graph[u])
        {
          int v = neighbor.Key;
          int weight = neighbor.Value;

          if (unvisitedNodes.Contains(v) && weight < keys[v])
          {
            parents[v] = u;
            keys[v] = weight;
          }
        }
      }
      
      stopWatch.Stop();
      // return parents;
      return stopWatch;
    }

    public static Stopwatch ParallelPrimaAlgorithm(Dictionary<int, Dictionary<int, int>> graph, int nodeA, int threadCount)
    {
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      Thread[] threads = new Thread[threadCount];
      CountdownEvent countdown = new CountdownEvent(threadCount);

      Dictionary<int, int> parents = new Dictionary<int, int>();
      ConcurrentDictionary<int, int> keys = new ConcurrentDictionary<int, int>();
      ConcurrentDictionary<int, byte> unvisitedNodes = new ConcurrentDictionary<int, byte>();

      object lockObj = new object();

      foreach (int vertex in graph.Keys)
      {
        keys[vertex] = int.MaxValue;
        unvisitedNodes[vertex] = 0;
      }
      keys[nodeA] = 0;

      while (unvisitedNodes.Count > 0)
      {
        int u = -1;
        int minKey = int.MaxValue;

        for (int i = 0; i < threadCount; i++)
        {
          threads[i] = new Thread(() =>
          {
            (int vertex, int key) localState = (-1, int.MaxValue);
            foreach (var vertex in unvisitedNodes.Keys)
            {
              int vertexKey = keys[vertex];
              if (vertexKey < localState.key)
              {
                localState.vertex = vertex;
                localState.key = vertexKey;
              }
            }

            lock (lockObj)
            {
              if (localState.key < minKey)
              {
                u = localState.vertex;
                minKey = localState.key;
              }
            }
            countdown.Signal();
          });
          threads[i].Start();
        }

        countdown.Wait();
        countdown.Reset();

        if (u == -1)
        {
          break;
        }
        unvisitedNodes.TryRemove(u, out _);

        for (int i = 0; i < threadCount; i++)
        {
          threads[i] = new Thread(() =>
          {
            foreach (var neighborPair in graph[u])
            {
              int v = neighborPair.Key;
              int weight = neighborPair.Value;

              if (unvisitedNodes.ContainsKey(v) && weight < keys[v])
              {
                lock (lockObj)
                {
                  if (unvisitedNodes.ContainsKey(v) && weight < keys[v])
                  {
                    parents[v] = u;
                    keys[v] = weight;
                  }
                }
              }
            }

            countdown.Signal();
          });
          threads[i].Start();
        }

        countdown.Wait();
        countdown.Reset();
      }

      stopWatch.Stop();
      return stopWatch;
      // return parents;
    }

    static void Main(string[] args)
    {
      int n = 80000;
      int k = 5;
      int a = 1;

      var graph = GenerateGraph(n);
      // PrintGraph(graph);

      Console.WriteLine($"n = {n}, a = {a}");

      // PrintResults(SequentialPrimaAlgorithm(graph, a));
      // Console.WriteLine("Parallel:");
      // PrintResults(ParallelPrimaAlgorithm(graph, a, k));

      var seqTime = SequentialPrimaAlgorithm(graph, a);
      Console.WriteLine($"Sequential time: {seqTime.ElapsedMilliseconds} ms");

      var parlTime = ParallelPrimaAlgorithm(graph, a, k);
      Console.WriteLine($"Parallel time: {parlTime.ElapsedMilliseconds} ms, threads: {k}");  

      var acceleration = seqTime.Elapsed / parlTime.Elapsed;
      var efficiency = acceleration / k;

      Console.WriteLine($"Acceleration: {acceleration}");
      Console.WriteLine($"Efficiency: {efficiency}");
    }
  }
}