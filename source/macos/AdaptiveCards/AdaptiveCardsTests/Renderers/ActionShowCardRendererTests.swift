@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ActionShowCardRendererTests: XCTestCase {
    private var hostConfig: FakeHostConfig!
    private var actionShowCard: FakeShowCardAction!
    private var acrView: ACRView!
    private var actionShowCardRenderer: ActionShowCardRenderer!
    
    override func setUpWithError() throws {
        try super.setUpWithError()
        hostConfig = .make()
        actionShowCard = .make()
        acrView = ACRView(style: .default, hostConfig: hostConfig, renderConfig: .default)
        actionShowCardRenderer = ActionShowCardRenderer()
    }
    
    func testRendersChevronButton() {
        let button = renderButton()
        XCTAssertTrue(button.showsChevron)
    }
    
    func testSetsTitle() {
        actionShowCard = .make(title: "Hello world!")
        let button = renderButton()
        XCTAssertEqual(button.title, "Hello world!")
    }
    
    func testSetsTargets() {
        actionShowCard = .make(card: FakeAdaptiveCard.make())
        let button = renderButton()
        guard let target = acrView.targets.first as? ActionShowCardTarget else { return XCTFail() }
        XCTAssertEqual(acrView.targets.count, 1)
        XCTAssertEqual(button.target as! ActionShowCardTarget, target)
    }
    
    private func renderButton() -> ACRButton {
        let view = actionShowCardRenderer.render(action: actionShowCard, with: hostConfig, style: .default, rootView: acrView, parentView: NSView(), inputs: [], config: .default)
        
        XCTAssertTrue(view is ACRButton)
        guard let button = view as? ACRButton else { fatalError() }
        return button
    }
}
