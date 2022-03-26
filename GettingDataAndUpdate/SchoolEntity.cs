using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel.DataAnnotations;

namespace ExerciseDAL
{
    public class SchoolEntity
    {
        public int Id { get; set; }
        [Timestamp]
        public byte[] Timer { get; set; }
    }
}
