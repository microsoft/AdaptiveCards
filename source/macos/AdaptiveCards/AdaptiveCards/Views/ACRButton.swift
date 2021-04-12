import AppKit

enum ActionStyle: String {
    case positive
    case `default`
    case destructive
    case inline
}

class ACRButton: FlatButton, ImageHoldingView {
    public var backgroundColor: NSColor = .clear
    
    private var disabledTextColor: NSColor = .linkColor
    private var disabledBorderColor: NSColor = .linkColor
    private var hoverButtonColor: NSColor = .linkColor
    private var buttonActionStyle: ActionStyle = .default
        
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
        setupButtonStyle(style: .default, buttonConfig: .default)
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
        setupButtonStyle(style: .default, buttonConfig: .default)
    }
    
    init(frame: NSRect = .zero, wantsChevron: Bool = false, wantsIcon: Bool = false, iconNamed: String = "", iconImageFileType: String = "", iconPosition: NSControl.ImagePosition = .imageLeft, style: ActionStyle = .default, buttonConfig: ButtonConfig = .default) {
        super.init(frame: frame)
        if wantsChevron {
            showsChevron = wantsChevron
        }
        if wantsIcon {
            showsIcon = wantsIcon
            iconImageName = iconNamed
            iconFileType = iconImageFileType
            iconPositioned = iconPosition
        }
        initialize()
        buttonActionStyle = style
        setupButtonStyle(style: style, buttonConfig: buttonConfig)
    }
    
    private func initialize() {
        borderWidth = 1
        onAnimationDuration = 0.0
        offAnimationDuration = 0.0
        momentary = !showsChevron
        if showsIcon {
            image = BundleUtils.getImage(iconImageName, ofType: iconFileType)
            imagePosition = iconPositioned
        }
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        initialize()
    }
    
    override open func layout() {
        super.layout()
        if buttonActionStyle != .inline {
            cornerRadius = bounds.height / 2
        }
    }
    
    func setImage(_ image: NSImage) {
        iconColor = NSColor(patternImage: image)
        selectedIconColor = iconColor
        self.image = image
        mouseExited(with: NSEvent()) // this is to force trigger the event for image updation
    }

    override open func mouseEntered(with event: NSEvent) {
        buttonColor = hoverButtonColor
        borderColor = selectedBorderColor
        textColor = selectedTextColor
        super.mouseEntered(with: event)
    }
    
    override open func mouseExited(with event: NSEvent) {
        super.mouseExited(with: event)
        buttonColor = backgroundColor
        borderColor = disabledBorderColor
        textColor = disabledTextColor
    }
    
    override func mouseDown(with event: NSEvent) {
        super.mouseDown(with: event)
        buttonColor = selectedButtonColor
        borderColor = selectedBorderColor
        textColor = selectedTextColor
    }
    
    private func setupButtonStyle(style: ActionStyle, buttonConfig: ButtonConfig) {
        // Common styling b/w all Action Style
        let colorConfig: ButtonColorConfig
        switch buttonActionStyle {
        case .default:
            colorConfig = buttonConfig.default
        case .positive:
            colorConfig = buttonConfig.positive
        case .destructive:
            colorConfig = buttonConfig.destructive
        case .inline:
            colorConfig = buttonConfig.inline
            contentInsets.left = 5
            contentInsets.right = 5
        }
        
        backgroundColor = colorConfig.buttonColor
        borderColor = colorConfig.borderColor
        selectedBorderColor = colorConfig.selectedBorderColor
        disabledBorderColor = borderColor
        
        buttonColor = colorConfig.buttonColor
        hoverButtonColor = colorConfig.hoverButtonColor
        selectedButtonColor = colorConfig.selectedButtonColor
        
        textColor = colorConfig.textColor
        selectedTextColor = colorConfig.selectedTextColor
        disabledTextColor = textColor
    }
}
