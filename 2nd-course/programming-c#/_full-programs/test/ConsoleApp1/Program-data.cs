
using System.Xml.Linq;

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

public class Data
{
    public List<Patient> Patients {get; set;}

    public Data()
    {
        Patients = new List<Patient>();
    }
    public void ReadPatientsFromCSV(string filePath)
    {
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

                Patients.Add(new Patient(id, surname, registrationDate));
            }
        }
        Console.WriteLine(Patients[1].Surname);
    }

    public void GenerateOutput(string output)
    {
        XDocument doc = new XDocument(
            new XElement("Output",
                new XAttribute("Result", "1")
            )
        );

        doc.Save(output);
    }
}

// class Program
// {
//     static void Main(string[] args)
//     {
//         // Console.WriteLine("1");

//         // var patients = Read.ReadPatientsFromCSV("input/input.csv");

//         // foreach(var p in patients) {
//         //     Console.WriteLine($"{p.Id}, {p.RegistrationDate}, {p.Surname}");
//         // }

//         // Console.WriteLine(patients[0]);
//     }

    
// }