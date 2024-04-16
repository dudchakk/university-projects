using System;
using System.Collections.Generic;
using System.Linq;

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

class Program
{
    static void Main(string[] args)
    {
        List<Employee> employees = new List<Employee>
        {
            new Employee(1, 3, "Smith"),
            new Employee(2, 2, "Johnson"),
            new Employee(3, 1, "Williams")
        };

        List<TimesheetEntry> timesheetEntries = new List<TimesheetEntry>
        {
            new TimesheetEntry(1, new DateTime(2023, 4, 4), 8),
            new TimesheetEntry(1, new DateTime(2023, 4, 24), 8),
            new TimesheetEntry(1, new DateTime(2023, 3, 4), 8),
            new TimesheetEntry(2, new DateTime(2023, 4, 27), 7),
            new TimesheetEntry(3, new DateTime(2023, 3, 15), 6)
        };

        List<ServiceReceipt> serviceReceipts = new List<ServiceReceipt>
        {
            new ServiceReceipt(1, new DateTime(2023, 6, 10), 101),
            new ServiceReceipt(2, new DateTime(2023, 4, 15), 101),
            new ServiceReceipt(2, new DateTime(2023, 4, 15), 102),
            new ServiceReceipt(3, new DateTime(2023, 12, 20), 103)
        };

        List<Rates> rates = new List<Rates>
        {
            new Rates(1, 15.50m),
            new Rates(2, 20.25m),
            new Rates(3, 25.75m)
        };

        List<Service> services = new List<Service>
        {
            new Service(101, "Cleaning", 30.50m),
            new Service(102, "Repair", 50.75m),
            new Service(103, "Consulting", 80.00m)
        };

        Console.WriteLine("Employees:");
        foreach (var employee in employees)
        {
            Console.WriteLine($"ID: {employee.Id}, Grade Number: {employee.GradeNumber}, Last Name: {employee.LastName}");
        }

        Console.WriteLine("\nTimesheet Entries:");
        foreach (var entry in timesheetEntries)
        {
            Console.WriteLine($"Employee ID: {entry.EmployeeId}, Date: {entry.Date.ToShortDateString()}, Hours Worked: {entry.HoursWorked}");
        }

        Console.WriteLine("\nService Receipts:");
        foreach (var receipt in serviceReceipts)
        {
            Console.WriteLine($"Employee ID: {receipt.EmployeeId}, Date: {receipt.Date.ToShortDateString()}, Service ID: {receipt.ServiceId}");
        }

        Console.WriteLine("\nRates:");
        foreach (var rate in rates)
        {
            Console.WriteLine($"Grade Number: {rate.GradeNumber}, Hourly Rate: {rate.HourlyRate}");
        }

        Console.WriteLine("\nServices:");
        foreach (var service in services)
        {
            Console.WriteLine($"ID: {service.Id}, Name: {service.Name}, Cost: {service.Cost}");
        }


        // а:

        Dictionary<int, int> monthlyTotalHoursWorked = new Dictionary<int, int>();

        foreach(var entry in timesheetEntries)
        {
            int month = entry.Date.Month;
            
            if (!monthlyTotalHoursWorked.ContainsKey(month))
            {
                monthlyTotalHoursWorked[month] = 0;
            }
            monthlyTotalHoursWorked[month] += entry.HoursWorked;
        }

        Console.WriteLine("\n---------------\nTask a:\n");
        foreach (var month in monthlyTotalHoursWorked)
        {
            Console.WriteLine($"Місяць: {month.Key}, Загальна кількість годин: {month.Value}");
        }


        // б:

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

        Console.WriteLine("\n---------------\nTask б:\n");
        Console.WriteLine("Зарплата | Оплата послуг | До виплати");
        foreach (var employee in employees)
        {
            decimal salary = employeeSalary.ContainsKey(employee.Id) ? employeeSalary[employee.Id] : 0;
            decimal servicePayment = employeeServicePayment.ContainsKey(employee.Id) ? employeeServicePayment[employee.Id] : 0;
            decimal totalPayment = salary - servicePayment;
            Console.WriteLine($"{employee.LastName}: {salary} год. | {servicePayment} грн. | {totalPayment} год.");
        }


        // в:

        Dictionary<int, decimal> serviceTotalAmount = new Dictionary<int, decimal>();
        
        foreach (var receipt in serviceReceipts)
        {
            if (!serviceTotalAmount.ContainsKey(receipt.ServiceId))
            {
                serviceTotalAmount[receipt.ServiceId] = 0;
            }
            serviceTotalAmount[receipt.ServiceId] += services.First(s => s.Id == receipt.ServiceId).Cost;
        }

        Console.WriteLine("\n---------------\nTask б:\n");
        Console.WriteLine("Суми за кожен вид послуги за весь період часу:");
        foreach (var pair in serviceTotalAmount)
        {
            Console.WriteLine($"Послуга ID {pair.Key}: {pair.Value} грн.");
        }
    }
}
