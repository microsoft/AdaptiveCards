@testable import AdaptiveCards
import AdaptiveCards_bridge
import XCTest

class ACRChoiceSetButtontests: XCTestCase {
    private var choiceCheckBoxButtonView: ACRChoiceButton!
    private var choiceRadioButtonView: ACRChoiceButton!
    private var renderConfig: RenderConfig!
    
    override func setUp() {
        super.setUp()
        renderConfig = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: .default,checkBoxButtonConfig: setupCheckBoxButton(), radioButtonConfig: setupRadioButton())
        choiceCheckBoxButtonView = ACRChoiceButton(renderConfig: renderConfig, buttonType: .switch)
        choiceRadioButtonView = ACRChoiceButton(renderConfig: renderConfig, buttonType: .radio)
    }
    
    func testCheckBoxButtonClick() {
        XCTAssertEqual(choiceCheckBoxButtonView.state, .off)
        choiceCheckBoxButtonView.button.performClick(nil)
        XCTAssertEqual(choiceCheckBoxButtonView.state, .on)
        choiceCheckBoxButtonView.button.performClick(nil)
        XCTAssertEqual(choiceCheckBoxButtonView.state, .off)
    }
    
    func testRadioButtonLabelClick() {
        XCTAssertEqual(choiceRadioButtonView.state, .off)
        choiceRadioButtonView.mouseDown(with: NSEvent())
        XCTAssertEqual(choiceRadioButtonView.state, .on)
        choiceRadioButtonView.mouseDown(with: NSEvent())
        XCTAssertEqual(choiceRadioButtonView.state, .on)
    }
    
    func testCheckBoxButtonLabelClick() {
        XCTAssertEqual(choiceCheckBoxButtonView.state, .off)
        choiceCheckBoxButtonView.mouseDown(with: NSEvent())
        XCTAssertEqual(choiceCheckBoxButtonView.state, .on)
        choiceCheckBoxButtonView.mouseDown(with: NSEvent())
        XCTAssertEqual(choiceCheckBoxButtonView.state, .off)
    }
    
    func testCheckBoxButtonImagesOff() {
        XCTAssertNotNil(choiceCheckBoxButtonView.button.image)
        XCTAssertNotNil(choiceCheckBoxButtonView.button.alternateImage)
        XCTAssertEqual(choiceCheckBoxButtonView.button.image, renderConfig.checkBoxButtonConfig?.normalIcon)
        XCTAssertEqual(choiceCheckBoxButtonView.button.alternateImage, renderConfig.checkBoxButtonConfig?.highlightedIcon)
    }
    
    func testCheckBoxButtonImagesOn() {
        choiceCheckBoxButtonView.state = .on
        XCTAssertNotNil(choiceCheckBoxButtonView.button.image)
        XCTAssertNotNil(choiceCheckBoxButtonView.button.alternateImage)
        XCTAssertEqual(choiceCheckBoxButtonView.button.image, renderConfig.checkBoxButtonConfig?.selectedHighlightedIcon)
        XCTAssertEqual(choiceCheckBoxButtonView.button.alternateImage, renderConfig.checkBoxButtonConfig?.selectedIcon)
    }

    func testRadioButtonImagesOff() {
        XCTAssertNotNil(choiceRadioButtonView.button.image)
        XCTAssertNotNil(choiceRadioButtonView.button.alternateImage)
        XCTAssertEqual(choiceRadioButtonView.button.image, renderConfig.radioButtonConfig?.normalIcon)
        XCTAssertEqual(choiceRadioButtonView.button.alternateImage, renderConfig.radioButtonConfig?.highlightedIcon)
    }
    
    func testRadioButtonImagesOn() {
        choiceRadioButtonView.state = .on
        XCTAssertNotNil(choiceRadioButtonView.button.image)
        XCTAssertNotNil(choiceRadioButtonView.button.alternateImage)
        XCTAssertEqual(choiceRadioButtonView.button.image, renderConfig.radioButtonConfig?.selectedHighlightedIcon)
        XCTAssertEqual(choiceRadioButtonView.button.alternateImage, renderConfig.radioButtonConfig?.selectedIcon)
    }
    
    func testRadioButtonWithoutImages() {
        renderConfig = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: .default, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        choiceRadioButtonView = ACRChoiceButton(renderConfig: renderConfig, buttonType: .radio)
        let defaultRadioButton = NSButton(radioButtonWithTitle: "", target: nil, action: nil)
        
        XCTAssertEqual(choiceRadioButtonView.button.image, defaultRadioButton.image)
        XCTAssertEqual(choiceRadioButtonView.button.alternateImage, defaultRadioButton.alternateImage)
    }
    
    func testCheckBoxButtonWithoutImages() {
        renderConfig = RenderConfig(isDarkMode: false, buttonConfig: .default, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: .default, checkBoxButtonConfig: nil, radioButtonConfig: nil)
        choiceCheckBoxButtonView = ACRChoiceButton(renderConfig: renderConfig, buttonType: .switch)
        let defaultCheckBoxButton = NSButton(checkboxWithTitle: "", target: nil, action: nil)
        
        XCTAssertEqual(choiceCheckBoxButtonView.button.image, defaultCheckBoxButton.image)
        XCTAssertEqual(choiceCheckBoxButtonView.button.alternateImage, defaultCheckBoxButton.alternateImage)
    }
    
    func testElementSpacing() {
        let elementSpacing = choiceRadioButtonView.fittingSize.width - (choiceRadioButtonView.label.fittingSize.width + choiceRadioButtonView.button.fittingSize.width)
        XCTAssertEqual(renderConfig.checkBoxButtonConfig?.elementSpacing, elementSpacing)
    }
    
    private func setupRadioButton() -> ChoiceSetButtonConfig {
        let onHoverIcon = NSImage()
        let offHoverIcon = NSImage()
        let onIcon = NSImage()
        let offIcon = NSImage()
        
        return ChoiceSetButtonConfig(selectedIcon: onIcon, normalIcon: offIcon, selectedHighlightedIcon: onHoverIcon, highlightedIcon: offHoverIcon, elementSpacing: 12)
    }
    
    private func setupCheckBoxButton() -> ChoiceSetButtonConfig {
        let onHoverIcon = NSImage()
        let offHoverIcon = NSImage()
        let onIcon = NSImage()
        let offIcon = NSImage()
        
        return ChoiceSetButtonConfig(selectedIcon: onIcon, normalIcon: offIcon, selectedHighlightedIcon: onHoverIcon, highlightedIcon: offHoverIcon, elementSpacing: 12)
    }
}
