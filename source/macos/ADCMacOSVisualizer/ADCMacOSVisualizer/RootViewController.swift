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
    private let webexConfig: String = "webex_light_config.json"
    private var darkTheme = false
    private var buttonConfig: ButtonConfig = .default
    
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
        switch AdaptiveCard.parseHostConfig(from: hostConfigString) {
        case .success(let config):
            let cardView = AdaptiveCard.render(card: card, with: config, width: 350, actionDelegate: self, resourceResolver: self, config: RenderConfig(isDarkMode: darkTheme, buttonConfig: buttonConfig, supportsSchemeV1_3: false, hyperlinkColorConfig: .default ))
            
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
        let lightThemePositivePressedColor = NSColor.color(from: Constants.lightThemePositivePressed) ?? .clear
        let lightThemeDestructiveColor = NSColor.color(from: Constants.lightThemeDestructive) ?? .clear
        let lightThemeDestructivePressedColor = NSColor.color(from: Constants.lightThemeDestructivePressed) ?? .clear
        let lightThemeDefaultColor = NSColor.color(from: Constants.lightThemeDefault) ?? .clear
        let lightThemeDefaultPressedColor = NSColor.color(from: Constants.lightThemeDefaultPressed) ?? .clear
        let lightThemeInlineColor = NSColor.color(from: Constants.lightThemeInline) ?? .clear
        let lightThemeInlinePressedColor = NSColor.color(from: Constants.lightThemeInlinePressed) ?? .clear
        let darkThemeDefaultColor = NSColor.color(from: Constants.darkThemePrimary) ?? .clear
        let darkThemeDefaultPressedColor = NSColor.color(from: Constants.darkThemePressed) ?? .clear
        let darkThemePositiveColor = NSColor.color(from: Constants.darkThemePositive) ?? .clear
        let darkThemeDestructiveColor = NSColor.color(from: Constants.darkThemeDestructive) ?? .clear
        let darkThemeDestructiveHover = NSColor.color(from: Constants.darkThemeDestructiveHover) ?? .clear
        let darkThemeDestructivePressed = NSColor.color(from: Constants.darkThemeDestructivePressed) ?? .clear
        
        let positive = ButtonColorConfig(buttonColor: darkTheme ? darkThemePositiveColor : .white, selectedButtonColor: lightThemePositivePressedColor, hoverButtonColor: lightThemePositiveColor, textColor: darkTheme ? .white : lightThemePositiveColor, selectedTextColor: .white, borderColor: darkTheme ? darkThemePositiveColor : lightThemePositiveColor, selectedBorderColor: lightThemePositivePressedColor)
        let destructive = ButtonColorConfig(buttonColor: darkTheme ? darkThemeDestructiveColor : .white, selectedButtonColor: darkTheme ? darkThemeDestructivePressed : lightThemeDestructivePressedColor, hoverButtonColor: darkTheme ? darkThemeDestructiveHover : lightThemeDestructiveColor, textColor: darkTheme ? .white : lightThemeDestructiveColor, selectedTextColor: .white, borderColor: darkTheme ? darkThemeDestructiveColor : lightThemeDestructiveColor, selectedBorderColor: darkTheme ? darkThemeDestructivePressed : lightThemeDestructivePressedColor)
        let `default` = ButtonColorConfig(buttonColor: darkTheme ? darkThemeDefaultColor : .white, selectedButtonColor: darkTheme ? darkThemeDefaultPressedColor : lightThemeDefaultPressedColor, hoverButtonColor: darkTheme ? darkThemeDefaultPressedColor : lightThemeDefaultColor, textColor: darkTheme ? .white : lightThemeDefaultColor, selectedTextColor: .white, borderColor: darkTheme ? darkThemeDefaultColor : lightThemeDefaultColor, selectedBorderColor: darkTheme ? darkThemeDefaultPressedColor : lightThemeDefaultPressedColor)
        let inline = ButtonColorConfig(buttonColor: .clear, selectedButtonColor: lightThemeInlinePressedColor, hoverButtonColor: lightThemeInlineColor, textColor: .black, selectedTextColor: .black, borderColor: .clear, selectedBorderColor: .clear)
       
        let buttonConfig = ButtonConfig(positive: positive, destructive: destructive, default: `default`, inline: inline)
        self.buttonConfig = buttonConfig
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
