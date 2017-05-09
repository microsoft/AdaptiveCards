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

            var navLinks = document.getElementsByClassName("navLink");
            for (var i = 0; i < navLinks.length; i++) {
                navLinks[i].className = navLinks[i].className.replace(" w3-gray", "");
            }
            var navLink = document.getElementById(folder + '-' + topic + '-link');
            navLink.className = navLink.className + " w3-gray";
        });
}

$(document).ready(() => {
    if (window.location.hash == '')
        showTopic("about", "overview");
    else {
        var parts = window.location.hash.slice(1).split('-');
        if (parts.length == 3 && parts[2] == 'page')
            showTopic(parts[0], parts[1]);
    }
});

window.addEventListener("hashchange", function () {
    var parts = window.location.hash.slice(1).split('-');
    if (parts.length == 3 && parts[2] == 'page')
        showTopic(parts[0], parts[1]);
}, false);
