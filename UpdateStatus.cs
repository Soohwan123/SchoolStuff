﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExerciseDAL
{
    public enum UpdateStatus
    {
        Ok= 1,
        Failed = -1,
        Stale = -2
    };
}
