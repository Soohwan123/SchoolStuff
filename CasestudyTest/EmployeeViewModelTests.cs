using HelpdeskViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Xunit;

namespace CaseempdyTests
{
    public class EmployeeViewModelTests
    {
        [Fact]
        public async Task Employee_GetByEmail()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Email = "bs@abc.com" };
                await vm.GetByEmail();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm);
        }


        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Id = 2 };
                await vm.GetById();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Lastname);
        }



        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeViewModel vm = new EmployeeViewModel();
            var stus = await vm.GetAll();
            int result = stus.Count;

            Assert.True(result > 0);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeViewModel model = new EmployeeViewModel();

            model.Firstname = "Soohwan";
            model.Lastname = "Lauersen";
            model.Phoneno = "(555)555-1234";
            model.Title = "Mr.";
            model.DepartmentID = 100;
            model.Email = "sk@sk.com";

            await model.Add();
            Assert.True(model.Id > 1);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            EmployeeViewModel model = new EmployeeViewModel();
            model.Firstname = "Soohwan";
            model.Lastname = "Lauersen";
            model.Phoneno = "(555)555-1234";
            model.Title = "Mr.";
            model.DepartmentID = 100;
            model.Email = "sk@sk.com";

            await model.GetByEmail();
            model.Phoneno = model.Phoneno == "(555)555-1234" ? "(555)555-5552" : "(555)555-1234";

            Assert.True(await model.Update() == 1);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            EmployeeViewModel vm = new EmployeeViewModel();
            vm.Email = "sk@sk.com";
            await vm.GetByEmail();
            Assert.True(await vm.Delete() == 1);
        }
    }
}