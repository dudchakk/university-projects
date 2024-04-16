namespace TestProjectWorkers;
using System;
using System.Collections.Generic;
using System.Linq;
using Xunit;

public class Employee
{
    public int Id { get; set; }
    public int GradeNumber { get; set; }
    public string LastName { get; set; }

    public Employee(int id, int gradeNumber, string lastName)
    {
        Id = id;
        GradeNumber = gradeNumber;
        LastName = lastName;
    }
}

public class TimesheetEntry
{
    public int EmployeeId { get; set; }
    public DateTime Date { get; set; }
    public int HoursWorked { get; set; }

    public TimesheetEntry(int employeeId, DateTime date, int hoursWorked)
    {
        EmployeeId = employeeId;
        Date = date;
        HoursWorked = hoursWorked;
    }
}

public class ServiceReceipt
{
    public int EmployeeId { get; set; }
    public DateTime Date { get; set; }
    public int ServiceId { get; set; }

    public ServiceReceipt(int employeeId, DateTime date, int serviceId)
    {
        EmployeeId = employeeId;
        Date = date;
        ServiceId = serviceId;
    }
}

public class Rates
{
    public int GradeNumber { get; set; }
    public decimal HourlyRate { get; set; }

    public Rates(int gradeNumber, decimal hourlyRate)
    {
        GradeNumber = gradeNumber;
        HourlyRate = hourlyRate;
    }
}

public class Service
{
    public int Id { get; set; }
    public string Name { get; set; }
    public decimal Cost { get; set; }

    public Service(int id, string name, decimal cost)
    {
        Id = id;
        Name = name;
        Cost = cost;
    }
}

public class WorkersData : IDisposable
{
    public List<Employee> Employees { get; }
    public List<TimesheetEntry> TimesheetEntries { get; }
    public List<ServiceReceipt> ServiceReceipts { get; }
    public List<Rates> Rates { get; }
    public List<Service> Services { get; }

    public WorkersData()
    {
        Employees = new List<Employee>
        {
            new Employee(1, 3, "Smith"),
            new Employee(2, 2, "Johnson"),
            new Employee(3, 1, "Williams")
        };

        TimesheetEntries = new List<TimesheetEntry>
        {
            new TimesheetEntry(1, new DateTime(2023, 4, 4), 8),
            new TimesheetEntry(1, new DateTime(2023, 4, 24), 8),
            new TimesheetEntry(1, new DateTime(2023, 3, 4), 8),
            new TimesheetEntry(2, new DateTime(2023, 4, 27), 7),
            new TimesheetEntry(3, new DateTime(2023, 3, 15), 6)
        };

        ServiceReceipts = new List<ServiceReceipt>
        {
            new ServiceReceipt(1, new DateTime(2023, 6, 10), 101),
            new ServiceReceipt(2, new DateTime(2023, 4, 15), 101),
            new ServiceReceipt(2, new DateTime(2023, 4, 15), 102),
            new ServiceReceipt(3, new DateTime(2023, 12, 20), 103)
        };

        Rates = new List<Rates>
        {
            new Rates(1, 15.50m),
            new Rates(2, 20.25m),
            new Rates(3, 25.75m)
        };

        Services = new List<Service>
        {
            new Service(101, "Cleaning", 30.50m),
            new Service(102, "Repair", 50.75m),
            new Service(103, "Consulting", 80.00m)
        };
    }
    public void Dispose()
    {
        Employees.Clear();
        TimesheetEntries.Clear();
        ServiceReceipts.Clear();
        Rates.Clear();
        Services.Clear();
    }
}

public class ClassFunctionalityTests : IClassFixture<WorkersData>
{
    WorkersData fixture;
    public ClassFunctionalityTests(WorkersData fixture)
    {
        this.fixture = fixture;
    }

    [Fact]
    public void TestEmployeeFunctionality()
    {
        int id = 1;
        int gradeNumber = 3;
        string lastName = "Smith";
        var employee1 = fixture.Employees[0];

        Assert.Equal(id, employee1.Id);
        Assert.Equal(gradeNumber, employee1.GradeNumber);
        Assert.Equal(lastName, employee1.LastName);
    }

    [Fact]
    public void TestTimesheetEntryFunctionality()
    {
        int employeeId = 1;
        DateTime date = new DateTime(2023, 4, 4);
        int hoursWorked = 8;
        var timesheetEntry1 = fixture.TimesheetEntries[0];

        Assert.Equal(employeeId, timesheetEntry1.EmployeeId);
        Assert.Equal(date, timesheetEntry1.Date);
        Assert.Equal(hoursWorked, timesheetEntry1.HoursWorked);
    }

    [Fact]
    public void TestServiceReceiptFunctionality()
    {
        int employeeId = 1;
        DateTime date = new DateTime(2023, 6, 10);
        int serviceId = 101;
        var serviceReceipt1 = fixture.ServiceReceipts[0];

        Assert.Equal(employeeId, serviceReceipt1.EmployeeId);
        Assert.Equal(date, serviceReceipt1.Date);
        Assert.Equal(serviceId, serviceReceipt1.ServiceId);
    }

    [Fact]
    public void TestRatesFunctionality()
    {
        int gradeNumber = 1;
        decimal hourlyRate = 15.50m;
        var rate1 = fixture.Rates[0];

        Assert.Equal(gradeNumber, rate1.GradeNumber);
        Assert.Equal(hourlyRate, rate1.HourlyRate);
    }

    [Fact]
    public void TestServiceFunctionality()
    {
        int id = 101;
        string name = "Cleaning";
        decimal cost = 30.50m;
        var service1 = fixture.Services[0];

        Assert.Equal(id, service1.Id);
        Assert.Equal(name, service1.Name);
        Assert.Equal(cost, service1.Cost);
    }
}

public class TasksTests : IClassFixture<WorkersData>
{
    WorkersData fixture;

    public TasksTests(WorkersData fixture)
    {
        this.fixture = fixture;
    }

    [Fact]
    public void TaskATest()
    {
        Dictionary<int, int> taskAResult = Program.TaskA(fixture.TimesheetEntries);

        var correctResult = new Dictionary<int, int>
        {
            {4, 23},
            {3, 14}
        };

        Assert.Equal(correctResult.Count, taskAResult.Count);
        foreach (var pair in correctResult)
        {
            Assert.Equal(correctResult[pair.Key], taskAResult[pair.Key]);
        }
    }

    [Fact]
    public void TaskBTest()
    {
        Dictionary<int, decimal[]> taskBResult = Program.TaskB(fixture.Employees, fixture.TimesheetEntries, 
        fixture.ServiceReceipts, fixture.Rates, fixture.Services);

        var correctResult = new Dictionary<int, decimal[]>
        {
            {1, [412.00m, 0m, 412.00m]},
            {2, [141.75m, 81.25m, 60.50m]}
        };

        Assert.Equal(correctResult.Count, taskBResult.Count);
        foreach (var pair in correctResult)
        {
            Assert.Equal(correctResult[pair.Key], taskBResult[pair.Key]);
        }
    }

    [Fact]
    public void TaskCTest()
    {
        Dictionary<int, decimal> taskCResult = Program.TaskC(fixture.ServiceReceipts, fixture.Services);

        var correctResult = new Dictionary<int, decimal>
        {
            {101, 61.00m},
            {102, 50.75m},
            {103, 80.00m}
        };

        Assert.Equal(correctResult.Count, taskCResult.Count);
        foreach (var pair in correctResult)
        {
            Assert.Equal(correctResult[pair.Key], taskCResult[pair.Key]);
        }
    }
}

public class Program
{
    public static Dictionary<int, int> TaskA(List<TimesheetEntry> timesheetEntries)
    {
        var monthlyTotalHoursWorked = new Dictionary<int, int>();

        foreach(var entry in timesheetEntries)
        {
            int month = entry.Date.Month;
            
            if (!monthlyTotalHoursWorked.ContainsKey(month))
            {
                monthlyTotalHoursWorked[month] = 0;
            }
            monthlyTotalHoursWorked[month] += entry.HoursWorked;
        }

        return monthlyTotalHoursWorked;
    }

    public static Dictionary<int, decimal[]> TaskB(List<Employee> employees, List<TimesheetEntry> timesheetEntries,
    List<ServiceReceipt> serviceReceipts, List<Rates> rates, List<Service> services)
    {
        DateTime startDate = new DateTime(2023, 4, 1);
        DateTime endDate = new DateTime(2023, 4, 30);

        var filteredTimesheetEntries = timesheetEntries.Where(entry => entry.Date >= startDate && entry.Date <= endDate);
        var filteredServiceReceipts = serviceReceipts.Where(receipt => receipt.Date >= startDate && receipt.Date <= endDate);

        Dictionary<int, decimal> employeeSalary = new Dictionary<int, decimal>();
        foreach (var entry in filteredTimesheetEntries)
        {
            var employee = employees.FirstOrDefault(emp => emp.Id == entry.EmployeeId);
            var rate = rates.FirstOrDefault(r => r.GradeNumber == employee.GradeNumber);
            decimal hourlyRate = rate != null ? rate.HourlyRate : 0;
            decimal salary = entry.HoursWorked * hourlyRate;

            if (!employeeSalary.ContainsKey(entry.EmployeeId))
            {
                employeeSalary[entry.EmployeeId] = 0;
            }
            employeeSalary[entry.EmployeeId] += salary;
        }

        Dictionary<int, decimal> employeeServicePayment = new Dictionary<int, decimal>();
        foreach (var receipt in filteredServiceReceipts)
        {
            var service = services.FirstOrDefault(s => s.Id == receipt.ServiceId);
            if (employeeServicePayment.ContainsKey(receipt.EmployeeId))
            {
                employeeServicePayment[receipt.EmployeeId] += service.Cost;
            }
            else
            {
                employeeServicePayment[receipt.EmployeeId] = service.Cost;
            }
        }

        Dictionary<int, decimal[]> employeeSummary = new Dictionary<int, decimal[]>();

        foreach (var entry in filteredTimesheetEntries)
        {
            var employee = employees.FirstOrDefault(emp => emp.Id == entry.EmployeeId);
            var rate = rates.FirstOrDefault(r => r.GradeNumber == employee.GradeNumber);
            decimal hourlyRate = rate != null ? rate.HourlyRate : 0;
            decimal salary = entry.HoursWorked * hourlyRate;

            decimal servicePayment = employeeServicePayment.ContainsKey(entry.EmployeeId) ? employeeServicePayment[entry.EmployeeId] : 0;

            if (!employeeSummary.ContainsKey(entry.EmployeeId))
            {
                employeeSummary[entry.EmployeeId] = new decimal[3];
            }
            employeeSummary[entry.EmployeeId][0] += salary;
            employeeSummary[entry.EmployeeId][1] += servicePayment;
        }

        foreach (var pair in employeeSummary)
        {
            decimal difference = pair.Value[0] - pair.Value[1];
            employeeSummary[pair.Key][2] = difference;
        }

        return employeeSummary;
    }

    public static Dictionary<int, decimal> TaskC(List<ServiceReceipt> serviceReceipts, List<Service> services)
    {
        Dictionary<int, decimal> serviceTotalAmount = new Dictionary<int, decimal>();
        
        foreach (var receipt in serviceReceipts)
        {
            if (!serviceTotalAmount.ContainsKey(receipt.ServiceId))
            {
                serviceTotalAmount[receipt.ServiceId] = 0;
            }
            serviceTotalAmount[receipt.ServiceId] += services.First(s => s.Id == receipt.ServiceId).Cost;
        }

        return serviceTotalAmount;
    }
}