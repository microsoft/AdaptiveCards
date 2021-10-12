@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionSetRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionSet: FakeActionSet!
    private var actionSetRenderer: ActionSetRenderer!
    private var rootView: FakeRootView!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionSet = .make()
        actionSetRenderer = ActionSetRenderer()
        rootView = FakeRootView()
    }
    
    func testRendererSetsDelegate() {
        let hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make()])
        
        let actionSetView = renderActionSetView()
        XCTAssertNotNil(actionSetView.delegate)
        XCTAssertTrue(actionSetView.delegate === rootView)
    }
    
    func testRendererGetActions() {
        let hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make()])
        
        let actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.actions.count, 1)
    }
    
    func testRendererCheckOrientation() {
        var hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .horizontal, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make(), FakeSubmitAction.make()])
        
        var actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.orientation, .horizontal)
        
        hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make(), FakeSubmitAction.make()])
        
        actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.orientation, .vertical)
    }
    
    func testRendererCheckAlignment() {
        // check for left alignment
        var hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .horizontal, actionAlignment: .left, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make()], aligned: .left)
        
        var actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.alignment, .leading)
        
        // check for right alignment
        hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .horizontal, actionAlignment: .left, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 0))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make()], aligned: .right)
        
        actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.alignment, .trailing)
        
        // check for center alignment
        hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .horizontal, actionAlignment: .left, buttonSpacing: 2, maxActions: 1, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 0))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make()], aligned: .center)
        
        actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.alignment, .centerY)
    }
    
    func testNumberOfAction() {
        let hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 5, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make(), FakeShowCardAction.make(), FakeOpenURLAction.make()])
        
        let actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.actions.count, 3)
    }
    
    func testNumberOfActionExceeded() {
        let hostConfigActions = ACSActionsConfig(showCard: FakeShowCardActionConfig(actionMode: .inline, style: .accent, inlineTopMargin: 0), actionsOrientation: .vertical, actionAlignment: .center, buttonSpacing: 2, maxActions: 2, spacing: .default, iconPlacement: .aboveTitle, iconSize: NSNumber(value: 1))
        hostConfig = .make(actions: hostConfigActions)
        actionSet = .make(actions: [FakeSubmitAction.make(), FakeShowCardAction.make(), FakeOpenURLAction.make()])
        
        let actionSetView = renderActionSetView()
        XCTAssertEqual(actionSetView.actions.count, 2)
    }
    
    private func renderActionSetView() -> ACRActionSetView {
        let view = actionSetRenderer.render(element: actionSet, with: hostConfig, style: .default, rootView: rootView, parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRActionSetView)
        guard let actionSetView = view as? ACRActionSetView else { fatalError() }
        return actionSetView
    }
}

