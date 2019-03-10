
var flowChartSVG = null;
var dynamicLineStart = null;
var dynamicLine = null;
var isDrawDynamicLine = false;

var selectedLine = null;

var divideExpression = "3ckew971n9gmjcoc";

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
    var flowChartPos = $(flowChartSVG).position();
    var cursor = [event.pageX - flowChartPos.left, event.pageY - flowChartPos.top];
    setCoordForLine(dynamicLine, cursor, center);
}

function initFlowChartsOnPage(svgElement) {
    flowChartSVG = svgElement;
    $(document).keydown(function (event) {
        switch (event.keyCode) {
            case 46:
                if (selectedLine != null)
                    $(selectedLine).remove();
                break;
        }
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
    return newLine;
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

    if ($("#" + $(one).attr("id") + divideExpression + $(two).attr("id")).length != 0)
        return;

    $(lineConnect).attr("id", $(one).attr("id") + divideExpression + $(two).attr("id"));
    $(lineConnect).click(function () { clickLine(this); });
    $(flowChartSVG).append(lineConnect);
    setCoordForLine(lineConnect, centerOne, centerTwo);
}



