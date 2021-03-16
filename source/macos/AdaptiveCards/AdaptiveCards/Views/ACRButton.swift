import AppKit

class ACRButton: FlatButton {
    public var backgroundColor: NSColor = .init(red: 0.35216, green: 0.823529412, blue: 1, alpha: 1)
    public var hoverBackgroundColor: NSColor = .linkColor
    public var activeBackgroundColor: NSColor = .gray
    
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
    }
    
    init(frame: NSRect, wantsChevron: Bool = false, wantsIcon: Bool = false, iconNamed: String = "", iconPosition: NSControl.ImagePosition = .imageLeft) {
        super.init(frame: frame)
        initialize()
        if wantsChevron {
            showsChevron = wantsChevron
        }
        if wantsIcon {
            showsIcon = wantsIcon
            iconImageName = iconNamed
            iconPositioned = iconPosition
        }
    }
    
    private func initialize() {
        borderWidth = 0
        borderColor = backgroundColor
        buttonColor = backgroundColor
        activeBorderColor = activeBackgroundColor
        activeButtonColor = activeBackgroundColor
        textColor = NSColor.white
        activeTextColor = NSColor.white
        onAnimationDuration = 0.0
        offAnimationDuration = 0.0
        iconColor = NSColor.white
        activeIconColor = NSColor.white
        momentary = false
        if showsIcon {
            guard let bundle = Bundle(identifier: "com.test.test.AdaptiveCards"),
                  let path = bundle.path(forResource: iconImageName, ofType: "png") else {
                logError("Image Not Found")
                return
            }
            image = NSImage(byReferencing: URL(fileURLWithPath: path))
            imagePosition = iconPositioned
        }
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        initialize()
    }
    
    override open func layout() {
        super.layout()
        cornerRadius = bounds.height / 2
    }

    override open func mouseEntered(with event: NSEvent) {
        buttonColor = hoverBackgroundColor
        borderColor = hoverBackgroundColor
        if mouseDown {
            setOn(state != .on)
        }
    }
    
    override open func mouseExited(with event: NSEvent) {
        buttonColor = backgroundColor
        borderColor = backgroundColor
        if mouseDown {
            setOn(state != .on)
            mouseDown = false
        }
    }
}
