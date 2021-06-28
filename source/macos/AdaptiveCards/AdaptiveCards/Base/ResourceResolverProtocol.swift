import AdaptiveCards_bridge
import AppKit

public protocol ImageResourceHandlerView: NSView {
    func setImage(_ image: NSImage, for url: String)
    func setImage(_ image: NSImage, forURLsContaining matcher: @escaping (String) -> Bool)
}

protocol ImageHoldingView: NSView {
    func setImage(_ image: NSImage)
}
