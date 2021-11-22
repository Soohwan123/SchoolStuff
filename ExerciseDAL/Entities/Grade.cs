using System;
using System.Collections.Generic;

#nullable disable

namespace ExerciseDAL
{
    public partial class Grade : SchoolEntity
    { 
        public int StudentId { get; set; }
        public int CourseId { get; set; }
        public int Mark { get; set; }
        public string Comments { get; set; }

        public virtual Course Course { get; set; }
        public virtual Student Student { get; set; }
    }
}
