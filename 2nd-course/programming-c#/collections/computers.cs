using System;
using System.Collections.Generic;

class Computer
{
    public string Name { get; }
    public double CPU_Speed { get; set; }
    public int RAM { get; set; }
    public int Disk { get; set; }
    public double Price { get; set; }

    public Computer(string brand, double cpuSpeed, int ram, int disk, double price)
    {
        Name = brand;
        CPU_Speed = cpuSpeed;
        RAM = ram;
        Disk = disk;
        Price = price;
    }

    public override string ToString()
    {
        return $"Brand: {Name}, CPU Speed: {CPU_Speed} GHz, RAM Size: {RAM} GB, Disk Size: {Disk} GB, Price: ${Price}";
    }
}

class Server : Computer
{
    public int AdditionalDisk { get; set; }

    public Server(string brand, double cpuSpeed, int ram, int disk, double price, int additionalDisk)
        : base(brand, cpuSpeed, ram, disk, price)
    {
        AdditionalDisk = additionalDisk;
    }
    
    public override string ToString()
    {
        return base.ToString() + $", Additional Disk: {AdditionalDisk} GB";
    }
}

class WorkStation : Computer
{
    public string MonitorBrand { get; set; }
    public double MonitorSize { get; set; }

    public WorkStation(string brand, double cpuSpeed, int ram, int disk, double price, string monitorBrand, double monitorSize)
        : base(brand, cpuSpeed, ram, disk, price)
    {
        MonitorBrand = monitorBrand;
        MonitorSize = monitorSize;
    }

    public override string ToString()
    {
        return base.ToString() + $", Monitor Brand: {MonitorBrand}, Monitor Size: {MonitorSize} inch";
    }
}

class mainpr
{
    static void Main(string[] args)
    {
        var computers = new Computer[]
        {
            new Computer("HP", 2.8, 8, 512, 800),
            new Computer("Acer", 3.0, 16, 1024, 1000),
            new Computer("HP", 3.2, 32, 2048, 1200)
        };
        var servers = new Server[]
        {
            new Server("Dell", 3.2, 16, 1024, 1200, 2048),
            new Server("IBM", 3.5, 32, 2048, 1500, 4096)
        };
        var workstations = new WorkStation[]
        {
            new WorkStation("Lenovo", 4.0, 32, 1024, 1500, "Samsung", 24),
            new WorkStation("Apple", 4.2, 64, 2048, 2000, "LG", 27)
        };
        
        //a
        Console.WriteLine("Computers:");
        foreach (var computer in computers)
        {
            Console.WriteLine(computer.ToString());
        }

        Console.WriteLine("\nServers:");
        foreach (var server in servers)
        {
            Console.WriteLine(server.ToString());
        }

        Console.WriteLine("\nWorkstations:");
        foreach (var workstation in workstations)
        {
            Console.WriteLine(workstation.ToString());
        }
        
        //b
        var brands = new List<string>();
        foreach (var computer in computers)
        {
            if (!brands.Contains(computer.Name))
            {
                brands.Add(computer.Name);
            }
        }
        Console.WriteLine("\nComputers:");
        foreach (var brand in brands)
        {
            double sum = 0;
            foreach (var computer in computers)
            {
                if (computer.Name == brand)
                {
                    sum += computer.Price;
                }
            }

            if (sum != 0)
            {
                Console.WriteLine($"Brand: {brand}, Total Price: ${sum}");
            }
        }
        foreach (var server in servers)
        {
            if (!brands.Contains(server.Name))
            {
                brands.Add(server.Name);
            }
        }
        Console.WriteLine("Servers:");
        foreach (var brand in brands)
        {
            double sum = 0;
            foreach (var server in servers)
            {
                if (server.Name == brand)
                {
                    sum += server.Price;
                }
            }

            if (sum != 0)
            {
                Console.WriteLine($"Brand: {brand}, Total Price: ${sum}");
            }
        }
        foreach (var workstation in workstations)
        {
            if (!brands.Contains(workstation.Name))
            {
                brands.Add(workstation.Name);
            }
        }
        Console.WriteLine("Workstations:");
        foreach (var brand in brands)
        {
            double sum = 0;
            foreach (var workstation in workstations)
            {
                if (workstation.Name == brand)
                {
                    sum += workstation.Price;
                }
            }
            if (sum != 0)
            {
                Console.WriteLine($"Brand: {brand}, Total Price: ${sum}");
            }
        }
        
        //c
        Console.WriteLine("\nServers:");
        foreach (var server in servers)
        {
            Console.WriteLine(server.ToString() + $", Total Disk: {server.Disk + server.AdditionalDisk} GB");
        }
        
        //d
        double maxMonitorSize = 0;
        foreach (var workstation in workstations)
        {
            if (workstation.MonitorSize > maxMonitorSize)
            {
                maxMonitorSize = workstation.MonitorSize;
            }
        }
        Console.WriteLine("\nWorkstations with the biggest monitors:");
        foreach (var workstation in workstations)
        {
            if (workstation.MonitorSize == maxMonitorSize)
            {
                Console.WriteLine(workstation.ToString());
            }
        }
        
        
    }
}
