@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionOpenURLRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionOpenURL: FakeOpenURLAction!
    private var acrView: ACRView!
    private var delegate: FakeACRViewOpenURLDelegate!
    private var actionOpenURLRenderer: ActionOpenURLRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionOpenURL = .make()
        delegate = FakeACRViewOpenURLDelegate()
        acrView = ACRView(style: .default, hostConfig: hostConfig)
        actionOpenURLRenderer = ActionOpenURLRenderer()
    }
    
    func testRendersNormalButton() {
        let button = renderButton()
        XCTAssertFalse(button.showsChevron)
    }
    
    func testSetsTitle() {
        actionOpenURL = .make(title: "Hello world!")
        let button = renderButton()
        XCTAssertEqual(button.title, "Hello world!")
    }
    
    func testSetsTargets() {
        actionOpenURL = .make(url: "www.google.com")
        let button = renderButton()
        guard let target = acrView.targets.first as? ActionOpenURLTarget else { return XCTFail() }
        XCTAssertEqual(acrView.targets.count, 1)
        XCTAssertEqual(button.target as! ActionOpenURLTarget, target)
    }
    
    func testViewCallsDelegateAction() {
        acrView.delegate = delegate
        acrView.handleOpenURLAction(button: NSButton(), urlString: "www.google.com")
        XCTAssertEqual(delegate.calledURL, "www.google.com")
    }
    
    private func renderButton() -> ACRButton {
        let view = actionOpenURLRenderer.render(action: actionOpenURL, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}

private class FakeACRViewOpenURLDelegate: ACRViewDelegate {
    func acrInputViewHandler(_ view: ACRView, didSubmitUserResponses dict: [String : String], button: NSButton) { }
    var calledURL: String?
    func acrView(_ view: ACRView, didSelectOpenURL url: String, button: NSButton) {
        calledURL = url
    }
}
