$(function () {

    $("#getBtn").click(async (e) => {
        try {
            let lastname = $("#lastNameBox").val();
            $("#status").text("please wait...");
            let response = await fetch(`/api/student/${lastname}`);
            if (response.ok) {
                let data = await response.json(); //this returns a promise, so we await it
                if (data.lastname !== "not found") {
                    $("#emailLbl").text(data.email);
                    $("#titleLbl").text(data.title);
                    $("#firstLbl").text(data.firstname); // we all know in StudentViewModel is Firstname, Title etc... but in js all things down to lower-case
                    $("#phoneLbl").text(data.phoneno);
                    $("#status").text("student found");
                } else {
                    $("firstLbl").text("not found");
                    $("#emailLbl").text("");
                    $("#titleLbl").text("");
                    $("#phoneLbl").text("");
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