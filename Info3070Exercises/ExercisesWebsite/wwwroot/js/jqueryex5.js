//Jquery do some code when the document is ready
$(function () { //main jQuery routine - executes every on page load

    //json string with student data in it
    //use ` to make it multiple lines
    let data;

    //event handler we're creating for the load button
    $('#loadBtn').click(async e => {
        if (sessionStorage.getItem("studentData") === null) {
            const url = "https://raw.githubusercontent.com/elauersen/info3070/master/jqueryex5.json"

            $('results').text('Locating student data on GitHub, please wait...');

            try {
                let response = await fetch(url);
                if (!response.ok)
                    throw new Error(`Status - ${response.status}, Text - ${response.statusText}`);

                data = await response.json();

                sessionStorage.setItem("studentData", JSON.stringify(data));
                $('#results').text('Student data on GitHub loaded!');
            } catch (err) {
                $('#results').text(err.message);
            }
        } else {
            data = JSON.parse(sessionStorage.getItem("studentData"));
        }

        let studentHtml = "";
        data.map(stu => {
            studentHtml += `<div id="${stu.id}" class="list-group-item">${stu.firstname}, ${stu.lastname},</div>`;
        });
        $('#studentList').html(studentHtml);
        $('#loadBtn').hide();
        $('#addBtn').show();
        $('#removeBtn').show();
    });




    $('#studentList').click(e => {
        // find the student the user has clicked on
        const stu = data.find(s => s.id === parseInt(e.target.id));
        // dump out a templated string to the bottom of the page
        $('#results').text(`you selected ${stu.firstname}, ${stu.lastname}`);
    }); // studentList div click

    //an event handler for a button with id attribute of abutton
    $('#addBtn').click(e => {  // # means go get it by id , . means by class
        if (data.length > 0) {
            const student = data[data.length - 1];

            $('#results').text(`adding student ${student.id + 101}`);

            data.push({ "id": student.id + 101, "firstname": "new", "lastname": "students" });
        }
        else {
            data.push({ "id": 101, "firstname": "new", "lastname": "student" });
        }

        sessionStorage.setItem("studentData", JSON.stringify(data));
        let html = "";
        data.forEach(student => {
            html += `<div id="${student.id}" class="list-group-item">${student.firstname}, ${student.lastname}</div>`;
        })

        $('#studentList').html(html);
    });

    $('#removeBtn').click(e => {
        if (data.length > 0) {
            const student = data[data.length - 1];
            data.splice(-1, 1);
            $('#results').text(`removed student ${student.id}`);

            sessionStorage.setItem("studentData", JSON.stringify(data));

            let html = "";
            data.map(student => {
                html += `<div id="${student.id}" class="list-group-item">${student.firstname}, ${student.lastname}</div>`;
            });
            $('#studenList').html(html);

        } else {
            $('#results').text(`no students to remove`);
        }
    });

});//jQuery routine
