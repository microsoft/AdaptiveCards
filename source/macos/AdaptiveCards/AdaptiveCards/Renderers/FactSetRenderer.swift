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
            let textProperties = BridgeTextUtils.convertFact(toRichTextElementProperties: fact)
            
            let valueMarkdownParserResult = BridgeTextUtils.processText(from: fact, hostConfig: hostConfig, isTitle: false)
            let valueMarkdownString = TextUtils.getMarkdownString(for: rootView, with: valueMarkdownParserResult)
            let valueAttributedContent = TextUtils.addFontProperties(attributedString: valueMarkdownString, textProperties: textProperties, hostConfig: hostConfig)
            
            let titleMarkdownParserResult = BridgeTextUtils.processText(from: fact, hostConfig: hostConfig, isTitle: true)
            let titleMarkdownString = TextUtils.getMarkdownString(for: rootView, with: titleMarkdownParserResult)
            let titleAttributedContent = TextUtils.addFontProperties(attributedString: titleMarkdownString, textProperties: textProperties, hostConfig: hostConfig)
            let titleBoldContent = TextUtils.addBoldProperty(attributedString: titleAttributedContent, textProperties: textProperties, hostConfig: hostConfig)
                         
            let titleView = ACRTextView(asFactSetFieldWith: config.hyperlinkColorConfig)
            let valueView = ACRTextView(asFactSetFieldWith: config.hyperlinkColorConfig)
            
            // If not markdown use plain text
            if !valueMarkdownParserResult.isHTML {
                valueView.string = fact.getValue() ?? ""
            } else {
                valueView.textStorage?.setAttributedString(valueAttributedContent)
            }
            
            if !titleMarkdownParserResult.isHTML {
                titleView.string = fact.getTitle() ?? ""
            } else {
                titleView.textStorage?.setAttributedString(titleBoldContent)
            }
            
            if let colorHex = hostConfig.getForegroundColor(style, color: .default, isSubtle: false), let textColor = ColorUtils.color(from: colorHex) {
                titleView.textColor = textColor
                valueView.textColor = textColor
            }
            
            if !(titleView.string.isEmpty) || !(valueView.string.isEmpty) {
                titleStack.addArrangedSubview(titleView)
                requiredWidth = max(titleView.attributedString().size().width + 10, requiredWidth)
                valueStack.addArrangedSubview(valueView)
            }
        }
        
        // Add both elements into the Horizontal Stack
        mainFactView.addSubview(titleStack)
        mainFactView.addSubview(valueStack)
        
        titleStack.leadingAnchor.constraint(equalTo: mainFactView.leadingAnchor).isActive = true
        titleStack.topAnchor.constraint(equalTo: mainFactView.topAnchor).isActive = true
        titleStack.bottomAnchor.constraint(equalTo: mainFactView.bottomAnchor).isActive = true
        titleStack.trailingAnchor.constraint(equalTo: valueStack.leadingAnchor).isActive = true
        
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
        let widthConstraint = valueStack.widthAnchor.constraint(lessThanOrEqualTo: mainFactView.widthAnchor, multiplier: 0.48)
        widthConstraint.priority = .defaultHigh
        widthConstraint.isActive = true

        // Make the height of each title and value equal
        for (index, elem) in titleStack.arrangedSubviews.enumerated() {
            let valueArray = valueStack.arrangedSubviews
            guard let titleView = elem as? ACRTextView, let valueView = valueArray[index] as? ACRTextView else {
                 logError("Element inside FactSetStack is not of type ACRFactTextField")
                 continue
            }
            titleView.heightAnchor.constraint(equalTo: valueView.heightAnchor).isActive = true
        }
        
        return mainFactView
    }
}
