var convert = require('./index');

var config = {
    supportsInteractivity: true,
    strongSeparation: {
        spacing: 40,
        lineThickness: 1,
        lineColor: "#EEEEEE"
    },
    fontFamily: "Segoe UI",
    fontSizes: {
        small: 8,
        normal: 10,
        medium: 12,
        large: 14,
        extraLarge: 16
    },
    fontWeights: {
        lighter: 200,
        normal: 400,
        bolder: 600
    },
    colors: {
        dark: {
            normal: "#0000FF",
            subtle: "#222222"
        },
        light: {
            normal: "#FFFFFF",
            subtle: "#DDDDDD"
        },
        accent: {
            normal: "#0000FF",
            subtle: "#0000DD" 
        },
        attention: {
            normal: "#FF6600",
            subtle: "#DD4400"
        },
        good: {
            normal: "#00FF00",
            subtle: "#00DD00"
        },
        warning: {
            normal: "#FF0000",
            subtle: "#DD0000"
        }
    },
    imageSizes: {
        small: 40,
        medium: 80,
        large: 160
    },
    actions: {
        maxActions: 5,
        separation: {
            spacing: 20
        },
        buttonSpacing: 20,
        showCard: {
            actionMode: "inlineEdgeToEdge",
            inlineTopMargin: 16,
            backgroundColor: "#22000000",
            padding: {
                top: 16,
                right: 16,
                bottom: 16,
                left: 16
            }
        },
        actionsOrientation: "horizontal",
        actionAlignment: "left"
    },
    adaptiveCard: {
        backgroundColor: "#00000000",
        padding: {
            left: 20,
            top: 20,
            right: 20,
            bottom: 20
        }
    },
    container: {
        separation: {
            spacing: 20
        },
        normal: {
            backgroundColor: "#FFFFFF",
        },
        emphasis: {
            backgroundColor: "#EEEEEE",
            borderColor: "#AAAAAA",
            borderThickness: {
                top: 1,
                right: 1,
                bottom: 1,
                left: 1
            },
            padding: {
                top: 10,
                right: 10,
                bottom: 10,
                left: 10
            }
        }
    },
    textBlock: {
        color: "dark",
        separations: {
            small: {
                spacing: 20,
            },
            normal: {
                spacing: 20
            },
            medium: {
                spacing: 20
            },
            large: {
                spacing: 20
            },
            extraLarge: {
                spacing: 20
            }
        }
    },
    image: {
        size: "medium",
        separation: {
            spacing: 20
        }
    },
    imageSet: {
        imageSize: "medium",
        separation: {
            spacing: 20
        }
    },
    factSet: {
        separation: {
            spacing: 20
        },
        title: {
            color: "dark",
            size: "normal",
            isSubtle: false,
            weight: "bolder",
            wrap: true,
            maxWidth: 150
        },
        value: {
            color: "dark",
            size: "normal",
            isSubtle: false,
            weight: "normal",
            wrap: true
        },
        spacing: 10
    },
    input: {
        separation: {
            spacing: 20
        }
    },
    columnSet: {
        separation: {
            spacing: 20
        }
    },
    column: {
        separation: {
            spacing: 20
        }
    }
};

var conversion = convert(config);

process.stdout.write(conversion);
