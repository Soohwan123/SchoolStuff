using ExerciseDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace ExerciseViewModels
{
    public class CourseViewModel
    {
        private CourseDAO _dao;


        public int? Id { get; set; }

        public string Name { get; set; }


        //constructor
        public CourseViewModel()
        {
            _dao = new CourseDAO();
        }

        //find Course using Lastname property

        public async Task<List<CourseViewModel>> GetAllCoursesForStudent(int studentId)
        {
            List<CourseViewModel> allVms = new List<CourseViewModel>();
            try
            {
                List<Course> allCourses = await _dao.GetCoursesByStudentId(studentId);
                foreach (Course course in allCourses)
                {
                    CourseViewModel vm = new CourseViewModel();
                    vm.Id = course.Id;
                    vm.Name = course.Name;
                    allVms.Add(vm);
                }

            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw ex;
            }
            return allVms;
        }
    }
}
