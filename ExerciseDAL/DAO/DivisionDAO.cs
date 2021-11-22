using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace ExerciseDAL
{
    public class DivisionDAO
    {
        readonly IRepository<Division> repo;

        public DivisionDAO()
        {
            repo = new SomeSchoolRepository<Division>();
        }

   
        public async Task<List<Division>> GetAll()
        {
            return await repo.GetAll();
        }
    }
}
