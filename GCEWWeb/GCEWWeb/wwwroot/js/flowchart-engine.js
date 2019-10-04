// Engine

class EngineFlowChart {

    constructor(frame, url) {
        this.dynamicLine = null;
        this.frame = frame;
        this.constructUrl = url;

        this.isNew = !$(frame).children("svg").length > 0;

        if (this.isNew) {
            this.svgId = generateUUID();
            this.svgElem = $(document.createElement("svg"));
            this.svgElem.attr("id", this.svgId);
            //this.svgElem.addClass("engine-workspace");
            this.svgElem.attr("style", "width:100%; height:99.999%;");
            this.svgElem.attr("baseProfile", "full");
            this.svgElem.attr("xmlns:ev", "http://www.w3.org/2001/xml-events");
            this.svgElem.attr("xmlns", "http://www.w3.org/2000/svg");
            this.svgElem.attr("xmlns:xlink", "http://www.w3.org/1999/xlink");
            $(this.frame).append(this.svgElem);
        } else {
            var ch = $(frame).children();
            this.svgId = generateUUID();
            this.svgElem = $(ch[0]);
            this.svgElem.attr("id", this.svgId);
        }
        this.chains = [];

        var workSpace = this;

        $(this.frame).mousemove(function (event) {
            if (!workSpace.dynamicLine)
                return;
            $(workSpace.dynamicLine.end).remove();
            workSpace.dynamicLine.end = workSpace.createEmptyForMouse(event, $(workSpace.dynamicLine.end).attr("type"));
        });

        $(this.frame).click(function (event) {
            if (workSpace.dynamicLine)
                workSpace.destroyDynamicLine();
        });
    }

    addChain(from, to, type) {
        if (from === to || !from || !to)
            return;
        if (!this.chains)
            this.chains = [];

        var chain = new Chain(from, to, type);
        chain.number = $('#' + to).attr("number");
        this.chains.push(chain);
    }

    removeChain(id) {
        this.chains = this.chains.filter(x => x.id !== id);
    }

    get position() {
        var elem = $('#' + this.svgId);
        return [elem.offset().left, elem.offset().top];
    }

    addElement(event, elemType) {
        console.log(elemType);
        var engine = this;
        var pos = this.position;
        ajaxPost(this.constructUrl, { Value: types[elemType] }, function (data) {
            var elem = elementFactory(data, [event.pageX - pos[0], event.pageY - pos[1]], elemType);
            // var elem = new EngineElement(data, [event.pageX - pos[0], event.pageY - pos[1]]);
            elem.frame = engine;
            if (!engine.elements)
                engine.elements = [];
            engine.elements.push(elem);
            elem.paint();
        });
    }

    removeElement(element) {
        this.chains.filter(x => x.from === element || x.to === element).forEach(x => this.removeChain(x));
        var elem = this.getById(element);
        elem.remove();
        this.elements = this.elements.filter(x => x.pureElement["guid"] !== element);
    }

    createEmptyForMouse(event, type) {
        var empty = document.createElement("p");
        $(empty).css("position", "absolute");
        $(empty).attr("type", type);
        $(empty).css("top", event.pageY);
        $(empty).css("left", event.pageX);
        $(document.body).append(empty);
        return empty;
    }

    startDynamicLine(event, element, type) {
        var color = type ? '#FF0000' : '#0099CC';
        this.dynamicLine = new LeaderLine(document.getElementById(element), this.createEmptyForMouse(event, type), { color: color }, { type: type });
    }

    destroyDynamicLine() {
        this.dynamicLine.remove();
        this.dynamicLine = null;
    }

    destroyAll() {
        this.elements.forEach(x => this.removeElement(x.pureElement["guid"]));
    }

    getById(id) {
        var elem = this.elements.filter(x => x.pureElement["guid"] === id);
        if (elem.length === 0)
            return null;
        return elem[0];
    }

    paint() {
        this.elements.forEach(x => x.paint());
        this.chains.forEach(x => x.paint());
    }

    paintFor(elem) {
        elem.paint();
        var fl = this;
        if (this.chains) {
            $(elem.htmlElement).find(".engine-interaction-element").each(function () {
                var id = $(this).attr("id");
                fl.chains.filter(x => x.from === id || x.to === id).forEach(x => x.paint());
            });
        }

        if ($(elem.htmlElement).hasClass("engine-interaction-element")) {
            var id = $(elem.htmlElement).attr("id");
            fl.chains.filter(x => x.from === id || x.to === id).forEach(x => x.paint());
        }
    }
}