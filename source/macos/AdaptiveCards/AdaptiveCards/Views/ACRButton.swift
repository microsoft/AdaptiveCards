import AdaptiveCards_bridge
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
    
    init(frame: NSRect = .zero, wantsChevron: Bool = false, wantsIcon: Bool = false, iconPosition: NSControl.ImagePosition = .imageLeft, style: ActionStyle = .default, buttonConfig: ButtonConfig = .default) {
        super.init(frame: frame)
        showsChevron = wantsChevron
        showsIcon = wantsIcon
        imagePosition = wantsIcon ? iconPosition : .noImage
        initialize()
        buttonActionStyle = style
        setupButtonStyle(style: style, buttonConfig: buttonConfig)
    }
    
    private func initialize() {
        borderWidth = 1
        onAnimationDuration = 0.0
        offAnimationDuration = 0.0
        momentary = !showsChevron
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

extension ACRButton {
    convenience init(actionElement: ACSBaseActionElement, iconPlacement: ACSIconPlacement?, buttonConfig: ButtonConfig, style: ActionStyle? = nil) {
        let buttonStyle = style ?? ActionStyle(rawValue: actionElement.getStyle() ?? "") ?? .default
        let position = iconPlacement?.imagePosition ?? .imageLeft
        self.init(wantsChevron: actionElement is ACSShowCardAction, wantsIcon: actionElement.hasValidIcon, iconPosition: position, style: buttonStyle, buttonConfig: buttonConfig)
        title = actionElement.getTitle() ?? ""
    }
}
