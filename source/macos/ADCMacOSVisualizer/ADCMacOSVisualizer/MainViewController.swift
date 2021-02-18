import AdaptiveCards
import AppKit

class MainViewController: NSViewController {
    // MARK: View Life-Cycle
    override func loadView() {
        guard let delegate = NSApplication.shared.delegate as? AppDelegate, let window = delegate.window else { return }
        view = NSView(frame: window.frame)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.wantsLayer = true
        
        setupViews()
        setupConstraints()
    }
    
    // MARK: Actions
    @objc private func handleButtonAction() {
        let result = AdaptiveCard.from(jsonString: testPayload)
        guard let card = result.getAdaptiveCard() else {
            print("RENDER FAILED")
            return
        }
        print("ELEMENTS:")
        card.getBody().forEach { print($0.getTypeString() ?? "nil") }
        card.getBody().forEach { print(type(of: $0)) }
        
        switch AdaptiveCard.parseHostConfig(from: sampleHostConfig) {
        case .success(let config):
            print("PARSED HOSTCONFIG")
            print("Font family - \(config.getFontFamily() ?? "nil")")
            
            let cardView = AdaptiveCard.render(card: card, with: config, width: 335)
            stackView.addArrangedSubview(cardView)
            
        case .failure(let error):
            print("Failure: \(error.localizedDescription)")
        }
    }
    
    // MARK: Views and Constraints
    private lazy var testButton: NSButton = {
        let view = NSButton(title: "Click Me!", target: self, action: #selector(handleButtonAction))
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    private lazy var stackView: NSStackView = {
        let view = NSStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.addArrangedSubview(testButton)
        return view
    }()
    
    private func setupViews() {
        view.addSubview(stackView)
    }
    
    private func setupConstraints() {
//        testButton.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
//        testButton.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
        
        stackView.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
        stackView.topAnchor.constraint(equalTo: view.topAnchor).isActive = true
        stackView.bottomAnchor.constraint(equalTo: view.bottomAnchor).isActive = true
        stackView.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
//        stackView.widthAnchor.constraint(equalTo: view.widthAnchor, multiplier: 0.33).isActive = true
    }
}

let simpleTextPayload = """
{
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "version": "1.0",
  "type": "AdaptiveCard",
  "speak": "Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM",
  "body": [
    {
      "type": "TextBlock",
      "text": "Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM",
      "separator": true,
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Passengers",
      "weight": "bolder",
      "isSubtle": false,
      "wrap": true
    }
  ]
}
"""

let testPayload = """
{
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
  "version": "1.0",
  "type": "AdaptiveCard",
  "speak": "Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM",
  "body": [
    {
      "type": "TextBlock",
      "text": "Passengers",
      "weight": "bolder",
      "isSubtle": false,
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM Your flight is confirmed for you and 3 other passengers from San Francisco to Amsterdam on Friday, October 10 8:30 AM",
      "separator": true,
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Jeremy Goldberg",
      "spacing": "none",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Evan Litvak",
      "spacing": "none",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "2 Stops",
      "weight": "bolder",
      "spacing": "medium",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Tue, May 30, 2017 12:25 PM",
      "weight": "bolder",
      "spacing": "none",
      "wrap": true
    },
    {
      "type": "ColumnSet",
      "separator": true,
      "columns": [
        {
          "type": "Column",
          "width": 1,
          "items": [
            {
              "type": "TextBlock",
              "text": "San Francisco",
              "isSubtle": true,
              "wrap": true
            },
            {
              "type": "TextBlock",
              "size": "extraLarge",
              "color": "accent",
              "text": "SFO",
              "spacing": "none",
              "wrap": true
            }
          ]
        },
        {
          "type": "Column",
          "width": "auto",
          "items": [
            {
              "type": "TextBlock",
              "text": " ",
              "wrap": true
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/airplane.png",
              "size": "small",
              "spacing": "none",
              "altText": "Flight to"
            }
          ]
        },
        {
          "type": "Column",
          "width": 1,
          "items": [
            {
              "type": "TextBlock",
              "horizontalAlignment": "right",
              "text": "Amsterdam",
              "isSubtle": true,
              "wrap": true
            },
            {
              "type": "TextBlock",
              "horizontalAlignment": "right",
              "size": "extraLarge",
              "color": "accent",
              "text": "AMS",
              "spacing": "none",
              "wrap": true
            }
          ]
        }
      ]
    },
    {
      "type": "TextBlock",
      "text": "Non-Stop",
      "weight": "bolder",
      "spacing": "medium",
      "wrap": true
    },
    {
      "type": "TextBlock",
      "text": "Fri, Jun 2, 2017 1:55 PM",
      "weight": "bolder",
      "spacing": "none",
      "wrap": true
    },
    {
      "type": "ColumnSet",
      "separator": true,
      "columns": [
        {
          "type": "Column",
          "width": 1,
          "items": [
            {
              "type": "TextBlock",
              "text": "Amsterdam",
              "isSubtle": true,
              "wrap": true
            },
            {
              "type": "TextBlock",
              "size": "extraLarge",
              "color": "accent",
              "text": "AMS",
              "spacing": "none",
              "wrap": true
            }
          ]
        },
        {
          "type": "Column",
          "width": "auto",
          "items": [
            {
              "type": "TextBlock",
              "text": " ",
              "wrap": true
            },
            {
              "type": "Image",
              "url": "https://adaptivecards.io/content/airplane.png",
              "size": "small",
              "spacing": "none",
              "altText": "Flight to"
            }
          ]
        },
        {
          "type": "Column",
          "width": 1,
          "items": [
            {
              "type": "TextBlock",
              "horizontalAlignment": "right",
              "text": "San Francisco",
              "isSubtle": true,
              "wrap": true
            },
            {
              "type": "TextBlock",
              "horizontalAlignment": "right",
              "size": "extraLarge",
              "color": "accent",
              "text": "SFO",
              "spacing": "none",
              "wrap": true
            }
          ]
        }
      ]
    },
    {
      "type": "ColumnSet",
      "spacing": "medium",
      "columns": [
        {
          "type": "Column",
          "width": "1",
          "items": [
            {
              "type": "TextBlock",
              "text": "Total",
              "size": "medium",
              "isSubtle": true,
              "wrap": true
            }
          ]
        },
        {
          "type": "Column",
          "width": 1,
          "items": [
            {
              "type": "TextBlock",
              "horizontalAlignment": "right",
              "text": "$4,032.54",
              "size": "medium",
              "weight": "bolder",
              "wrap": true
            }
          ]
        }
      ]
    }
  ]
}
"""

let sampleHostConfig = """
{
    "hostCapabilities": {
        "capabilities": null
    },
    "choiceSetInputValueSeparator": ",",
    "supportsInteractivity": true,
    "fontFamily": "CiscoSans",
    "spacing": {
        "small": 4,
        "default": 12,
        "medium": 12,
        "large": 12,
        "extraLarge": 16,
        "padding": 12
    },
    "separator": {
        "lineThickness": 1,
        "lineColor": "#EEEEEE"
    },
    "fontSizes": {
        "small": 12,
        "default": 14,
        "medium": 16,
        "large": 20,
        "extraLarge": 22
    },
    "fontWeights": {
        "lighter": 300,
        "default": 400,
        "bolder": 600
    },
    "imageSizes": {
        "small": 40,
        "medium": 80,
        "large": 160
    },
    "containerStyles": {
        "default": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#535759",
                    "subtle": "#929596"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#FFFFFF"
        },
        "emphasis": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#383C40",
                    "subtle": "#737678"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#F2F4F5"
        },
        "good": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#535759",
                    "subtle": "#929596"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#E8FAE9"
        },
        "accent": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#535759",
                    "subtle": "#929596"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#E6F9FC"
        },
        "warning": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#535759",
                    "subtle": "#929596"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#FFE1D9"
        },
        "attention": {
            "foregroundColors": {
                "default": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "dark": {
                    "default": "#171B1F",
                    "subtle": "#535759"
                },
                "light": {
                    "default": "#535759",
                    "subtle": "#929596"
                },
                "accent": {
                    "default": "#007EA8",
                    "subtle": "#00A0D1"
                },
                "good": {
                    "default": "#1B8728",
                    "subtle": "#24AB31"
                },
                "warning": {
                    "default": "#D93829",
                    "subtle": "#FF5C4A"
                },
                "attention": {
                    "default": "#C74F0E",
                    "subtle": "#F26B1D"
                }
            },
            "backgroundColor": "#FCF4E1"
        }
    },
    "actions": {
        "maxActions": 5,
        "buttonSpacing": 8,
        "showCard": {
            "actionMode": "Inline",
            "inlineTopMargin": 8,
            "style": "emphasis"
        },
        "style": "emphasis",
        "preExpandSingleShowCardAction": false,
        "actionsOrientation": "Vertical",
        "actionAlignment": "stretch"
    },
    "adaptiveCard": {
        "allowCustomStyle": false
    },
    "imageSet": {
        "maxImageHeight": 100
    },
    "media": {
        "allowInlinePlayback": false
    },
    "factSet": {
        "title": {
            "size": "Default",
            "color": "Default",
            "isSubtle": false,
            "weight": "Bolder",
            "wrap": true
        },
        "value": {
            "size": "Default",
            "color": "Default",
            "isSubtle": false,
            "weight": "Default",
            "wrap": true
        },
        "spacing": 10
    },
    "cssClassNamePrefix": null
}
"""
