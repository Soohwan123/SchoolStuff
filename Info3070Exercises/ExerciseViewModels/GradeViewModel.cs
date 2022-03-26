using ExerciseDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace ExerciseViewModels
{
    public class GradeViewModel
    {
        private GradeDAO _dao;


        public int? Id { get; set; }

        public int StudentId { get; set; }
        public int CourseId { get; set; }
        public int Mark { get; set; }
        public string Comments { get; set; }
        public string Timer { get; set; }



        public string ErrorMessage { get; set; }

        //constructor
        public GradeViewModel()
        {
            _dao = new GradeDAO();
        }

        //find Grade using Lastname property

        public async Task<List<GradeViewModel>> GetGradesByStudentId(int studentId)
        {
            List<GradeViewModel> allVms = new List<GradeViewModel>();
            try
            {
                List<Grade> allGradesForStu = await _dao.GetGradesByStudentId(studentId);
                foreach (Grade grade in allGradesForStu)
                {
                    GradeViewModel vm = new GradeViewModel();
                    vm.Id = grade.Id;
                    vm.Timer = Convert.ToBase64String(grade.Timer);
                    vm.StudentId = grade.StudentId;
                    vm.CourseId = grade.CourseId;
                    vm.Comments = grade.Comments;
                    vm.Mark = grade.Mark;
                    allVms.Add(vm);
                }

            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allVms;
        }

        //By the time we hit this method, all of the properties inside this GradeViewModel object will be filled
        public async Task Add()
        {
            Id = -1;
            try
            {
                Grade grade = new Grade();
                grade.Comments = Comments;
                grade.CourseId = CourseId;
                grade.StudentId = StudentId;
                grade.Mark = Mark;

                Id = await _dao.Add(grade);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
        }
        public async Task<int> Update()
        {
            UpdateStatus status = UpdateStatus.Failed;
            try
            {
                Grade grade = new Grade();
                grade.Comments = Comments;
                grade.CourseId = CourseId;
                grade.StudentId = StudentId;
                grade.Mark = Mark;

                grade.Id = Id.Value;
                grade.Timer = Convert.FromBase64String(this.Timer);
                status = await _dao.Update(grade);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return Convert.ToInt16(status);
        }
    }
}
