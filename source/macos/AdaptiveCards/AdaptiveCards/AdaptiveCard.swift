import AdaptiveCards_bridge
import AppKit

public protocol AdaptiveCardActionDelegate: AnyObject {
    func adaptiveCard(_ adaptiveCard: NSView, didSelectOpenURL urlString: String, button: NSButton)
}

public protocol AdaptiveCardResourceResolver: AnyObject {
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith key: ResourceKey) -> NSSize?
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, requestImageFor key: ResourceKey)
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
    
    public static func render(card: ACSAdaptiveCard, with hostConfig: ACSHostConfig, width: CGFloat, actionDelegate: AdaptiveCardActionDelegate?, resourceResolver: AdaptiveCardResourceResolver?) -> NSView {
        AdaptiveCardRenderer.shared.actionDelegate = actionDelegate
        AdaptiveCardRenderer.shared.resolverDelegate = resourceResolver
        return AdaptiveCardRenderer.shared.renderAdaptiveCard(card, with: hostConfig, width: width)
    }
}
