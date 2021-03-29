import AdaptiveCards_bridge
import AppKit

public protocol ImageResourceHandlerView: NSView {
    func setImage(_ image: NSImage, for url: String)
}

protocol ImageHoldingView: NSView {
    func setImage(_ image: NSImage)
}
