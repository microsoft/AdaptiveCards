import AdaptiveCards_bridge
import AppKit

public protocol AdaptiveCardActionDelegate: AnyObject {
    func adaptiveCard(_ adaptiveCard: NSView, didSelectOpenURL urlString: String, actionView: NSView)
    func adaptiveCard(_ adaptiveCard: NSView, didSubmitUserResponses dict: [String: Any], actionView: NSView)
    func adaptiveCard(_ adaptiveCard: NSView, didShowCardWith actionView: NSView, previousHeight: CGFloat, newHeight: CGFloat)
    func adaptiveCard(_ adaptiveCard: NSView, didUpdateBoundsFrom oldValue: NSRect, to newValue: NSRect)
}

public protocol AdaptiveCardResourceResolver: AnyObject {
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize?
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, requestImageFor url: String)
    func adaptiveCard(_ adaptiveCard: NSView, attributedStringFor htmlString: String) -> NSAttributedString?
}

enum HostConfigParseError: Error {
    case resultIsNil, configIsNil
}

open class AdaptiveCard {
    public static func from(jsonString: String) -> ACSParseResult {
        return BridgeConverter.parseAdaptiveCard(fromJSON: jsonString)
    }
    
    public static func parseHostConfig(from jsonString: String) -> Result<ACSHostConfig, Error> {
        guard let result = BridgeConverter.parseHostConfig(fromJSON: jsonString) else {
            return .failure(HostConfigParseError.resultIsNil)
        }
        guard result.isValid, let hostConfig = result.config else {
            return .failure(result.error ?? HostConfigParseError.configIsNil)
        }
        return .success(hostConfig)
    }
    
    public static func render(card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, width: CGFloat, actionDelegate: AdaptiveCardActionDelegate?, resourceResolver: AdaptiveCardResourceResolver?, config: RenderConfig = .default) -> NSView {
        return AdaptiveCardRenderer.shared.renderAdaptiveCard(card, with: hostConfig, width: width, config: config, actionDelegate: actionDelegate, resourceResolver: resourceResolver)
    }
}

public struct RenderConfig {
    public static let `default` = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: .default, checkBoxButtonConfig: nil, radioButtonConfig: nil)
    let isDarkMode: Bool
    let buttonConfig: ButtonConfig
    // swiftlint:disable identifier_name
    let supportsSchemeV1_3: Bool
    let hyperlinkColorConfig: HyperlinkColorConfig
    let checkBoxButtonConfig: ChoiceSetButtonConfig?
    let radioButtonConfig: ChoiceSetButtonConfig?
    let inputFieldConfig: InputFieldConfig
    
    public init(isDarkMode: Bool, buttonConfig: ButtonConfig, supportsSchemeV1_3: Bool, hyperlinkColorConfig: HyperlinkColorConfig, inputFieldConfig: InputFieldConfig, checkBoxButtonConfig: ChoiceSetButtonConfig?, radioButtonConfig: ChoiceSetButtonConfig?) {
        self.isDarkMode = isDarkMode
        self.buttonConfig = buttonConfig
		self.supportsSchemeV1_3 = supportsSchemeV1_3
        self.hyperlinkColorConfig = hyperlinkColorConfig
        self.checkBoxButtonConfig = checkBoxButtonConfig
        self.radioButtonConfig = radioButtonConfig
        self.inputFieldConfig = inputFieldConfig
    }
}

public struct ButtonColorConfig {
    // buttonColor
    let buttonColor: NSColor
    let selectedButtonColor: NSColor
    let hoverButtonColor: NSColor
    
    // textColor
    let textColor: NSColor
    let selectedTextColor: NSColor
    
    // borderColor
    let borderColor: NSColor
    let selectedBorderColor: NSColor
        
    public init(buttonColor: NSColor, selectedButtonColor: NSColor, hoverButtonColor: NSColor, textColor: NSColor, selectedTextColor: NSColor, borderColor: NSColor, selectedBorderColor: NSColor) {
        self.buttonColor = buttonColor
        self.selectedButtonColor = selectedButtonColor
        self.hoverButtonColor = hoverButtonColor
        self.textColor = textColor
        self.selectedTextColor = selectedTextColor
        self.borderColor = borderColor
        self.selectedBorderColor = selectedBorderColor
    }
}

public struct ButtonConfig {
    public static let `default` = ButtonConfig(positive: .init(buttonColor: .green, selectedButtonColor: .systemGreen, hoverButtonColor: .systemGreen, textColor: .white, selectedTextColor: .white, borderColor: .green, selectedBorderColor: .systemGreen), destructive: .init(buttonColor: .systemRed, selectedButtonColor: .red, hoverButtonColor: .red, textColor: .white, selectedTextColor: .white, borderColor: .systemRed, selectedBorderColor: .red), default: .init(buttonColor: .systemBlue, selectedButtonColor: .blue, hoverButtonColor: .blue, textColor: .white, selectedTextColor: .white, borderColor: .systemBlue, selectedBorderColor: .blue), inline: .init(buttonColor: .clear, selectedButtonColor: .gray, hoverButtonColor: .darkGray, textColor: .black, selectedTextColor: .black, borderColor: .clear, selectedBorderColor: .clear))
    
    let positive: ButtonColorConfig
    let destructive: ButtonColorConfig
    let `default`: ButtonColorConfig
    let inline: ButtonColorConfig
    
    public init(positive: ButtonColorConfig, destructive: ButtonColorConfig, default: ButtonColorConfig, inline: ButtonColorConfig) {
        self.positive = positive
        self.destructive = destructive
        self.default = `default`
        self.inline = inline
    }
}

public struct HyperlinkColorConfig {
    public static let `default` = HyperlinkColorConfig(foregroundColor: .systemBlue, isUnderlined: false, underlineColor: .blue, underlineStyle: .single)
    
    let foregroundColor: NSColor
    let isUnderlined: Bool
    let underlineColor: NSColor
    let underlineStyle: NSUnderlineStyle
    
    public init(foregroundColor: NSColor, isUnderlined: Bool, underlineColor: NSColor, underlineStyle: NSUnderlineStyle) {
        self.foregroundColor = foregroundColor
        self.isUnderlined = isUnderlined
        self.underlineColor = isUnderlined ? underlineColor : .clear
        self.underlineStyle = underlineStyle
    }
}

public struct ChoiceSetButtonConfig {
    let selectedIcon: NSImage
    let normalIcon: NSImage
    let selectedHighlightedIcon: NSImage
    let highlightedIcon: NSImage
    let elementSpacing: CGFloat
    
    public init(selectedIcon: NSImage, normalIcon: NSImage, selectedHighlightedIcon: NSImage, highlightedIcon: NSImage, elementSpacing: CGFloat) {
        self.selectedIcon = selectedIcon
        self.normalIcon = normalIcon
        self.selectedHighlightedIcon = selectedHighlightedIcon
        self.highlightedIcon = highlightedIcon
        self.elementSpacing = elementSpacing
    }
}
public struct InputFieldConfig {
    public static let `default` = InputFieldConfig(height: 20, leftPadding: 0, rightPadding: 0, yPadding: 0, focusRingCornerRadius: 0, borderWidth: 0.3, wantsClearButton: false, clearButtonImage: nil, calendarImage: nil, clockImage: nil, font: .systemFont(ofSize: 12), highlightedColor: .lightGray, backgroundColor: .white, borderColor: .darkGray)
    
    let height: CGFloat
    let leftPadding: CGFloat
    let rightPadding: CGFloat
    let yPadding: CGFloat
    let focusRingCornerRadius: CGFloat
    let borderWidth: CGFloat
    let wantsClearButton: Bool
    let clearButtonImage: NSImage?
    let calendarImage: NSImage?
    let clockImage: NSImage?
    let font: NSFont
    let highlightedColor: NSColor
    let backgroundColor: NSColor
    let borderColor: NSColor
    
    public init(height: CGFloat, leftPadding: CGFloat, rightPadding: CGFloat, yPadding: CGFloat, focusRingCornerRadius: CGFloat, borderWidth: CGFloat, wantsClearButton: Bool, clearButtonImage: NSImage?, calendarImage: NSImage?, clockImage: NSImage?, font: NSFont, highlightedColor: NSColor, backgroundColor: NSColor, borderColor: NSColor) {
        self.height = height
        self.leftPadding = leftPadding
        self.rightPadding = rightPadding
        self.yPadding = yPadding
        self.focusRingCornerRadius = focusRingCornerRadius
        self.borderWidth = borderWidth
        self.wantsClearButton = wantsClearButton
        self.clearButtonImage = clearButtonImage
        self.calendarImage = calendarImage
        self.clockImage = clockImage
        self.font = font
        self.highlightedColor = highlightedColor
        self.backgroundColor = backgroundColor
        self.borderColor = borderColor
    }
}
