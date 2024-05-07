﻿using System;
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

class Program
{
    static void Main(string[] args)
    {
        List<Patient> patients = ReadPatientsFromCSV("patients.csv");
        List<Doctor> doctors = ReadDoctorsFromCSV("doctors.csv");
        List<Service> services = ReadServicesFromCSV("services.csv");
        List<ServiceReport> serviceReports = ReadServiceReportsFromCSV("service_reports_1.csv");
        List<ServiceReport> serviceReports2 = ReadServiceReportsFromCSV("service_reports_2.csv");
        
        foreach (var it in serviceReports2)
        {
            serviceReports.Add(it);
        }
        serviceReports2.Clear();

        var taskalist = TaskA(doctors, services, serviceReports, patients);

        foreach (var item in taskalist)
        {
            Console.WriteLine(item);
        }
        
        string surname = "Williams";
        Console.WriteLine($"{surname}: {TaskB(serviceReports, patients, services, surname, new DateTime(2024, 1, 1), new DateTime(2024, 12, 31))}");

    }

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
            decimal discount = price * (d / 100);
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

        List<string> earningsStrings = new List<string>();
        foreach (var item in sortedEarnings)
        {
            earningsStrings.Add($"{item.Doctor.Surname}: {item.TotalEarnings}");
        }

        return earningsStrings;
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