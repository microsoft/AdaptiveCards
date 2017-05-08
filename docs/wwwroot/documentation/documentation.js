function myAccFunc(sectionName) {
    var x = document.getElementById(sectionName);
    if (x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
        x.previousElementSibling.className += " w3-gray";
    } else {
        x.className = x.className.replace(" w3-show", "");
        x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" w3-gray", "");
    }
}

function myDropFunc() {
    var x = document.getElementById("demoDrop");
    if (x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
        x.previousElementSibling.className += " w3-gray";
    } else {
        x.className = x.className.replace(" w3-show", "");
        x.previousElementSibling.className =
            x.previousElementSibling.className.replace(" w3-gray", "");
    }
}

function showTopic(folder, topic) {
    var path = "/api/markdown/documentation/markdown";
    if (folder)
        path = path + "/" + folder;
    path = path + "/" + topic + ".md";
    $.get(path,
        null,
        function (data) {
            document.getElementById('topic').innerHTML = data;
        });
}

$(document).ready(() => {
    if (window.location.hash == '')
        showTopic("about", "overview");
    else {
        var parts = window.location.hash.slice(1).split('-');
        showTopic(parts[0], parts[1]);
    }
});

window.addEventListener("hashchange", function () {
    var parts = window.location.hash.slice(1).split('-');
    showTopic(parts[0], parts[1]);
}, false);
