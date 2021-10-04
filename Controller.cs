using ExerciseViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace ExercisesWebsite.Controllers
{
    [Route("api/Student")]
    [ApiController]
    public class StudentController : ControllerBase
    {
        //would have to hit this route
        //api/Student/Corcoran
        [HttpGet("{lastname}")]
        public async Task<IActionResult> GetByLastnameAsync(string lastname)
        {
            try
            {
                StudentViewModel vm = new StudentViewModel();
                {
                    vm.Lastname = lastname;
                };
                await vm.GetByLastName();
                return Ok(vm);
            }catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //somethind went wrong
            }
        }
    }
}
