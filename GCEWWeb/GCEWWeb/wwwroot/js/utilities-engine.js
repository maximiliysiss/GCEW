
var generateUUID = function () {
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
        var r = Math.random() * 16 | 0;
        return (c == 'x' ? r : (r & 0x3 | 0x8)).toString(16);
    });
};

var elementFromString = function (htmlString) {
    var div = document.createElement('div');
    div.innerHTML = htmlString.trim();
    return div.firstChild;
}

var getSize = function (elemJQuery) {
    var clone = elemJQuery.clone(false);
    clone.css('visibility', 'hidden');
    clone.css('position', 'absolute');
    var size = [clone.width(), clone.height()];
    $('body').append(clone);
    clone.remove();
    return size;
}

var emptyWorkspace = '';