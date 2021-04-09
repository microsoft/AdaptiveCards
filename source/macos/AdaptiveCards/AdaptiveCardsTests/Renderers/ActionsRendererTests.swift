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
        let hostConfigActions = ACSActionsConfig(showCard: .init(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: .init(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actions.append(FakeSubmitAction.make())
        
        let actionSetView = renderActionsView()
        XCTAssertEqual(actionSetView.actions.count, 1)
    }
    
    func testRendererCheckOrientation() {
        var hostConfigActions = ACSActionsConfig(showCard: .init(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .horizontal, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: .init(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actions.append(FakeSubmitAction.make())
        
        var actionSetView = renderActionsView()
        XCTAssertEqual(actionSetView.orientation, .horizontal)
        
        hostConfigActions = ACSActionsConfig(showCard: .init(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: .init(value: 1))
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
