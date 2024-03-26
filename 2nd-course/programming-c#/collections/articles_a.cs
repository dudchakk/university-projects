using System.Collections.Generic;
using System;
using System.Linq;

public class Author
{
    public int Id { get; set; }
    public string LastName { get; set; }
    public string Country { get; set; }
    
    public Author(int id, string nl, string c)
    {
        Id = id;
        LastName = nl;
        Country = c;
    }
}

public class Article
{
    public int Id { get; set; }
    public int AuthorId { get; set; }
    public string Title { get; set; }
    
    public Article(int id, int aid, string t)
    {
        Id = id;
        AuthorId = aid;
        Title = t;
    }
}

public class BiblData
{
    public int ArticleId { get; set; }
    public string YearAndNum { get; set; }
    
    public BiblData(int aid, string y)
    {
        ArticleId = aid;
        YearAndNum = y;
    }
}

class Program
{
    static void Main(string[] args)
    {
        List<Author> authors = new List<Author>
        {
            new Author (1, "Smith", "USA" ),
            new Author (2, "Johnson", "Canada" ),
            new Author (3, "Brown", "USA" ),
            new Author (4, "Williams", "UK" )
        };

        List<Article> articles = new List<Article>
        {
            new Article (101, 1, "Title A"),
            new Article (102, 2, "Title B"),
            new Article (103, 3, "Title C"),
            new Article (104, 4, "Title D")
        };

        List<BiblData> bibliographicData = new List<BiblData>
        {
            new BiblData( 101, "2023, 1"),
            new BiblData( 102, "2024, 2"),
            new BiblData( 103, "2025, 3"),
            new BiblData( 104, "2026, 4")
        };

        // a
        
        foreach (var author in authors.OrderBy(a => a.LastName))
        {
    
            foreach (var article in articles)
            {
                if (article.AuthorId == author.Id)
                {
                    Console.WriteLine($"{author.LastName}, {article.Title}");
                }
            }
        }
    }
}