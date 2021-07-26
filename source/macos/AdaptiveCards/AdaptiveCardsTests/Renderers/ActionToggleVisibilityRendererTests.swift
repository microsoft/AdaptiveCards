@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionToggleVisibilityRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var toggleVisibilityAction: FakeToggleVisibilityAction!
    private var acrView: ACRView!
    private var delegate: FakeAdaptiveCardActionDelegate!
    private var targetHandlerDelegate: FakeTargetHandlerDelegate!
    private var actionToggleVisibilityRenderer: ActionToggleVisibilityRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        toggleVisibilityAction = .make()
        acrView = ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default)
        delegate = FakeAdaptiveCardActionDelegate()
        targetHandlerDelegate = FakeTargetHandlerDelegate()
        actionToggleVisibilityRenderer = ActionToggleVisibilityRenderer()
    }
    
    func testRendersChevronButton() {
        let button = renderButton()
        XCTAssertFalse(button.showsChevron)
    }
    
    func testSetsTitle() {
        toggleVisibilityAction = .make(title: "Hello world!")
        let button = renderButton()
        XCTAssertEqual(button.title, "Hello world!")
    }
    
    func testSetsTargets() {
        toggleVisibilityAction = .make(inputText: FakeInputText.make())
        let button = renderButton()
        guard let target = acrView.targets.first as? ActionToggleVisibilityTarget else { return XCTFail() }
        XCTAssertEqual(acrView.targets.count, 1)
        XCTAssertEqual(button.target as! ActionToggleVisibilityTarget, target)
    }
    
    func testToggleVisibilityActionCalled() {
        let fakeTargets = [FakeToggleVisibilityTarget.make(elementId: "hello", isVisible: .isVisibleTrue)]
        toggleVisibilityAction = .make(targetElements: fakeTargets)
        let button = renderButton()
        button.performClick()
        
        XCTAssertEqual(targetHandlerDelegate.calledView, button)
        XCTAssertEqual(targetHandlerDelegate.lastToggleTargets?.count, toggleVisibilityAction.targetElements.count)
        XCTAssertTrue(targetHandlerDelegate.lastToggleTargets?[0] === fakeTargets[0])
    }
    
    func testIconPosition() {
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .aboveTitle))
        toggleVisibilityAction = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        toggleVisibilityAction = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageAbove)
        
        hostConfig = .make(actions: FakeActionsConfig.make(iconPlacement: .leftOfTitle))
        toggleVisibilityAction = .make()
        XCTAssertEqual(renderButton().imagePosition, .noImage) // No Icon case
        
        toggleVisibilityAction = .make(iconUrl: "test.url")
        XCTAssertEqual(renderButton().imagePosition, .imageLeft)
    }

    private func renderButton() -> ACRButton {
        let view = actionToggleVisibilityRenderer.render(action: toggleVisibilityAction, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), targetHandlerDelegate: targetHandlerDelegate, inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}
