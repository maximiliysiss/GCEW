

$(".custom-modal-holder").click(function () {
    $("#" + $(this).attr("modal")).css("display", "block");
});

$(".close-modal").click(function () {
    $("#" + $(this).attr("modal")).css("display", "none");
});

$(document).click(function () {
    $("custom-modal").css("display", "none");
});

$(".modal-content").click(function () {
    event.preventDefault();
    event.stopPropagation();
});

$(".custom-modal").click(function () {
    $(this).css("display", "none");
});