import AppKit

enum ActionStyle: String {
    case positive
    case `default`
    case destructive
    case none
    case inline
}

class ACRButton: FlatButton {
    struct Constants {
        static let blueColorCode = "#007EA8"
        static let darkBlueColorCode = "#0A5E7D"
        
        static let greenColorCode = "#1B8728"
        static let darkGreenColorCode = "#196323"
        
        static let redColorCode = "#D93829"
        static let darkRedColorCode = "#A12C23"
        
        static let grayColorCode = "#E6E8E8"
        static let darkGrayColorCode = "#B4B6B8"
    }
    
    public var backgroundColor: NSColor = .init(red: 0.35216, green: 0.823529412, blue: 1, alpha: 1)
    public var hoverBackgroundColor: NSColor = .linkColor
    public var activeBackgroundColor: NSColor = .linkColor
    
    private var inActiveTextColor: NSColor = .linkColor
    private var inActiveborderColor: NSColor = .linkColor
    private var hoverButtonColor: NSColor = .linkColor
    private var buttonStyle: ActionStyle = .default
    
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
        setupButtonStyle()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
        setupButtonStyle()
    }
    
    init(frame: NSRect = .zero, wantsChevron: Bool = false, wantsIcon: Bool = false, iconNamed: String = "", iconImageFileType: String = "", iconPosition: NSControl.ImagePosition = .imageLeft, style: ActionStyle = .default) {
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
        buttonStyle = style
        setupButtonStyle(style: style)
    }
    
    private func initialize() {
        borderWidth = 1
        onAnimationDuration = 0.0
        offAnimationDuration = 0.0
        iconColor = NSColor.white
        activeIconColor = NSColor.white
        momentary = !showsChevron
        iconColor = .white
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
        if buttonStyle != .inline {
            cornerRadius = bounds.height / 2
        }
    }

    override open func mouseEntered(with event: NSEvent) {
        buttonColor = hoverButtonColor
        borderColor = activeBorderColor
        textColor = activeTextColor
        super.mouseEntered(with: event)
    }
    
    override open func mouseExited(with event: NSEvent) {
        super.mouseExited(with: event)
        buttonColor = backgroundColor
        borderColor = inActiveborderColor
        textColor = inActiveTextColor
    }
    
    override func mouseDown(with event: NSEvent) {
        super.mouseDown(with: event)
        buttonColor = activeButtonColor
        borderColor = activeBorderColor
        textColor = activeTextColor
    }
    
    private func setupButtonStyle(style: ActionStyle = .default) {
        // Common styling b/w all Action Style
        backgroundColor = .white
        buttonColor = .white
        activeTextColor = .white
        
        switch style {
        case .default:
            // borderColor
            borderColor = ColorUtils.color(from: Constants.blueColorCode) ?? .clear
            inActiveborderColor = borderColor
            activeBorderColor = ColorUtils.color(from: Constants.darkBlueColorCode) ?? .clear
            
            // button color
            activeButtonColor = activeBorderColor
            hoverButtonColor = borderColor
            
            // textColor
            textColor = activeBorderColor
            inActiveTextColor = textColor
            
        case .positive:
            // borderColor
            borderColor = ColorUtils.color(from: Constants.greenColorCode) ?? .clear
            inActiveborderColor = borderColor
            activeBorderColor = ColorUtils.color(from: Constants.darkGreenColorCode) ?? .clear
            
            // button color
            activeButtonColor = activeBorderColor
            hoverButtonColor = borderColor
            
            // textColor
            textColor = activeBorderColor
            inActiveTextColor = textColor
            
        case .destructive:
            // borderColor
            borderColor = ColorUtils.color(from: Constants.redColorCode) ?? .clear
            inActiveborderColor = borderColor
            activeBorderColor = ColorUtils.color(from: Constants.darkRedColorCode) ?? .clear
            
            // button color
            activeButtonColor = activeBorderColor
            hoverButtonColor = borderColor
            
            // textColor
            textColor = activeBorderColor
            inActiveTextColor = textColor
            
        case .inline:
            borderColor = .clear
            inActiveborderColor = .clear
            activeBorderColor = .clear
            backgroundColor = .clear
            // button color
            buttonColor = backgroundColor
            activeButtonColor = ColorUtils.color(from: Constants.darkGrayColorCode) ?? .clear
            hoverButtonColor = ColorUtils.color(from: Constants.grayColorCode) ?? .clear
            
            // textColor
            textColor = .black
            activeTextColor = .black
            inActiveTextColor = textColor
            contentInsets.left = 5
            contentInsets.right = 5
            
        case .none:
            backgroundColor = .init(red: 0.35216, green: 0.823529412, blue: 1, alpha: 1)
            // borderColor
            borderColor = backgroundColor
            inActiveborderColor = backgroundColor
            activeBorderColor = activeBackgroundColor
            
            // button color
            buttonColor = backgroundColor
            activeButtonColor = activeBackgroundColor
            hoverButtonColor = activeBackgroundColor
            
            // textColor
            textColor = .white
            inActiveTextColor = textColor
        }
    }
}
