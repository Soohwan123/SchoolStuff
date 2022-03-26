using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace ExerciseDAL
{
    public class CourseDAO
    {
        readonly IRepository<Course> repo;

        public CourseDAO()
        {
            repo = new SomeSchoolRepository<Course>();
        }

        public async Task<List<Course>> GetCoursesByStudentId(int studentId)
        {
            List<Course> studentCourses = new List<Course>();

            List<Grade> studentGrades = await new GradeDAO().GetGradesByStudentId(studentId);
            foreach (var grade in studentGrades)
            {
                studentCourses.Add(grade.Course);
            }
            return studentCourses;
        }
    }
}