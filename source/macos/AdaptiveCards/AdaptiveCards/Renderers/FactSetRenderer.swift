import AdaptiveCards_bridge
import AppKit

class FactSetRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = FactSetRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
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
            let attributedContent = TextUtils.getMarkdownString(parserResult: markdownParserResult)
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
                    attributedContent.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedContent.length))
                    valueView.attributedTextValue = attributedContent
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
        // Getting Max width from Host config if it exists
        let maxAllowedWidth = CGFloat(truncating: factsetConfig?.title.maxWidth ?? 150)
        if requiredWidth > maxAllowedWidth {
            titleStack.widthAnchor.constraint(equalToConstant: maxAllowedWidth).isActive = true
        } else {
            titleStack.widthAnchor.constraint(equalToConstant: (requiredWidth + 1)).isActive = true
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
