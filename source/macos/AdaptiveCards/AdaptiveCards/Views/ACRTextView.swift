import AppKit

class ACRTextView: NSTextView, SelectActionHandlingProtocol {
    weak var responderDelegate: ACRTextViewResponderDelegate?
    var placeholderAttrString: NSAttributedString?
    var placeholderLeftPadding: CGFloat?
    var target: TargetHandler?
    
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
        responderDelegate?.textViewDidBecomeFirstResponder()
        return super.becomeFirstResponder()
    }

    override func draw(_ dirtyRect: NSRect) {
        super.draw(dirtyRect)

        guard string.isEmpty else { return }
        placeholderAttrString?.draw(in: dirtyRect.offsetBy(dx: placeholderLeftPadding ?? 5, dy: 0))
    }
    
    override func resignFirstResponder() -> Bool {
        self.needsDisplay = true
        clearSelectedRange()
        responderDelegate?.textViewDidResignFirstResponder()
        return super.resignFirstResponder()
    }
    
    override func mouseDown(with event: NSEvent) {
        super.mouseDown(with: event)
        guard target != nil else { return }
        
        // SelectAction exists
        let location = convert(event.locationInWindow, from: nil)
        var fraction: CGFloat = 0.0
        if let textContainer = self.textContainer, let textStorage = self.textStorage, let layoutManager = self.layoutManager {
            let characterIndex = layoutManager.characterIndex(for: location, in: textContainer, fractionOfDistanceBetweenInsertionPoints: &fraction)
            if characterIndex < textStorage.length, let action = textStorage.attribute(.selectAction, at: characterIndex, effectiveRange: nil) as? TargetHandler {
                action.handleSelectionAction(for: self)
            }
        }
    }
    
    override func hitTest(_ point: NSPoint) -> NSView? {
        guard target != nil else {
            return super.hitTest(point)
        }
        
        // SelectAction exists
        var location = convert(point, from: self)
        location.y = self.bounds.height - location.y
        var fraction: CGFloat = 0.0
        if let textContainer = self.textContainer, let textStorage = self.textStorage, let layoutManager = self.layoutManager {
            let characterIndex = layoutManager.characterIndex(for: location, in: textContainer, fractionOfDistanceBetweenInsertionPoints: &fraction)
            if characterIndex < textStorage.length, textStorage.attribute(.selectAction, at: characterIndex, effectiveRange: nil) != nil {
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
    
    convenience init(asFactSetFieldWith config: HyperlinkColorConfig) {
        self.init()
        setContentCompressionResistancePriority(.required, for: .vertical)
        alignment = .left
        isEditable = false
        backgroundColor = .clear
        linkTextAttributes = [
            .foregroundColor: config.foregroundColor,
            .underlineColor: config.underlineColor,
            .underlineStyle: config.underlineStyle.rawValue
        ]
    }
    
    override var canBecomeKeyView: Bool {
        return isEditable
    }
}

protocol ACRTextViewResponderDelegate: AnyObject {
    func textViewDidBecomeFirstResponder()
    func textViewDidResignFirstResponder()
}
