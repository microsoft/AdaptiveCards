@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionsRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionSetRenderer: ActionSetRenderer!
    private var actions: [ACSBaseActionElement] = []
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionSetRenderer = ActionSetRenderer()
    }
    
    func testRendererGetActions() {
        let hostConfigActions = FakeActionsConfig.make(actionsOrientation: .vertical, maxActions: 5)
        hostConfig = .make(actions: hostConfigActions)
        actions.append(FakeSubmitAction.make())
        
        let actionSetView = renderActionsView()
        XCTAssertEqual(actionSetView.actions.count, 1)
    }
    
    func testRendererCheckOrientation() {
        var hostConfigActions = FakeActionsConfig.make(actionsOrientation: .horizontal, maxActions: 5)
        hostConfig = .make(actions: hostConfigActions)
        actions.append(FakeSubmitAction.make())
        
        var actionSetView = renderActionsView()
        XCTAssertEqual(actionSetView.orientation, .horizontal)
        
        hostConfigActions = FakeActionsConfig.make(actionsOrientation: .vertical, maxActions: 5)
        hostConfig = .make(actions: hostConfigActions)
        
        actionSetView = renderActionsView()
        XCTAssertEqual(actionSetView.orientation, .vertical)
    }
    
    private func renderActionsView() -> ACRActionSetView {
        let view = actionSetRenderer.renderActionButtons(actions: actions, with: hostConfig, style: .default, rootView: ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRActionSetView)
        guard let actionSetView = view as? ACRActionSetView else { fatalError() }
        return actionSetView
    }
}
