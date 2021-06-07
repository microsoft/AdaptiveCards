import AdaptiveCards_bridge
import AppKit

class RichTextBlockRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = RichTextBlockRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let richTextBlock = element as? ACSRichTextBlock else {
            logError("Element is not of type ACSRichTextBlock")
            return NSView()
        }
        
        let textView = ACRTextView()
        textView.translatesAutoresizingMaskIntoConstraints = false
        textView.isEditable = false
        textView.textContainer?.lineFragmentPadding = 0
        textView.textContainerInset = .zero
        textView.layoutManager?.usesFontLeading = false
        textView.setContentHuggingPriority(.required, for: .vertical)
        textView.backgroundColor = .clear
        textView.linkTextAttributes = [
            NSAttributedString.Key.foregroundColor: config.hyperlinkColorConfig.foregroundColor,
            NSAttributedString.Key.underlineColor: config.hyperlinkColorConfig.underlineColor,
            NSAttributedString.Key.underlineStyle: config.hyperlinkColorConfig.underlineStyle.rawValue
        ]
        // init content
        let content = NSMutableAttributedString()
        
        // parsing through the inlines
        for inline in richTextBlock.getInlines() {
            guard let textRun = inline as? ACSTextRun else {
                logError("Not of type ACSTextRun")
                continue
            }
                
            let markdownResult = BridgeTextUtils.processText(fromRichTextBlock: textRun, hostConfig: hostConfig)
            
            let textRunContent = TextUtils.getMarkdownString(parserResult: markdownResult)
                
            // Set paragraph style such as line break mode and alignment
            let paragraphStyle = NSMutableParagraphStyle()
            paragraphStyle.alignment = ACSHostConfig.getTextBlockAlignment(from: richTextBlock.getHorizontalAlignment())
            textRunContent.addAttributes([.paragraphStyle: paragraphStyle], range: NSRange(location: 0, length: textRunContent.length))

            // Obtain text color to apply to the attributed string
            if let colorHex = hostConfig.getForegroundColor(style, color: textRun.getTextColor(), isSubtle: textRun.getIsSubtle()) {
                let foregroundColor = ColorUtils.color(from: colorHex) ?? NSColor.darkGray
                textRunContent.addAttributes([.foregroundColor: foregroundColor], range: NSRange(location: 0, length: textRunContent.length))
            }
            
            // apply highlight to textrun
            if textRun.getHighlight() {
                if let colorHex = hostConfig.getHighlightColor(style, color: textRun.getTextColor(), isSubtle: textRun.getIsSubtle()) {
                    if let highlightColor = ColorUtils.color(from: colorHex) {
                        textRunContent.addAttributes([.backgroundColor: highlightColor], range: NSRange(location: 0, length: textRunContent.length))
                    }
                }
            }
            
            // Add SelectAction to textRun
            if textRun.getSelectAction() != nil {
                let target = textView.getTargetHandler(for: textRun.getSelectAction(), rootView: rootView)
                if let actionTarget = target {
                    textRunContent.addAttributes([.submitAction: actionTarget], range: NSRange(location: 0, length: textRunContent.length))
                    textRunContent.addAttributes([.foregroundColor: NSColor.linkColor], range: NSRange(location: 0, length: textRunContent.length))
                    textRunContent.addAttributes([.underlineStyle: 1], range: NSRange(location: 0, length: textRunContent.length))
                    // Rootview add target
                    rootView.addTarget(actionTarget)
                }
            }
                                
            // apply strikethrough to textrun
            if textRun.getStrikethrough() {
                textRunContent.addAttributes([.strikethroughStyle: 1], range: NSRange(location: 0, length: textRunContent.length))
            }
                    
            // apply underline to textrun
            if config.supportsSchemeV1_3, textRun.getUnderline() {
                textRunContent.addAttributes([.underlineStyle: NSUnderlineStyle.single.rawValue], range: NSRange(location: 0, length: textRunContent.length))
            }
            content.append(textRunContent)
        }
 
        textView.textContainer?.lineBreakMode = .byTruncatingTail
        textView.textStorage?.setAttributedString(content)
        textView.textContainer?.widthTracksTextView = true
   
    return textView
    }
}
