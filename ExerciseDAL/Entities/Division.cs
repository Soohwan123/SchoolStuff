using System;
using System.Collections.Generic;

#nullable disable

namespace ExerciseDAL
{
    public partial class Division : SchoolEntity
    {
        public Division()
        {
            Courses = new HashSet<Course>();
            Students = new HashSet<Student>();
        }
        public string Name { get; set; }
        public virtual ICollection<Course> Courses { get; set; }
        public virtual ICollection<Student> Students { get; set; }
    }
}
