@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionSubmitRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionSubmit: FakeSubmitAction!
    private var acrView: ACRView!
    private var delegate: FakeAdaptiveCardActionDelegate!
    private var targetHandlerDelegate: FakeTargetHandlerDelegate!
    private var actionSubmitRenderer: ActionSubmitRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionSubmit = .make()
        acrView = ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default)
        delegate = FakeAdaptiveCardActionDelegate()
        targetHandlerDelegate = FakeTargetHandlerDelegate()
        actionSubmitRenderer = ActionSubmitRenderer()
    }
    
    func testRendersChevronButton() {
        let button = renderButton()
        XCTAssertFalse(button.showsChevron)
    }
    
    func testSetsTitle() {
        actionSubmit = .make(title: "Hello world!")
        let button = renderButton()
        XCTAssertEqual(button.title, "Hello world!")
    }
    
    func testSetsTargets() {
        actionSubmit = .make(inputText: FakeInputText.make())
        let button = renderButton()
        guard let target = acrView.targets.first as? ActionSubmitTarget else { return XCTFail() }
        XCTAssertEqual(acrView.targets.count, 1)
        XCTAssertEqual(button.target as! ActionSubmitTarget, target)
    }
    
    func testSubmitActionCalled() {
        actionSubmit = .make(dataJson: "helloworld")
        let button = renderButton()
        button.performClick()
        
        XCTAssertEqual(targetHandlerDelegate.calledView, button)
        XCTAssertEqual(targetHandlerDelegate.lastDataJSON, "helloworld")
    }
    
    func testIconPosition() {
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .aboveTitle))
        actionSubmit = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        actionSubmit = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageAbove)
        
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .leftOfTitle))
        actionSubmit = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        actionSubmit = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageLeft)
    }

    private func renderButton() -> ACRButton {
        let view = actionSubmitRenderer.render(action: actionSubmit, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), targetHandlerDelegate: targetHandlerDelegate, inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}
