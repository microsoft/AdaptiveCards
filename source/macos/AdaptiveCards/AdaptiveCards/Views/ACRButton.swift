import AppKit

class ACRButton: FlatButton {
    public var backgroundColor: NSColor = .init(red: 0.35216, green: 0.823529412, blue: 1, alpha: 1)
    public var hoverBackgroundColor: NSColor = .linkColor
    public var activeBackgroundColor: NSColor = .gray
    public var chevron: Bool = true {
        didSet {
        }
    }
    
    override init(frame: NSRect) {
        super.init(frame: frame)
        initialize()
    }
    
    required init?(coder: NSCoder) {
        super.init(coder: coder)
        initialize()
    }
    
    private func initialize() {
        cornerRadius = 15
        borderWidth = 0
        borderColor = backgroundColor
        buttonColor = backgroundColor
        activeBorderColor = activeBackgroundColor
        activeButtonColor = activeBackgroundColor
        textColor = NSColor.white
        activeTextColor = NSColor.white
        onAnimationDuration = 0.0
        offAnimationDuration = 0.0
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
