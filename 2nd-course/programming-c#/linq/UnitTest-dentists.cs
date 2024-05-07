namespace TestProject1;
using System;
using Xunit;
using System.Collections.Generic;
using System.IO;
using System.Linq;

public class Patient
{
    public int Id { get; }
    public string Surname { get; set; }
    public DateTime RegistrationDate { get; }

    public Patient(int id, string surname, DateTime registrationDate)
    {
        Id = id;
        Surname = surname;
        RegistrationDate = registrationDate;
    }
}

public class Service
{
    public int Id { get; }
    public string Name { get; set; }
    public decimal Price { get; set; }

    public Service(int id, string name, decimal price)
    {
        Id = id;
        Name = name;
        Price = price;
    }
}

public class Doctor
{
    public int Id { get; }
    public string Surname { get; set; }

    public Doctor(int id, string surname)
    {
        Id = id;
        Surname = surname;
    }
}

public class ServiceReport
{
    public DateTime Date { get; set; }
    public int PatientId { get; }
    public int DoctorId { get; }
    public int ServiceId { get; }
    public int Quantity { get; set; }

    public ServiceReport(DateTime date, int patientId, int doctorId, int serviceId, int quantity)
    {
        Date = date;
        PatientId = patientId;
        DoctorId = doctorId;
        ServiceId = serviceId;
        Quantity = quantity;
    }
}


public class DentistsData : IDisposable
{
    public List<Service> Services { get; set; }
    public List<Patient> Patients { get; set; }
    public List<Doctor> Doctors { get; set; }
    public List<ServiceReport> ServiceReports { get; set; }

    public DentistsData()
    {
        Patients = Program.ReadPatientsFromCSV("patients.csv");
        Doctors = Program.ReadDoctorsFromCSV("doctors.csv");
        Services = Program.ReadServicesFromCSV("services.csv");
        List<ServiceReport> temp = Program.ReadServiceReportsFromCSV("service_reports_1.csv");
        List<ServiceReport> temp2 = Program.ReadServiceReportsFromCSV("service_reports_2.csv");
        
        foreach (var it in temp2)
        {
            temp.Add(it);
        }
        ServiceReports = temp;
    }

    public void Dispose()
    {
        Services.Clear();
        Patients.Clear();
        Doctors.Clear();
        ServiceReports.Clear();
    }
}

public class ClassFunctionalityTests : IClassFixture<DentistsData>
{
    DentistsData fixture;

    public ClassFunctionalityTests(DentistsData fixture)
    {
        this.fixture = fixture;
    }

    [Fact]
    public void TestServiceFunctionality()
    {
        int id = 1;
        string name = "Consultation";
        decimal price = 50;
        var employee1 = fixture.Services[0];

        Assert.Equal(id, employee1.Id);
        Assert.Equal(name, employee1.Name);
        Assert.Equal(price, employee1.Price);
    }

    [Fact]
    public void TestPatientFunctionality()
    {
        int id = 1;
        DateTime date = new DateTime(2020, 4, 15);
        string surname = "Smith";
        var timesheetEntry1 = fixture.Patients[0];

        Assert.Equal(id, timesheetEntry1.Id);
        Assert.Equal(date, timesheetEntry1.RegistrationDate);
        Assert.Equal(surname, timesheetEntry1.Surname);
    }

    [Fact]
    public void TestDoctorsFunctionality()
    {
        int employeeId = 1;
        string surname = "Johnson";
        var serviceReceipt1 = fixture.Doctors[0];

        Assert.Equal(employeeId, serviceReceipt1.Id);
        Assert.Equal(surname, serviceReceipt1.Surname);
    }

    [Fact]
    public void TestServiceReportsFunctionality()
    {
        DateTime date = new DateTime(2024, 4, 20);
        int PatientId = 1;
        int DoctorId = 2;
        int ServiceId = 1;
        int Quantity = 2;
        var rate1 = fixture.ServiceReports[0];

        Assert.Equal(date, rate1.Date);
        Assert.Equal(PatientId, rate1.PatientId);
        Assert.Equal(DoctorId, rate1.DoctorId);
        Assert.Equal(ServiceId, rate1.ServiceId);
        Assert.Equal(Quantity, rate1.Quantity);
    }
}

public class TasksTests : IClassFixture<DentistsData>
{
    DentistsData fixure;

    public TasksTests(DentistsData fixure)
    {
        this.fixure = fixure;
    }

    [Fact]
    public void TaskATest()
    {
        var taskAResult = Program.TaskA(fixure.Doctors, fixure.Services, fixure.ServiceReports, fixure.Patients);

        var correctResult = new List<string>
        {
            "Johnson: 570.0",
            "Davis: 360.0",
            "Brown: 352.5",
            "Williams: 240.0",
            "Jones: 190.0"
        };

        Assert.Equal(correctResult.Count, taskAResult.Count);
        for (int i = 0; i < correctResult.Count; i++)
        {
            Assert.Equal(correctResult[i], taskAResult[i]);
        }
    }
    
    [Fact]
    public void TaskBTest()
    {
        var expectedExpenses = 382.5m;
        var patientSurname = "Williams";
        var startDate = new DateTime(2024, 1, 1);
        var endDate = new DateTime(2024, 12, 31);

        var actualExpenses = Program.TaskB(fixure.ServiceReports, fixure.Patients, fixure.Services, patientSurname, startDate, endDate);

        Assert.Equal(expectedExpenses, actualExpenses);
    }


}

class Program
{
    public static List<Patient> ReadPatientsFromCSV(string filePath)
    {
        List<Patient> patients = new List<Patient>();
        using (var reader = new StreamReader(filePath))
        {
            reader.ReadLine();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split(',');

                int id = int.Parse(values[0]);
                string surname = values[1];
                DateTime registrationDate = DateTime.Parse(values[2]);

                patients.Add(new Patient(id, surname, registrationDate));
            }
        }
        return patients;
    }
    public static List<Doctor> ReadDoctorsFromCSV(string filePath)
    {
        List<Doctor> doctors = new List<Doctor>();
        using (var reader = new StreamReader(filePath))
        {
            reader.ReadLine();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split(',');

                int id = int.Parse(values[0]);
                string surname = values[1];

                doctors.Add(new Doctor(id, surname));
            }
        }
        return doctors;
    }

    public static List<Service> ReadServicesFromCSV(string filePath)
    {
        List<Service> services = new List<Service>();
        using (var reader = new StreamReader(filePath))
        {
            reader.ReadLine();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split(',');

                int id = int.Parse(values[0]);
                string name = values[1];
                decimal price = decimal.Parse(values[2]);

                services.Add(new Service(id, name, price));
            }
        }
        return services;
    }

    public static List<ServiceReport> ReadServiceReportsFromCSV(string filePath)
    {
        List<ServiceReport> serviceReports = new List<ServiceReport>();
        using (var reader = new StreamReader(filePath))
        {
            reader.ReadLine();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split(',');

                DateTime date = DateTime.Parse(values[0]);
                int patientId = int.Parse(values[1]);
                int doctorId = int.Parse(values[2]);
                int serviceId = int.Parse(values[3]);
                int quantity = int.Parse(values[4]);

                serviceReports.Add(new ServiceReport(date, patientId, doctorId, serviceId, quantity));
            }
        }
        return serviceReports;
    }

    public static decimal CalculateDiscount(decimal price, int quantity, DateTime registrationDate, DateTime paymentDate, decimal d)
    {
        int yearsRegistered = paymentDate.Year - registrationDate.Year;

        if (yearsRegistered >= 3)
        {
            decimal discount = price * (d/100);
            return (price - discount) * quantity;
        }
        else
        {
            return price * quantity;
        }
    }

    public static List<string> TaskA(List<Doctor> doctors, List<Service> services, List<ServiceReport> serviceReports, List<Patient> patients)
    {
        var joinedData = from sr in serviceReports
                        join s in services on sr.ServiceId equals s.Id
                        join p in patients on sr.PatientId equals p.Id
                        select new { ServiceReport = sr, Service = s, Patient = p };

        var doctorEarnings = from data in joinedData
                            join d in doctors on data.ServiceReport.DoctorId equals d.Id
                            group data by new { Doctor = d, Patient = data.Patient } into g
                            select new
                            {
                                g.Key.Doctor,
                                g.Key.Patient,
                                TotalEarnings = g.Sum(x => CalculateDiscount(x.Service.Price, x.ServiceReport.Quantity, x.Patient.RegistrationDate, x.ServiceReport.Date, 10))
                            };

        var aggregatedEarnings = from item in doctorEarnings
                                group item by item.Doctor into g
                                select new
                                {
                                    Doctor = g.Key,
                                    TotalEarnings = g.Sum(x => x.TotalEarnings)
                                };

        var sortedEarnings = aggregatedEarnings.OrderByDescending(item => item.TotalEarnings);

        List<string> earningsperDoctor = new List<string>();
        foreach (var item in sortedEarnings)
        {
            earningsperDoctor.Add($"{item.Doctor.Surname}: {item.TotalEarnings}");
        }

        return earningsperDoctor;
    }

    public static decimal TaskB(List<ServiceReport> serviceReports, List<Patient> patients, List<Service> services, string patientSurname, DateTime startDate, DateTime endDate)
    {
        var patient = patients.First(p => p.Surname == patientSurname);

        var totalExpenses = (from sr in serviceReports
                                join p in patients on sr.PatientId equals p.Id
                                join s in services on sr.ServiceId equals s.Id
                                where p.Surname == patientSurname && sr.Date >= startDate && sr.Date <= endDate
                                select CalculateDiscount(s.Price, sr.Quantity, p.RegistrationDate, sr.Date, 10)).Sum();

        return totalExpenses;
    }


}