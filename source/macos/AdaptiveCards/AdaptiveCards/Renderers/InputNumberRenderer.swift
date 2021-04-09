import AdaptiveCards_bridge
import AppKit

open class InputNumberRenderer: NSObject, BaseCardElementRendererProtocol {
    static let shared = InputNumberRenderer()
    
    func render(element: ACSBaseCardElement, with hostConfig: ACSHostConfig, style: ACSContainerStyle, rootView: ACRView, parentView: NSView, inputs: [BaseInputHandler], config: RenderConfig) -> NSView {
        guard let inputElement = element as? ACSNumberInput else {
            logError("Element is not of type ACSNumberInput")
            return NSView()
        }
        
        // setting up basic properties for Input.Number TextField
        let inputField: ACRNumericTextField = {
            let view = ACRNumericTextField()
            view.placeholder = inputElement.getPlaceholder() ?? ""
            view.maxValue = inputElement.getMax()?.doubleValue ?? ACRNumericTextField.MAXVAL
            view.minValue = inputElement.getMin()?.doubleValue ?? ACRNumericTextField.MINVAL
            view.inputString = inputElement.getValue()?.stringValue ?? ""
            return view
        }()

        inputField.setNumericFormatter(InputNumberFormatter())
        inputField.stepperShouldWrapValues(false)
        inputField.isHidden = !inputElement.getIsVisible()
        inputField.id = inputElement.getId()
        rootView.addInputHandler(inputField)
        
        return inputField
    }
}

// MARK: - ACRNumericTextField Class
open class ACRNumericTextField: NSView, NSTextFieldDelegate {
    var id: String?
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
        setupConstraints()
        setUpControls()
        setUpTheme()
        setupTrackingArea()
    }
    
    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private lazy var textField: NSTextField = {
        let view = NSTextField()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.delegate = self
        view.isEditable = true
        return view
    }()

    private lazy var stepper: NSStepper = {
        let view = NSStepper()
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()

    @objc private func handleStepperAction(_ sender: NSStepper) {
        textField.stringValue = "\(sender.integerValue)"
    }
    
    public func controlTextDidChange(_ obj: Notification) {
        guard let textView = obj.object as? NSTextField else { return }
        // updating the stepper value when text field value change
        stepper.doubleValue = Double(textView.stringValue) ?? stepper.doubleValue
    }
    
    func setupViews() {
        addSubview(textField)
        addSubview(stepper)
    }
    
    func setupConstraints() {
        textField.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        textField.topAnchor.constraint(equalTo: topAnchor).isActive = true
        textField.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        stepper.leadingAnchor.constraint(equalTo: textField.trailingAnchor).isActive = true
        stepper.topAnchor.constraint(equalTo: topAnchor).isActive = true
        stepper.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        stepper.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
    }
    
    func setUpControls() {
        stepper.target = self
        stepper.action = #selector(handleStepperAction(_:))
    }
    
    func setUpTheme() {
        textField.wantsLayer = true
        textField.layer?.backgroundColor = .clear
        stepper.wantsLayer = true
        stepper.layer?.backgroundColor = .clear
    }
    
    func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    override open func mouseEntered(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRNumericTextField else { return }
        contentView.textField.backgroundColor = ColorUtils.hoverColorOnMouseEnter()
    }
    
    override open func mouseExited(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRNumericTextField else { return }
        contentView.textField.backgroundColor = ColorUtils.hoverColorOnMouseExit()
    }
}

// MARK: - EXTENSION
extension ACRNumericTextField: InputHandlingViewProtocol {
    static let MAXVAL = Double.greatestFiniteMagnitude
    static let MINVAL = -MAXVAL
    
    var inputValue: Double {
        get { return textField.doubleValue }
        set { textField.doubleValue = newValue
            stepper.doubleValue = newValue }
    }
    
    var inputString: String {
        get { return String(inputValue) }
        set {
            if !newValue.isEmpty, let doubleVal = Double(newValue) {
                inputValue = doubleVal
            }
        }
    }
    
    var minValue: Double {
        get { return stepper.minValue }
        set { stepper.minValue = newValue }
    }
    
    var maxValue: Double {
        get { return stepper.maxValue }
        set { stepper.maxValue = newValue }
    }
    
    var attributedPlaceholder: NSAttributedString {
        get { return textField.placeholderAttributedString ?? NSAttributedString(string: "") }
        set { textField.placeholderAttributedString = newValue }
    }
    
    var placeholder: String {
        get { return textField.placeholderString ?? "" }
        set { textField.placeholderString = newValue }
    }
    
    func setNumericFormatter(_ formatter: NumberFormatter) {
        textField.formatter = formatter
    }
    
    func stepperShouldWrapValues(_ shouldWrap: Bool) {
        stepper.valueWraps = shouldWrap
    }
    
    func setId(idString: String?) {
        self.id = idString
    }
    
    var value: String {
        return String(Int(inputValue))
    }
    
    var key: String {
        guard let id = id else {
            logError("ID must be set on creation")
            return ""
        }
        return id
    }
    
    var isValid: Bool {
        return !isHidden && !(superview?.isHidden ?? false)
    }
}

// MARK: - Numeric Formatter
open class InputNumberFormatter: NumberFormatter {
    override init() {
        super.init()
        hasThousandSeparators = false
        numberStyle = Style.decimal
    }
    
    public required init?(coder: NSCoder) {
        super.init(coder: coder)
    }
}
