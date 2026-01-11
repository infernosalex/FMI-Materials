using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laborator2
{
    internal class Employee
    {
        // Definirea atributelor(proprietatilor)
        public int EmployeeId { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public decimal Salary { get; set; }

        // Constructor pentru initializarea obiectului Employee
        public Employee(int employeeId, string firstName, string lastName, decimal salary)
        {
            this.EmployeeId = employeeId;
            this.FirstName = firstName;
            LastName = lastName;
            Salary = salary;
        }

        // Metoda pentru afisarea detaliilor angajatului
        public void Index()
        {
            Console.WriteLine("Employee ID: " + EmployeeId);
            Console.WriteLine("First Name: " + FirstName);
            Console.WriteLine("Last Name: " + LastName);
            Console.WriteLine("Salary: " + Salary);
        }
    }
}
