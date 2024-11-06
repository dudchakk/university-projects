﻿using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace ConsoleApp1
{
  internal class Program
  {
    public static void PrintMatrix(int[,] m)
    {
      for (int i = 0; i < m.GetLength(0); i++)
      {
        for (int j = 0; j < m.GetLength(1); j++)
        {
          Console.Write(m[i, j] + " ");
        }
        Console.WriteLine();
      }
      Console.WriteLine();
    }
    
    public static int[,] generateMatrix(int n, int m)
    {
      int[,] matrix = new int[n, m];
      Random random = new Random();
      
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          matrix[i, j] = random.Next(0, 100);
        }
      }
      return matrix;
    }
    
    public static TimeSpan SequentialMatrixAddition(int[,] matrixA, int[,] matrixB)
    {
      int n = matrixA.GetLength(0);
      int m = matrixA.GetLength(1);
      int[,] resultMatrix = new int[n, m];

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          resultMatrix[i, j] = matrixA[i, j] + matrixB[i, j];
        }
      }
      stopWatch.Stop();

      return stopWatch.Elapsed;
    }

    public static TimeSpan SequentialMatrixSubstraction(int[,] matrixA, int[,] matrixB)
    {
      int n = matrixA.GetLength(0);
      int m = matrixA.GetLength(1);
      int[,] resultMatrix = new int[n, m];

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          resultMatrix[i, j] = matrixA[i, j] - matrixB[i, j];
        }
      }
      stopWatch.Stop();

      return stopWatch.Elapsed;
      // return resultMatrix;
    }

    public static TimeSpan ParallelMatrixComputation(int[,] matrixA, int[,] matrixB, int threadCount, Boolean isSum)
    {
      int n = matrixA.GetLength(0);
      int m = matrixA.GetLength(1);
      int[,] resultMatrix = new int[n, m];

      Thread[] threads = new Thread[threadCount];
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();
      
      int baseRowsPerThread = n / threadCount;
      int extraRows = n % threadCount;

      void SumMatrixRows(int startRow, int endRow)
      {
        for (int i = startRow; i < endRow; i++)
        {
          for (int j = 0; j < m; j++)
          {
            resultMatrix[i, j] = matrixA[i, j] + matrixB[i, j];
          }
        }
      }

      void SubMatrixRows(int startRow, int endRow)
      {
        for (int i = startRow; i < endRow; i++)
        {
          for (int j = 0; j < m; j++)
          {
            resultMatrix[i, j] = matrixA[i, j] - matrixB[i, j];
          }
        }
      }

      Action<int, int> operation = isSum ? (Action<int, int>)SumMatrixRows : SubMatrixRows;
      
      for (int i = 0; i < threadCount; i++)
      {
        int startRow = i * baseRowsPerThread + Math.Min(i, extraRows);
        int endRow = startRow + baseRowsPerThread + (i < extraRows ? 1 : 0);

        threads[i] = new Thread(() => operation(startRow, endRow));
        threads[i].Start();
      }

      foreach (var thread in threads)
      {
        thread.Join();
      }
      
      stopWatch.Stop();
      return stopWatch.Elapsed;
      // return resultMatrix;
    }
    
    static void Main(string[] args)
    {
      int n = 10000;
      int m = 10000;
      int k = 10;

      var m1 = generateMatrix(n, m);
      var m2 = generateMatrix(n, m);

      Console.WriteLine($"n = {n}, m = {m}");

      TimeSpan sequentialMethodTime = SequentialMatrixSubstraction(m1, m2);
      Console.WriteLine($"Sequential time: {sequentialMethodTime.Milliseconds} ms");

      TimeSpan parallelMethodTime = ParallelMatrixComputation(m1, m2, k, true);
      Console.WriteLine($"Parallel time: {parallelMethodTime.Milliseconds} ms, threads: {k}");

      var acceleration = sequentialMethodTime / parallelMethodTime;
      var efficiency = acceleration / k;

      Console.WriteLine($"Acceleration of parallel: {acceleration}");
      Console.WriteLine($"Efficiency of parallel: {efficiency}");

      // PrintMatrix(m1);
      // PrintMatrix(m2);

      // var m3 = ParallelMatrixComputation(m1, m2, k, true);
      // PrintMatrix(m3);
    }
  }
}
