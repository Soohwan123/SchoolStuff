//Jquery do some code when the document is ready
$(function () { //main jQuery routine - executes every on page load

    //this is declaring a string variable, notice the use of the tick
    //instead of quotes to allow us using multiple lines, here we're
    //defining 3 students in JSON format
    const studentData = JSON.parse(
        `[{ "id": 123, "firstname": "Teachers", "lastname": "Pet" },
         { "id": 234, "firstname": "Brown", "lastname": "Nose" },
         { "id": 345, "firstname": "Always", "lastname": "Late" }]`);

    $('#loadBtn').click(e => {  // # means go get it by id , . means by class
        // we'll manually build a string of html. We use let because
        // the string will be mutated.
        let studentHtml = "";
        // using the array map operator here to iterate through the object array
        // for each object it finds we'll label it as student and then dump out the 3 properties using a templated string inside a div node
        studentData.map(stu => {
            studentHtml += `<div id="${stu.id}" class ="list-group-item">${stu.id},${stu.firstname},${stu.lastname}, </div>`;
        });

        // dump the dynamically generated html into an element with an
        // id attribute of studentList (in this case a <div></div>)
        $('#studentList').html(studentHtml);
        $('#loadBtn').hide();
        //$("#loadbutton").show();
    });//load button.click()

    $('#studentList').click(e => {
        alert(e.target.id);
        const stu = studentData.find(s => s.id === parseInt(e.target.id));
        $('#results').text(`you selected ${stu.firstname}, ${stu.lastname}`);
    });
});//jQuery routine
