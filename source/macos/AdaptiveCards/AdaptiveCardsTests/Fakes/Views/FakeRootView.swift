@testable import AdaptiveCards
import AdaptiveCards_bridge
import AppKit

class FakeRootView: ACRView {
    init() {
        super.init(style: .default, hostConfig: FakeHostConfig.make(), renderConfig: .default)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class FakeResourceResolver: AdaptiveCardResourceResolver {
    var calledCount = 0
    var calledURLs: [String] = []
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, requestImageFor url: String) {
        calledCount += 1
        calledURLs.append(url)
        adaptiveCard.setImage(NSImage(), for: url)
    }
    
    func adaptiveCard(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize? {
        return nil
    }
    
    var textResolverCalled = false
    func adaptiveCard(_ adaptiveCard: NSView, attributedStringFor htmlString: String) -> NSAttributedString? {
        textResolverCalled = true
        return nil
    }
}

class FakeAdaptiveCardActionDelegate: AdaptiveCardActionDelegate {
    var calledURL: String?
    func adaptiveCard(_ adaptiveCard: NSView, didSelectOpenURL urlString: String, actionView: NSView) {
        calledURL = urlString
    }
    
    var submitActionCount = 0
    var dictValues = 0
    var dict: [String: Any] = [:]
    func adaptiveCard(_ adaptiveCard: NSView, didSubmitUserResponses dict: [String : Any], actionView: NSView) {
        submitActionCount += 1
        dictValues += dict.count
        self.dict = dict
    }
    
    func adaptiveCard(_ adaptiveCard: NSView, didUpdateBoundsFrom oldValue: NSRect, to newValue: NSRect) { }
    func adaptiveCard(_ adaptiveCard: NSView, didShowCardWith actionView: NSView, previousHeight: CGFloat, newHeight: CGFloat) { }
}

class FakeTargetHandlerDelegate: ShowCardTargetHandlerDelegate {
    var calledView: NSView?
    var isShowCardActionCalled = false
    func handleShowCardAction(button: NSButton, showCard: ACSAdaptiveCard) {
        isShowCardActionCalled = true
        calledView = button
    }
    
    var calledURL: String?
    func handleOpenURLAction(actionView: NSView, urlString: String) {
        calledView = actionView
        calledURL = urlString
    }
    
    var lastDataJSON: String?
    func handleSubmitAction(actionView: NSView, dataJson: String?) {
        calledView = actionView
        lastDataJSON = dataJson
    }
    
    var lastToggleTargets: [ACSToggleVisibilityTarget]?
    func handleToggleVisibilityAction(actionView: NSView, toggleTargets: [ACSToggleVisibilityTarget]) {
        calledView = actionView
        lastToggleTargets = toggleTargets
    }
}
