using ExerciseViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;


namespace ExercisesWebsite.Controllers
{
    [Route("api/Division")]             //Important!!
    [ApiController]
    public class DivisionController : Controller
    {
        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            try
            {
                DivisionViewModel viewModel = new DivisionViewModel();
                List<DivisionViewModel> allDivisions = await viewModel.GetAll();
                return Ok(allDivisions);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }
    }
}
