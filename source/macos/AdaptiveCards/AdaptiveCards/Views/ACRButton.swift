import AppKit

enum ActionStyle: String {
    case positive
    case `default`
    case destructive
    case inline
}

class ACRButton: FlatButton, ImageHoldingView {
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
        
        borderColor = colorConfig.borderColor
        selectedBorderColor = colorConfig.selectedBorderColor
        
        buttonColor = colorConfig.buttonColor
        hoverButtonColor = colorConfig.hoverButtonColor
        selectedButtonColor = colorConfig.selectedButtonColor
        
        textColor = colorConfig.textColor
        selectedTextColor = colorConfig.selectedTextColor
    }
}
