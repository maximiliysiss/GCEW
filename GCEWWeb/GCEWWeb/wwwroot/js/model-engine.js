
function elementFactory(data, pos, type) {
    console.log(pos);
    switch (type) {
        case "Variable":
            return new Variable(data, pos, type);
        case "Addiction":
        case "Substract":
        case "Divide":
        case "Multiply":
        case "GlobalStart":
        case "Print":
            return new PrimitiveOperation(data, pos, type);
    }
    return new EngineElement(data, pos);
}

class Chain {
    constructor(from, to, type) {
        this.from = from;
        this.to = to;
        this.id = generateUUID();
        var color = type ? "#FF0000" : '#0099CC';
        this.line = new LeaderLine($("#" + from)[0], $("#" + to)[0], { color: color });
    }

    paint() {
        this.line.position();
    }
}

class EngineElement {
    constructor(pureElement, position, type) {
        var el = this;
        this.pureElement = pureElement;
        this.type = type;
        this.elementId = pureElement["guid"];
        this.isShow = false;
        this.htmlElement = $(elementFromString(pureElement["html"]));
        var size = getSize($(this.htmlElement));
        console.log(size);
        position = [position[0] - size[0] / 2, position[1] - size[1] / 2];
        this.position = position;
        this.htmlElement.css("left", position[0]);
        this.htmlElement.css("top", position[1]);
        this.onClickEvent = function (event, x) {

            var type = $(x).hasClass("flow");

            if (el.frame.dynamicLine && $(x).hasClass("input") && type.toString() === $(el.frame.dynamicLine.end).attr("type")) {
                el.frame.addChain($(el.frame.dynamicLine.start).attr("id"), $(x).attr("id"), type);
                el.frame.destroyDynamicLine();
            }
            else if ($(x).hasClass("output"))
                el.frame.startDynamicLine(event, $(x).attr("id"), $(x).hasClass("flow"));

            event.preventDefault();
            event.stopPropagation();
        };

        this.frame = null;
        this.elementsType = [];

        createContextMenu($(this.htmlElement));

        $(this.htmlElement).draggable({
            drag: function () {
                el.frame.paintFor(el);
            }
        });
    }

    getProperty(name) {
        return this.pureElement[name];
    }

    get actualFrame() {
        return $('#' + this.frame.svgId);
    }

    get htmlActual() {
        return $('#' + this.elementId);
    }

    get actualPosition() {
        var elem = this.htmlActual.position();
        return [elem.left, elem.top];
    }

    paint() {
        if (!this.isShow)
            this.actualFrame.append(this.htmlElement);
        this.isShow = true;
    }

    remove() {
        this.htmlActual.remove();
    }
}

class Variable extends EngineElement {
    constructor(pureElement, position, type) {
        super(pureElement, position, type);

        var va = this;

        $(this.htmlElement).click(function (event) { va.onClickEvent(event, el.htmlActual); });
        this.value = "";
        var el = this;
        $(this.htmlElement).find(".value").each(function () {
            $(this).on('input', function () {
                el.value = $(this).val();
                console.log(el.value);
            });
        });
    }
}

class PrimitiveOperation extends EngineElement {
    constructor(pureElement, position, type) {
        super(pureElement, position, type);

        var va = this;

        $(this.htmlElement).find(".engine-interaction-element").each(function () {
            $(this).attr("id", generateUUID());
            $(this).click(function (event) { va.onClickEvent(event, this); });
        });
    }
}