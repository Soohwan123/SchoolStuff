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
    [Route("api/[controller]")]
    [ApiController]
    public class GradeController : ControllerBase
    {
        [HttpGet("{studentId}")]
        public async Task<IActionResult> GetAllGradesForStudent(int studentId)
        {
            try
            {
                GradeViewModel vm = new GradeViewModel();
                var allDivs = await vm.GetGradesByStudentId(studentId);
                return Ok(allDivs);
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError); //somethind went wrong
            }
        }
        [HttpPut]
        public async Task<ActionResult> Put([FromBody] GradeViewModel viewmodel)
        {
            try
            {
                int retVal = await viewmodel.Update();
                return retVal switch
                {
                    1 => Ok(new { msg = "Grade " + viewmodel.Id + " updated!" }),
                    -1 => Ok(new { msg = "Grade " + viewmodel.Id + " not updated!" }),
                    -2 => Ok(new { msg = "Data is stale for " + viewmodel.Id + " , Grade not updated" }),
                    _ => Ok(new { msg = "Grade " + viewmodel.Id + " not updated!" }),
                };
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError); // something went wrong
            }
        }

    }
}
