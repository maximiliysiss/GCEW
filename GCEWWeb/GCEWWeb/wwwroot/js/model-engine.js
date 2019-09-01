
var Chain = function (from, to) {
    this.from = from;
    this.to = to;
    this.id = generateUUID();
    this.line = new LeaderLine($("#" + from), "#" + to, { color: '#0099CC' });
}

Chain.prototype.paint = function () {
    this.line.position();
}

var EngineElement = function (pureElement, position) {
    var el = this;
    this.pureElement = pureElement;
    this.pureElement["id"] = pureElement["Id"];
    this.isShow = false;
    this.htmlElement = $(createElementFromHTML(pureElement["Html"]));
    this.engineClickable = $(this.htmlElment).children(".engine-interaction-element").forEach(x => {
        $(x).click(function (event) {
            if (el.frame.dynamicLine && x.hasClass("inputElement"))
                el.frame.addChain(x.id, $(event.target).attr("id"));
            else if (x.hasClass("outputElement"))
                el.frame.startDynamicLine(event, x);
        });
    });
    this.position = position;
    this.frame = null;
    this.elementsType = [];

    $(this.htmlElement).draggable({
        drag: function () {
            el.frame.paintFor(el);
        }
    });
}

EngineElement.prototype.getProperty = function (name) {
    return pureElement[name];
}

EngineElement.prototype.paint = function () {
    $(this.htmlElement).css("left", this.position[0]);
    $(this.htmlElement).css("top", this.position[1]);
    if (!isShow)
        $(frame).append(this.htmlElement);
}