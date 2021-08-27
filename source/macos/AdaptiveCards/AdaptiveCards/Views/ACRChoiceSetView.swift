import AdaptiveCards_bridge
import AppKit

// MARK: ACRChoiceSetView
class ACRChoiceSetView: NSView, InputHandlingViewProtocol {
    private lazy var stackview: NSStackView = {
        let view = NSStackView()
        view.orientation = .vertical
        view.alignment = .leading
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    public var isRadioGroup = false
    public var previousButton: ACRChoiceButton?
    public var wrap = false
    public var idString: String?
    
    private let renderConfig: RenderConfig
    
    init(renderConfig: RenderConfig) {
        self.renderConfig = renderConfig
        super.init(frame: .zero)
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
        if previousButton?.buttonValue != clickedButton.buttonValue {
            previousButton?.state = .off
            previousButton = clickedButton
        }
    }
    
    public func addChoiceButton(_ choiceButton: ACRChoiceButton) {
        choiceButton.delegate = self
        stackview.addArrangedSubview(choiceButton)
    }
    
    public func setupButton(attributedString: NSMutableAttributedString, value: String?) -> ACRChoiceButton {
        let newButton = ACRChoiceButton(renderConfig: renderConfig, buttonType: isRadioGroup ? .radio : .switch)
        newButton.labelAttributedString = attributedString
        newButton.wrap = self.wrap
        newButton.buttonValue = value
        return newButton
    }
    
    var value: String {
        var stringOfSelectedValues: [String] = []
        let arrayViews = stackview.arrangedSubviews
        for view in arrayViews {
            if let view = view as? ACRChoiceButton, view.state == .on {
                stringOfSelectedValues.append(view.buttonValue ?? "")
            }
        }
        return stringOfSelectedValues.joined(separator: ",")
    }
    
    var key: String {
        guard let id = idString else {
            logError("ID must be set on creation")
            return ""
        }
        return id
    }
    
    var isValid: Bool {
        return true
    }
}
// MARK: Extension
extension ACRChoiceSetView: ACRChoiceButtonDelegate {
    func acrChoiceButtonDidSelect(_ button: ACRChoiceButton) {
        handleClickAction(button)
    }
}

// MARK: ACRChoiceSetFieldCompactView
class ACRChoiceSetCompactView: NSPopUpButton, InputHandlingViewProtocol {
    public let type: ACSChoiceSetStyle = .compact
    private var trackingAreaDefined = false
    public var idString: String?
    public var valueSelected: String?
    public var arrayValues: [String] = []
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
    
    var value: String {
        return arrayValues[indexOfSelectedItem]
    }
    
    var key: String {
        guard let id = idString else {
            logError("ID must be set on creation")
            return ""
        }
        return id
    }
    
    var isValid: Bool {
        return true
    }
}
