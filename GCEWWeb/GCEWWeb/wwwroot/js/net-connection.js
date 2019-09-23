
function ajaxPost(method, data, success) {
    $.ajax({
        url: method,
        method: "POST",
        data: data,
        success: success,
        error: function (jqxhr, status, errorMsg) {
            console.log(errorMsg);
            toastr["error"]("Error " + method);
        }
    });
}

function ajaxGet(method, data, success) {
    $.ajax({
        url: method,
        method: "GET",
        data: data,
        success: success,
        error: function (jqxhr, status, errorMsg) {
            console.log(errorMsg);
            toastr["error"]("Error " + method);
        }
    });
}