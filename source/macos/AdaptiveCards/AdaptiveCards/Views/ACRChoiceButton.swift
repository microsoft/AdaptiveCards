import AppKit

protocol ACRChoiceButtonDelegate: NSObjectProtocol {
    func acrChoiceButtonDidSelect(_ button: ACRChoiceButton)
}

class ACRChoiceButton: NSView, NSTextFieldDelegate {
    weak var delegate: ACRChoiceButtonDelegate?
    public var value: String?
    public var buttonType: NSButton.ButtonType = .switch
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
        setupConstraints()
        setupActions()
        setupTrackingArea()
    }
    
    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // Label
    private lazy var label: NSTextField = {
        let view = NSTextField()
        view.isEditable = false
        view.delegate = self
        view.isBordered = false
        view.isHighlighted = false
        view.translatesAutoresizingMaskIntoConstraints = false
        view.backgroundColor = .clear
        return view
    }()
    
    // Button
    private lazy var button: NSButton = {
        let view = NSButton()
        view.title = ""
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    // Click on Text to change state
    override func mouseDown(with event: NSEvent) {
        state = state == .on ? .off : .on
        if  state == .on {
            handleButtonAction()
        }
    }
    
    private func setupViews() {
        addSubview(button)
        addSubview(label)
    }
    
    private func setupActions() {
        // random action
        button.target = self
        button.action = #selector(handleButtonAction)
    }
    
    private func setupConstraints() {
        button.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        button.topAnchor.constraint(equalTo: topAnchor).isActive = true
        button.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        label.leadingAnchor.constraint(equalTo: button.trailingAnchor).isActive = true
        label.topAnchor.constraint(equalTo: topAnchor).isActive = true
        label.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        label.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
    }
    
    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    override func mouseEntered(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRChoiceButton else { return }
        contentView.button.isHighlighted = true
    }
    override func mouseExited(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRChoiceButton else { return }
        contentView.button.isHighlighted = false
    }
    
    @objc private func handleButtonAction() {
        delegate?.acrChoiceButtonDidSelect(self)
    }
}
// MARK: EXTENSION
extension ACRChoiceButton {
    var backgroundColor: NSColor {
        get { label.backgroundColor ?? .clear }
        set {
            label.backgroundColor = newValue
        }
    }
    
    var labelAttributedString: NSAttributedString {
        get { label.attributedStringValue }
        set {
            label.attributedStringValue = newValue
        }
    }
    
    var state: NSControl.StateValue {
        get { button.state }
        set {
            button.state = newValue
        }
    }
    
    var wrap: Bool? {
        get { ((label.cell?.wraps) ) }
        set {
            label.cell?.wraps = newValue ?? false
        }
    }
    
    var type: NSButton.ButtonType {
        get { buttonType }
        set {
            button.setButtonType(newValue)
            buttonType = newValue
        }
    }
    
    var title: String {
        get { label.stringValue }
        set {
            label.stringValue = newValue
        }
    }
}
