import AdaptiveCards_bridge
import AppKit

class ACRMultilineInputTextView: NSView, NSTextViewDelegate {
    @IBOutlet var contentView: NSView!
    @IBOutlet var scrollView: ACRScrollView!
    @IBOutlet var textView: ACRTextView!
    
    private var placeholderAttrString: NSAttributedString?
    private let config: InputFieldConfig
    var maxLen: Int = 0
    var id: String?
    
    init(config: InputFieldConfig) {
        self.config = config
        super.init(frame: .zero)
        BundleUtils.loadNibNamed("ACRMultilineInputTextView", owner: self)
        textView.allowsUndo = true
        setupViews()
        setupConstaints()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupViews() {
        addSubview(contentView)
    }
    
    private func setupConstaints() {
        contentView.translatesAutoresizingMaskIntoConstraints = false
        contentView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        contentView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        contentView.topAnchor.constraint(equalTo: topAnchor).isActive = true
        contentView.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        let heightConstraint = contentView.heightAnchor.constraint(equalToConstant: 100.0)
        heightConstraint.priority = .fittingSizeCompression
        heightConstraint.isActive = true
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        scrollView.wantsLayer = true
        scrollView.focusRingCornerRadius = config.focusRingCornerRadius
        scrollView.focusRingType = .exterior
        scrollView.autohidesScrollers = true
        scrollView.disableScroll = true
        textView.delegate = self
        textView.responderDelegate = self
        textView.isAutomaticQuoteSubstitutionEnabled = false
        textView.isAutomaticDashSubstitutionEnabled = false
        textView.isAutomaticTextReplacementEnabled = false
        textView.smartInsertDeleteEnabled = false
        textView.font = config.font
        // 2 is added as extra padding to match single line input text element
        textView.textContainer?.lineFragmentPadding = config.leftPadding + 2
        wantsLayer = true
        layer?.borderColor = config.borderColor.cgColor
        layer?.borderWidth = config.borderWidth
        layer?.cornerRadius = config.focusRingCornerRadius
        textView.backgroundColor = config.backgroundColor
        
        // For hover need tracking area
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    func setPlaceholder(_ placeholder: String) {
        let placeholderValue = NSMutableAttributedString(string: placeholder)
        placeholderValue.addAttributes([.foregroundColor: config.placeholderTextColor, .font: config.font], range: NSRange(location: 0, length: placeholderValue.length))
        // 2 is added as extra padding to match single line input text element
        textView.placeholderLeftPadding = config.leftPadding + 2
        textView.placeholderAttrString = placeholderValue
    }
    
    func setValue(value: String, maximumLen: NSNumber?) {
        var attributedValue = NSMutableAttributedString(string: value)
        let maxCharLen = Int(truncating: maximumLen ?? 0)
        if maxCharLen > 0, attributedValue.string.count > maxCharLen {
            attributedValue = NSMutableAttributedString(string: String(attributedValue.string.dropLast(attributedValue.string.count - maxCharLen)))
        }
        attributedValue.addAttributes([.foregroundColor: NSColor.textColor, .font: config.font], range: NSRange(location: 0, length: attributedValue.length))
        textView.textStorage?.setAttributedString(attributedValue)
    }
    
    func setId(_ idString: String?) {
        self.id = idString
    }
    
    func setVisibilty(to isVisible: Bool) {
        self.isHidden = !isVisible
    }
    
    func textDidChange(_ notification: Notification) {
        guard maxLen > 0  else { return } // maxLen returns 0 if propery not set
        // This stops the user from exceeding the maxLength property of Inut.Text if prroperty was set
        guard let textView = notification.object as? NSTextView, textView.string.count > maxLen else { return }
        textView.string = String(textView.string.dropLast())
        // Below check added to ensure prefilled value doesn't exceede the maxLength property if set
        if textView.string.count > maxLen {
            textView.string = String(textView.string.dropLast(textView.string.count - maxLen))
        }
    }
    
    override func mouseEntered(with event: NSEvent) {
        textView.backgroundColor = config.highlightedColor
    }
    
    override func mouseExited(with event: NSEvent) {
        textView.backgroundColor = config.backgroundColor
    }
}

extension ACRMultilineInputTextView: InputHandlingViewProtocol {
    var value: String {
        textView.string
    }
    
    var key: String {
        guard let id = id else {
            logError("ID must be set on creation")
            return ""
        }
        return id
    }
    
    var isValid: Bool {
        return true
    }
}

extension ACRMultilineInputTextView: ACRTextViewResponderDelegate {
    func textViewDidBecomeFirstResponder() {
        scrollView.disableScroll = false
        layer?.borderColor = config.activeBorderColor.cgColor
    }
    
    func textViewDidResignFirstResponder() {
        scrollView.disableScroll = true
        layer?.borderColor = config.borderColor.cgColor
    }
}
