
class Chain {
    constructor(from, to) {
        this.from = from;
        this.to = to;
        this.id = generateUUID();
        this.line = new LeaderLine($("#" + from), "#" + to, { color: '#0099CC' });
    }

    paint() {
        this.line.position();
    }
}

class EngineElement {
    constructor(pureElement, position) {
        var el = this;
        this.pureElement = pureElement;
        this.elementId = pureElement["id"];
        this.isShow = false;
        this.htmlElement = $(elementFromString(pureElement["html"]));
        this.htmlElement.css({ position: "", visibility: "", display: "" });
        //this.engineClickable = $(this.htmlElment).children(".engine-interaction-element").each(x => {
        //    $(x).click(function (event) {
        //        if (el.frame.dynamicLine && x.hasClass("inputElement"))
        //            el.frame.addChain(x.id, $(event.target).attr("id"));
        //        else if (x.hasClass("outputElement"))
        //            el.frame.startDynamicLine(event, x);
        //    });
        //});
        this.frame = null;
        this.position = position;
        this.elementsType = [];

        $(this.htmlElement).draggable({
            drag: function () {
                //el.frame.paintFor(el);
            }
        });
    }

    getProperty(name) {
        return this.pureElement[name];
    }

    get actualFrame() {
        return $('#' + this.frame.svgId);
    }

    paint() {
        $('#' + this.elementId).css("left", this.position[0]);
        $('#' + this.elementId).css("top", this.position[1]);
        if (!this.isShow)
            this.actualFrame.append(this.htmlElement);
    }
}