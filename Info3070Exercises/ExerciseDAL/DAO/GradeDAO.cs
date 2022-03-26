using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace ExerciseDAL
{
    public class GradeDAO
    {
        readonly IRepository<Grade> repo;

        public GradeDAO()
        {
            repo = new SomeSchoolRepository<Grade>();
        }

        public async Task<List<Grade>> GetGradesByStudentId(int stuId)
        {
            return await repo.GetSome(gra => gra.StudentId == stuId);
        }

        public async Task<Grade> GetById(int id)
        {
            return await repo.GetOne(gra => gra.Id == id);
        }

        public async Task<List<Grade>> GetAll()
        {
            return await repo.GetAll();
        }

        public async Task<int> Add(Grade newGrade)
        {
            return (await repo.Add(newGrade)).Id;
        }

        public async Task<UpdateStatus> Update(Grade updatedGrade)
        {
            return await repo.Update(updatedGrade);
        }
    }
}