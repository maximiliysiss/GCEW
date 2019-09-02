// Engine

class EngineFlowChart {

    constructor(frame, url) {
        this.dynamicLine = null;
        this.frame = frame;
        this.constructUrl = url;
        this.svgId = generateUUID();
        this.svgElem = $(document.createElement("svg"));
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

    addChain(from, to) {
        if (from === to || !from || !to)
            return;
        if (!this.chains)
            this.chains = [];
        this.chains.push(new Chain(from, to));
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
        ajaxPost(this.constructUrl, { Value: elemType }, function (data) {
            var elem = new EngineElement(data, [event.pageX - pos[0], event.pageY - pos[1]]);
            elem.frame = engine;
            if (!this.elements)
                this.elements = [];
            this.elements.push(elem);
            elem.paint();
        });
    }

    removeElement(element) {
        this.chains.filter(x => x.from === element || x.to === element).forEach(x => this.removeChain(x));
        engineElements = engineElements.filter(x => x.pureElement["id"] !== element.getProperty("id"));
    }

    createEmptyForMouse(event) {
        var empty = document.createElement("p");
        $(empty).css("position", "absolute");
        $(empty).css("top", event.pageY);
        $(empty).css("left", event.pageX);
        $(document.body).append(empty);
        return empty;
    }

    startDynamicLine(event, element) {
        this.dynamicLine = new LeaderLine($(element), this.createEmptyForMouse(event), { color: '#0099CC' });
    }

    destroyDynamicLine() {
        this.dynamicLine.remove();
        this.dynamicLine = null;
    }

    destroyAll() {
        this.elements.forEach(x => this.removeElement(x));
    }

    getById(id) {
        var elem = engineElements.filter(x => x.pureElement["id"] === element.getProperty("id"));
        if (elem.length == 0)
            return null;
        return elem[0];
    }

    paint() {
        this.elements.forEach(x => x.paint());
        this.chains.forEach(x => x.paint());
    }

    paintFor(elem) {
        elem.paint();
        if (this.chains)
            this.chains.filter(x => x.from === elem || x.to === elem).forEach(x => x.paint());
    }
}