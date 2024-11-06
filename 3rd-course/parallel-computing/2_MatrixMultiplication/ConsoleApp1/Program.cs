using System.Threading;
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

    public static Stopwatch SequentialMatrixMultiplication(int[,] matrixA, int[,] matrixB)
    {
      int rowsA = matrixA.GetLength(0);
      int colsA = matrixA.GetLength(1);
      int rowsB = matrixB.GetLength(0);
      int colsB = matrixB.GetLength(1);

      if (colsA != rowsB)
      {
        throw new ArgumentException("Matrices cannot be multiplied: colsA != rowsB.");
      }
      int[,] resultMatrix = new int[rowsA, colsB];

      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      for (int i = 0; i < rowsA; i++)
      {
        for (int j = 0; j < colsB; j++)
        {
          int sum = 0;
          for (int k = 0; k < colsA; k++)
          {
            sum += matrixA[i, k] * matrixB[k, j];
          }
          resultMatrix[i, j] = sum;
        }
      }
      stopWatch.Stop();
      return stopWatch;
    }

    public static Stopwatch ParallelMatrixMultiplication(int[,] matrixA, int[,] matrixB, int threadCount)
    {
      int rowsA = matrixA.GetLength(0);
      int colsA = matrixA.GetLength(1);
      int rowsB = matrixB.GetLength(0);
      int colsB = matrixB.GetLength(1);

      if (colsA != rowsB)
      {
        throw new ArgumentException("Matrices cannot be multiplied: colsA != rowsB.");
      }
      int[,] resultMatrix = new int[rowsA, colsB];

      CountdownEvent countdown = new CountdownEvent(threadCount);
      Stopwatch stopWatch = new Stopwatch();
      stopWatch.Start();

      int baseRowsPerThread = rowsA / threadCount;
      int extraRows = rowsA % threadCount;

      void ComputeMatrixRows(int startRow, int endRow)
      {
        for (int i = startRow; i < endRow; i++)
        {
          for (int j = 0; j < colsB; j++)
          {
            int sum = 0;
            for (int k = 0; k < colsA; k++)
            {
              sum += matrixA[i, k] * matrixB[k, j];
            }
            resultMatrix[i, j] = sum;
          }
        }
        countdown.Signal();
      }

      for (int i = 0; i < threadCount; i++)
      {
        int startRow = i * baseRowsPerThread + Math.Min(i, extraRows);
        int endRow = startRow + baseRowsPerThread + (i < extraRows ? 1 : 0);

        new Thread(() => ComputeMatrixRows(startRow, endRow)).Start();
      }

      countdown.Wait();

      stopWatch.Stop();
      return stopWatch;
    }

    static void Main(string[] args)
    {
      int n = 200;
      int m = 300;
      int l = 100;
      int k = 2;

      var m1 = generateMatrix(n, m);
      var m2 = generateMatrix(m, l);

      Console.WriteLine($"nA = {n}, mA = {n}, nB = {n}, mB = {n}");

      Stopwatch sequentialMethodTime = SequentialMatrixMultiplication(m1, m2);
      Console.WriteLine($"Sequential time: {sequentialMethodTime.ElapsedMilliseconds} ms");

      Stopwatch parallelMethodTime = ParallelMatrixMultiplication(m1, m2, k);
      Console.WriteLine($"Parallel time: {parallelMethodTime.ElapsedMilliseconds} ms, threads: {k}");

      var acceleration = sequentialMethodTime.Elapsed / parallelMethodTime.Elapsed;
      var efficiency = acceleration / k;

      Console.WriteLine();
      Console.WriteLine($"Acceleration of parallel: {acceleration}");
      Console.WriteLine($"Efficiency of parallel: {efficiency}");

      // PrintMatrix(m1);
      // PrintMatrix(m2);

      // var m3 = SequentialMatrixMultiplication(m1, m2);
      // PrintMatrix(m3);
    }
  }
}
