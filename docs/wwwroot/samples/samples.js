AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
    alert(JSON.stringify(action));
};

AdaptiveCards.setHostConfig({
    "supportsInteractivity": true,
    "strongSeparation": {
        "spacing": 10,
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
            "normal": "#FF00FF",
            "subtle": "#DDFF00FF"
        },
        "good": {
            "normal": "#00a000",
            "subtle": "#DD00a000"
        },
        "warning": {
            "normal": "#c00000",
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
            "spacing": 10
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
        "backgroundColor": "#fafafa",
        "padding": {
            "left": 10,
            "top": 10,
            "right": 10,
            "bottom": 10
        }
    },
    "container": {
        "separation": {
            "spacing": 10
        },
        "normal": {},
        "emphasis": {
            "backgroundColor": "#cccccc",
            "borderColor": "#aaaaaa",
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
                "spacing": 10
            },
            "normal": {
                "spacing": 10
            },
            "medium": {
                "spacing": 10
            },
            "large": {
                "spacing": 10
            },
            "extraLarge": {
                "spacing": 10
            }
        }
    },
    "image": {
        "size": "medium",
        "separation": {
            "spacing": 10
        }
    },
    "imageSet": {
        "imageSize": "medium",
        "separation": {
            "spacing": 10
        }
    },
    "factSet": {
        "separation": {
            "spacing": 10
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
            "spacing": 10
        }
    },
    "columnSet": {
        "separation": {
            "spacing": 10
        }
    },
    "column": {
        "separation": {
            "spacing": 10
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

