#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = std::numeric_limits<int>::max();

class Graph
{
  int** graph;
  int num_of_vertexes;

  public:
    Graph(int vc): num_of_vertexes(vc)
    {
      graph = new int*[num_of_vertexes];
      
      for(size_t i = 0; i < num_of_vertexes; i++)
      {
        graph[i] = new int[num_of_vertexes];
        for(size_t j = 0; j < num_of_vertexes; j++)
        {
          graph[i][j] = 0;
        }
      }
    }

    void add_edge(size_t vert1, size_t vert2, size_t weight)
    {
      if(graph[vert1][vert2] != 0)
      {
        throw out_of_range("Edje already exist");
      }

      graph[vert1][vert2] = weight;
      graph[vert2][vert1] = weight;
    }

    size_t GetVertexCount()
    {
      return num_of_vertexes;
    }

    size_t GetWeight(size_t vert1, size_t vert2)
    {
      return graph[vert1][vert2];
    }
};

int MinDistanceToAdjacent(vector<int> dist, vector<bool> set, size_t n)
{
  int min = INT_MAX, min_index;

  for(size_t i = 0; i < n; i++)
  {
    if(!set[i] && dist[i] <= min)
    {
      min = dist[i];
      min_index = i;
    }
  }

  return min_index;
}

vector<int> DijkstraAlgorithm(Graph g, int src)
{
  vector<int> dist(g.GetVertexCount(), INF);
  vector<bool> set(g.GetVertexCount(), false);

  dist[src] = 0;

  for(size_t i = 0; i < g.GetVertexCount() - 1; i++)
  {
    int u = MinDistanceToAdjacent(dist, set, g.GetVertexCount());
    set[u] = true;
        
    for(int v = 0; v < g.GetVertexCount(); v++)
    {
      if (!set[v] && g.GetWeight(u, v) != 0 && dist[u] != INT_MAX && dist[u] + g.GetWeight(u, v) < dist[v])
      {
        dist[v] = dist[u] + g.GetWeight(u, v);
      }
    }
  }
  return dist;
}

TEST_CASE("Testing Dijkstra Algorithm")
{
  Graph g(6);
  g.add_edge(0, 1, 3);
  g.add_edge(0, 5, 4);
  g.add_edge(1, 5, 6);
  g.add_edge(1, 2, 5);
  g.add_edge(2, 5, 6);
  g.add_edge(2, 3, 5);
  g.add_edge(3, 4, 4);
  g.add_edge(4, 5, 7);

  CHECK(g.GetWeight(0, 1) == 3);
  CHECK(g.GetWeight(0, 5) == 4);
  CHECK(g.GetWeight(1, 5) == 6);
  CHECK(g.GetWeight(1, 2) == 5);
  CHECK(g.GetWeight(2, 5) == 6);
  CHECK(g.GetWeight(2, 3) == 5);
  CHECK(g.GetWeight(3, 4) == 4);
  CHECK(g.GetWeight(4, 5) == 7);

  vector<int> dist = DijkstraAlgorithm(g, 0);

  CHECK(dist[0] == 0);
  CHECK(dist[1] == 3);
  CHECK(dist[2] == 8);
  CHECK(dist[3] == 13);
  CHECK(dist[4] == 11);
  CHECK(dist[5] == 4);
}