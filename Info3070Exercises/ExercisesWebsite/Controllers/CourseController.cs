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
    public class CourseController : Controller
    {
        [HttpGet("{studentId}")]
        public async Task<IActionResult> GetAll(int studentId)
        {
            try
            {
                CourseViewModel viewModel = new CourseViewModel();
                var allDivisions = await viewModel.GetAllCoursesForStudent(studentId);
                return Ok(allDivisions);
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }
    }
}
