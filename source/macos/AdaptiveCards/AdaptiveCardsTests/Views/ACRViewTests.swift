@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRViewTests: XCTestCase {
    private var view: ACRView!
    private var fakeResourceResolver: FakeResourceResolver!
    private var fakeACRViewDelegate: FakeACRViewDelegate!
    
    override func setUp() {
        super.setUp()
        view = ACRView(style: .default, hostConfig: FakeHostConfig.make(), renderConfig: .default)
        fakeResourceResolver = FakeResourceResolver()
        view.resolverDelegate = fakeResourceResolver
        fakeACRViewDelegate = FakeACRViewDelegate()
    }
    
    func testRegisterImageHandlingView() {
        let imageView1 = FakeImageHoldingView()
        let imageView2 = FakeImageHoldingView()
        
        view.registerImageHandlingView(imageView1, for: "test1")
        view.registerImageHandlingView(imageView2, for: "test2")
        
        XCTAssertEqual(view.imageViewMap["test1"]![0], imageView1)
        XCTAssertEqual(view.imageViewMap["test2"]![0], imageView2)
    }
    
    func testResourceResolver() {
        let imageView1 = FakeImageHoldingView()
        let imageView2 = FakeImageHoldingView()
        let imageView3 = FakeImageHoldingView()
        
        view.registerImageHandlingView(imageView1, for: "test1")
        view.registerImageHandlingView(imageView2, for: "test2")
        view.registerImageHandlingView(imageView3, for: "test3")
        
        view.dispatchResolveRequests()
        
        XCTAssertEqual(fakeResourceResolver.calledCount, 3)
        XCTAssertTrue(imageView1.imageDidSet)
        XCTAssertTrue(imageView2.imageDidSet)
        XCTAssertTrue(imageView3.imageDidSet)
    }
    
    func testDispatchesUniqueURLRequests() {
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test")
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test")
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test")
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test")
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test")
        view.registerImageHandlingView(FakeImageHoldingView(), for: "test2")
        
        view.dispatchResolveRequests()
        
        XCTAssertEqual(fakeResourceResolver.calledCount, 2)
        XCTAssertEqual(fakeResourceResolver.calledURLs.count, 2)
        XCTAssertEqual(fakeResourceResolver.calledURLs.sorted()[0], "test")
        XCTAssertEqual(fakeResourceResolver.calledURLs.sorted()[1], "test2")
    }
    
    func testAllImageViewIsCalled() {
        let imageView1 = FakeImageHoldingView()
        let imageView2 = FakeImageHoldingView()
        let imageView3 = FakeImageHoldingView()
        
        view.registerImageHandlingView(imageView1, for: "test")
        view.registerImageHandlingView(imageView2, for: "test")
        view.registerImageHandlingView(imageView3, for: "test")
        
        view.dispatchResolveRequests()
        
        XCTAssertEqual(fakeResourceResolver.calledCount, 1)
        XCTAssertTrue(imageView1.imageDidSet)
        XCTAssertTrue(imageView2.imageDidSet)
        XCTAssertTrue(imageView3.imageDidSet)
    }
    
    // Test when ShowCard's Submit Action is Clicked
    func testSubmitActionCountWithAShowCard() {
        let fakeShowCard = ACRView(style: .default, hostConfig: FakeHostConfig(), renderConfig: .default)
        fakeShowCard.delegate = fakeACRViewDelegate
        
        view.addShowCard(fakeShowCard)
        fakeShowCard.handleSubmitAction(actionView: NSView(), dataJson: "")
        
        XCTAssertEqual(fakeACRViewDelegate.submitActionCount, 1)
    }
    
    // Test when ShowCard's Submit Action is clicked in nested setup
    func testSubmitActionCountWithNestedShowCard() {
        let fakeShowCard = ACRView(style: .default, hostConfig: FakeHostConfig(), renderConfig: .default)
        let fakeShowCard2 = ACRView(style: .default, hostConfig: FakeHostConfig(), renderConfig: .default)
        
        fakeShowCard.addInputHandler(fakeInputHandlingView())
        fakeShowCard.addInputHandler(fakeInputHandlingView())
        fakeShowCard2.addInputHandler(fakeInputHandlingView())
        
        fakeShowCard2.delegate = fakeACRViewDelegate
        
        // Nested show cards
        view.addShowCard(fakeShowCard)
        fakeShowCard.addShowCard(fakeShowCard2)
        
        fakeShowCard2.handleSubmitAction(actionView: NSView(), dataJson: "")
        
        XCTAssertEqual(fakeACRViewDelegate.dictValues, 3)
    }
    
    // Test when ShowCard's Submit Action is clicked with sibling showcard
    func testSubmitActionCountWithSiblingShowCard() {
        let fakeShowCard = ACRView(style: .default, hostConfig: FakeHostConfig(), renderConfig: .default)
        let fakeShowCard2 = ACRView(style: .default, hostConfig: FakeHostConfig(), renderConfig: .default)
        
        fakeShowCard.addInputHandler(fakeInputHandlingView())
        fakeShowCard2.addInputHandler(fakeInputHandlingView())
        
        fakeShowCard2.delegate = fakeACRViewDelegate
        
        // sibling show cards
        view.addShowCard(fakeShowCard)
        view.addShowCard(fakeShowCard2)
        
        fakeShowCard2.handleSubmitAction(actionView: NSView(), dataJson: "")
        
        XCTAssertEqual(fakeACRViewDelegate.dictValues, 1)
    }
}

private class FakeACRViewDelegate: NSView, ACRViewDelegate {
    var submitActionCount = 0
    var dictValues = 0
    func acrView(_ view: ACRView, didSelectOpenURL url: String, actionView: NSView) {}
    func acrView(_ view: ACRView, didShowCardWith actionView: NSView, previousHeight: CGFloat, newHeight: CGFloat) {}
    
    func acrView(_ view: ACRView, didSubmitUserResponses dict: [String : Any], actionView: NSView) {
        submitActionCount += 1
        dictValues += dict.count
    }
}

private class fakeInputHandlingView: NSView, InputHandlingViewProtocol {
    var value: String = NSUUID().uuidString
    var key: String = NSUUID().uuidString
    var isValid: Bool = true
}

private class FakeImageHoldingView: NSView, ImageHoldingView {
    var imageDidSet = false
    func setImage(_ image: NSImage) {
        imageDidSet = true
    }
}

private class FakeResourceResolver: ACRViewResourceResolverDelegate {
    var calledCount = 0
    var calledURLs: [String] = []
    func resolve(_ adaptiveCard: ImageResourceHandlerView, requestImageFor url: String) {
        calledCount += 1
        calledURLs.append(url)
        adaptiveCard.setImage(NSImage(), for: url)
    }
    
    func resolve(_ adaptiveCard: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize? {
        return nil
    }
}
