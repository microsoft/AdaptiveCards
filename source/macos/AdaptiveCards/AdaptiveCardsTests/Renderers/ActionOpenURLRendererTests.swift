@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionOpenURLRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionOpenURL: FakeOpenURLAction!
    private var acrView: ACRView!
    private var delegate: FakeAdaptiveCardActionDelegate!
    private var targetHandlerDelegate: FakeTargetHandlerDelegate!
    private var actionOpenURLRenderer: ActionOpenURLRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionOpenURL = .make()
        delegate = FakeAdaptiveCardActionDelegate()
        targetHandlerDelegate = FakeTargetHandlerDelegate()
        acrView = ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default)
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
        actionOpenURL = .make(url: "www.google.com")
        
        let button = renderButton()
        button.performClick()
        
        XCTAssertEqual(targetHandlerDelegate.calledURL, "www.google.com")
        XCTAssertEqual(targetHandlerDelegate.calledView, button)
    }
    
    func testViewCallsDelegateAction_forRootView() {
        acrView.delegate = delegate
        actionOpenURL = .make(url: "www.google.com")
        
        let button = renderButton(targetHandler: acrView)
        button.performClick()
        
        XCTAssertEqual(delegate.calledURL, "www.google.com")
    }
    
    func testIconPosition() {
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .aboveTitle))
        actionOpenURL = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        actionOpenURL = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageAbove)
        
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .leftOfTitle))
        actionOpenURL = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        actionOpenURL = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageLeft)
    }
    
    private func renderButton(targetHandler: TargetHandlerDelegate? = nil) -> ACRButton {
        let view = actionOpenURLRenderer.render(action: actionOpenURL, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), targetHandlerDelegate: targetHandler ?? targetHandlerDelegate, inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}
