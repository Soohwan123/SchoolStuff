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
        getGradeInfo(id);
        loadCourseDDL(id); //calling divisions
        data.map(student => {
            if (student.id === parseInt(id)) {

                $("#TextBoxFirstname").val(student.firstname);
                $("#TextBoxLastname").val(student.lastname);
                sessionStorage.setItem("id", student.id);
                sessionStorage.setItem("divisionId", student.divisionId);
                sessionStorage.setItem("timer", student.timer);
                $("#modalstatus").text("update data");
                $("#myModal").modal("toggle");
                $("#myModalLabel").text("Update");
            }// if
        });//data.map
    };//setupForUpdate

    const clearModalFields = () => {
        $("#TextBoxFirstname").val("");
        $("#TextBoxLastname").val("");
        $("#TextBoxMark").val(0);
        $("#MarkRow").hide();
        $('#CommentsRow').hide();
        $("#actionbutton").hide();
        $("#TextBoxComments").val("");
        sessionStorage.removeItem("id");
        sessionStorage.removeItem("divisionId");
        sessionStorage.removeItem("timer");
        $("#myModal").modal("toggle");
    };//clearModalFields


    const update = async () => {
        try {
            //go get the "current" student data from session storage
            //set up a new client side instance of Student
            stu = new Object();

            //populate the properties
            //Overwrite with the updated values
            stu.firstname = $("#TextBoxFirstname").val();
            stu.lastname = $("#TextBoxLastname").val();
            stu.name = $("#ddlCourses").val();
            stu.mark = $("#TextBoxMark").val();
            stu.comments = $("#TextBoxComments").val();;
            const thisStudentGrades = JSON.parse(sessionStorage.getItem("StudentGrades"));
            let grade = thisStudentGrades.find(g => g.courseId === parseInt($('#ddlCourses').val()));
            stu.grade = grade;

            //stored earlier, numbers needed for Ids or http 401
            stu.id = parseInt(sessionStorage.getItem("id"));
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

    let loadCourseDDL = async (studentId) => {
        //go get all the division data
        response = await fetch(`/api/course/${studentId}`);
        if (!response.ok)
            throw new Error(`Status - ${response.status}, Text - ${response.statusText}`);
        let courses = await response.json();

        html = '';
        $('#ddlCourses').empty();
        courses.map(course =>
            html += `<option value="${course.id}">${course.name}</option>`
        );
        $('#ddlCourses').append(html);
        $('#ddlCourses').val(-1);
    };

    let getGradeInfo = async (studentId) => {
        response = await fetch(`/api/grade/${studentId}`);
        let grades = await response.json();
        sessionStorage.setItem('StudentGrades', JSON.stringify(grades));

        sessionStorage.setItem('SelectedGrade',
            JSON.stringify(grades.find(
                g => g.courseId === parseInt($('#ddlCourses').val()
                ))));

        $("#TextBoxMark").val(studentId.mark);
        $("#TextBoxComments").val(studentId.comments);

    }
    $("#ddlCourses").change((e) => {
        var gradeData = JSON.parse(sessionStorage.getItem("StudentGrades"));
        var curGrade = gradeData.find(g => g.courseId === parseInt($('#ddlCourses').val()));
        sessionStorage.setItem("SelectedGrade", JSON.stringify(curGrade));
        $("#MarkRow").show();
        $("#CommentsRow").show();
        $("#actionbutton").show();
        $("#TextBoxMark").show();
        $("#TextBoxComments").show();
        $("#TextBoxMark").val(curGrade.mark);
        $("#TextBoxComments").val(curGrade.comments);
        $('#modalstatus').text('');
    })



    $("#actionbutton").click(async () => {
        $("#actionbutton").val() === update();
        try {
            let gradeObject = JSON.parse(sessionStorage.getItem("SelectedGrade"));

            gradeObject.comments = $('#TextBoxComments').val();
            gradeObject.mark = $("#TextBoxMark").val();
            let response = await fetch('/api/grade', {
                method: "PUT",
                headers: { 'Content-Type': 'application/json; charset=utf-8' },
                body: JSON.stringify(gradeObject)

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


    const buildStudentList = (data) => {
        $("#studentList").empty();  //empty the list first
        div = $(`<div class="list-group-item text-white bg-secondary row d-flex" id="status">Student Info</div>
        <div class= "list-group-item row d-flex text-center" id="heading">
            <div class="col-4 h4">Title</div>
            <div class="col-4 h4">First</div>
            <div class="col-4 h4">Last</div>
        </div>`);
        div.appendTo($("#studentList"));
        sessionStorage.setItem("allstudents", JSON.stringify(data));
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

    

    getAll(""); //first grab the data from the server
   
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