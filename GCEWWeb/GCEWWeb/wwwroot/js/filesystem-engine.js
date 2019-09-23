
var urlFileSystems;
var url = '';

function createNewProject(event) {
    $("#new-project-form").submit();
}

function openFile(path) {
    var fileName = path.replace(/^.*[\\\/]/, '').split('.')[0];
    ajaxPost(urlFileSystems["OpenFile"], { path: path }, function (data) {

        var empty = elementFromString(data);
        actualEngine = new EngineFlowChart(empty, url);
        actualEngine.path = path;
        enginesFlowChart.push(actualEngine);

        var newItemConfig = {
            title: fileName,
            type: 'component',
            componentName: 'window-component',
            componentState: { text: empty },
            props: { path: path, type: "file" }
        };
        dockLayouts.root.contentItems[0].contentItems[1].addChild(newItemConfig);
        if (actualEngine.isNew)
            actualEngine.addElement({ pageX: actualEngine.position[0] + 150, pageY: actualEngine.position[1] + 150 }, "GlobalStart");
        reHandlerContextMenus();
    });
}

function deleteFile(event) {
    ajaxPost(urlFileSystems["DeleteFile"], { name: contextMenuTarget.attr("path") }, function (data) {
        if (data)
            updateProjectTree();
        toastr["success"](data ? "Success" : "Failed");
    });
}

function deleteFolder(event) {
    ajaxPost(urlFileSystems["DeleteFolder"], { name: contextMenuTarget.attr("path") }, function (data) {
        if (data)
            updateProjectTree();
        toastr["success"](data ? "Success" : "Failed");
    });
}

function onAddNewFileInFolder(ev) {
    fileSystemOperationWithInput(urlFileSystems["CreateFileInFolder"]);
}

function onAddFolder(ev) {
    fileSystemOperationWithInput(urlFileSystems["AddNewFolder"]);
}

function addFolder(event) {
    createTextBoxForEnterData("Enter folder name", onAddFolder);
}

function addFraphicFile(event) {
    createTextBoxForEnterData("Enter filename", onAddNewFileInFolder);
}

function addNewFile(event) {
    createTextBoxForEnterData("Enter name", onAddNewFile);
}

function findActiveDocumentRoot(dockLayouts) {
    return findActiveDoc(dockLayouts.config);
}

function findActiveDoc(dockLayouts) {
    if (dockLayouts.componentName === "window-component" && dockLayouts.props && dockLayouts.props.type === "file")
        return dockLayouts;

    if (dockLayouts.content) {

        var find = null;

        for (var i = 0; i < dockLayouts.content.length; i++) {
            var elem = dockLayouts.content[i];
            if (elem.activeItemIndex !== undefined)
                find = findActiveDoc(elem.content[elem.activeItemIndex]);
            else
                find = findActiveDoc(elem);

            if (find)
                return find;
        }
    }

    return null;
}