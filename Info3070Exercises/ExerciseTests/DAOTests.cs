using Microsoft.EntityFrameworkCore;
using System;
using Xunit;
using ExerciseDAL;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace ExerciseTests
{
    public class DAOTests
    {
        [Fact]
        public async Task Student_GetByLastNameTest()
        {
            StudentDAO dao = new ExerciseDAL.StudentDAO();
            Student selectedStudent = await dao.GetbyLastName("Pet");
            Assert.NotNull(selectedStudent);
        }

        [Fact]
        public async Task Student_GetByIdTest()
        {
            StudentDAO dao = new ExerciseDAL.StudentDAO();
            Student selectedStudent = await dao.GetById(2);
            Assert.NotNull(selectedStudent);
        }

        [Fact]
        public async Task Student_GetAllTest()
        {
            StudentDAO dao = new ExerciseDAL.StudentDAO();
            List<Student> allStudents = await dao.GetAll();
            int counts = allStudents.Count;
            Assert.True(counts > 0);
        }

        [Fact]
        public async Task Student_AddTest()
        {
            StudentDAO dao = new StudentDAO();
            Student newStudents = new Student();
            newStudents.FirstName = "Soohwan";
            newStudents.LastName = "Kim";
            newStudents.PhoneNo = "(555)555-12343";
            newStudents.Title = "Mr.";
            newStudents.DivisionId = 10;
            newStudents.Email = "sc@sc.com";
            await dao.Add(newStudents);
            Assert.True(newStudents.Id > 0);
        }

        [Fact]
        public async Task Student_UpdateTest()
        {
            StudentDAO dao = new StudentDAO();
            Student studentForUpdate = await dao.GetbyLastName("Kim");
            if(studentForUpdate != null)
            {
                string oldPhoneNo = studentForUpdate.PhoneNo;
                string newPhoneNo = oldPhoneNo == "519-555-12343" ? "555-555-5555" : "519-555-1234";
                studentForUpdate.PhoneNo = newPhoneNo;
            }
            Assert.True(await dao.Update(studentForUpdate) == UpdateStatus.Ok); //indicates the # of rows updated
        }

        [Fact]
        public async Task Student_DeleteTest()
        {
            StudentDAO stu = new StudentDAO();
            Assert.True(await stu.Delete(13) == 1);
        }

        [Fact]
        public async Task Student_ConcurrencyTest()
        {
            StudentDAO dao1 = new StudentDAO();
            StudentDAO dao2 = new StudentDAO();
            Student studentForUpdate1 = await dao1.GetbyLastName("Kim");
            Student studentForUpdate2 = await dao2.GetbyLastName("Kim");

            if(studentForUpdate1 != null)
            {
                string oldPhoneNo = studentForUpdate1.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555)555-1234" ? "555-555-5555" : "(555)555-1234";
                studentForUpdate1.PhoneNo = newPhoneNo;
                if (await dao1.Update(studentForUpdate1) == UpdateStatus.Ok)
                {
                    //need to change the phone # to something else
                    studentForUpdate2.PhoneNo = "666-666-6666";
                    Assert.True(await dao2.Update(studentForUpdate2) == UpdateStatus.Stale);
                }
                else
                    Assert.True(false);
            }
        }

        [Fact]
        public async Task Student_LoadPicsTest()
        {
            try
            {
                ExercisesDAL.DALUtil util = new ExercisesDAL.DALUtil();
                Assert.True(await util.AddStudentPicsToDb());
       
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
        }
    }
}
