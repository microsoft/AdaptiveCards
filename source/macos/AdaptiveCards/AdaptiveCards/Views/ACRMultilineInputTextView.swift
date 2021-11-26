import AdaptiveCards_bridge
import AppKit

class ACRMultilineInputTextView: NSView, NSTextViewDelegate {
    @IBOutlet var contentView: NSView!
    @IBOutlet var scrollView: ACRScrollView!
    @IBOutlet var textView: ACRTextView!
    
    private var placeholderAttrString: NSAttributedString?
    private let config: RenderConfig
    private let inputConfig: InputFieldConfig
    var maxLen: Int = 0
    var id: String?
    
    init(config: RenderConfig) {
        self.config = config
        self.inputConfig = config.inputFieldConfig
        super.init(frame: .zero)
        BundleUtils.loadNibNamed("ACRMultilineInputTextView", owner: self)
        textView.allowsUndo = true
        setupViews()
        setupConstraints()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupViews() {
        addSubview(contentView)
    }
    
    private func setupConstraints() {
        contentView.translatesAutoresizingMaskIntoConstraints = false
        contentView.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        contentView.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        contentView.topAnchor.constraint(equalTo: topAnchor).isActive = true
        contentView.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        let heightConstraint = contentView.heightAnchor.constraint(greaterThanOrEqualToConstant: 100)
        heightConstraint.isActive = true
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        scrollView.wantsLayer = true
        scrollView.focusRingCornerRadius = inputConfig.focusRingCornerRadius
        scrollView.focusRingType = .exterior
        scrollView.autohidesScrollers = true
        scrollView.disableScroll = true
        textView.delegate = self
        textView.responderDelegate = self
        textView.isAutomaticQuoteSubstitutionEnabled = false
        textView.isAutomaticDashSubstitutionEnabled = false
        textView.isAutomaticTextReplacementEnabled = false
        textView.smartInsertDeleteEnabled = false
        textView.font = inputConfig.font
        textView.textContainer?.lineFragmentPadding = 0
        textView.textContainerInset = NSSize(width: inputConfig.multilineFieldInsets.left, height: inputConfig.multilineFieldInsets.top)
        wantsLayer = true
        layer?.borderColor = inputConfig.borderColor.cgColor
        layer?.borderWidth = inputConfig.borderWidth
        layer?.cornerRadius = inputConfig.focusRingCornerRadius
        textView.backgroundColor = inputConfig.backgroundColor
        textView.setAccessibilityTitle(config.localisedStringConfig.inputTextFieldAccessibilityTitle)
        
        // For hover need tracking area
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    func setPlaceholder(_ placeholder: String) {
        let placeholderValue = NSMutableAttributedString(string: placeholder)
        placeholderValue.addAttributes([.foregroundColor: inputConfig.placeholderTextColor, .font: inputConfig.font], range: NSRange(location: 0, length: placeholderValue.length))
        textView.placeholderLeftPadding = inputConfig.multilineFieldInsets.left
        textView.placeholderTopPadding = inputConfig.multilineFieldInsets.top
        textView.placeholderAttrString = placeholderValue
    }
    
    func setValue(value: String, maximumLen: NSNumber?) {
        var attributedValue = NSMutableAttributedString(string: value)
        let maxCharLen = Int(truncating: maximumLen ?? 0)
        if maxCharLen > 0, attributedValue.string.count > maxCharLen {
            attributedValue = NSMutableAttributedString(string: String(attributedValue.string.dropLast(attributedValue.string.count - maxCharLen)))
        }
        attributedValue.addAttributes([.foregroundColor: NSColor.textColor, .font: inputConfig.font], range: NSRange(location: 0, length: attributedValue.length))
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
        textView.backgroundColor = inputConfig.highlightedColor
    }
    
    override func mouseExited(with event: NSEvent) {
        textView.backgroundColor = inputConfig.backgroundColor
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
        layer?.borderColor = inputConfig.activeBorderColor.cgColor
    }
    
    func textViewDidResignFirstResponder() {
        scrollView.disableScroll = true
        layer?.borderColor = inputConfig.borderColor.cgColor
    }
}
