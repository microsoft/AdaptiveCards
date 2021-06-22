import AdaptiveCards_bridge
import AppKit

class TextBlockRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = TextBlockRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let textBlock = element as? ACSTextBlock else {
            logError("Element is not of type ACSTextBlock")
            return NSView()
        }
        let textView = ACRTextView()
        textView.translatesAutoresizingMaskIntoConstraints = false
        
        let markdownResult = BridgeTextUtils.processText(from: textBlock, hostConfig: hostConfig)
        let markdownString = TextUtils.getMarkdownString(for: rootView, with: markdownResult)
        let attributedString = TextUtils.addFontProperties(attributedString: markdownString, textProperties: BridgeTextUtils.convertTextBlock(toRichTextElementProperties: textBlock), hostConfig: hostConfig)
        
        textView.isEditable = false
        textView.textContainer?.lineFragmentPadding = 0
        textView.textContainerInset = .zero
        textView.layoutManager?.usesFontLeading = false
        textView.setContentHuggingPriority(.required, for: .vertical)
        
        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.alignment = ACSHostConfig.getTextBlockAlignment(from: textBlock.getHorizontalAlignment())
        
        attributedString.addAttributes([.paragraphStyle: paragraphStyle], range: NSRange(location: 0, length: attributedString.length))
        
        if let colorHex = hostConfig.getForegroundColor(style, color: textBlock.getTextColor(), isSubtle: textBlock.getIsSubtle()), let textColor = ColorUtils.color(from: colorHex) {
            attributedString.addAttributes([.foregroundColor: textColor], range: NSRange(location: 0, length: attributedString.length))
        }
        
        textView.textContainer?.lineBreakMode = .byTruncatingTail
        let resolvedMaxLines = textBlock.getMaxLines()?.intValue ?? 0
        textView.textContainer?.maximumNumberOfLines = textBlock.getWrap() ? resolvedMaxLines : 1
    
        textView.textStorage?.setAttributedString(attributedString)
        textView.textContainer?.widthTracksTextView = true
        textView.backgroundColor = .clear
        textView.linkTextAttributes = [
            NSAttributedString.Key.foregroundColor: config.hyperlinkColorConfig.foregroundColor,
            NSAttributedString.Key.underlineColor: config.hyperlinkColorConfig.underlineColor,
            NSAttributedString.Key.underlineStyle: config.hyperlinkColorConfig.underlineStyle.rawValue
        ]
        
        if attributedString.string.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
            // Hide accessibility Element
        }
        
        return textView
    }
}

extension NSAttributedString.Key {
    static let submitAction = NSAttributedString.Key("submitAction")
}
