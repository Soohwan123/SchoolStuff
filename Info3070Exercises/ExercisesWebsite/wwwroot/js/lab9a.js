$(function () {

    $("#getbutton").click(async (e) => {
        try {
            let lastname = $("#TextBoxFindLastname").val();
            $("#status").text("please wait...");
            //toggle the modal to show it or hide it
            $("#myModal").modal("toggle");
            let response = await fetch(`/api/student/${lastname}`);
            if (response.ok) {
                let data = await response.json(); //this returns a promise, so we await it
                sessionStorage.setItem('student', JSON.stringify(data));
                if (data.lastname !== "not found") {
                    $("#TextBoxEmail").val(data.email);
                    $("#TextBoxTitle").val(data.title);
                    $("#TextBoxFirstname").val(data.firstname); // we all know in StudentViewModel is Firstname, Title etc... but in js all things down to lower-case
                    $("#TextBoxLastname").val(data.lastname);
                    $("#TextBoxPhone").val(data.phoneno);
                    $("#status").text("student found");
                    //return these non-mutated values later
                    sessionStorage.setItem("id", data.id);
                    sessionStorage.setItem("divisionId", data.divisionId);
                    sessionStorage.setItem("timer", data.timer);
                } else {
                    $("#TextBoxFirstname").val("not found");
                    $("#TextBoxEmail").val("");
                    $("#TextBoxTitle").val("");
                    $("#TextBoxPhone").val("");
                    $("#TextBoxLastname").val("");
                    $("#status").text("no such student");
                }
            } else if (response.status !== 404) {
                let problemJson = await response.json();
                errorRtn(problemJson, response.status);
            } else { //else 404 not found
                $("#status").text("no such path on server")
            }
        } catch (error) { //catastrophic
            $("#status").text(error.message);
        }
    });

    $("#updatebutton").click(async (e) => {
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
            stu.divisionId = parseInt(sessionStorage.getItem("divisionId"));
            stu.timer = sessionStorage.getItem("timer");

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
    }); // update button click
});



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