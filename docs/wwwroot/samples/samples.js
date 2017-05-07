AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
    alert(JSON.stringify(action));
};

AdaptiveCards.setHostConfig({
    "supportsInteractivity": true,
    "strongSeparation": {
        "spacing": 40,
        "lineThickness": 1,
        "lineColor": "#EEEEEE"
    },
    "fontFamily": "Segoe UI",
    "fontSizes": {
        "small": 12,
        "normal": 14,
        "medium": 17,
        "large": 21,
        "extraLarge": 26
    },
    "fontWeights": {
        "lighter": 200,
        "normal": 400,
        "bolder": 600
    },
    "colors": {
        "dark": {
            "normal": "#333333",
            "subtle": "#EE333333"
        },
        "light": {
            "normal": "#FFFFFF",
            "subtle": "#88FFFFFF"
        },
        "accent": {
            "normal": "#2E89FC",
            "subtle": "#882E89FC"
        },
        "attention": {
            "normal": "#FFD800",
            "subtle": "#DDFFD800"
        },
        "good": {
            "normal": "#00FF00",
            "subtle": "#DD00FF00"
        },
        "warning": {
            "normal": "#FF0000",
            "subtle": "#DDFF0000"
        }
    },
    "imageSizes": {
        "small": 40,
        "medium": 80,
        "large": 160
    },
    "actions": {
        "maxActions": 5,
        "separation": {
            "spacing": 20
        },
        "buttonSpacing": 20,
        "stretch": false,
        "showCard": {
            "actionMode": "inlineEdgeToEdge",
            "inlineCardSpacing": 16,
            "backgroundColor": "#08000000",
            "padding": {
                "top": 16,
                "right": 16,
                "bottom": 16,
                "left": 16
            }
        },
        "actionsOrientation": "horizontal",
        "actionAlignment": "left"
    },
    "adaptiveCard": {
        "backgroundColor": "#00000000",
        "padding": {
            "left": 20,
            "top": 20,
            "right": 20,
            "bottom": 20
        }
    },
    "container": {
        "separation": {
            "spacing": 20
        },
        "normal": {},
        "emphasis": {
            "backgroundColor": "#EEEEEE",
            "borderColor": "#AAAAAA",
            "borderThickness": {
                "top": 1,
                "right": 1,
                "bottom": 1,
                "left": 1
            },
            "padding": {
                "top": 10,
                "right": 10,
                "bottom": 10,
                "left": 10
            }
        }
    },
    "textBlock": {
        "color": "dark",
        "separations": {
            "small": {
                "spacing": 20
            },
            "normal": {
                "spacing": 20
            },
            "medium": {
                "spacing": 20
            },
            "large": {
                "spacing": 20
            },
            "extraLarge": {
                "spacing": 20
            }
        }
    },
    "image": {
        "size": "medium",
        "separation": {
            "spacing": 20
        }
    },
    "imageSet": {
        "imageSize": "medium",
        "separation": {
            "spacing": 20
        }
    },
    "factSet": {
        "separation": {
            "spacing": 20
        },
        "title": {
            "color": "dark",
            "size": "normal",
            "isSubtle": false,
            "weight": "bolder"
        },
        "value": {
            "color": "dark",
            "size": "normal",
            "isSubtle": false,
            "weight": "normal"
        },
        "spacing": 10
    },
    "input": {
        "separation": {
            "spacing": 20
        }
    },
    "columnSet": {
        "separation": {
            "spacing": 20
        }
    },
    "column": {
        "separation": {
            "spacing": 20
        }
    }
});

function renderCard(targetDiv, card) {
    var adaptiveCard = new AdaptiveCards.AdaptiveCard();
    adaptiveCard.parse(card);
    var renderedCard = adaptiveCard.render();
    var div = document.getElementById(targetDiv).appendChild(renderedCard);
}

function toggleContent(id) {
    // Get the DOM reference
    var contentId = document.getElementById(id);
    contentId.style.display == "block" ? contentId.style.display = "none" : contentId.style.display = "block";
}

function showElement(id) {
    var elements = document.getElementsByClassName("element");
    // hide all elements
    for (var i = 0; i < elements.length; i++) {
        var element = elements[i];
        element.style.display = "none";
    }
    var element = document.getElementById(id + 'Content');
    element.style.display = 'block';

    var elementLinks = document.getElementsByClassName("elementLink");
    for (var i = 0; i < elementLinks.length; i++) {
        elementLinks[i].className = elementLinks[i].className.replace(" w3-gray", "");
    }
    var elementLink = document.getElementById(id + 'Link');
    elementLink.className = elementLink.className + " w3-gray";
}

window.addEventListener("hashchange", function () {
    showElement(window.location.hash.slice(1));
}, false);

