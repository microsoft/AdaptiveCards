import AdaptiveCards
import Cocoa

class RootViewController: NSViewController, NSTableViewDelegate, NSTableViewDataSource, NSComboBoxDelegate, NSComboBoxDataSource {
    @IBOutlet var tableView: NSTableView!
    @IBOutlet var stackView: NSStackView!
    @IBOutlet var textView: NSTextView!
    @IBOutlet var comboBox: NSComboBox!
    @IBOutlet var cardScrollView: NSView!
    private var items: [String] = []
    private var configs: [String] = []
    private var hostConfigString = sampleHostConfig // default config string
    private let webexConfig: String = "webex_rebranded_light.json"
    private var darkTheme = false
    private var buttonConfig: ButtonConfig = .default
    private var checkButtonConfig: ChoiceSetButtonConfig?
    private var radioButtonConfig: ChoiceSetButtonConfig?
    private var inputFieldConfig: InputFieldConfig = .default
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let main = Bundle.main
        let filesManager = FileManager.default
        guard let sample = main.resourcePath?.appending("/samples") else { return }
        do {
            let samples = try filesManager.contentsOfDirectory(atPath: sample)
            items = samples.sorted()
        } catch {
            print(error)
        }
        guard let hostConfig = main.resourcePath?.appending("/hostconfigs") else { return }
        do {
            let hostConfigs = try filesManager.contentsOfDirectory(atPath: hostConfig)
            configs = hostConfigs.sorted()
        } catch {
            print(error)
        }
        
        comboBox.dataSource = self
        comboBox.delegate = self
        
        // setting Webex Light theme if present or the first config entry
        if !configs.isEmpty {
            comboBox.selectItem(at: configs.firstIndex(of: webexConfig) ?? 0)
            hostConfigString = selectedHostConfigString()
        }
        comboBox.numberOfVisibleItems = 10
        
        tableView.rowHeight = 32
        textView.isAutomaticQuoteSubstitutionEnabled = false
        textView.isAutomaticDashSubstitutionEnabled = false
        textView.isAutomaticTextReplacementEnabled = false
        textView.smartInsertDeleteEnabled = false
        cardScrollView.translatesAutoresizingMaskIntoConstraints = true
    }
    
    // MARK: Private Methods
    private func renderCard(with jsonString: String) {
        guard !jsonString.isEmpty else { return }
        let result = AdaptiveCard.from(jsonString: jsonString)
        guard let card = result.getAdaptiveCard() else {
            print("RENDER FAILED")
            return
        }
        setupButtonConfig()
        setupInputFieldConfig()
        switch AdaptiveCard.parseHostConfig(from: hostConfigString) {
        case .success(let config):
            let cardView = AdaptiveCard.render(card: card, with: config, width: 350, actionDelegate: self, resourceResolver: self, config: RenderConfig(isDarkMode: darkTheme, buttonConfig: buttonConfig, supportsSchemeV1_3: false, hyperlinkColorConfig: .default, inputFieldConfig: inputFieldConfig, checkBoxButtonConfig: checkButtonConfig, radioButtonConfig: radioButtonConfig, localisedStringConfig: nil))
            
            if let renderedView = stackView.arrangedSubviews.first {
                renderedView.removeFromSuperview()
            }
            stackView.addArrangedSubview(cardView)
            
        case .failure(let error):
            print("Failure: \(error.localizedDescription)")
        }
    }
    
    private func selectedHostConfigString() -> String {
        var config: String = sampleHostConfig
        let selectedItem = comboBox.indexOfSelectedItem
        guard selectedItem >= 0 && selectedItem < configs.count else { return config }
        let path = "/hostconfigs/\(configs[selectedItem])"
        let parts = path.components(separatedBy: ".")
        // Check for dark theme in hostConfig file path
        darkTheme = path.contains("dark")
        guard let filepath = Bundle.main.path(forResource: parts[0], ofType: "json") else {
            print("File Not found: \(configs[selectedItem])")
            return config
        }
        do {
            config = try String(contentsOfFile: filepath)
        } catch {
            print(error)
        }
        return config
    }

    @IBAction private func handleRenderAction(_ sender: Any) {
        renderCard(with: textView.string)
    }
    
    private func setupButtonConfig() {
        let lightThemePositiveColor = NSColor.color(from: Constants.lightThemePositive) ?? .clear
        let lightThemePositiveHoverColor = NSColor.color(from: Constants.lightThemePositiveHover) ?? .clear
        let lightThemePositivePressedColor = NSColor.color(from: Constants.lightThemePositivePressed) ?? .clear
        let lightThemePositiveTextColor = NSColor.color(from: Constants.lightThemePositiveTextColor) ?? .clear
        let lightThemePositivePressedTextColor = NSColor.color(from: Constants.lightThemePositiveSelectedTextColor) ?? .clear
        let lightThemePositiveBorderColor = NSColor.color(from: Constants.lightThemePositiveBorder) ?? .clear
        let lightThemePositivePressedBorderColor = NSColor.color(from: Constants.lightThemePositivePressedBorderColor) ?? .clear
        
        let lightThemeDestructiveColor = NSColor.color(from: Constants.lightThemeDestructive) ?? .clear
        let lightThemeDestructiveHoverColor = NSColor.color(from: Constants.lightThemeDestructiveHover) ?? .clear
        let lightThemeDestructivePressedColor = NSColor.color(from: Constants.lightThemeDestructivePressed) ?? .clear
        let lightThemeDestructiveTextColor = NSColor.color(from: Constants.lightThemeDestructiveTextColor) ?? .clear
        let lightThemeDestructivePressedTextColor = NSColor.color(from: Constants.lightThemeDestructiveSelectedTextColor) ?? .clear
        let lightThemeDestructiveBorderColor = NSColor.color(from: Constants.lightThemeDestructiveBorder) ?? .clear
        let lightThemeDestructivePressedBorderColor = NSColor.color(from: Constants.lightThemeDestructivePressedBorderColor) ?? .clear
        
        let lightThemeDefaultColor = NSColor.color(from: Constants.lightThemeDefault) ?? .clear
        let lightThemeDefaultHoverColor = NSColor.color(from: Constants.lightThemeDefaultHover) ?? .clear
        let lightThemeDefaultPressedColor = NSColor.color(from: Constants.lightThemeDefaultPressed) ?? .clear
        let lightThemeDefaultTextColor = NSColor.color(from: Constants.lightThemeDefaultTextColor) ?? .clear
        let lightThemeDefaultPressedTextColor = NSColor.color(from: Constants.lightThemeDefaultSelectedTextColor) ?? .clear
        let lightThemeDefaultBorderColor = NSColor.color(from: Constants.lightThemeDefaultBorder) ?? .clear
        let lightThemeDefaultPressedBorderColor = NSColor.color(from: Constants.lightThemeDefaultPressedBorderColor) ?? .clear
        
        let darkThemePositiveColor = NSColor.color(from: Constants.darkThemePositive) ?? .clear
        let darkThemePositiveHoverColor = NSColor.color(from: Constants.darkThemePositiveHover) ?? .clear
        let darkThemePositivePressedColor = NSColor.color(from: Constants.darkThemePositivePressed) ?? .clear
        let darkThemePositiveTextColor = NSColor.color(from: Constants.darkThemePositiveTextColor) ?? .clear
        let darkThemePositivePressedTextColor = NSColor.color(from: Constants.darkThemePositiveSelectedTextColor) ?? .clear
        let darkThemePositiveBorderColor = NSColor.color(from: Constants.darkThemePositiveBorder) ?? .clear
        let darkThemePositivePressedBorderColor = NSColor.color(from: Constants.darkThemePositivePressedBorderColor) ?? .clear
        
        let darkThemeDestructiveColor = NSColor.color(from: Constants.darkThemeDestructive) ?? .clear
        let darkThemeDestructiveHoverColor = NSColor.color(from: Constants.darkThemeDestructiveHover) ?? .clear
        let darkThemeDestructivePressedColor = NSColor.color(from: Constants.darkThemeDestructivePressed) ?? .clear
        let darkThemeDestructiveTextColor = NSColor.color(from: Constants.darkThemeDestructiveTextColor) ?? .clear
        let darkThemeDestructivePressedTextColor = NSColor.color(from: Constants.darkThemeDestructiveSelectedTextColor) ?? .clear
        let darkThemeDestructiveBorderColor = NSColor.color(from: Constants.darkThemeDestructiveBorder) ?? .clear
        let darkThemeDestructivePressedBorderColor = NSColor.color(from: Constants.darkThemeDestructivePressedBorderColor) ?? .clear
        
        let darkThemeDefaultColor = NSColor.color(from: Constants.darkThemeDefault) ?? .clear
        let darkThemeDefaultHoverColor = NSColor.color(from: Constants.darkThemeDefaultHover) ?? .clear
        let darkThemeDefaultPressedColor = NSColor.color(from: Constants.darkThemeDefaultPressed) ?? .clear
        let darkThemeDefaultTextColor = NSColor.color(from: Constants.darkThemeDefaultTextColor) ?? .clear
        let darkThemeDefaultPressedTextColor = NSColor.color(from: Constants.darkThemeDefaultSelectedTextColor) ?? .clear
        let darkThemeDefaultBorderColor = NSColor.color(from: Constants.darkThemeDefaultBorder) ?? .clear
        let darkThemeDefaultPressedBorderColor = NSColor.color(from: Constants.darkThemeDefaultPressedBorderColor) ?? .clear
        
        let positive = ButtonColorConfig(buttonColor: darkTheme ? darkThemePositiveColor : lightThemePositiveColor, selectedButtonColor: darkTheme ? darkThemePositivePressedColor : lightThemePositivePressedColor, hoverButtonColor: darkTheme ? darkThemePositiveHoverColor : lightThemePositiveHoverColor, textColor: darkTheme ? darkThemePositiveTextColor : lightThemePositiveTextColor, selectedTextColor: darkTheme ? darkThemePositivePressedTextColor : lightThemePositivePressedTextColor, borderColor: darkTheme ? darkThemePositiveBorderColor : lightThemePositiveBorderColor, selectedBorderColor: darkTheme ? darkThemePositivePressedBorderColor : lightThemePositivePressedBorderColor, wantsBorder: true)
        let destructive = ButtonColorConfig(buttonColor: darkTheme ? darkThemeDestructiveColor : lightThemeDestructiveColor, selectedButtonColor: darkTheme ? darkThemeDestructivePressedColor : lightThemeDestructivePressedColor, hoverButtonColor: darkTheme ? darkThemeDestructiveHoverColor : lightThemeDestructiveHoverColor, textColor: darkTheme ? darkThemeDestructiveTextColor : lightThemeDestructiveTextColor, selectedTextColor: darkTheme ? darkThemeDestructivePressedTextColor : lightThemeDestructivePressedTextColor, borderColor: darkTheme ? darkThemeDestructiveBorderColor : lightThemeDestructiveBorderColor, selectedBorderColor: darkTheme ? darkThemeDestructivePressedBorderColor : lightThemeDestructivePressedBorderColor, wantsBorder: true)
        let `default` = ButtonColorConfig(buttonColor: darkTheme ? darkThemeDefaultColor : lightThemeDefaultColor, selectedButtonColor: darkTheme ? darkThemeDefaultPressedColor : lightThemeDefaultPressedColor, hoverButtonColor: darkTheme ? darkThemeDefaultHoverColor : lightThemeDefaultHoverColor, textColor: darkTheme ? darkThemeDefaultTextColor : lightThemeDefaultTextColor, selectedTextColor: darkTheme ? darkThemeDefaultPressedTextColor : lightThemeDefaultPressedTextColor, borderColor: darkTheme ? darkThemeDefaultBorderColor : lightThemeDefaultBorderColor, selectedBorderColor: darkTheme ? darkThemeDefaultPressedBorderColor : lightThemeDefaultPressedBorderColor, wantsBorder: false)
        let inline = ButtonColorConfig(buttonColor: darkTheme ? darkThemeDefaultColor : lightThemeDefaultColor, selectedButtonColor: darkTheme ? darkThemeDefaultPressedColor : lightThemeDefaultPressedColor, hoverButtonColor: darkTheme ? darkThemeDefaultHoverColor : lightThemeDefaultHoverColor, textColor: darkTheme ? darkThemeDefaultTextColor : lightThemeDefaultTextColor, selectedTextColor: darkTheme ? darkThemeDefaultPressedTextColor : lightThemeDefaultPressedTextColor, borderColor: darkTheme ? darkThemeDefaultBorderColor : lightThemeDefaultBorderColor, selectedBorderColor: darkTheme ? darkThemeDefaultPressedBorderColor : lightThemeDefaultPressedBorderColor, wantsBorder: false)
       
        let buttonConfig = ButtonConfig(positive: positive, destructive: destructive, default: `default`, inline: inline, font: NSFont.systemFont(ofSize: 14, weight: .semibold), buttonContentInsets: NSEdgeInsets(top: 5, left: 10, bottom: 5, right: 10), chevronUpImage: nil, chevronDownImage: nil)
        self.buttonConfig = buttonConfig
    }
    
    private func setupInputFieldConfig() {
        if darkTheme {
            let clearButtonimage = NSImage(named: "cancel_16_w")
            let calendarImage = NSImage(named: "calendar-month-dark")
            let clockImage = NSImage(named: "recents_20_w")
            inputFieldConfig = InputFieldConfig(height: 32, leftPadding: 8, rightPadding: 8, yPadding: 1, focusRingCornerRadius: 8, borderWidth: 1, wantsClearButton: true, clearButtonImage: clearButtonimage, calendarImage: calendarImage, clockImage: clockImage, font: .systemFont(ofSize: 14), highlightedColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.07), backgroundColor: NSColor(red: 0, green: 0, blue: 0, alpha: 1), borderColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.4), activeBorderColor: NSColor(red: 0.19, green: 0.38, blue: 0.77, alpha: 1), placeholderTextColor: NSColor(red: 1, green: 1, blue: 1, alpha: 0.7), multilineFieldInsets: NSEdgeInsets(top: 5, left: 10, bottom: 0, right: 0))
        } else {
            let clearButtonimage = NSImage(named: "cancel_16")
            let calendarImage = NSImage(named: "calendar-month-light")
            let clockImage = NSImage(named: "recents_20")
            inputFieldConfig = InputFieldConfig(height: 32, leftPadding: 8, rightPadding: 8, yPadding: 1, focusRingCornerRadius: 8, borderWidth: 1, wantsClearButton: true, clearButtonImage: clearButtonimage, calendarImage: calendarImage, clockImage: clockImage, font: .systemFont(ofSize: 14), highlightedColor: NSColor(red: 0, green: 0, blue: 0, alpha: 0.07), backgroundColor: NSColor(red: 1, green: 1, blue: 1, alpha: 1), borderColor: NSColor(red: 0, green: 0, blue: 0, alpha: 0.3), activeBorderColor: NSColor(red: 0.38, green: 0.61, blue: 0.97, alpha: 1), placeholderTextColor: NSColor(red: 0, green: 0, blue: 0, alpha: 0.6), multilineFieldInsets: NSEdgeInsets(top: 5, left: 10, bottom: 0, right: 0))
        }
    }
    
    private func setupRadioButton() {
            let onHoverIcon = NSImage(named: "radioHoverOn") ?? NSImage()
            let offHoverIcon = NSImage(named: "radioHoverOff") ?? NSImage()
            let onIcon = NSImage(named: "radioOn") ?? NSImage()
            let offIcon = NSImage(named: "radioOff") ?? NSImage()

            self.radioButtonConfig = ChoiceSetButtonConfig(selectedIcon: onIcon, normalIcon: offIcon, selectedHighlightedIcon: onHoverIcon, highlightedIcon: offHoverIcon, elementSpacing: 8)
        }

    private func setupCheckButton() {
            let onHoverIcon = NSImage(named: "checkHoverOn") ?? NSImage()
            let offHoverIcon = NSImage(named: "checkHoverOff") ?? NSImage()
            let onIcon = NSImage(named: "checkOn") ?? NSImage()
            let offIcon = NSImage(named: "checkOff") ?? NSImage()

            self.checkButtonConfig = ChoiceSetButtonConfig(selectedIcon: onIcon, normalIcon: offIcon, selectedHighlightedIcon: onHoverIcon, highlightedIcon: offHoverIcon, elementSpacing: 8)
        }
    // MARK: TableView Datasource
    func numberOfRows(in tableView: NSTableView) -> Int {
        return items.count
    }
    
    func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any? {
        return items[row]
    }
    
    func tableViewSelectionDidChange(_ notification: Notification) {
        let selectedRowNum = tableView.selectedRow
        guard selectedRowNum >= 0 && selectedRowNum < items.count else { return }
        let path = "/samples/\(items[selectedRowNum])"
        let parts = path.components(separatedBy: ".")
        guard let filepath = Bundle.main.path(forResource: parts[0], ofType: "json") else {
            print("File Not found: \(items[selectedRowNum])")
            return
        }
        do {
            let contents = try String(contentsOfFile: filepath)
            renderCard(with: contents)
            textView.string = contents
        } catch {
            print(error)
        }
    }
    
    // MARK: ComboBox
    func comboBox(_ comboBox: NSComboBox, objectValueForItemAt index: Int) -> Any? {
        return configs[index]
    }
    
    func numberOfItems(in comboBox: NSComboBox) -> Int {
        configs.count
    }
    
    func comboBoxSelectionDidChange(_ notification: Notification) {
        if (notification.object as? NSComboBox) != nil {
            hostConfigString = selectedHostConfigString()
            if !textView.string.isEmpty {
                renderCard(with: textView.string)
            }
        }
    }
}

extension RootViewController: AdaptiveCardActionDelegate {
    func adaptiveCard(_ adaptiveCard: NSView, didUpdateBoundsFrom oldValue: NSRect, to newValue: NSRect) {
        print("LAYOUT CHANGE: Height changed from \(oldValue.height) to \(newValue.height)")
    }
    
    func adaptiveCard(_ adaptiveCard: NSView, didSelectOpenURL urlString: String, actionView: NSView) {
        print("OPEN URL ACTION: \(urlString)")
        guard let url = URL(string: urlString) else { return }
        NSWorkspace.shared.open(url)
    }
    
    func adaptiveCard(_ adaptiveCard: NSView, didSubmitUserResponses: [String: Any], actionView: NSView) {
        let alert = NSAlert()
        guard let jsonData = try? JSONSerialization.data(withJSONObject: didSubmitUserResponses, options: [.prettyPrinted]), let jsonString = String(data: jsonData, encoding: .ascii) else {
            return
        }
        if let button = actionView as? NSButton {
            alert.messageText = button.title
        } else {
            alert.messageText = "Select Action"
        }
        alert.informativeText = jsonString
        alert.alertStyle = .informational
        alert.addButton(withTitle: "Ok")
        alert.runModal()
    }
    
    func adaptiveCard(_ adaptiveCard: NSView, didShowCardWith actionView: NSView, previousHeight: CGFloat, newHeight: CGFloat) {
        print("SHOW CARD ACTION: Height changed from \(previousHeight) to \(newHeight)")
    }
}

extension RootViewController: AdaptiveCardResourceResolver {
    func adaptiveCard(_ card: ImageResourceHandlerView, dimensionsForImageWith url: String) -> NSSize? {
        guard let dimensions = TestUtils.imageDimensionsDict[url] else {
            print("### ResourceResolver: returning nil for URL '\(url)'")
            return nil
        }
        return dimensions
    }
    
    func adaptiveCard(_ card: ImageResourceHandlerView, requestImageFor url: String) {
        guard let imageURL = URL(string: url) else {
            print("IMG ERR: URL '\(url)' not valid")
            return
        }
        DispatchQueue.global().async {
            if let data = try? Data(contentsOf: imageURL), let image = NSImage(data: data) {
                if TestUtils.imageDimensionsDict[url] == nil {
                    print("""
                    #####
                    ResourceResolver: Dimension for new image that's not in `imageDimensionsDict`
                        URL       : \(url)
                        DIMENSION : \(image.size)
                    #####
                    """)
                } else if let size = TestUtils.imageDimensionsDict[url], size != image.size {
                    print("""
                    #####
                    ResourceResolver: `imageDimensionsDict` Dimension mis-match!
                        URL          : \(url)
                        CACHED DIMEN : \(size)
                        DIMENSION    : \(image.size)
                    #####
                    """)
                }
                DispatchQueue.main.async {
                    card.setImage(image, for: url)
                }
            }
        }
    }
    
    func adaptiveCard(_ adaptiveCard: NSView, attributedStringFor htmlString: String) -> NSAttributedString? {
        return nil
    }
}
