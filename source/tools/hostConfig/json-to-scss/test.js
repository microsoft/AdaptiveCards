var convert = require('./index');

var config = {
    "spacing": {
      "small": 3,
      "default": 8,
      "medium": 20,
      "large": 30,
      "extraLarge": 40,
      "padding": 15
    },
    "separator": {
      "lineThickness": 1,
      "lineColor": "#EEEEEE"
    },
  "supportsInteractivity": true,
  "fontFamily": "Segoe UI",
  "fontSizes": {
     "small": 12,
     "default": 14,
     "medium": 17,
     "large": 21,
     "extraLarge": 26
    },
    "fontWeights": {
      "lighter": 200,
      "default": 400,
      "bolder": 600
    },
    "containerStyles": {
      "default": {
        "backgroundColor": "#00000000",
        "foregroundColors": {
          "default": {
            "default": "#FF333333",
            "subtle": "#EE333333"
          },
          "accent": {
            "default": "#FF2E89FC",
            "subtle": "#882E89FC"
          },
          "attention": {
            "default": "#FFcc3300",
            "subtle": "#DDcc3300"
          },
          "good": {
            "default": "#FF54a254",
            "subtle": "#DD027502"
          },
          "warning": {
            "default": "#FFe69500",
            "subtle": "#DDe69500"
          }
        }
      },
      "emphasis": {
        "backgroundColor": "#08000000",
        "foregroundColors": {
          "default": {
            "default": "#FF333333",
            "subtle": "#EE333333"
          },
          "accent": {
            "default": "#FF2E89FC",
            "subtle": "#882E89FC"
          },
          "attention": {
            "default": "#FFcc3300",
            "subtle": "#DDcc3300"
          },
          "good": {
            "default": "#FF54a254",
            "subtle": "#DD027502"
          },
          "warning": {
            "default": "#FFe69500",
            "subtle": "#DDe69500"
          }
        }
      }
    },
    "imageSizes": {
      "small": 40,
      "medium": 80,
      "large": 160
    },
    "actions": {
      "maxActions": 5,
      "spacing": "default",
      "buttonSpacing": 10,
      "showCard": {
        "actionMode": "inline",
        "inlineTopMargin": 16
      },
      "actionsOrientation": "horizontal",
      "actionAlignment": "stretch"
    },
    "adaptiveCard": {
      "allowCustomStyle": false
    },
    "imageSet": {
      "imageSize": "medium",
      "maxImageHeight": 100
    },
    "factSet": {
      "title": {
        "color": "default",
        "size": "default",
        "isSubtle": false,
        "weight": "bolder",
        "wrap": true,
        "maxWidth": 150
      },
      "value": {
        "color": "default",
        "size": "default",
        "isSubtle": false,
        "weight": "default",
        "wrap": true
      },
      "spacing": 10
    }
  };

var conversion = convert(config);

process.stdout.write(conversion);
