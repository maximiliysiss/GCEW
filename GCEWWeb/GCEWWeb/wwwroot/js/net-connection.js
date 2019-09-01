
function ajaxPost(method, data, success) {
    $.ajax({
        url: method,
        method: "POST",
        data: data,
        success: success,
        error: function () {
            toastr["error"]("Error " + method);
        }
    });
}