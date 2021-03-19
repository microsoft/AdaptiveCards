import AdaptiveCards_bridge
import AppKit

public enum ResourceType {
    case image, backgroundImage, imageSet, iconUrl
}

public struct ResourceKey {
    public var url: String
    public var type: ResourceType
}

public protocol ImageResourceHandlerView: NSView {
    func setImage(_ image: NSImage, for key: ResourceKey)
}
