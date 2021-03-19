import AdaptiveCards
import Cocoa

class RootViewController: NSViewController, NSTableViewDelegate, NSTableViewDataSource, NSComboBoxDelegate, NSComboBoxDataSource {
    @IBOutlet var tableView: NSTableView!
    @IBOutlet var stackView: NSStackView!
    @IBOutlet var textView: NSTextView!
    @IBOutlet var comboBox: NSComboBox!
    
    private var items: [String] = []
    private var configs: [String] = []
    private var hostConfigString = sampleHostConfig // default config string
    private let webexConfig: String = "webex_light_config.json"
    private var darkTheme: Bool = false
    
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
    }
    
    // MARK: Private Methods
    private func renderCard(with jsonString: String) {
        guard !jsonString.isEmpty else { return }
        let result = AdaptiveCard.from(jsonString: jsonString)
        guard let card = result.getAdaptiveCard() else {
            print("RENDER FAILED")
            return
        }
        print("ELEMENTS:")
        card.getBody().forEach { print($0.getTypeString() ?? "nil") }
        card.getBody().forEach { print(type(of: $0)) }

        switch AdaptiveCard.parseHostConfig(from: hostConfigString) {
        case .success(let config):
            print("PARSED HOSTCONFIG")
            print("Font family - \(config.getFontFamily() ?? "nil")")
            
            let cardView = AdaptiveCard.render(card: card, with: config, width: 335, actionDelegate: self, resourceResolver: self)
            // This changes the appearance of the native components depending on the hostConfig
            if darkTheme {
                if #available(OSX 10.14, *) {
                    cardView.appearance = NSAppearance(named: .darkAqua)
                } else {
                    // Fallback on earlier versions
                    cardView.appearance = NSAppearance(named: .aqua)
                }
            }
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
    func adaptiveCard(_ adaptiveCard: NSView, didSelectOpenURL urlString: String, button: NSButton) {
        print("OPEN URL ACTION: \(urlString)")
        guard let url = URL(string: urlString) else { return }
        NSWorkspace.shared.open(url)
    }
}

extension RootViewController: AdaptiveCardResourceResolver {
    func adaptiveCard(_ card: ImageResourceHandlerView, dimensionsForImageWith key: ResourceKey) -> NSSize? {
        return nil
    }
    
    func adaptiveCard(_ card: ImageResourceHandlerView, requestImageFor key: ResourceKey) {
        guard let imageURL = URL(string: key.url) else {
            return
        }
        DispatchQueue.global().async { [weak self] in
            if let data = try? Data(contentsOf: imageURL) {
                if let image = NSImage(data: data) {
                    DispatchQueue.main.async {
                        card.setImage(image, for: key)
                    }
                }
            }
        }
    }
}
