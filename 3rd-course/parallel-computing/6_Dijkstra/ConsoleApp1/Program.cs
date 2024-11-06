using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;

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

    public static void PrintDistances(Dictionary<int, int> distances, int startNode)
    {
      Console.WriteLine($"Distances from {startNode}:");

      foreach (var distance in distances)
      {
        if (distance.Value == int.MaxValue)
        {
          Console.WriteLine($"Not possible to reach {distance.Key}.");
        }
        else
        {
          Console.WriteLine($"Vertex {distance.Key}: {distance.Value}");
        }
      }
    }

    public static void PrintDistancesParallel(ConcurrentDictionary<int, int> distances, int startNode)
    {
      Console.WriteLine($"Distances from {startNode}:");

      foreach (var distance in distances)
      {
        if (distance.Value == int.MaxValue)
        {
          Console.WriteLine($"Not possible to reach {distance.Key}.");
        }
        else
        {
          Console.WriteLine($"Vertex {distance.Key}: {distance.Value}");
        }
      }
    }

    public static Stopwatch SequentialDijkstraAlgorithm(Dictionary<int, Dictionary<int, int>> graph, int nodeA)
    {
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      var distances = new Dictionary<int, int>();
      var set = new Dictionary<int, bool>();
      int vertexCount = graph.Count;
      
      for (int i = 0; i < vertexCount; i++)
      {
        distances[i] = int.MaxValue;
        set[i] = false;
      }
      distances[nodeA] = 0;

      for (int i = 0; i < vertexCount - 1; i++)
      {
        int minDist = int.MaxValue;
        int curNode = -1;

        foreach (var node in distances)
        {
          if (!set[node.Key] && node.Value <= minDist)
          {
            minDist = node.Value;
            curNode = node.Key;
          }
        }
        if (curNode != -1)
        {
          set[curNode] = true;
          foreach (var edge in graph[curNode])
          {
            int updDist = distances[curNode] + edge.Value;
            if (updDist < distances[edge.Key])
            {
              distances[edge.Key] = updDist;
            }
          }
        }
      }

      stopWatch.Stop();
      // PrintDistances(distances, nodeA);
      return stopWatch;
    }

    public static Stopwatch ParallelDijkstraAlgorithm(Dictionary<int, Dictionary<int, int>> graph, int nodeA, int maxThreadCount)
    {
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      var distances = new ConcurrentDictionary<int, int>();
      var set = new ConcurrentDictionary<int, bool>();
      int vertexCount = graph.Count;

      for (int i = 0; i < vertexCount; i++)
      {
        distances[i] = int.MaxValue;
        set[i] = false;
      }
      distances[nodeA] = 0;

      int completedNodesCount = 0;

      while (completedNodesCount < vertexCount - 1)
      {
        int minDist = int.MaxValue;
        int curNode = -1;

        Parallel.ForEach(Partitioner.Create(0, vertexCount, vertexCount / maxThreadCount), range =>
        {
          for (int i = range.Item1; i < range.Item2; i++)
          {
            if (!set[i] && distances[i] <= minDist)
            {
              lock (set)
              {
                if (!set[i] && distances[i] <= minDist)
                {
                  minDist = distances[i];
                  curNode = i;
                }
              }
            }
          }
        });

        if (curNode != -1)
        {
          set[curNode] = true;
          completedNodesCount++;

          var curEdges = graph[curNode];

          Parallel.ForEach(Partitioner.Create(0, curEdges.Count), range =>
          {
            int localIndex = 0;
            foreach (var edge in curEdges)
            {
              if (localIndex >= range.Item1 && localIndex < range.Item2)
              {
                int updDist = distances[curNode] + edge.Value;
                if (updDist < distances[edge.Key])
                {
                  lock (distances)
                  {
                    if (updDist < distances[edge.Key])
                    {
                      distances[edge.Key] = updDist;
                    }
                  }
                }
              }
              localIndex++;
            }
          });
        }
      }

      stopWatch.Stop();
      // PrintDistancesParallel(distances, nodeA);
      return stopWatch;
    }

    static void Main(string[] args)
    {
      int n = 5000;
      int k = 10;
      int a = 3;

      var graph = GenerateGraph(n);
      // PrintGraph(graph);

      Console.WriteLine($"n = {n}, a = {a}");

      var seqTime = SequentialDijkstraAlgorithm(graph, a);
      Console.WriteLine($"Sequential time: {seqTime.ElapsedMilliseconds} ms");

      var parlTime = ParallelDijkstraAlgorithm(graph, a, k);
      Console.WriteLine($"Parallel time: {parlTime.ElapsedMilliseconds} ms, threads: {k}");  

      var acceleration = seqTime.Elapsed / parlTime.Elapsed;
      var efficiency = acceleration / k;

      Console.WriteLine($"Acceleration: {acceleration}");
      Console.WriteLine($"Efficiency: {efficiency}");

    }
  }
}