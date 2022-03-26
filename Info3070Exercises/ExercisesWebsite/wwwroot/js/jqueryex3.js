//Jquery do some code when the document is ready
$(function () { //main jQuery routine - executes every on page load

    //this is declaring a string variable, notice the use of the tick
    //instead of quotes to allow us using multiple lines, here we're
    //defining 3 students in JSON format
    const stringData = 
        `[{ "id": 123, "firstname": "Teachers", "lastname": "Pet" },
         { "id": 234, "firstname": "Brown", "lastname": "Nose" },
         { "id": 345, "firstname": "Always", "lastname": "Late" }]`;

    //if statement
    sessionStorage.getItem("studentData") === 'null'
        || sessionStorage.getItem("studentData") === null
        ? sessionStorage.setItem("studentData", stringData) : null;

    let data = JSON.parse(sessionStorage.getItem("studentData"));

    //event handler we're creating for the load button
    $('#loadBtn').click(e => {
        let studentHtml = "";
        data.map(stu => {
            studentHtml += `<div id="${stu.id}" class="list-group-item">${stu.firstname}, ${stu.lastname},</div>`;
        });

        $('#studentList').html(studentHtml);
        $('#loadBtn').hide();
        $('#addBtn').show();
    });

    $('#studentList').click(e => {
        // find the student the user has clicked on
        const stu = data.find(s => s.id === parseInt(e.target.id));
        // dump out a templated string to the bottom of the page
        $('#results').text(`you selected ${stu.firstname}, ${stu.lastname}`);
    }); // studentList div click

    //an event handler for a button with id attribute of abutton
    $('#addBtn').click(e => {  // # means go get it by id , . means by class

        const student = data[data.length - 1];

        $('#results').text(`adding student ${student.id + 101}`);

        data.push({ "id": student.id + 101, "firstname": "Soohwan", "lastname": "Kim" });

        sessionStorage.setItem("studentData", JSON.stringify(data));
        let html = "";
        data.forEach(student => {
            html += `<div id="${student.id}" class="list-group-item">${student.firstname}, ${student.lastname}</div>`;
        })

        $('#studentList').html(html);
    });
})//jQuery routine
