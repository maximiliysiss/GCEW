
var flowChartSVG = null;
var dynamicLineStart = null;
var dynamicLine = null;
var isDrawDynamicLine = false;
var flowChartPosition = null;

var lines = [];
var onReload = null;
var flowsElements = [];

function moveCursorDynamic(event) {
    if (!isDrawDynamicLine)
        return;
    $(dynamicLine.end).remove();
    dynamicLine.end = createEmptyForMouse(event);
}

function createElementFromHTML(htmlString) {
    var div = document.createElement('div');
    div.innerHTML = htmlString.trim();
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

    $(".flowChartHandlerBool").click(function (event) {
        var res = eventForStart(event);
        if (res)
            startDynamic(this, event);
        event.stopPropagation();
    });

    $(".flowChartHandlerInputBool").click(function (event) {
        if (isDrawDynamicLine && $(dynamicLineStart).hasClass("flowChartHandlerBool"))
            eventForTargets(event);
        event.stopPropagation();
    });

    $(".flowChartHandlerInput").click(function (event) {
        if (isDrawDynamicLine && $(dynamicLineStart).hasClass("flowChartHandler"))
            eventForTargets(event);
        event.stopPropagation();
    });
}

function initFlowChartsOnPage(svgElement, onReloadEvent) {
    onReload = onReloadEvent;

    console.log("initFlowChartsOnPage");
    flowChartSVG = svgElement;
    flowChartPosition = $(flowChartSVG).position();
    onReload();
}

function addElement(data, pos) {
    var elem = $(createElementFromHTML(data["html"]));
    elem.css("top", pos[1] + "px");
    elem.css("left", pos[0] + "px");
    $(flowChartSVG).parent().append(elem);
    flowsElements.push(data);
    onReload();
}

function mouseClick(event) {
    if (dynamicLine !== null)
        destroyDynamicLine();
}

function removeElementWithChains(element) {
    var id = $(element).attr("id");

    lines.forEach(function (elem, i) {
        if ($(elem.start).attr("id").indexOf(id) !== -1
            || $(elem.end).attr("id").indexOf(id) !== -1) {
            elem.remove();
            lines = lines.filter(function (val, i, arr) {
                return val._id !== elem._id;
            });
        }
    });
    flowsElements = flowsElements.filter(function (v, i, a) { return v["guid"] === id; });
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

    var oneID = $(one).attr("id");
    var twoID = $(two).attr("id");

    var line = new LeaderLine($(one).get(0), $(two).get(0));
    lines.push(line);

    var realIdFrom = oneID.lastIndexOf('-') == oneID.length - 2 ? oneID.substr(0, oneID.lastIndexOf('-')) : oneID;
    var realIdTo = twoID.lastIndexOf('-') == twoID.length - 2 ? twoID.substr(0, twoID.lastIndexOf('-')) : twoID;

    console.log(realIdFrom + " " + realIdTo);

    var fromObj = flowsElements.find(obj => { return obj["guid"] === realIdFrom; });
    var toObj = flowsElements.find(obj => { return obj["guid"] === realIdTo; });

    switch (toObj["elementType"]) {
        case 0:
            break;
        case 0:
            break;
        case 0:
            break;
        case 0:
            break;
        case 0:
            break;
    }

    onReload();
}



