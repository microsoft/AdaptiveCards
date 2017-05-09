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

function showTopic(hashmark) {
    hashmark = hashmark.slice(1);
    var path = "/api/markdown/documentation/markdown/" + hashmark.replace(/-/g,'/') + ".md";
    $.get(path,
        null,
        function (data) {
            document.getElementById('topic').innerHTML = data;

            var navLinks = document.getElementsByClassName("navLink");
            for (var i = 0; i < navLinks.length; i++) {
                navLinks[i].className = navLinks[i].className.replace(" w3-gray", "");
            }
            var navLink = document.getElementById(hashmark + '-link');
            navLink.className = navLink.className + " w3-gray";
        });
}

$(document).ready(() => {
    if (window.location.hash == '')
        showTopic("#about-overview");
    else {
        if (window.location.hash.startsWith('#about') ||
            window.location.hash.startsWith('#create') ||
            window.location.hash.startsWith('#display') ||
            window.location.hash.startsWith('#resources'))
            showTopic(window.location.hash);
    }
});

window.addEventListener("hashchange", function () {
    if (window.location.hash.startsWith('#about') ||
        window.location.hash.startsWith('#create') ||
        window.location.hash.startsWith('#display') ||
        window.location.hash.startsWith('#resources'))
        showTopic(window.location.hash);
}, false);
