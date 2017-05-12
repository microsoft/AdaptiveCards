function myAccFunc(sectionName) {
    var x = document.getElementById(sectionName);
    if (x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
    } else {
        x.className = x.className.replace(" w3-show", "");
    }
}

function showSection(sectionName) {
    var x = document.getElementById(sectionName);
    if (x && x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
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
    var parts = hashmark.split('-');
    var part ='';
    // make sure it's visible
    for (i= 0; i < parts.length;i++)
    {
        if (part[i] == "about")
            part += "aboutPage";
        else 
            part += parts[i];
        showSection(part);
        part += '-';
    }

    var path = "/api/markdown/documentation/markdown/" + hashmark.replace(/-/g,'/') + ".md";
    $.get(path,
        null,
        function (data) {
            // load content
            document.getElementById('topic').innerHTML = data;
            document.getElementById("sidebar").style = "";
            // set table classes
            $("table").addClass("w3-table w3-bordered");

            // show selected
            var navLinks = document.getElementsByClassName("navLink");
            for (var i = 0; i < navLinks.length; i++) {
                navLinks[i].className = navLinks[i].className.replace(" w3-gray", "");
            }
            var navLink = document.getElementById(hashmark + '-link');
            navLink.className = navLink.className + " w3-gray";
        });
}

function showSideBar() {
    var x = document.getElementById("sidebar");
    if (x.className.indexOf("w3-show") == -1) {
        x.style = "display: block!important";
    } 
}

$(document).ready(() => {
    if (window.location.hash == '') {
        showTopic("#about-overview");
        var x = document.getElementById("aboutPage");
        if (x.className.indexOf("w3-show") == -1) 
            x.className += " w3-show";
    }
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
