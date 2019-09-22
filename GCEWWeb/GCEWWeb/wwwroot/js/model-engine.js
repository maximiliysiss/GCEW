
function elementFactory(data, pos, type) {
    console.log(pos);
    switch (type) {
        case "Variable":
            return new Variable(data, pos);
        case "Addiction":
        case "Substract":
        case "Divide":
        case "Multiply":
        case "GlobalStart":
            return new PrimitiveOperation(data, pos);
    }
    return new EngineElement(data, pos);
}

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
            if (el.frame.dynamicLine && $(x).hasClass("inputElement"))
                el.frame.addChain($(x).attr("id"), $(event.target).attr("id"));
            else if ($(x).hasClass("outputElement"))
                el.frame.startDynamicLine(event, $(x).attr("id"));
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
    constructor(pureElement, position) {
        super(pureElement, position);

        var va = this;

        $(this.htmlElement).click(function (event) { va.onClickEvent(event, el.htmlActual); });
        this.value = "";
        var el = this;
        $(this.htmlElement).children(".value").each(function () {
            $(this).on('input', function () {
                el.value = $(this).val();
                console.log(el.value);
            });
        });
    }
}

class PrimitiveOperation extends EngineElement {
    constructor(pureElement, position) {
        super(pureElement, position);
        $(this.htmlElement).children(".engine-interaction-element").each(x => {
            $(x).click(function (event) { onClickEvent(event, x); });
        });
    }
}

class Print extends EngineElement {
    constructor(pureElement, position) {
        super(pureElement, position);
    }
}