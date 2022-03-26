using System;
using Xunit;
using HelpdeskDAL;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading.Tasks;
namespace CasestudyTests
{
    public class DAOTests
    {
        [Fact]
        public async Task Employee_GetByEmailTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetbyEmail("bs@abc.com");
            Assert.NotNull(selectedEmployee);
        }
        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetById(2);
            Assert.NotNull(selectedEmployee);
        }

        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            List<Employee> allEmployees = await dao.GetAll();
            Assert.NotNull(allEmployees);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee newEmployees = new Employee();
            await dao.Add(newEmployees);
            Assert.True(newEmployees.Id > 0);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            HelpdeskContext _db = new HelpdeskContext();
            Employee newEmployee = new Employee();
            newEmployee.FirstName = "Soohwan";
            newEmployee.LastName = "Kim";
            newEmployee.PhoneNo = "(555)555-1234";
            newEmployee.Title = "Mr.";
            newEmployee.DepartmentId = 10;
            newEmployee.Email = "sc@sc.com";
            await _db.Employees.AddAsync(newEmployee);
            await _db.SaveChangesAsync();
            Assert.True(newEmployee.Id > 1);

            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Assert.True(await dao.Update(newEmployee) == 1);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            Employee stu = new Employee();
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            await dao.Delete(6);
            Assert.True(await dao.Delete(6) == 1);
        }
    }

}