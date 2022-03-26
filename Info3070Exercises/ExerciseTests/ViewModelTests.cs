using ExerciseViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Xunit;

namespace ExerciseTests
{
    public class ViewModelTests
    {
        [Fact]
        public async Task ViewModel_GetByLastNameTest()
        {
            StudentViewModel vm = null;
            try
            {
                vm = new StudentViewModel { Lastname = "Lauersen" };
                await vm.GetByLastName();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm);
        }


        [Fact]
        public async Task ViewModel_GetByIdTest()
        {
            StudentViewModel vm = null;
            try
            {
                vm = new StudentViewModel { Id = 2 };
                await vm.GetById();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Lastname);
        }


        [Fact]
        public async Task ViewModel_GetAllTest()
        {
            StudentViewModel lvm = null;
            lvm = new StudentViewModel();
            var stus = await lvm.GetAll();
            Assert.True(stus.Count > 0);
        }

        [Fact]
        public async Task ViewModel_AddTest()
        {
            StudentViewModel model = new StudentViewModel();

            model.Firstname = "Soohwan";
            model.Lastname = "Kim";
            model.Phoneno = "(555)555-1234";
            model.Title = "Mr.";
            model.DivisionId = 30;
            model.Email = "sk@sk.com";

            await model.Add();
            Assert.True(model.Id > 1);
        }

        [Fact]
        public async Task ViewModel_UpdateTest()
        {
            StudentViewModel vm = new StudentViewModel() { Lastname = "Kim" };
             await vm.GetByLastName();
            vm.Phoneno = vm.Phoneno == "(555)555-1234" ? "(555)555-5552" : "(555)555-1234";
            Assert.True(await vm.Update() == 1);
        }

        [Fact]
        public async Task ViewModel_DeleteTest()
        {
            StudentViewModel vm = new StudentViewModel();
            vm.Lastname = "Kim";
            await vm.GetByLastName();
            Assert.True(await vm.Delete() == 1);
        }

        [Fact]
        public async Task Student_ConcurrencyTest()
        {
            int studentsUpdated = -1;
            try
            {
                StudentViewModel vm1 = new StudentViewModel { Lastname = "Kim" };
                StudentViewModel vm2 = new StudentViewModel { Lastname = "Kim" };
                await vm1.GetByLastName(); // Student just added
                await vm2.GetByLastName(); // Student just added
                vm1.Phoneno = vm1.Phoneno == "(555)555-1234" ? "(555)555-5552" : "(555)555-1234";
                if(await vm1.Update() == 1)
                {
                    vm2.Phoneno = "(666)666-6666"; // just need any value
                    studentsUpdated = await vm2.Update();
                }
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.True(studentsUpdated == -2);
        }
    }
}
