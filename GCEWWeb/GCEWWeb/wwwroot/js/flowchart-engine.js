// Engine

var EngineFlowChart = function (frame, url) {
    this.dynamicLine = null;
    this.frame = frame;
    this.constructUrl = url;
    this.svgId = generateUUID();
    this.svgElem = $(document.createElement("svg"));
    this.elements = [];
    this.chains = [];
    this.svgElem.attr("id", this.svgId);
    this.svgElem.addClass("engine-workspace");
    this.svgElem.attr("baseProfile", "full");
    this.svgElem.attr("xmlns:ev", "http://www.w3.org/2001/xml-events");
    this.svgElem.attr("xmlns", "http://www.w3.org/2000/svg");
    this.svgElem.attr("xmlns:xlink", "http://www.w3.org/1999/xlink");
    $(this.frame).append(this.svgElem);

    var workSpace = this;

    $(this.svgElem).mousemove(function (event) {
        if (!workSpace.dynamicLine)
            return;
        $(workSpace.dynamicLine.end).remove();
        workSpace.dynamicLine.end = workSpace.createEmptyForMouse(event);
    });

    $(this.svgElem).mousedown(function (event) {
        if (workSpace.dynamicLine)
            workSpace.destroyDynamicLine();
    });
}

EngineFlowChart.prototype.addChain = function (from, to) {
    if (from === to || !from || !to)
        return;

    this.chains.push(new Chain(from, to));
}

EngineFlowChart.prototype.removeChain = function (id) {
    this.chains = this.chains.filter(x => x.id !== id);
}

EngineFlowChart.prototype.addElement = function (event, elemType) {

    ajaxPost(this.constructUrl, { elementType: type }, function (data) {
        var elem = new EngineElement(data, [event.pageX, event.pageY]);
        elem.frame = this;
        this.elements.push(elem);
    });
}

EngineFlowChart.prototype.removeElement = function (element) {
    this.chains.filter(x => x.from === element || x.to === element).forEach(x => this.removeChain(x));
    engineElements = engineElements.filter(x => x.pureElement["id"] !== element.getProperty("id"));
}

EngineFlowChart.prototype.createEmptyForMouse = function (event) {
    var empty = document.createElement("p");
    $(empty).css("position", "absolute");
    $(empty).css("top", event.pageY);
    $(empty).css("left", event.pageX);
    $(document.body).append(empty);
    return empty;
}

EngineFlowChart.prototype.startDynamicLine = function (event, element) {
    this.dynamicLine = new LeaderLine($(element), this.createEmptyForMouse(event), { color: '#0099CC' });
}

EngineFlowChart.prototype.destroyDynamicLine = function () {
    this.dynamicLine.remove();
    this.dynamicLine = null;
}

EngineFlowChart.prototype.destroyAll = function () {
    this.elements.forEach(x => this.removeElement(x));
}

EngineFlowChart.prototype.getById = function (id) {
    var elem = engineElements.filter(x => x.pureElement["id"] === element.getProperty("id"));
    if (elem.length == 0)
        return null;
    return elem[0];
}

EngineFlowChart.prototype.paint = function () {
    this.elements.forEach(x => x.paint());
    this.chains.forEach(x => x.paint());
}

EngineFlowChart.prototype.paintFor = function (elem) {
    elem.paint();
    this.chains.filter(x => x.from === elem || x.to === elem).forEach(x => x.paint());
}
