using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace ConsoleApp1
{
  internal class Program
  {
    public static void PrintMatrix(double[,] m)
    {
      for (int i = 0; i < m.GetLength(0); i++)
      {
        for (int j = 0; j < m.GetLength(1); j++)
        {
          Console.Write(m[i, j] + " ");
          
          if (j == m.GetLength(1) - 2)
          {
            Console.Write("| ");
          }
        }
        Console.WriteLine();
      }
      Console.WriteLine();
    }
    public static double[,] GenerateMatrix(int n)
    {
      double[,] matrix = new double[n, n + 1];
      Random random = new Random();

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n + 1; j++)
        {
          matrix[i, j] = random.Next(0, 10);
        }
      }
      return matrix;
    }

    public static void CheckNonZeroDiagonal(double[,] matrix)
    {
      for (int i = 0; i < matrix.GetLength(0); i++)
      {
        if (matrix[i, i] == 0) 
        {
          throw new DivideByZeroException();
        }
      }
    }

    public static double[] SequentialGaussElimination(double[,] matrix)
    {
      int n = matrix.GetLength(0);

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      double[] resultArray = new double[n];

      try {
        for (int curRow = 0; curRow < n; curRow++)
        {
          for (int i = curRow + 1; i < n; i++)
          {
            double multiplier = matrix[i, curRow] / matrix[curRow, curRow];
            for (int j = curRow; j <= n; j++)
            {
              matrix[i, j] -= multiplier * matrix[curRow, j];
            }
          }
        }

        CheckNonZeroDiagonal(matrix);
        
        for (int curRow = n - 1; curRow >= 0; curRow--)
        {
          resultArray[curRow] = matrix[curRow, n];
          for (int j = curRow + 1; j < n; j++)
          {
            resultArray[curRow] -= matrix[curRow, j] * resultArray[j];
          }
          resultArray[curRow] /= matrix[curRow, curRow];
        }
      } 
      catch (DivideByZeroException ex)
      {
        throw new InvalidOperationException("Error: Division by zero encountered during Gaussian elimination.", ex);
      }

      stopWatch.Stop();
      // return stopWatch;
      return resultArray;
    }

    public static double[] ParallelGaussElimination(double[,] matrix, int threadCount)
    {
      int n = matrix.GetLength(0);
      
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      CountdownEvent countdownEvent = new CountdownEvent(threadCount);
      int baseRowsPerThread = n / threadCount;
      int extraRows = n % threadCount;

      for (int i = 0; i < threadCount; i++)
      {
        int startRow = i * baseRowsPerThread + Math.Min(i, extraRows);
        int endRow = startRow + baseRowsPerThread + (i < extraRows ? 1 : 0);

        Thread thread = new Thread(() =>
        {
          for (int curRow = startRow; curRow < endRow; curRow++)
          {
            for (int j = curRow + 1; j < n; j++)
            {
              double multiplier = matrix[j, curRow] / matrix[curRow, curRow];
              for (int k = curRow; k <= n; k++)
              {
                matrix[j, k] -= multiplier * matrix[curRow, k];
              }
            }
          }
          countdownEvent.Signal();
        });

        thread.Start();
      }

      countdownEvent.Wait();
      CheckNonZeroDiagonal(matrix);
      double[] resultArray = new double[n];

      for (int curRow = n - 1; curRow >= 0; curRow--)
      {
        resultArray[curRow] = matrix[curRow, n];
        for (int j = curRow + 1; j < n; j++)
        {
          resultArray[curRow] -= matrix[curRow, j] * resultArray[j];
        }
        resultArray[curRow] /= matrix[curRow, curRow];
      }
      
      stopWatch.Stop();
      // return stopWatch;
      return resultArray;
    }

    static void Main(string[] args)
    {
      int n = 5;
      int k = 2;

      var m = GenerateMatrix(n);

      // Console.WriteLine($"n = {n}");

      // Stopwatch sequentialMethodTime = SequentialGaussElimination(m);
      // Console.WriteLine($"Sequential time: {sequentialMethodTime.ElapsedMilliseconds} ms");

      // Stopwatch parallelMethodTime = ParallelGaussElimination(m, k);
      // Console.WriteLine($"Parallel time: {parallelMethodTime.ElapsedMilliseconds} ms, threads: {k}");

      // var acceleration = sequentialMethodTime.Elapsed / parallelMethodTime.Elapsed;
      // var efficiency = acceleration / k;

      // Console.WriteLine();
      // Console.WriteLine($"Acceleration of parallel: {acceleration}");
      // Console.WriteLine($"Efficiency of parallel: {efficiency}");

      PrintMatrix(m);

      double[] results = SequentialGaussElimination(m);
      for(int i = 0; i < results.Length; i++) 
      {
        Console.WriteLine(results[i]);
      }
      double[] resulta = ParallelGaussElimination(m, k);
      for(int i = 0; i < resulta.Length; i++) 
      {
        Console.WriteLine(resulta[i]);
      }
    }
  }
}
