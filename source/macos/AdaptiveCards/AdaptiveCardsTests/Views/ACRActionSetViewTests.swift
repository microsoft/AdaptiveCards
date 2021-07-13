@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRActionSetViewTests: XCTestCase {
    private var view: ACRActionSetView!
    private var rootView: FakeRootView!
    private var delegate: FakeActionSetViewDelegate!
    private var actions: [ACSBaseActionElement] = []
    
    override func setUp() {
        super.setUp()
        actions = []
        rootView = FakeRootView()
        delegate = FakeActionSetViewDelegate()
    }
    
    func testAlignmentSetup() {
        renderActionSetView(alignment: .leading)
        XCTAssertEqual(view.stackView.alignment, .leading)
        
        renderActionSetView(alignment: .trailing)
        XCTAssertEqual(view.stackView.alignment, .trailing)
        XCTAssertEqual(view.showCardStackView.alignment, .leading)
        XCTAssertEqual(view.showCardStackView.orientation, .vertical)
    }
    
    func testOpenURLActionCall() {
        actions = [FakeOpenURLAction.make(url: "google.com")]
        renderActionSetView()
        actionButtons[0].performClick()
        
        XCTAssertTrue(delegate.isOpenURLCalled)
        XCTAssertEqual(delegate.calledURL, "google.com")
    }
    
    func testSubmitActionCall() {
        actions = [FakeSubmitAction.make(dataJson: "hello")]
        renderActionSetView()
        actionButtons[0].performClick()
        
        XCTAssertTrue(delegate.submitInputsCalled)
        XCTAssertEqual(delegate.lastDataJSON, "hello")
    }
    
    func testShowCardAction() {
        actions = [FakeShowCardAction.make(card: FakeAdaptiveCard())]
        let fakeShowCard = NSView()
        delegate.cardToReturn = fakeShowCard
        renderActionSetView()
        actionButtons[0].performClick()
        
        XCTAssertTrue(delegate.willShowCardCalled)
        XCTAssertTrue(delegate.didShowCardCalled)
        XCTAssertEqual(view.showCardStackView.arrangedSubviews.first, fakeShowCard)
        XCTAssertFalse(fakeShowCard.isHidden)
        XCTAssertEqual(actionButtons[0].state, .on)
        
        actionButtons[0].performClick()
        XCTAssertTrue(fakeShowCard.isHidden)
        XCTAssertEqual(actionButtons[0].state, .off)
    }
    
    func testShowCardAction_multipleShowCards() {
        actions = [FakeShowCardAction.make(card: FakeAdaptiveCard()), FakeShowCardAction.make(card: FakeAdaptiveCard())]
        renderActionSetView()
        
        let fakeShowCard1 = NSView()
        delegate.cardToReturn = fakeShowCard1
        actionButtons[0].performClick()
        
        XCTAssertTrue(delegate.willShowCardCalled)
        XCTAssertTrue(delegate.didShowCardCalled)
        XCTAssertEqual(view.showCardStackView.arrangedSubviews[0], fakeShowCard1)
        XCTAssertFalse(fakeShowCard1.isHidden)
        XCTAssertEqual(actionButtons[0].state, .on)
        
        let fakeShowCard2 = NSView()
        delegate.cardToReturn = fakeShowCard2
        actionButtons[1].performClick()
        
        XCTAssertTrue(fakeShowCard1.isHidden)
        XCTAssertEqual(actionButtons[0].state, .off)
        XCTAssertEqual(view.showCardStackView.arrangedSubviews[1], fakeShowCard2)
        XCTAssertFalse(fakeShowCard2.isHidden)
        XCTAssertEqual(actionButtons[1].state, .on)
        
        actionButtons[1].performClick()
        XCTAssertTrue(fakeShowCard1.isHidden)
        XCTAssertEqual(actionButtons[0].state, .off)
        XCTAssertTrue(fakeShowCard2.isHidden)
        XCTAssertEqual(actionButtons[1].state, .off)
    }
    
    private var actionButtons: [NSButton] {
        return view.actions as! [NSButton]
    }
    
    private func renderActionSetView(alignment: NSLayoutConstraint.Attribute = .leading) {
        view = ACRActionSetView(orientation: .horizontal, alignment: alignment, buttonSpacing: 8, exteriorPadding: 8)
        let actionViews = actions.map {
            RendererManager.shared.actionRenderer(for: $0.getType())
                .render(action: $0, with: FakeHostConfig(), style: .default, rootView: rootView, parentView: NSView(), targetHandlerDelegate: view, inputs: [], config: .default) }
        view.setActions(actionViews)
        view.delegate = delegate
    }
}

private class FakeActionSetViewDelegate: ACRActionSetViewDelegate {
    var isOpenURLCalled = false
    var calledURL: String?
    func actionSetView(_ view: ACRActionSetView, didOpenURLWith actionView: NSView, urlString: String) {
        isOpenURLCalled = true
        calledURL = urlString
    }
    
    var submitInputsCalled = false
    var lastDataJSON: String?
    func actionSetView(_ view: ACRActionSetView, didSubmitInputsWith actionView: NSView, dataJson: String?) {
        submitInputsCalled = true
        lastDataJSON = dataJson
    }
    
    var willShowCardCalled = false
    func actionSetView(_ view: ACRActionSetView, willShowCardWith button: NSButton) {
        willShowCardCalled = true
    }
    
    var didShowCardCalled = false
    func actionSetView(_ view: ACRActionSetView, didShowCardWith button: NSButton) {
        assert(willShowCardCalled, "willShowCard should be called first")
        didShowCardCalled = true
    }
    
    var cardToReturn: NSView?
    func actionSetView(_ view: ACRActionSetView, renderShowCardFor cardData: ACSAdaptiveCard) -> NSView {
        return cardToReturn ?? NSView()
    }
}
