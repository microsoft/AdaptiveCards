// This script will be run within the webview itself
// It cannot access the main VS Code APIs directly.
(function () {
    const vscode = acquireVsCodeApi();
    $(document).ready(function(){
            

        $('#loginFrame').on("navigating", function(){
            vscode.postMessage({
                command: 'action',
                text: "We are navigating!"
            })
        })
    })

}());