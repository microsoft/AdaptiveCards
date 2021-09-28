@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest


class HostConfigUtilsTests: XCTestCase {
    private var color: NSColor!
    
    override func setUp() {
        super.setUp()
        color = .clear
    }
    
    func testColorUtilsEightCharHexString() {
        color = ColorUtils.color(from: "#9900FFCC")
        XCTAssertEqual(color, NSColor(red: 0.6, green: 0, blue: 1, alpha: 0.8))
    }
    
    func testColorUtilsSixCharHexString() {
        color = ColorUtils.color(from: "#336699")
        XCTAssertEqual(color, NSColor(red: 0.2, green: 0.4, blue: 0.6, alpha: 1))
    }
    
    func testColorUtilsInvalidCharHexString() {
        color = ColorUtils.color(from: "#123")
        XCTAssertNil(color)
    }
}
