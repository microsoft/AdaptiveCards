import AdaptiveCards_bridge
import AppKit

class ACRDateField: NSView, InputHandlingViewProtocol {
    private lazy var dateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = isTimeMode ? "HH:mm" : "yyyy-MM-dd"
        return formatter
    }()
    
    private lazy var dateFormatterOut: DateFormatter = {
        let formatter = DateFormatter()
        if isTimeMode {
            formatter.timeStyle = .short
        } else {
            formatter.dateStyle = .medium
        }
        return formatter
    }()
    
    private (set) lazy var textField: ACRTextField = {
        let view = ACRTextField(dateTimeFieldWith: config)
        view.translatesAutoresizingMaskIntoConstraints = false
        view.isEditable = true
        view.isSelectable = false
        view.cell?.lineBreakMode = .byTruncatingTail
        view.stringValue = ""
        view.textFieldDelegate = self
       return view
    }()

    private (set) lazy var iconButton: NSButtonWithImageSpacing = {
        let calendarResourceName = isDarkMode ? "calendar-month-dark" : "calendar-month-light"
        let clockResourceName = isDarkMode ? "recents_20_w" : "recents_20"
        let calendarImage = BundleUtils.getImage(calendarResourceName, ofType: "png")
        let clockImage = BundleUtils.getImage(clockResourceName, ofType: "png")
        let inputFieldConfig = config.inputFieldConfig
        let view = NSButtonWithImageSpacing(image: (isTimeMode ? inputFieldConfig.clockImage ?? clockImage : inputFieldConfig.calendarImage ?? calendarImage) ?? NSImage(), target: self, action: #selector(handleOpenPickerAction))
        view.translatesAutoresizingMaskIntoConstraints = false
        view.wantsLayer = true
        view.layer?.backgroundColor = NSColor.clear.cgColor
        view.isBordered = false
        view.setAccessibilityTitle(isTimeMode ? config.localisedStringConfig.timePickerButtonAccessibilityTitle: config.localisedStringConfig.datePickerButtonAccessibilityTitle)
        return view
    }()
    
    private lazy var stackview: NSStackView = {
       let view = NSStackView()
       view.orientation = .vertical
       view.alignment = .centerX
       view.translatesAutoresizingMaskIntoConstraints = false
       return view
    }()
    
    private var popover: NSPopover?
       
    let datePickerCalendar = NSDatePicker()
    let datePickerTextfield = NSDatePicker()
    let isTimeMode: Bool
    let isDarkMode: Bool
    let config: RenderConfig

    var selectedDate: Date? {
        didSet {
            if let selectedDate = selectedDate {
                textField.stringValue = dateFormatterOut.string(from: selectedDate)
                datePickerCalendar.dateValue = selectedDate
                datePickerTextfield.dateValue = selectedDate
            }
        }
    }
    var initialDateValue: String? {
        didSet {
            if let initialDateValue = initialDateValue {
                selectedDate = dateFormatter.date(from: initialDateValue)
            }
        }
    }
    var minDateValue: String?
    var maxDateValue: String?
    var idString: String?
    var dateValue: String? {
        get {
            if let selectedDate = selectedDate {
                return dateFormatter.string(from: selectedDate)
            } else {
                return nil
            }
        }
    }
    var placeholder: String? {
        didSet {
            if let placeholder = placeholder {
                textField.placeholderString = placeholder
            }
        }
    }
    
    var value: String {
        guard !textField.stringValue.isEmpty, let selectedDate = selectedDate else {
            return ""
        }
        return dateFormatter.string(from: selectedDate)
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
    
    init(isTimeMode: Bool, config: RenderConfig) {
        self.isTimeMode = isTimeMode
        self.isDarkMode = config.isDarkMode
        self.config = config
        super.init(frame: .zero)
        setupViews()
        setupConstraints()
        setupPopover()
        setupAccessibility()
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private func setupViews() {
        addSubview(textField)
        addSubview(iconButton)
    }
    
    private func setupConstraints() {
        textField.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        textField.topAnchor.constraint(equalTo: topAnchor).isActive = true
        textField.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        textField.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        iconButton.leadingAnchor.constraint(equalTo: textField.leadingAnchor, constant: config.inputFieldConfig.leftPadding).isActive = true
        iconButton.centerYAnchor.constraint(equalTo: centerYAnchor).isActive = true
    }
    
    private func setupPopover() {
        datePickerCalendar.dateValue = Date()
        datePickerTextfield.dateValue = Date()
    }
    
    private func setupAccessibility() {
        setAccessibilityElement(true)
        setAccessibilityRoleDescription(isTimeMode  ? config.localisedStringConfig.timePickerFieldAccessibilityRoleDescription : config.localisedStringConfig.datePickerFieldAccessibilityRoleDescription)
    }

    override func accessibilityChildren() -> [Any]? {
        var temp = textField.accessibilityChildren()
        temp?.append(iconButton)
        return temp
    }
    
    override func mouseDown(with event: NSEvent) {
        handleOpenPickerAction()
        super.mouseDown(with: event)
    }
    
    @objc private func handleOpenPickerAction() {
        let frame = isTimeMode ? NSRect(x: 0, y: 0, width: 122, height: 122) : NSRect(x: 0, y: 0, width: 138, height: 147)
        if let dateValue = selectedDate {
            datePickerCalendar.dateValue = dateValue
            datePickerTextfield.dateValue = dateValue
        }
        if let minDate = minDateValue, let date = dateFormatter.date(from: minDate) {
            datePickerCalendar.minDate = date
            datePickerTextfield.minDate = date
        }
        if let maxDate = maxDateValue, let date = dateFormatter.date(from: maxDate) {
            datePickerCalendar.maxDate = date
            datePickerTextfield.maxDate = date
        }
        datePickerCalendar.datePickerStyle = .clockAndCalendar
        datePickerCalendar.datePickerElements = isTimeMode ? .hourMinute : .yearMonthDay
        datePickerCalendar.target = self
        datePickerCalendar.action = #selector(handleDateAction(_:))

        datePickerTextfield.datePickerStyle = .textFieldAndStepper
        datePickerTextfield.datePickerElements = isTimeMode ? .hourMinute : .yearMonthDay
        datePickerTextfield.target = self
        datePickerTextfield.action = #selector(handleDateAction(_:))
        if popover == nil {
            stackview.addArrangedSubview(datePickerTextfield)
            stackview.addArrangedSubview(datePickerCalendar)
            if isTimeMode {
                stackview.spacing = 3
                stackview.edgeInsets.bottom = 3
            }
            let popoverView = NSViewController()
            popoverView.view = stackview
            popoverView.view.frame = frame
            popover = NSPopover(contentViewController: popoverView, sender: iconButton, bounds: frame, preferredEdge: .maxY, behavior: .transient, animates: true, delegate: nil)
            popover?.setAccessibilityParent(self)
        } else {
            popover?.show(relativeTo: iconButton.bounds, of: iconButton, preferredEdge: .maxY)
        }
    }
    
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
    }
    
    @objc private func handleDateAction(_ datePicker: NSDatePicker) {
        selectedDate = datePicker.dateValue
    }
    
    override func accessibilityLabel() -> String? {
        if !textField.stringValue.isEmpty {
            return textField.stringValue
        } else if let placeholder = placeholder {
            return placeholder
        }
        return nil
    }
}

extension NSPopover {
    convenience init(contentViewController: NSViewController,
                     sender: NSView,
                     bounds: NSRect,
                     preferredEdge: NSRectEdge = NSRectEdge.maxY,
                     behavior: NSPopover.Behavior? = .transient,
                     animates: Bool = true,
                     delegate: NSPopoverDelegate? = nil,
                     shouldShow: Bool = true) {
        self.init()

        if sender.window != nil {
            self.behavior = .transient
            self.contentViewController = contentViewController
            self.animates = animates
            self.delegate = delegate
            if shouldShow {
                self.show(relativeTo: bounds, of: sender, preferredEdge: preferredEdge)
            }
        } else { assert(false) }
    }
}

@IBDesignable class NSButtonWithImageSpacing: NSButton {
    @IBInspectable var verticalImagePadding: CGFloat = 1
    @IBInspectable var horizontalImagePadding: CGFloat = 1
    
    override func draw(_ drawRect: NSRect) {
        // Reset the bounds after drawing is complete
        let originalBounds = self.bounds
        defer { self.bounds = originalBounds }

        // Inset bounds by the image padding
        self.bounds = originalBounds.insetBy(
            dx: horizontalImagePadding,
            dy: verticalImagePadding
        )

        // Draw the button content with padding
        super.draw(drawRect)
    }
}

extension ACRDateField: ACRTextFieldDelegate {
    func acrTextFieldDidSelectClear(_ textField: ACRTextField) {
        selectedDate = nil
    }
}
