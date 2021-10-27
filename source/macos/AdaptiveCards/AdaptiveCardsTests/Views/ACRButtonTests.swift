@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRButtonTests: XCTestCase {
    var button: ACRButton!
    var buttonConfig: ButtonConfig!
    
    override func setUp() {
        super.setUp()
        // This is the default buttonConfig, except we're passing chevron icons here instead of passing nil.
        buttonConfig = ButtonConfig(positive: ButtonColorConfig(buttonColor: .green, selectedButtonColor: .systemGreen, hoverButtonColor: .systemGreen, textColor: .white, selectedTextColor: .white, borderColor: .green, selectedBorderColor: .systemGreen, wantsBorder: true), destructive: ButtonColorConfig(buttonColor: .systemRed, selectedButtonColor: .red, hoverButtonColor: .red, textColor: .white, selectedTextColor: .white, borderColor: .systemRed, selectedBorderColor: .red, wantsBorder: true), default: ButtonColorConfig(buttonColor: .systemBlue, selectedButtonColor: .blue, hoverButtonColor: .blue, textColor: .white, selectedTextColor: .white, borderColor: .systemBlue, selectedBorderColor: .blue, wantsBorder: true), inline: ButtonColorConfig(buttonColor: .systemBlue, selectedButtonColor: .blue, hoverButtonColor: .blue, textColor: .white, selectedTextColor: .white, borderColor: .systemBlue, selectedBorderColor: .blue, wantsBorder: true), font: .systemFont(ofSize: 12), buttonContentInsets: NSEdgeInsets(top: 5, left: 16, bottom: 5, right: 16), chevronUpImage: BundleUtils.getImage("arrowup", ofType: "png"), chevronDownImage: BundleUtils.getImage("arrowdown", ofType: "png"))
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .default, buttonConfig: buttonConfig)
    }
    
    func testBackgroundColors() {
        XCTAssertEqual(button.buttonColor, buttonConfig.default.buttonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .destructive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.buttonColor, buttonConfig.destructive.buttonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .inline, buttonConfig: buttonConfig)
        XCTAssertEqual(button.buttonColor, buttonConfig.inline.buttonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .positive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.buttonColor, buttonConfig.positive.buttonColor)
    }
    
    func testBorderColors() {
        XCTAssertEqual(button.borderColor, buttonConfig.default.borderColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .destructive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.borderColor, buttonConfig.destructive.borderColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .inline, buttonConfig: buttonConfig)
        XCTAssertEqual(button.borderColor, buttonConfig.inline.borderColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .positive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.borderColor, buttonConfig.positive.borderColor)
    }
    
    func testHoverColors() {
        XCTAssertEqual(button.hoverButtonColor, buttonConfig.default.hoverButtonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .destructive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.hoverButtonColor, buttonConfig.destructive.hoverButtonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .inline, buttonConfig: buttonConfig)
        XCTAssertEqual(button.hoverButtonColor, buttonConfig.inline.hoverButtonColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .positive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.hoverButtonColor, buttonConfig.positive.hoverButtonColor)
    }
    
    func testTextColors() {
        XCTAssertEqual(button.textColor, buttonConfig.default.textColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .destructive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.textColor, buttonConfig.destructive.textColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .inline, buttonConfig: buttonConfig)
        XCTAssertEqual(button.textColor, buttonConfig.inline.textColor)
        
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .positive, buttonConfig: buttonConfig)
        XCTAssertEqual(button.textColor, buttonConfig.positive.textColor)
    }
    
    func testFont() {
        guard let buttonFont: NSFont = button.titleLayer.font as? NSFont else { return XCTFail() }
        XCTAssertEqual(buttonFont, buttonConfig.font)
    }
    
    func testInsets() {
        XCTAssertEqual(button.contentInsets.left, buttonConfig.buttonContentInsets.left)
        XCTAssertEqual(button.contentInsets.top, buttonConfig.buttonContentInsets.top)
        XCTAssertEqual(button.contentInsets.right, buttonConfig.buttonContentInsets.right)
        XCTAssertEqual(button.contentInsets.bottom, buttonConfig.buttonContentInsets.bottom)
    }
    
    func testChevronUpImage() {
        XCTAssertEqual(button.chevronUpIcon, buttonConfig.chevronUpImage)
        // checking default chevron up icon now
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .default, buttonConfig: .default)
        XCTAssertNotNil(button.chevronUpIcon)
    }
    
    func testChevronDownImage() {
        XCTAssertEqual(button.chevronDownIcon, buttonConfig.chevronDownImage)
        // checking default chevron down icon now
        button = ACRButton(frame: .zero, wantsChevron: false, wantsIcon: false, iconPosition: .imageLeft, style: .default, buttonConfig: .default)
        XCTAssertNotNil(button.chevronDownIcon)
    }
}
