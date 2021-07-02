@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ImageSetImageViewTests: XCTestCase {
    var hostConfig: FakeHostConfig!
    
    override func setUp() {
        super.setUp()
        hostConfig = FakeHostConfig()
    }
    
    func testImageSize_explicitCases() {
        var imageView = ImageSetImageView(imageSize: .large, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .large)
        
        imageView = ImageSetImageView(imageSize: .medium, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .medium)
        
        imageView = ImageSetImageView(imageSize: .small, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .small)
    }
    
    func testImageSize_nonExplicitCases() {
        var imageView = ImageSetImageView(imageSize: .stretch, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .medium)
        
        imageView = ImageSetImageView(imageSize: .none, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .medium)
        
        imageView = ImageSetImageView(imageSize: .auto, hostConfig: hostConfig)
        XCTAssertEqual(imageView.imageSize, .medium)
    }
}
