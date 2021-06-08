import AdaptiveCards_bridge
import AppKit

class FactSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = FactSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let factSet = element as? ACSFactSet else {
            logError("Element is not of type ACSFactSet")
            return NSView()
        }
        let factArray = factSet.getFacts()
        let factsetConfig = hostConfig.getFactSet()
        
        let mainFactView = ACRFactSetView()
        mainFactView.translatesAutoresizingMaskIntoConstraints = false
        
        // Create stacks to hold title and value of FactSet
        let titleStack = NSStackView()
        titleStack.translatesAutoresizingMaskIntoConstraints = false
        titleStack.orientation = .vertical
        titleStack.alignment = .leading
        
        let valueStack = NSStackView()
        valueStack.translatesAutoresizingMaskIntoConstraints = false
        valueStack.orientation = .vertical
        valueStack.alignment = .leading
        
        var requiredWidth: CGFloat = 0
        // Main loop to iterate over Array of facts
        for fact in factArray {
            let markdownParserResult = BridgeTextUtils.processText(from: fact, hostConfig: hostConfig)
            let markdownString = TextUtils.getMarkdownString(parserResult: markdownParserResult)
            let attributedContent = TextUtils.addFontProperties(attributedString: markdownString, textProperties: BridgeTextUtils.convertFact(toRichTextElementProperties: fact), hostConfig: hostConfig)
            let titleView = ACRFactTextField()
            let valueView = ACRFactTextField()
            titleView.plainTextValue = fact.getTitle()
            titleView.setupTitleString(with: hostConfig.getFontSize(.default, size: .default))
            // If not markdown use plain text
            if !markdownParserResult.isHTML {
                valueView.plainTextValue = fact.getValue()
            } else {
                valueView.attributedTextValue = attributedContent
            }
            
            if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: false), let textColor = ColorUtils.color(from: colorHex) {
                titleView.textColor = textColor
                valueView.textColor = textColor
                if markdownParserResult.isHTML {
                    if let attributedString = valueView.attributedTextValue {
                        let attributedStringCopy = NSMutableAttributedString(attributedString: attributedString)
                        attributedString.enumerateAttributes(in: NSRange(location: 0, length: attributedString.length), options: .longestEffectiveRangeNotRequired, using: { attributes, range, _ in
                            if (attributes[.foregroundColor] as? NSColor) != nil {
                                attributedStringCopy.addAttribute(.foregroundColor, value: textColor as Any, range: range)
                            }
                            if (attributes[NSAttributedString.Key.link ] as? NSURL) != nil {
                                attributedStringCopy.addAttribute(.foregroundColor, value: config.hyperlinkColorConfig.foregroundColor, range: range)
                                attributedStringCopy.addAttribute(.underlineColor, value: config.hyperlinkColorConfig.underlineColor, range: range)
                                attributedStringCopy.addAttribute(.underlineStyle, value: config.hyperlinkColorConfig.underlineStyle.rawValue, range: range)
                            }
                        })
                        valueView.attributedTextValue = attributedStringCopy
                    }
                }
            }
            
            if !(titleView.isEmpty) || !(valueView.isEmpty) {
                titleStack.addArrangedSubview(titleView)
                requiredWidth = max(titleView.attributedTextValue?.size().width ?? 0, requiredWidth)
                valueStack.addArrangedSubview(valueView)
            }
        }
        
        // Add both elements into the Horizontal Stack
        mainFactView.addSubview(titleStack)
        mainFactView.addSubview(valueStack)
        
        titleStack.leadingAnchor.constraint(equalTo: mainFactView.leadingAnchor).isActive = true
        titleStack.topAnchor.constraint(equalTo: mainFactView.topAnchor).isActive = true
        titleStack.bottomAnchor.constraint(equalTo: mainFactView.bottomAnchor).isActive = true
        // Spacing between title and value in the horizontal Stack
        titleStack.trailingAnchor.constraint(equalTo: valueStack.leadingAnchor, constant: -10).isActive = true
        
        let constraint = titleStack.widthAnchor.constraint(lessThanOrEqualTo: mainFactView.widthAnchor, multiplier: 0.48)
        constraint.priority = .defaultHigh
        constraint.isActive = true

        if let maxWidth = factsetConfig?.title.maxWidth, let maxAllowedWidth = CGFloat(exactly: maxWidth), requiredWidth > maxAllowedWidth {
            titleStack.widthAnchor.constraint(lessThanOrEqualToConstant: maxAllowedWidth).isActive = true
        } else {
            titleStack.widthAnchor.constraint(lessThanOrEqualToConstant: requiredWidth + 2).isActive = true
        }

        valueStack.trailingAnchor.constraint(equalTo: mainFactView.trailingAnchor).isActive = true
        valueStack.topAnchor.constraint(equalTo: mainFactView.topAnchor).isActive = true
        valueStack.bottomAnchor.constraint(equalTo: mainFactView.bottomAnchor).isActive = true

        // Make the height of each title and value equal
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            let valueArray = valueStack.arrangedSubviews
            guard let titleView = elem as? ACRFactTextField, let valueView = valueArray[index] as? ACRFactTextField else {
                 logError("Element inside FactSetStack is not of type ACRFactTextField")
                 continue
            }
            titleView.heightAnchor.constraint(equalTo: valueView.heightAnchor).isActive = true
        }
        
        return mainFactView
    }
}
