using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection.Metadata;
using System.Xml.Linq;
using System.Xml.Schema;

public class Category
{
    public int Id { get; set; }
    public string Name { get; set; }
    public int WarrantyYears { get; set; }
    public Category(int id, string name, int years)
    {
        Id = id;
        Name = name;
        WarrantyYears = years;
    }
}

public class Operation
{
    public int Id { get; set; }
    public string Name { get; set; }
    public decimal Cost { get; set; }
    public Operation(int id, string name, decimal cost)
    {
        Id = id;
        Name = name;
        Cost = cost;
    }
}

public class Receipt
{
    public int CategoryId { get; set; }
    public int Year { get; set; }
    public int OperationId { get; set; }
    public Receipt(int cId, int year, int oId)
    {
        CategoryId = cId;
        Year = year;
        OperationId = oId;
    }
}


class Program
{
    static void Main(string[] args)
    {
        var categories = new List<Category>
        {
            new Category(1, "Category 1", 3),
            new Category(2, "Category 2", 2)
        };

        var operations = new List<Operation>
        {
            new Operation(1, "Operation 1", 20.50m),
            new Operation(2, "Operation 2", 30.00m)
        };

        var receipts = new List<Receipt>
        {
            new Receipt(1, 2020, 1),
            new Receipt(1, 2023, 2),
            new Receipt(1, 2020, 1),
            new Receipt(1, 2022, 1),
            new Receipt(1, 2022, 1),
            new Receipt(2, 2021, 1),
            new Receipt(2, 2020, 2),
            new Receipt(2, 2023, 2)
        };

        string output1 = "C:\\Projects\\university-projects\\2nd-course\\programming-c#\\_full-programs\\xml-service-center\\ConsoleApp1\\bin\\Debug\\net8.0\\output1.xml";
        string output2 = "C:\\Projects\\university-projects\\2nd-course\\programming-c#\\_full-programs\\xml-service-center\\ConsoleApp1\\bin\\Debug\\net8.0\\output2.xml";
        string output3 = "C:\\Projects\\university-projects\\2nd-course\\programming-c#\\_full-programs\\xml-service-center\\ConsoleApp1\\bin\\Debug\\net8.0\\output3.xml";

        int categoryId = 1;

        Program program = new Program();
        program.TaskA(categories, operations, receipts, output1);
        // program.TaskB(categories, operations, receipts, output2);
        // program.TaskC(categories, operations, receipts, output3, categoryId);
    }

    public void TaskA(List<Category> categories, List<Operation> operations, List<Receipt> receipts, string output)
    {
        var query = from receipt in receipts
                    join category in categories on receipt.CategoryId equals category.Id
                    join operation in operations on receipt.OperationId equals operation.Id
                    group new { receipt, operation } by category.Name into groupCategory
                    orderby groupCategory.Key
                    select new 
                    {
                        categoryName = groupCategory.Key,
                        operationList = from groupC in groupCategory
                                        group new {groupC.operation, groupC.receipt} by groupC.operation.Name 
                                        into groupOperation
                                        orderby groupOperation.Count() descending
                                        select new
                                        {
                                            operationName = groupOperation.Key,
                                            operationCount = groupOperation.Count()
                                        }
                    };
    
        var doc = new XDocument(
            new XElement("Categories",
                query.Select(category => new XElement("Category",
                    new XAttribute("Name", category.categoryName),
                    category.operationList.Select(op => new XElement("Operation",
                        new XAttribute("Name", op.operationName),
                        new XAttribute("Count", op.operationCount)
                        )
                    )
                    )
                )
            )
        );

        doc.Save(output);
    }

    // public void TaskB(List<Category> categories, List<Operation> operations, List<Receipt> receipts, string output)
    // {
    //     var query = from receipt in receipts
    //                 join category in categories on receipt.CategoryId equals category.Id
    //                 join operation in operations on receipt.OperationId equals operation.Id
    //                 group new {category, operation, receipt} by category.Name into groupCategory
    //                 orderby groupCategory.Key
    //                 select new 
    //                 {
    //                     categoryName = groupCategory.Key,
    //                     operationList = from groupC in groupCategory
    //                                     group new {groupC.operation, groupC.receipt, groupC.category} by groupC.operation.Name
    //                                     into groupOperation
    //                                     orderby groupOperation
    //                                             .Where(x => x.category.WarrantyYears + x.receipt.Year < DateTime.Now.Year)
    //                                             .Sum(x => x.operation.Cost)
    //                                             descending
    //                                     select new
    //                                     {
    //                                         operationName = groupOperation.Key,
    //                                         totalCost = groupOperation
    //                                                     .Where(x => x.category.WarrantyYears + x.receipt.Year < DateTime.Now.Year)
    //                                                     .Sum(x => x.operation.Cost)
                                                        
    //                                     }
    //                 };
    
    //     var doc = new XDocument(
    //         new XElement("Categories",
    //             query.Select(category => new XElement("Category",
    //                 new XAttribute("Name", category.categoryName),
    //                 category.operationList.Select(op => new XElement("Operation",
    //                     new XAttribute("Name", op.operationName),
    //                     new XAttribute("TotalCost", op.totalCost)
    //                 ))
    //             ))
    //         )
    //     );

    //     doc.Save(output);
    // }

    // public void TaskC(List<Category> categories, List<Operation> operations, List<Receipt> receipts, string output, int categoryId)
    // {
    //     var query = from receipt in receipts
    //                 join category in categories on receipt.CategoryId equals category.Id
    //                 join operation in operations on receipt.OperationId equals operation.Id
    //                 where (category.Id == categoryId)
    //                 && (category.WarrantyYears + receipt.Year >= DateTime.Now.Year)
    //                 group operation by operation.Name into groupOperation
    //                 orderby groupOperation.Count() descending
    //                 select new
    //                 {
    //                     operationName = groupOperation.Key,
    //                     operationCount = groupOperation.Count()
    //                 };
    
    //     var doc = new XDocument(
    //         new XElement("Operations",
    //             query.Select(op => new XElement("Operation",
    //                 new XAttribute("Name", op.operationName),
    //                 new XAttribute("Count", op.operationCount)
    //                 )
    //             )
    //         )
    //     );

    //     doc.Save(output);
    // }
}
