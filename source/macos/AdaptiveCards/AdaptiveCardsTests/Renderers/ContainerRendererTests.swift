@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ContainerRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var container: FakeContainer!
    private var containerRenderer: ContainerRenderer!
   
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        container = .make()
        containerRenderer = ContainerRenderer()
    }
    
    func testRendererSetsStyle() {
        container = .make(style: .none)
        let containerView = renderContainerView()
        XCTAssertEqual(containerView.layer?.backgroundColor, nil)
    }
    
    func testRendererSetsVerticalContentAlignment() {
        container = .make(verticalContentAlignment: .top)
        var containerView = renderContainerView()
        XCTAssertEqual(containerView.stackView.arrangedSubviews.capacity, 0)
        
        container = .make(verticalContentAlignment: .bottom)
        containerView = renderContainerView()
        XCTAssertEqual(containerView.stackView.arrangedSubviews.capacity, 1)
        
        container = .make(verticalContentAlignment: .center)
        containerView = renderContainerView()
        XCTAssertEqual(containerView.stackView.arrangedSubviews.capacity, 2)
    }
    
    func testSelectActionTargetIsSet() {
        var containerView: ACRContentStackView!
        
        container = .make(selectAction: FakeSubmitAction.make())
        containerView = renderContainerView()
        
        XCTAssertNotNil(containerView.target)
        XCTAssertTrue(containerView.target is ActionSubmitTarget)
        
        container = .make(selectAction: FakeOpenURLAction.make())
        containerView = renderContainerView()
        
        XCTAssertNotNil(containerView.target)
        XCTAssertTrue(containerView.target is ActionOpenURLTarget)
        
        container = .make(selectAction: FakeToggleVisibilityAction.make())
        containerView = renderContainerView()
        
        XCTAssertNotNil(containerView.target)
        XCTAssertTrue(containerView.target is ActionToggleVisibilityTarget)
        
        // ShowCard Action is not available as a SelectAction
        container = .make(selectAction: FakeShowCardAction.make())
        containerView = renderContainerView()
    
        XCTAssertNil(containerView.target)
    }
    
    func testRendersItems() {
        container = .make(items: [FakeInputToggle.make()])
        let containerView = renderContainerView()
        XCTAssertEqual(containerView.arrangedSubviews.count, 1)
    }
    
    private func renderContainerView() -> ACRColumnView {
        let view = containerRenderer.render(element: container, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRColumnView)
        guard let containerView = view as? ACRColumnView else { fatalError() }
        return containerView
    }
}
