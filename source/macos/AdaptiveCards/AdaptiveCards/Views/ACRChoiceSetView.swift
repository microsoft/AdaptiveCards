import AdaptiveCards_bridge
import AppKit

// MARK: ACRChoiceSetView
class ACRChoiceSetView: NSView {
    private lazy var stackview: NSStackView = {
        let view = NSStackView()
        view.orientation = .vertical
        view.alignment = .leading
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    public var isRadioGroup: Bool = false
    public var previousButton: ACRChoiceButton?
    public var wrap: Bool = false
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        addSubview(stackview)
        setupConstraints()
    }
    
    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupConstraints() {
        stackview.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        stackview.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        stackview.topAnchor.constraint(equalTo: topAnchor).isActive = true
        stackview.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
    }
    
    private func handleClickAction(_ clickedButton: ACRChoiceButton) {
        guard isRadioGroup else { return }
        if previousButton?.value != clickedButton.value {
            previousButton?.state = .off
            previousButton = clickedButton
        }
    }
    
    public func addChoiceButton(_ choiceButton: ACRChoiceButton) {
        choiceButton.delegate = self
        stackview.addArrangedSubview(choiceButton)
    }
    
    public func setupButton(attributedString: NSMutableAttributedString, value: String?) -> ACRChoiceButton {
        let newButton = ACRChoiceButton()
        newButton.labelAttributedString = attributedString
        newButton.wrap = self.wrap
        newButton.value = value
        return newButton
    }
}
// MARK: Extension
extension ACRChoiceSetView: ACRChoiceButtonDelegate {
    func acrChoiceButtonDidSelect(_ button: ACRChoiceButton) {
        handleClickAction(button)
    }
}

// MARK: ACRChoiceSetFieldCompactView
class ACRChoiceSetCompactView: NSPopUpButton {
    public let type: ACSChoiceSetStyle = .compact
    private var trackingAreaDefined: Bool = false
    override func viewDidMoveToSuperview() {
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
        // Could not create in init, had to add tracking area here
        if !trackingAreaDefined {
            trackingAreaDefined = true
            let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
            addTrackingArea(trackingArea)
        }
    }
    
    override func mouseEntered(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRChoiceSetCompactView else { return }
        contentView.isHighlighted = true
    }
    override func mouseExited(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRChoiceSetCompactView else { return }
        contentView.isHighlighted = false
    }
}
