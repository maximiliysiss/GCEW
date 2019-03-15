
var flowChartSVG = null;
var dynamicLineStart = null;
var dynamicLine = null;
var isDrawDynamicLine = false;
var scrollChanger = 0.1;
var moveSpeed = 8;
var flowChartPosition = null;

var selectedLine = null;
var isMoveOnField = false;
var startDragging = null;

var onReload = null;

var divideExpression = "3ckew971n9gmjcoc";

function normVector2D(vec) {
    var len = Math.sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    return [vec[0] / len, vec[1] / len];
}

function getAngle(vec1, vec2) {
    let len = function (x, y) { return Math.sqrt(x * x + y * y); };
    let scalar2d = function (vec1, vec2) { return vec1[0] * vec2[0] + vec1[1] * vec2[1]; };
    let l1 = len(vec1[0], vec1[1]);
    let l2 = len(vec2[0], vec2[1]);
    return Math.acos(scalar2d(vec1, vec2) / (l1 * l2)) * 180 / Math.PI;
}

function getCenter(element) {
    var pos = $(element).position();
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
    var center = getCenter(dynamicLineStart);
    var cursor = [event.pageX - flowChartPosition.left, event.pageY - flowChartPosition.top];
    setCoordForLine(dynamicLine, cursor, center);
}

function getChangeCenter(dragElementPosition, cursorPosition, coeff) {

    var dDistance = [cursorPosition[1] - dragElementPosition.top, cursorPosition[0] - dragElementPosition.left];
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

        //var oneTwo = getChangeCenter($(this).position(), cursor, coeff);

        //var left = $(this).position().left;
        //var top = $(this).position().top;

        //$(this).css("left", (left + oneTwo[0]) + "px");
        //$(this).css("top", (top + oneTwo[1]) + "px");

        reDrawAll();
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
                if (selectedLine != null)
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
    $(flowChartSVG).bind('DOMMouseScroll', function (e) {
        scrollReaction(1 + (e.originalEvent.detail > 0 ? -scrollChanger : scrollChanger), e);
        return false;
    });

    $(flowChartSVG).bind('mousewheel', function (e) {
        scrollReaction(1 + (e.originalEvent.wheelDelta < 0 ? -scrollChanger : scrollChanger), e);
        return false;
    });
}

function mouseClick(event) {
    isDrawDynamicLine = false;
    if (dynamicLine !== null)
        $(dynamicLine).remove();
}

function removeElementWithChains(element) {
    $("line[id*='" + $(element).attr("id") + "']").each(function () { $(this).remove(); });
}

function eventForTargets(event) {
    if (!isDrawDynamicLine)
        return true;
    isDrawDynamicLine = false;
    $("#connector").remove();
    var target = event.target;
    if ($(target).attr("id") === $(dynamicLineStart).attr("id"))
        return false;
    createConnectionBetweenElements(dynamicLineStart, target);
    event.stopPropagation();
    return false;
}

function clickLine(elem) {
    var isActive = $(elem).attr("stroke") == "red";
    if (isActive) {
        $(elem).attr("stroke", "black");
        selectedLine = null;
    }
    else {
        if (selectedLine != null)
            $(selectedLine).attr("stroke", "black");
        $(elem).attr("stroke", "red");
        selectedLine = elem;
    }
}

function getLine() {
    var newLine = document.createElementNS("http://www.w3.org/2000/svg", 'line');
    $(newLine).attr("stroke", "black");
    $(newLine).attr("stroke-width", "5px");
    $(newLine).attr("menu", "Element");
    return newLine;
}

function reDrawAll() {
    $("line").each(function () {
        var elements = $(this).attr("id").split(divideExpression);
        setCoordForLine(this, getCenter($("#" + elements[0])), getCenter($("#" + elements[1])));
    });
}

function reDrawScheme(id) {
    $("#svgOne line[id*='" + id + "']").each(function () {
        var elements = $(this).attr("id").split(divideExpression);
        setCoordForLine(this, getCenter($("#" + elements[0])), getCenter($("#" + elements[1])));
    });
}

function startDynamic(elem) {
    if (dynamicLine !== null)
        $(dynamicLine).remove();
    isDrawDynamicLine = true;
    dynamicLine = getLine();
    $(dynamicLine).attr("id", "connector");
    $(flowChartSVG).append(dynamicLine);
    dynamicLineStart = elem;
    $(flowChartSVG).mousemove(function (event) { moveCursorDynamic(event); });
    $(flowChartSVG).mousedown(function (event) { mouseClick(event); })
}

function createConnectionBetweenElements(one, two) {
    var centerOne = getCenter(one);
    var centerTwo = getCenter(two);

    var lineConnect = getLine();

    if ($("#" + $(one).attr("id") + divideExpression + $(two).attr("id")).length != 0
        || $("#" + $(two).attr("id") + divideExpression + $(one).attr("id")).length != 0)
        return;

    $(lineConnect).attr("id", $(one).attr("id") + divideExpression + $(two).attr("id"));
    $(lineConnect).click(function () { clickLine(this); });
    $(flowChartSVG).append(lineConnect);
    setCoordForLine(lineConnect, centerOne, centerTwo);

    onReload();
}



