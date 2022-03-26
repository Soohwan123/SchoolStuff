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
        [HttpPut]
        public async Task<ActionResult> Put(StudentViewModel viewmodel)
        {
            try
            {
                int retVal = await viewmodel.Update();
                return retVal switch
                {
                    1 => Ok(new { msg = "Student " + viewmodel.Lastname + " updated!" }),
                    -1 => Ok(new { msg = "Student " + viewmodel.Lastname + " not updated!" }),
                    -2 => Ok(new { msg = "Data is stale for " + viewmodel.Lastname + " , Student not updated" }),
                    _ => Ok(new { msg = "Student " + viewmodel.Lastname + " not updated!" }),
                };
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); // something went wrong
            }
        }

        [HttpGet]
        public async Task<IActionResult> GetAll()
        {
            try
            {
                StudentViewModel viewModel = new StudentViewModel();
                List<StudentViewModel> allStudents = await viewModel.GetAll();
                return Ok(allStudents);
            }
            catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }

        [HttpPost]
        public async Task<ActionResult> Post(StudentViewModel viewModel)
        {
            try
            {
                await viewModel.Add();
                if(viewModel.Id > 1)
                {
                    return Ok(new { msg = "Student " + viewModel.Lastname + " added!" });
                }
                else
                {
                    return Ok(new { msg = "Student " + viewModel.Lastname + " no added!" });
                }
            } catch(Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> Delete(int id)
        {
            try
            {
                StudentViewModel viewmodel = new StudentViewModel { Id = id };
                return await viewmodel.Delete() == 1 ? Ok(new { msg = "Student " + id + " deleted!" }) : Ok(new { msg = "Student " + id + " not deleted!" });
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                return StatusCode(StatusCodes.Status500InternalServerError); //something went wrong
            }
        }
    }
    
}
