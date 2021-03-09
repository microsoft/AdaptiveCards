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
    
    func testRendererSetsMinHeight() {
        container = .make(minHeight: 200)
        let containerView = renderContainerView()
        XCTAssertEqual(containerView.fittingSize.height, 200)
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
    
    private func renderContainerView() -> ACRColumnView {
        let view = containerRenderer.render(element: container, with: hostConfig, style: .default, rootView: NSView(), parentView: NSView(), inputs: [])
        
        XCTAssertTrue(view is ACRColumnView)
        guard let containerView = view as? ACRColumnView else { fatalError() }
        return containerView
    }
}
