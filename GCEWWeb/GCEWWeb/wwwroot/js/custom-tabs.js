
$(function () {

    $(".tab").click(function () {
        var group = $(this).attr("group");
        if (!group)
            return;

        $(".tab[group='" + group + "']").each(function () {
            $(this).removeClass("open-tab");
        });

        $(".tab-content[group='" + group + "']").each(function () {
            $(this).removeClass("open-tab-content");
        });

        $(this).addClass("open-tab");
        var attrID = $(this).attr("content-id");
        $(".tab-content[content-id='" + attrID + "']").each(function () {
            $(this).addClass("open-tab-content");
        });
    });

});

function addTab() {

}