
var contextMenuTarget = null;


function reHandlerContextMenus() {
    $("[menu]").contextmenu(function (event) {
        $(".menuContextRoot").each(function () { $(this).removeClass("open-context-menu"); });
        var menu = $("#" + $(this).attr("menu"));
        if (menu !== null) {
            contextMenuTarget = $(event.currentTarget);
            menu.addClass("open-context-menu");
            menu.css("top", event.pageY);
            menu.css("left", event.pageX);
            event.preventDefault();
            event.stopPropagation();
        }
    });
}


$(function () {

    reHandlerContextMenus();

    $(".menuContextElements > li").click(function (event) {
        var isVisible = $(this).children("div").first().is(":visible");

        $(this).parent().children().each(function () {
            $(this).removeClass("open-menu-elem");
            $(this).children().each(function () {
                $(this).removeClass("open-inner-menu");
            });
        });

        var pos = $(this).position();
        var leftPos = $(this).outerWidth() + pos.left;

        $(this).children("div").each(function () {
            $(this).css("top", pos.top);
            $(this).css("left", leftPos);
            if (isVisible)
                $(this).removeClass("open-inner-menu");
            else
                $(this).addClass("open-inner-menu");
        });


        if ($(this).children("div").length > 0) {
            $(this).addClass("open-menu-elem");
            event.stopPropagation();
        }
        else
            $(document).click();
    });


    $(document).click(function () {
        $(".menuContextRoot").each(function () { $(this).removeClass("open-context-menu"); });
        $(".menuContextElements > li").each(function () { $(this).removeClass("open-menu-elem"); });
        $(".open-inner-menu").each(function () { $(this).removeClass("open-inner-menu"); });
    });
});