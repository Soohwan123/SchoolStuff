using System;
using System.Collections.Generic;

#nullable disable

namespace ExerciseDAL
{
    public partial class Course : SchoolEntity
    {
        public Course()
        {
            Grades = new HashSet<Grade>();
        }


        public string Name { get; set; }
        public int Credits { get; set; }
        public int DivisionId { get; set; }


        public virtual Division Division { get; set; }
        public virtual ICollection<Grade> Grades { get; set; }
    }
}
