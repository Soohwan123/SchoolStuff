using ExerciseDAL;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using System.Threading.Tasks;
using Xunit;

namespace ExerciseTests
{
    public class LinqTests
    {
        [Fact]
        public void Test1()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            var selectedStudents = from stu in _db.Students
                                   where stu.Id == 2
                                   select stu;

            int stus = selectedStudents.Count();

            Assert.True(selectedStudents.Count() > 0);
        }

        [Fact]
        public void Test2()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            var selectedStudents = from stu in _db.Students
                                   where stu.Title == "Ms." || stu.Title == "Mrs."
                                   select stu;

            Assert.True(selectedStudents.Count() > 0);
        }

        [Fact]
        public void Test3()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            var selectedStudents = from stu in _db.Students
                                   where stu.Division.Id == 50
                                   select stu;


            Assert.True(selectedStudents.Count() > 0);
        }

        //same as Test1
        [Fact]
        public void Test4()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            //FirstOrDefault : return the first of the database or just returns NULL
            Student selectStudent = _db.Students.FirstOrDefault(
                stu =>
                stu.Id == 2
                );

            Assert.True(selectStudent.FirstName == "Teachers");
        }


        //same as Test2
        [Fact]
        public void Test5()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            //FirstOrDefault : return the first of the database or just returns NULL
            var selectStudent = _db.Students.Where(
                stu =>
                stu.Title == "Ms." || stu.Title == "Mrs."
                );

            Assert.True(selectStudent.Count() > 0);
        }

        [Fact]
        public void Test6()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            var selectedStudents = _db.Students.Where(
                stu =>
                stu.Division.Name == "Design"
                );
            var firstStu = selectedStudents.FirstOrDefault();

            Assert.True(selectedStudents.Count() > 0);
        }

        [Fact]
        public async Task Test7()
        {
            SomeSchoolContext _db = new SomeSchoolContext();

            Student selectedStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.Id == 1007);

            if (selectedStudent != null)
            {
                string currentEmail = selectedStudent.Email;
                string newEmail = currentEmail == "sk@sk.com" ? "sc@sc.com" : "sk@sk.com";  //if currentPhoneNo is "519-555-1234" -> change to "555-555-5555", otherwise change to "519-555-1234" 

                selectedStudent.Email = newEmail;
                _db.Entry(selectedStudent).CurrentValues.SetValues(selectedStudent);                    // Entry -> get the entity SetValues -> override the phone number to the number that we just changed
            }

            Assert.True(await _db.SaveChangesAsync() == 1);                                             // This is why we use asny in case of there's too many datas ( SaveChangesAsync -> boolean ) 1 is good, 0 nothing is changed
        }


        //Adding
        [Fact]
        public async Task Test8()
        {
            SomeSchoolContext _db = new SomeSchoolContext();
            Student newStudent = new Student();
            newStudent.FirstName = "Soohwan";
            newStudent.LastName = "Kim";
            newStudent.PhoneNo = "(555)555-1234";
            newStudent.Title = "Mr.";
            newStudent.DivisionId = 10;
            newStudent.Email = "sc@sc.com";
            await _db.Students.AddAsync(newStudent);
            await _db.SaveChangesAsync();
            Assert.True(newStudent.Id > 1);
        }

        [Fact]
        public async Task Test9()
        {
            SomeSchoolContext _db = new SomeSchoolContext();
            Student selectedStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.FirstName == "Soohwan");
            if (selectedStudent != null)
            {
                _db.Students.Remove(selectedStudent);
                Assert.True(await _db.SaveChangesAsync() == 1);
            }
            else
            {
                Assert.True(false);
            }
        }
    }
}
