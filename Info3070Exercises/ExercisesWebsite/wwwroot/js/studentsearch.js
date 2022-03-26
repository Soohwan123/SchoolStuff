$(function () {
    // Go to the server, get our list of students

    // build the student list add feature

    // When they do click the list, we have to figure our if it's going to be an Add or Update

    // Setup the modal for an add, or setup the modal for and update

    // They've git the action button

    const getAll = async (msg) => {
        try {
            $("#studentList").text("Finding Student Information...");
            let response = await fetch(`/api/student`);
            if (response.ok) {
                let payload = await response.json(); //this returns a promise, so we await it
                buildStudentList(payload);
                msg === "" ? // are we appending to an existing message
                    $("#status").text("Students Loaded") : $("#status").text(`${msg} - Students Loaded`)
            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else {  // else 404 not found
                $("#status").text(error.message);
            } // else
        } catch (error) {
            $("status").text(error.message);
        }
    }; //getAll

    const setupForUpdate = (id, data) => {
        $("#actionbutton").val("update");
        $("#modaltitle").html("<h4>update student</h4>");
        $("#deletebutton").show();

        clearModalFields();
        data.map(student => {
            if (student.id === parseInt(id)) {
                //set value of ddl for divisions
                $('#ddlDivisions').val(student.divisionId);

                $("#TextBoxTitle").val(student.title);
                $("#TextBoxFirstname").val(student.firstname);
                $("#TextBoxLastname").val(student.lastname);
                $("#TextBoxPhone").val(student.phoneno);
                $("#TextBoxEmail").val(student.email);
                sessionStorage.setItem("id", student.id);
                sessionStorage.setItem("divisionId", student.divisionId);
                sessionStorage.setItem("timer", student.timer);
                $("#modalstatus").text("update data");
                $("#myModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }// if
        });//data.map
    };//setupForUpdate

    const setupForAdd = () => {
        $("#actionbutton").val("add");
        $("#modaltitle").html("<h4>add student</h4>")
        $("#myModal").modal("toggle");
        $("#modalstatus").text("add new student");
        $("#myModalLabel").text("Add");
        $('#ddlDivisions').val(-1);
        $("#deletebutton").hide();
        clearModalFields();

    }; //setupForAdd


    const clearModalFields = () => {
        $("#TextBoxTitle").val("");
        $("#TextBoxFirstName").val("");
        $("#TextBoxLastName").val("");
        $("#TextBoxPhone").val("");
        $("#TextBoxEmail").val("");
        $('#ddlDivisions').val(-1);
        sessionStorage.removeItem("id");
        sessionStorage.removeItem("divisionId");
        sessionStorage.removeItem("timer");
        $("#myModal").modal("toggle");
    };//clearModalFields


    //const loadDivisionDDL = (studiv) => {
    //    html = '';
    //    $('#ddlDivisions').empty();
    //    let alldivisions = JSON.parse(sessionStorage.getItem('alldivisions');
    //    for (div of alldivisions) { html += `<option value="${div.id}">${div.name}</option>` };
    //    $('#ddlDivisions').append(html);
    //    $('#ddlDivisions').val(studiv);
    //};//loadDivisionDDL

    const add = async () => {
        try {
            stu = new Object();
            stu.title = $("#TextBoxTitle").val();
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxLastname").val();
            stu.phoneno = $("#TextBoxPhone").val();
            stu.email = $("#TextBoxEmail").val();
            stu.divisionId = parseInt($("#ddlDivisions").val());
            stu.id = 4213;

            //send the student info to the server ansychronously using POST
            let response = await fetch('/api/student', {
                method: "POST",  // Post is for a new data, Put is for updating existing data
                headers: { 'Content-Type': 'application/json; charset=utf-8' },
                body: JSON.stringify(stu)
            });
            if (response.ok) //or check for response.status
            {
                let data = await response.json();
                getAll(data.msg);
            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else { // else 404 not found
                $("#status").text("no such path on server");
            } //else
        } catch (error) {
            $("#status").text(error.message);
        } // try/catch
        $("#myModal").modal("toggle");
    };//add

    const update = async () => {
        try {
            //go get the "current" student data from session storage
            //set up a new client side instance of Student
            stu = new Object();

            //populate the properties
            //Overwrite with the updated values
            stu.title = $("#TextBoxTitle").val();
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxLastname").val();
            stu.phoneno = $("#TextBoxPhone").val();
            stu.email = $("#TextBoxEmail").val();
            stu.divisionName = "";
            stu.picture64 = "";

            //stored earlier, numbers needed for Ids or http 401
            stu.id = parseInt(sessionStorage.getItem("id"));
            stu.divisionId = parseInt($("#ddlDivisions").val());
            stu.timer = sessionStorage.getItem("timer");
            stu.picture64 = null;

            //don't have to do ID, Timer, and division Id because they're already stored in studentObject from before
            //sent the updated back to the server asynchronously using PUT
            let response = await fetch('/api/student', {
                method: "PUT",
                headers: { 'Content-Type': 'application/json; charset=utf-8' },
                body: JSON.stringify(stu)
            });
            if (response.ok) //or check for response.status
            {
                let responseDate = await response.json();
                $("#status").text(responseDate.msg);
                getAll(data.msg); // very important !! timer will change. so if we wanna update twice in a row it will fail. so call getAll again for this!!

            } else if (response.status !== 404) { //probably some other client side error
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else { // else 404 not found
                $("#status").text("no such path on server");
            } //else
        } catch (error) {
            $("#status").text(error.message);
            console.table(error);
        }
    }; // update






    $("#actionbutton").mouseup(async (e) => {
        $("#actionbutton").val() === "Update" ? update() : add();
    });

    //finds the student id out of the html element that is clicked
    $("#studentList").click((e) => {
        clearModalFields();
        if (!e) e = window.event;
        let id = e.target.parentNode.id;
        if (id === "studentList" || id === "") {
            id = e.target.id;
        } // clicked on row somewhere else

        if (id !== "status" && id !== "heading") {
            let data = JSON.parse(sessionStorage.getItem("allstudents"));
            id === "0" ? setupForAdd() : setupForUpdate(id, data);
        } //if
        else {
            return false; // ignore if they clicked on heading or status
        }
    }); //studentList Click


    const buildStudentList = (data, usealldata = true) => {
        $("#studentList").empty();  //empty the list first
        div = $(`<div class="list-group-item text-white bg-secondary row d-flex" id="status">Student Info</div>
        <div class= "list-group-item row d-flex text-center" id="heading">
            <div class="col-4 h4">Title</div>
            <div class="col-4 h4">First</div>
            <div class="col-4 h4">Last</div>
        </div>`);
        div.appendTo($("#studentList"));
        usealldata ? sessionStorage.setItem("allstudents", JSON.stringify(data)) : null;
        btn = $(`<button class="list-group-item row d-flex" id="0">...click to add student</button>`)
        btn.appendTo($("#studentList"));
        data.map(stu => {
            btn = $(`<button class="list-group-item row d-flex" id="${stu.id}">`);
            btn.html(`<div class="col-4" id="studenttitle${stu.id}">${stu.title}</div>
            <div class="col-4" id="studentfname${stu.id}">${stu.firstname}</div>
            <div class="col-4" id="studentlastname${stu.id}">${stu.lastname}</div>`
            );
            btn.appendTo($("#studentList"));
        }); // map
    }; //buildStudentList

    const _delete = async () => {
        try {
            let response = await fetch(`/api/student/${sessionStorage.getItem('id')}`, {
                method: 'DELETE',
                headers: { 'Content-Type': 'application/json; charset=utf-8' }
            });
            if (response.ok) //or check for response.status
            {
                let data = await response.json();
                getAll(data.msg);
            } else {
                $('#status').text(`Status - ${response.status}, Problem on delete server side, see server console`);
            } //else
            $('#myModal').modal('toggle');
        } catch (error) {
            $('#status').text(error.message);
        }
    }; // delete

    $('#deletebutton').click(() => {
        if (window.confirm('Are you sure')) {
            _delete();
        }
    })

   

    let loadDivisionDDL = async () => {
        //go get all the division data
        response = await fetch(`/api/division`)
        if (!response.ok)
            throw new Error(`Status - ${response.status}, Text - ${response.statusText}`);
        let divs = await response.json();

        html = '';
        $('#ddlDivisions').empty();
        divs.map(div =>
            html += `<option value="${div.id}">${div.name}</option>`
        );
        $('#ddlDivisions').append(html);
    }

    $("#srch").keyup(() => {
        let alldata = JSON.parse(sessionStorage.getItem("allstudents"));
        let filtereddata = alldata.filter((stu) => stu.lastname.match(new RegExp($("#srch").val(), 'i')));
        buildStudentList(filtereddata, false);

    }); //srch keyup

    getAll(""); //first grab the data from the server
    loadDivisionDDL(); //calling divisions
}); // jQuery method

// server was reached but server had a problem with the call
const errorRtn = (problemJson, status) => {
    if (status > 499) {
        $("status").text("Problem sever side, see debug console");
    } else {
        let keys = Object.keys(problemJson.errors)
        problem = {
            status: status,
            statusText: problemJson.errors[keys[0]][0], //first error
        };
        $("#status").text("Problem client side, see browser console");
        console.log(problem);
    }
}