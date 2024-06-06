using System.Threading.Tasks;
using System.Xml.Linq;

public class Brigade
{
    public int Id { get; set; }
    public string Name { get; set; }
    public Brigade(int id, string name)
    {
        Id = id; 
        Name = name; 
    }
}

public class Prystryi
{
    public int Id { get; set; }
    public string Name { get; set; }
    public Prystryi(int id, string name)
    {
        Id = id;
        Name = name;
    }
}

public class Worker
{
    public int Id { get; set; }
    public string Surname { get; set; }
    public int TariffId { get; set; }
    public int BrigadeId { get; set; }
    public Worker(int id, string surname, int tariffId, int brigadeId)
    {
        Id = id;
        Surname = surname;
        TariffId = tariffId;
        BrigadeId = brigadeId;
    }
}

public class Tariff
{
    public int Id { get; set; }
    public int Cost { get; set; }
    public Tariff(int id, int cost)
    {
        Id = id;
        Cost = cost;
    }
}

public class Receipt
{
    public int WorkerId { get; set; }
    public int HoursSpent { get; set; }
    public int PrystriyId { get; set; }
    public int PrystryiCount { get; set; }
}

public class Data
{
    public List<Brigade> Brigades { get; set; }
    public List<Prystryi> Prystyis { get; set; }
    public List<Worker> Workers { get; set; }
    public List<Tariff> Tariffs { get; set; }
    public List<Receipt> Receipts { get; set; }

    public Data()
    {
        Brigades = new List<Brigade>
        {
            new Brigade(1, "Brigade1"),
            new Brigade(2, "Brigade2")
        };
        Prystyis = new List<Prystryi>
        {
            new Prystryi(1, "Prystryi 1"),
            new Prystryi(2, "Prystryi 2")
        };
        Workers = new List<Worker>
        {
            new Worker(1, "Furman", 1, 1),
            new Worker(2, "Dudynets", 2, 1),
            new Worker(3, "Urbanskyi", 1, 2)
        };
        Tariffs = new List<Tariff>
        {
            new Tariff(1, 20),
            new Tariff(2, 25)
        };
        Receipts = new List<Receipt>();

    }

    public static decimal CalculateCost(int tariffcost, int hours)
    {
        return tariffcost * hours;
    }

    public static decimal CalculateCount(int tariffcost, int hours)
    {
        return tariffcost * hours;
    }
    public List<Receipt> Load1(string filePath)
    {
        XDocument doc = XDocument.Load(filePath);
        return doc.Descendants("Item")
            .Select(x => new Receipt
            {
                WorkerId = (int)x.Element("WorkerId"),
                HoursSpent = (int)x.Element("HoursSpent"),
                PrystriyId = (int)x.Element("PrystriyId"),
                PrystryiCount = (int)x.Element("PrystryiCount")
            })
            .ToList();
    }

    public List<string> TaskA(string output)
    {
        var query = from receipt in Receipts
                    join worker in Workers on receipt.WorkerId equals worker.Id
                    join prystryi in Prystyis on receipt.PrystriyId equals prystryi.Id
                    join brigade in Brigades on worker.BrigadeId equals brigade.Id
                    join tariff in Tariffs on worker.TariffId equals tariff.Id
                    group new { receipt, worker, prystryi, brigade, tariff } by brigade.Name into grBrigades
                    orderby grBrigades.Key
                    select new
                    {
                        Name = grBrigades.Key,
                        WorkerList = from grB in grBrigades
                                     group new { grB.receipt, grB.worker, grB.prystryi, grB.brigade, grB.tariff }
                                     by grB.worker.Surname into grWorkers
                                     orderby grWorkers.Key
                                     select new
                                     {
                                         Name = grWorkers.Key,
                                         Cost = grWorkers
                                                .Sum(x => CalculateCost(x.tariff.Cost, x.receipt.HoursSpent))
                                     }
                    };


        var doc = new XDocument(
            new XElement("Brigades",
                query.Select(group => new XElement("Brigade",
                    new XAttribute("Name", group.Name),
                    group.WorkerList.Select(st => new XElement("Worker",
                        new XAttribute("Name", st.Name),
                        new XAttribute("TotalCost", st.Cost)
                    )
                )
            )))
        );

        if (output != "")
        {
            doc.Save(output);
        }

        var res = new List<string>();
        foreach (var brigade in query)
        {
            foreach (var worker in brigade.WorkerList)
            {
                res.Add($"{brigade.Name} {worker.Name} {worker.Cost}");
            }
        }

        return res;
    }

    public List<string> TaskB(string output)
    {

        var query = from receipt in Receipts
                    join worker in Workers on receipt.WorkerId equals worker.Id
                    join prystryi in Prystyis on receipt.PrystriyId equals prystryi.Id
                    join brigade in Brigades on worker.BrigadeId equals brigade.Id
                    join tariff in Tariffs on worker.TariffId equals tariff.Id
                    group new { receipt, worker, prystryi, brigade, tariff } by prystryi.Name into grPrystryis
                    //orderby grPrystryis.Key
                    select new
                    {
                        Name = grPrystryis.Key,
                        Count = grPrystryis
                                .Sum(x => x.receipt.PrystryiCount)
                    };

        var doc = new XDocument(new XElement("Prystryis",
            query.OrderByDescending(g => g.Count)
            .Select(g => new XElement("Prystryi",
                new XAttribute("Name", g.Name),
                new XAttribute("Count", g.Count)
            ))
        ));


        if (output != "")
        {
            doc.Save(output);
        }

        var res = new List<string>();
        
        foreach (var pr in query)
        {
            res.Add($"{pr.Name} {pr.Count}");
        }

        return res;
    }

    public List<string> TaskC(string output)
    {
        var res = new List<string>();
        return res;
    }
}