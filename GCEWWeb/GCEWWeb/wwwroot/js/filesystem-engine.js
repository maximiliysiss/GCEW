
var urlFileSystems;
var url = '';

function createNewProject(event) {
    $("#new-project-form").submit();
}

function openFile(path) {
    var fileName = path.replace(/^.*[\\\/]/, '').split('.')[0];
    ajaxPost(urlFileSystems["OpenFile"], { path: path }, function (data) {

        var empty = elementFromString(emptyWorkspace);
        actualEngine = new EngineFlowChart(empty, url);
        enginesFlowChart.push(actualEngine);

        var newItemConfig = {
            title: fileName,
            type: 'component',
            componentName: 'window-component',
            componentState: { text: empty }
        };
        dockLayouts.root.contentItems[0].contentItems[1].addChild(newItemConfig);
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