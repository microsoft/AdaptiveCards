@testable import AdaptiveCards
import AppKit

class FakeRootView: ACRView {
    init() {
        super.init(style: .default, hostConfig: FakeHostConfig.make(), renderConfig: .default)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class FakeResourceResolver: ACRViewResourceResolverDelegate {
    var calledCount = 0
    var calledURLs: [String] = []
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor url: String) {
        calledCount += 1
        calledURLs.append(url)
        adaptiveCard.setImage(NSImage(), for: url)
    }
    
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize? {
        return nil
    }
    
    var textResolverCalled = false
    func resolve(_ adaptiveCard: NSView, attributedStringFor htmlString: String) -> NSAttributedString? {
        textResolverCalled = true
        return nil
    }
}
