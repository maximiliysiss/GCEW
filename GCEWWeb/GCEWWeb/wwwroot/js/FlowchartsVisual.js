
var flowChartSVG = null;
var dynamicLineStart = null;
var dynamicLine = null;
var isDrawDynamicLine = false;
var scrollChanger = 0.1;
var scrollChahgeCoeff = 0;
var moveSpeed = 5;
var flowChartPosition = null;

var selectedLine = null;
var selectedElem = null;
var isMoveOnField = false;
var startDragging = null;

var lines = [];
var onReload = null;
var flowsElements = [];

var divideExpression = "3ckew971n9gmjcoc";

function normVector2D(vec) {
    var len = Math.sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    return [vec[0] / len, vec[1] / len];
}

function getCenter(element) {
    var pos = $(element).offset();
    var plotOffset = $(flowChartSVG).offset();
    pos.left -= plotOffset.left;
    pos.top -= plotOffset.top;
    var wX = pos.left + $(element).width() / 2;
    var hY = pos.top + $(element).height() / 2;
    return [wX, hY];
}

function setCoordForLine(line, coord1, coord2) {
    $(line).attr("x1", coord1[0]);
    $(line).attr("y1", coord1[1]);
    $(line).attr("x2", coord2[0]);
    $(line).attr("y2", coord2[1]);
}

function moveCursorDynamic(event) {
    if (!isDrawDynamicLine)
        return;
    $(dynamicLine.end).remove();
    dynamicLine.end = createEmptyForMouse(event);
}

function getChangeCenter(dragElementPosition, cursorPosition, coeff) {

    var dDistance = [cursorPosition[0] - dragElementPosition.left, cursorPosition[1] - dragElementPosition.top];
    var dDistanceCoef = [coeff * dDistance[0], coeff * dDistance[1]];
    return [(dDistance[0] - dDistanceCoef[0]) / 2, (dDistance[1] - dDistanceCoef[1]) / 2];
}

function scrollReaction(coeff, event) {

    var cursor = [event.pageX - flowChartPosition.left, event.pageY - flowChartPosition.top];

    $(".dragElement").each(function () {
        var h = $(this).height();
        var w = $(this).width()
        $(this).width(w * coeff);
        $(this).height(h * coeff);

        var oneTwo = getChangeCenter($(this).position(), cursor, coeff);

        var left = $(this).position().left;
        var top = $(this).position().top;

        $(this).css("left", (left + oneTwo[0]) + "px");
        $(this).css("top", (top + oneTwo[1]) + "px");

        reDrawAll();
    });
}

function createElementFromHTML(htmlString) {
    var div = document.createElement('div');
    div.innerHTML = htmlString.trim();

    // Change this to div.childNodes to support multiple top-level nodes
    return div.firstChild;
}

function reloadElements() {

    $(".dragElement").unbind("draggable");
    $(".flowChartHandler").unbind("click");

    $(".dragElement").draggable({
        drag: function () { reDrawScheme($(this).attr("id")); }
    });

    $(".flowChartHandler").click(function (event) {
        var res = eventForStart(event);
        if (res)
            startDynamic(this, event);
        event.stopPropagation();
    });

    $(".flowChartHandlerInput").click(function (event) {
        if (isDrawDynamicLine)
            eventForTargets(event);
        event.stopPropagation();
    });
}

function initFlowChartsOnPage(svgElement, onReloadEvent) {
    onReload = onReloadEvent;

    console.log("initFlowChartsOnPage");
    flowChartSVG = svgElement;
    flowChartPosition = $(flowChartSVG).position();
    $(document).keydown(function (event) {
        switch (event.keyCode) {
            case 46:
                if (selectedLine !== null)
                    $(selectedLine).remove();
                break;
        }
    });
    $(flowChartSVG).mousedown(function (event) {
        isMoveOnField = true;
        startDragging = [event.pageX - flowChartPosition.left, event.pageY - flowChartPosition.top];
        $(flowChartSVG).css("cursor", "pointer");
    });
    $(flowChartSVG).mouseup(function () {
        if (isMoveOnField) {
            isMoveOnField = false; startDragging = null;
            $(flowChartSVG).css("cursor", "auto");
        }
    });
    $(flowChartSVG).mouseover(function () {
        $(flowChartSVG).mouseup();
    })
    $(flowChartSVG).mousemove(function (event) {
        if (!isMoveOnField)
            return true;

        var currentPos = [event.pageX - flowChartPosition.left, event.pageY - flowChartPosition.top];
        startDragging = [startDragging[0], startDragging[1]];
        var vectorMove = [(currentPos[0] - startDragging[0]), (currentPos[1] - startDragging[1])];
        vectorMove = normVector2D(vectorMove);
        $(".dragElement").each(function () {
            var pos = $(this).position();
            $(this).css("top", pos.top + vectorMove[1] * moveSpeed);
            $(this).css("left", pos.left + vectorMove[0] * moveSpeed);
            reDrawAll();
        });
    });
    //$(flowChartSVG).bind('DOMMouseScroll', function (e) {
    //    scrollReaction(1 + (e.originalEvent.detail > 0 ? -scrollChanger : scrollChanger), e);
    //    return false;
    //});

    //$(flowChartSVG).bind('mousewheel', function (e) {
    //    scrollReaction(1 + (e.originalEvent.wheelDelta < 0 ? -scrollChanger : scrollChanger), e);
    //    return false;
    //});

    onReload();
}

function addElement(data, pos) {
    var elem = $(createElementFromHTML(data));
    elem.css("top", pos[1] + "px");
    elem.css("left", pos[0] + "px");
    $(flowChartSVG).parent().append(elem);
    flowsElements.push($(flowChartSVG).parent().children().last());
    onReload();
}

function mouseClick(event) {
    if (dynamicLine !== null)
        destroyDynamicLine();
}

function removeElementWithChains(element) {
    lines.forEach(function (elem, i) {
        if ($(elem.start).attr("id") === $(element).attr("id")
            || $(elem.end).attr("id") === $(element).attr("id")) {
            elem.remove();
            lines = lines.filter(function (val, i, arr) {
                return val._id !== elem._id;
            });
        }
    });
    reDrawAll();
}

function eventForStart(event) {
    if (!isDrawDynamicLine)
        return true;
    destroyDynamicLine();
}

function destroyDynamicLine() {
    isDrawDynamicLine = false;
    $(dynamicLine.end).remove();
    dynamicLine.remove();
    dynamicLine = null;
}

function eventForTargets(event) {
    if (!isDrawDynamicLine)
        return true;
    destroyDynamicLine();
    var target = event.currentTarget;
    if ($(target).attr("id") === $(dynamicLineStart).attr("id"))
        return false;
    createConnectionBetweenElements(dynamicLineStart, target);
    event.stopPropagation();
    return false;
}

function clickLine(elem) {
    var isActive = $(elem).attr("stroke") === "red";
    if (isActive) {
        $(elem).attr("stroke", "black");
        selectedLine = null;
    }
    else {
        if (selectedLine !== null)
            $(selectedLine).attr("stroke", "black");
        $(elem).attr("stroke", "red");
        selectedLine = elem;
    }
}

function reDrawAll() {
    $(lines).each(function () { this.position(); });
    console.log(lines.length);
}

function reDrawScheme(id, withInner = true) {
    reDrawAll();
}

function createEmptyForMouse(event) {
    var empty = document.createElement("p");
    $(empty).css("position", "absolute");
    $(empty).css("top", event.pageY);
    $(empty).css("left", event.pageX);
    $(document.body).append(empty);
    return empty;
}

function startDynamic(elem, event) {
    if (dynamicLine !== null)
        destroyDynamicLine();
    isDrawDynamicLine = true;
    dynamicLineStart = $(elem);
    dynamicLine = new LeaderLine(elem, createEmptyForMouse(event));
    $(flowChartSVG).mousemove(function (event) { moveCursorDynamic(event); });
    $(flowChartSVG).mousedown(function (event) { mouseClick(event); });
}

function createConnectionBetweenElements(one, two) {
    var line = new LeaderLine($(one).get(0), $(two).get(0));
    $("[id^='leader-line-" + line._id + "-line-shape']").attr("onClick", "alert123(event)");
    lines.push(line);
    onReload();
}



