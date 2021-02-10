import AdaptiveCards_bridge
import AppKit

protocol BaseInputHandler { }

protocol BaseCardElementRendererProtocol {
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView
}

class TextBlockRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = TextBlockRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: NSView, parentView: NSView, inputs: [BaseInputHandler]) -> NSView {
        guard let textBlock = element as? ACSTextBlock else {
            logError("Element is not of type ACSTextBlock")
            return NSView()
        }
        let textView = ACRTextView()
        textView.translatesAutoresizingMaskIntoConstraints = false
        
        let markdownResult = BridgeTextUtils.processText(from: textBlock, hostConfig: hostConfig)
        let attributedString: NSMutableAttributedString
        if markdownResult.isHTML, let htmlData = markdownResult.htmlData {
            do {
                attributedString = try NSMutableAttributedString(data: htmlData, options: [.documentType: NSAttributedString.DocumentType.html], documentAttributes: nil)
                // Delete trailing newline character
                attributedString.deleteCharacters(in: NSRange(location: attributedString.length - 1, length: 1))
                textView.isSelectable = true
            } catch {
                attributedString = NSMutableAttributedString(string: markdownResult.parsedString)
            }
        } else {
            attributedString = NSMutableAttributedString(string: markdownResult.parsedString)
            // Delete <p> and </p>
            attributedString.deleteCharacters(in: NSRange(location: 0, length: 3))
            attributedString.deleteCharacters(in: NSRange(location: attributedString.length - 4, length: 4))
        }
        
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
        textView.textContainer?.maximumNumberOfLines = textBlock.getMaxLines()?.intValue ?? 0
        if textView.textContainer?.maximumNumberOfLines == 0 && !textBlock.getWrap() {
            // TODO: To revisit
            textView.textContainer?.maximumNumberOfLines = 0
        }
    
        textView.textStorage?.setAttributedString(attributedString)
        textView.font = FontUtils.getFont(for: hostConfig, with: BridgeTextUtils.convertTextBlock(toRichTextElementProperties: textBlock))
        textView.textContainer?.widthTracksTextView = true
        textView.backgroundColor = .clear
        
        if attributedString.string.trimmingCharacters(in: .whitespacesAndNewlines).isEmpty {
            // Hide accessibility Element
        }
        
        return textView
    }
}

class ACRTextView: NSTextView {
    override var intrinsicContentSize: NSSize {
        guard let layoutManager = layoutManager, let textContainer = textContainer else {
            return super.intrinsicContentSize
        }
        layoutManager.ensureLayout(for: textContainer)
        return layoutManager.usedRect(for: textContainer).size
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
}
