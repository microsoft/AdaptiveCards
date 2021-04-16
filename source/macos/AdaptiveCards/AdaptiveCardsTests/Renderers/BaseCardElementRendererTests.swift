@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class BaseCardElementRendererrTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var container: FakeContainer!
    private var backgroundImage: FakeBackgroundImage!
    private var baseCardRenderer: BaseCardElementRenderer!
    private var containerRenderer: ContainerRenderer!
   
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        container = .make()
        baseCardRenderer = BaseCardElementRenderer()
        containerRenderer = ContainerRenderer()
        
    }
    
    func testRendererSetsMinHeight() {
        container = .make(minHeight: 200)
        let viewWithInheritedProperties = renderBaseCardElementView()
        XCTAssertEqual(viewWithInheritedProperties.fittingSize.height, 200)
    }
    
    func testRendererSetsVisible() {
        container = .make(visible: true)
        var viewWithInheritedProperties = renderBaseCardElementView()
        XCTAssertEqual(viewWithInheritedProperties.isHidden, false)
        
        container = .make(visible: false)
        viewWithInheritedProperties = renderBaseCardElementView()
        XCTAssertEqual(viewWithInheritedProperties.isHidden, true)
    }
    
    func testRendererSetsBackgroundImage() {
        backgroundImage = .make(url: "https://picsum.photos/200", fillMode: .repeat)
        container = .make(backgroundImage: backgroundImage)
        let viewWithInheritedProperties = renderBaseCardElementView()
        guard let updatedView = viewWithInheritedProperties.arrangedSubviews[0] as? ACRColumnView else {
            fatalError()
        }
        XCTAssertEqual(updatedView.backgroundImageView.fillMode, .repeat)
    }
    
    
    private func renderBaseCardElementView() -> ACRContentStackView {
        let view = containerRenderer.render(element: container, with: hostConfig, style: .default, rootView: FakeRootView(), parentView: NSView(), inputs: [], config: .default)
        XCTAssertTrue(view is ACRColumnView)
        
        let viewWithInheritedProperties = baseCardRenderer.updateView(view: view, element: container, rootView: FakeRootView(), style: .default, hostConfig: hostConfig, config: .default, isfirstElement: true)
        XCTAssertTrue(viewWithInheritedProperties is ACRContentStackView)
        
        guard let updatedView = viewWithInheritedProperties as? ACRContentStackView else { fatalError() }
        return updatedView
    }
}
