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

class ACRTextView: NSTextView, SelectActionHandlingProtocol {
    var placeholderAttrString: NSAttributedString?
    
    override var intrinsicContentSize: NSSize {
        guard let layoutManager = layoutManager, let textContainer = textContainer else {
            return super.intrinsicContentSize
        }
        layoutManager.ensureLayout(for: textContainer)
        let size = layoutManager.usedRect(for: textContainer).size
        let width = size.width + 2
        return NSSize(width: width, height: size.height)
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
        let constraint = heightAnchor.constraint(equalTo: superview.heightAnchor)
        constraint.priority = .defaultHigh
        constraint.isActive = true
    }
    
    // This point onwards adds placeholder funcunality to TextView
    override func becomeFirstResponder() -> Bool {
        self.needsDisplay = true
        return super.becomeFirstResponder()
    }

    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)

        guard string.isEmpty else { return }
        placeholderAttrString?.draw(in: dirtyRect.offsetBy(dx: 5, dy: 0))
    }
    
    override func resignFirstResponder() -> Bool {
        self.needsDisplay = true
        clearSelectedRange()
        return super.resignFirstResponder()
    }
    
    override func mouseDown(with event: NSEvent) {
        super.mouseDown(with: event)
        let location = convert(event.locationInWindow, from: nil)
        var fraction: CGFloat = 0.0
        if let textContainer = self.textContainer, let textStorage = self.textStorage, let layoutManager = self.layoutManager {
            let characterIndex = layoutManager.characterIndex(for: location, in: textContainer, fractionOfDistanceBetweenInsertionPoints: &fraction)
            if characterIndex < textStorage.length, let action = textStorage.attribute(.submitAction, at: characterIndex, effectiveRange: nil) as? TargetHandler {
                action.handleSelectionAction(for: self)
            }
        }
    }
    
    override func hitTest(_ point: NSPoint) -> NSView? {
        var location = convert(point, from: self)
        location.y = self.bounds.height - location.y
        var fraction: CGFloat = 0.0
        if let textContainer = self.textContainer, let textStorage = self.textStorage, let layoutManager = self.layoutManager {
            let characterIndex = layoutManager.characterIndex(for: location, in: textContainer, fractionOfDistanceBetweenInsertionPoints: &fraction)
            if characterIndex < textStorage.length, textStorage.attribute(.submitAction, at: characterIndex, effectiveRange: nil) != nil {
                return self
            }
        }
        return super.hitTest(point)
    }
    
    func clearSelectedRange() {
        let selectedString = (string as NSString).substring(with: selectedRange())
        if !selectedString.isEmpty {
            setSelectedRange(NSRange(location: 0, length: 0))
        }
    }
}

extension NSAttributedString.Key {
    static let submitAction = NSAttributedString.Key("submitAction")
}
