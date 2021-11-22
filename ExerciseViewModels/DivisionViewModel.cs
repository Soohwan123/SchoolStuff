using ExerciseDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace ExerciseViewModels
{
    public class DivisionViewModel
    {
        private DivisionDAO _model;

        public int Id { get; set; }
        public string Name { get; set; }

        //constructor

        public DivisionViewModel()
        {
            _model = new DivisionDAO();
        }

        public async Task<List<DivisionViewModel>> GetAll()
        {
            List<DivisionViewModel> allVms = new List<DivisionViewModel>();
            try
            {
                List<Division> allDivisions = await _model.GetAll();
                foreach (Division div in allDivisions)
                {
                    DivisionViewModel vm = new DivisionViewModel();
                    vm.Id = div.Id;
                    vm.Name = div.Name;
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
    }

   
}
