using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace ExerciseDAL
{
    public class StudentDAO
    {
        readonly IRepository<Student> repo;

        public StudentDAO()
        {
            repo = new SomeSchoolRepository<Student>();
        }

        public async Task<Student> GetbyLastName(string name)
        {
            return await repo.GetOne(stu => stu.LastName == name);
        }
        //public async Task<Student> GetbyLastName(string name)
        //{
        //    Student selectedStudent = null;
        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        selectedStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.LastName == name);
        //    }
        //    catch(Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return selectedStudent;
        //}

        public async Task<Student> GetById(int id)
        {
            return await repo.GetOne(stu => stu.Id == id);
        }
        //public async Task<Student> GetById(int id)
        //{
        //    Student selectedStudent = null;

        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        selectedStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.Id == id);
        //    }
        //    catch (Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return selectedStudent;
        //}

        public async Task<List<Student>> GetAll()
        {
            return await repo.GetAll();
        }
        //public async Task<List<Student>> GetAll()
        //{
        //    List<Student> allStudents = new List<Student>();
        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        allStudents = await _db.Students.ToListAsync();
        //    }
        //    catch(Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return allStudents;
        //}

        public async Task<int> Add(Student newStudent)
        {
            return (await repo.Add(newStudent)).Id;
        }
        //public async Task<int> Add(Student newStudent)
        //{
        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        await _db.Students.AddAsync(newStudent);
        //        await _db.SaveChangesAsync();
        //    }
        //    catch(Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return newStudent.Id;
        //}


        public async Task<UpdateStatus> Update(Student updatedStudent)
        {
            return await repo.Update(updatedStudent);
        }
        //public async Task<UpdateStatus> Update(Student updatedStudent)
        //{
        //    UpdateStatus operationStatus = UpdateStatus.Failed;
        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        Student currentStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.Id == updatedStudent.Id);
        //        _db.Entry(currentStudent).OriginalValues["Timer"] = updatedStudent.Timer;
        //        _db.Entry(currentStudent).CurrentValues.SetValues(updatedStudent);
        //        if (await _db.SaveChangesAsync() == 1)
        //        {
        //            operationStatus = UpdateStatus.Ok;
        //        }
        //    }
        //    catch (DbUpdateConcurrencyException)
        //    {
        //        operationStatus = UpdateStatus.Stale;
        //    }
        //    catch (Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return operationStatus;
        //}
        public async Task<int> Delete(int id)
        {
            return await repo.Delete(id);
        }
        //public async Task<int> Delete(int id)
        //{
        //    int studentsDeleted = -1;
        //    try
        //    {
        //        SomeSchoolContext _db = new SomeSchoolContext();
        //        Student selectedStudent = await _db.Students.FirstOrDefaultAsync(stu => stu.Id == id);
        //        _db.Students.Remove(selectedStudent);
        //        studentsDeleted = await _db.SaveChangesAsync(); //returns # of rows removed
        //    }
        //    catch (Exception ex)
        //    {
        //        Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
        //        throw;
        //    }
        //    return studentsDeleted;
        //}


    } 
}
