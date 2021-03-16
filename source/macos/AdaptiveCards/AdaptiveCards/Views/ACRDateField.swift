import AdaptiveCards_bridge
import AppKit

class ACRDateField: NSView {
    private lazy var dateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateFormat = isTimeMode ? "HH:mm:ss" : "yyyy/MM/dd"
        return formatter
    }()
    private lazy var dateFormatterOut: DateFormatter = {
        let formatter = DateFormatter()
        if isTimeMode {
            formatter.timeStyle = .medium
        } else {
            formatter.dateStyle = .medium
        }
        return formatter
    }()
    private let datepicker = NSDatePicker()
    var issecondadded: Bool = false
    var isTimeMode: Bool = false
    var selectedDate: Date?
    var minDateValue: String?
    var maxDateValue: String?
    var dateValue: String? {
        didSet {
            if let dateValue = dateValue, let date = dateFormatter.date(from: dateValue) {
                datepicker.dateValue = date
                textField.stringValue = dateFormatterOut.string(from: date)
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
    
    override init(frame frameRect: NSRect) {
        super.init(frame: frameRect)
        setupViews()
        setupConstraints()
        setupTrackingArea()
    }
    
    public required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    private lazy var textField: NSTextField = {
        let view = NSTextField()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.isEditable = true
        view.isSelectable = false
        view.isBordered = true
        return view
    }()
 
    private lazy var testButton: NSButton = {
        let view = NSButton(image: NSImage(named: "NSTouchBarHistoryTemplate") ?? NSImage(), target: self, action: #selector(handleButtonAction))
        view.translatesAutoresizingMaskIntoConstraints = false
        return view
    }()
    
    private func setupViews() {
        addSubview(textField)
        addSubview(testButton)
    }
    
    private func setupConstraints() {
        textField.leadingAnchor.constraint(equalTo: leadingAnchor).isActive = true
        textField.topAnchor.constraint(equalTo: topAnchor).isActive = true
        textField.bottomAnchor.constraint(equalTo: bottomAnchor).isActive = true
        textField.trailingAnchor.constraint(equalTo: testButton.leadingAnchor, constant: -10).isActive = true
        
        testButton.trailingAnchor.constraint(equalTo: trailingAnchor).isActive = true
        testButton.centerYAnchor.constraint(equalTo: centerYAnchor).isActive = true
    }
    
    private func setupTrackingArea() {
        let trackingArea = NSTrackingArea(rect: bounds, options: [.activeAlways, .inVisibleRect, .mouseEnteredAndExited], owner: self, userInfo: nil)
        addTrackingArea(trackingArea)
    }
    
    override func mouseEntered(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRDateField else { return }
        contentView.textField.backgroundColor = ColorUtils.hoverColorOnMouseEnter()
    }
    override func mouseExited(with event: NSEvent) {
        guard let contentView = event.trackingArea?.owner as? ACRDateField else { return }
        contentView.textField.backgroundColor = ColorUtils.hoverColorOnMouseExit()
    }
    
    // MARK: Actions
    @objc private func handleButtonAction() {
        let frame = isTimeMode ? NSRect(x: 0, y: 0, width: 122, height: 122) : NSRect(x: 0, y: 0, width: 138, height: 147)
        if let dateValue = selectedDate {
            datepicker.dateValue = dateValue
        }
        if let minDate = minDateValue, let date = dateFormatter.date(from: minDate) {
            datepicker.minDate = date
        }
        if let maxDate = maxDateValue, let date = dateFormatter.date(from: maxDate) {
            datepicker.maxDate = date
        }
        datepicker.datePickerStyle = .clockAndCalendar
        datepicker.datePickerElements = isTimeMode ? .hourMinuteSecond : .yearMonthDay
        datepicker.target = self
        datepicker.action = #selector(handleDateAction(_:))
        let popover = NSViewController()
        popover.view = datepicker
        popover.view.frame = frame
        _ = NSPopover(contentViewController: popover, sender: testButton, bounds: frame, preferredEdge: .maxY, behavior: .transient, animates: true, delegate: nil)
    }
    
    @objc private func handleDateAction(_ datePicker: NSDatePicker) {
        textField.stringValue = dateFormatterOut.string(from: datePicker.dateValue)
        selectedDate = datePicker.dateValue
    }
    override func viewDidMoveToSuperview() {
        super.viewDidMoveToSuperview()
        // Should look for better solution
        guard let superview = superview else { return }
        widthAnchor.constraint(equalTo: superview.widthAnchor).isActive = true
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
