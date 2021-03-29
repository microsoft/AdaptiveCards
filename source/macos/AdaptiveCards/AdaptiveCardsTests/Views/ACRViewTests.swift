@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRViewTests: XCTestCase {
    private var view: ACRView!
    private var fakeResourceResolver: FakeResourceResolver!
    
    override func setUp() {
        super.setUp()
        view = ACRView(style: .default, hostConfig: FakeHostConfig.make())
        fakeResourceResolver = FakeResourceResolver()
        view.resolverDelegate = fakeResourceResolver
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
