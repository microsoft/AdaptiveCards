import AdaptiveCards_bridge

open class FakeHostConfig: ACSHostConfig {
    public var fontFamily: String?
    public var fontSizes: ACSFontSizesConfig?
    public var fontWeight: ACSFontWeightsConfig?
    public var fontTypes: ACSFontTypesDefinition?
    public var supportsInteractivity: Bool = false
    public var imageBaseUrl: String?
    public var imageSizes: ACSImageSizesConfig?
    public var image: ACSImageConfig?
    public var separator: ACSSeparatorConfig?
    public var spacing: ACSSpacingConfig?
    public var adaptiveCard: ACSAdaptiveCardConfig?
    public var imageSet: ACSImageSetConfig?
    public var factSet: ACSFactSetConfig?
    public var actions: ACSActionsConfig?
    public var containerStyles: ACSContainerStylesDefinition?
    public var media: ACSMediaConfig?
    public var inputs: ACSInputsConfig?

    open override func getFontType(_ fontType: ACSFontType) -> ACSFontTypeDefinition? {
        return nil
    }

    open override func getFontFamily(_ fontType: ACSFontType) -> String? {
        return nil
    }

    open override func getFontSize(_ fontType: ACSFontType, size: ACSTextSize) -> NSNumber? {
        return 0
    }

    open override func getFontWeight(_ fontType: ACSFontType, weight: ACSTextWeight) -> NSNumber? {
        return 0
    }

    open override func getBackgroundColor(_ style: ACSContainerStyle) -> String? {
        return nil
    }

    open override func getForegroundColor(_ style: ACSContainerStyle, color: ACSForegroundColor, isSubtle: Bool) -> String? {
        return nil
    }

    open override func getHighlightColor(_ style: ACSContainerStyle, color: ACSForegroundColor, isSubtle: Bool) -> String? {
        return nil
    }

    open override func getBorderColor(_ style: ACSContainerStyle) -> String? {
        return nil
    }

    open override func getBorderThickness(_ style: ACSContainerStyle) -> NSNumber? {
        return 0
    }

    open override func getFontFamily() -> String? {
        return fontFamily
    }

    open override func setFontFamily(_ value: String) {
        fontFamily = value
    }

    open override func getFontSizes() -> ACSFontSizesConfig? {
        return fontSizes
    }

    open override func setFontSizes(_ value: ACSFontSizesConfig) {
        fontSizes = value
    }

    open override func getFontWeights() -> ACSFontWeightsConfig? {
        return fontWeight
    }

    open override func setFontWeights(_ value: ACSFontWeightsConfig) {
        fontWeight = value
    }

    open override func getFontTypes() -> ACSFontTypesDefinition? {
        return fontTypes
    }

    open override func setFontTypes(_ value: ACSFontTypesDefinition) {
        fontTypes = value
    }

    open override func getSupportsInteractivity() -> Bool {
        return supportsInteractivity
    }

    open override func setSupportsInteractivity(_ value: Bool) {
        supportsInteractivity = value
    }

    open override func getImageBaseUrl() -> String? {
        return imageBaseUrl
    }

    open override func setImageBaseUrl(_ value: String) {
        imageBaseUrl = value
    }

    open override func getImageSizes() -> ACSImageSizesConfig? {
        return imageSizes
    }

    open override func setImageSizes(_ value: ACSImageSizesConfig) {
        imageSizes = value
    }

    open override func getImage() -> ACSImageConfig? {
        return image
    }

    open override func setImage(_ value: ACSImageConfig) {
        image = value
    }

    open override func getSeparator() -> ACSSeparatorConfig? {
        return separator
    }

    open override func setSeparator(_ value: ACSSeparatorConfig) {
        separator = value
    }

    open override func getSpacing() -> ACSSpacingConfig? {
        return spacing
    }

    open override func setSpacing(_ value: ACSSpacingConfig) {
        spacing = value
    }

    open override func getAdaptiveCard() -> ACSAdaptiveCardConfig? {
        return adaptiveCard
    }

    open override func setAdaptiveCard(_ value: ACSAdaptiveCardConfig) {
        adaptiveCard = value
    }

    open override func getImageSet() -> ACSImageSetConfig? {
        return imageSet
    }

    open override func setImageSet(_ value: ACSImageSetConfig) {
        imageSet = value
    }

    open override func getFactSet() -> ACSFactSetConfig? {
        return factSet
    }

    open override func setFactSet(_ value: ACSFactSetConfig) {
        factSet = value
    }

    open override func getActions() -> ACSActionsConfig? {
        return actions
    }

    open override func setActions(_ value: ACSActionsConfig) {
        actions = value
    }

    open override func getContainerStyles() -> ACSContainerStylesDefinition? {
        return containerStyles
    }

    open override func setContainerStyles(_ value: ACSContainerStylesDefinition) {
        containerStyles = value
    }

    open override func getMedia() -> ACSMediaConfig? {
        return media
    }

    open override func setMedia(_ value: ACSMediaConfig) {
        media = value
    }

    open override func getInputs() -> ACSInputsConfig? {
        return inputs
    }

    open override func setInputs(_ value: ACSInputsConfig) {
        inputs = value
    }
}

extension FakeHostConfig {
    static func make(fontFamily: String? = nil, fontSizes: ACSFontSizesConfig? = nil, fontWeight: ACSFontWeightsConfig? = nil, fontTypes: ACSFontTypesDefinition? = nil, supportsInteractivity: Bool = false, imageBaseUrl: String? = nil, imageSizes: ACSImageSizesConfig? = nil, image: ACSImageConfig? = nil, separator: ACSSeparatorConfig? = nil, spacing: ACSSpacingConfig? = nil, adaptiveCard: ACSAdaptiveCardConfig? = nil, imageSet: ACSImageSetConfig? = nil, factSet: ACSFactSetConfig? = nil, actions: ACSActionsConfig? = nil, containerStyles: ACSContainerStylesDefinition? = nil, media: ACSMediaConfig? = nil, inputs: ACSInputsConfig? = nil) -> FakeHostConfig {
        let fakeConfig = FakeHostConfig()
        fakeConfig.fontFamily = fontFamily
        fakeConfig.fontSizes = fontSizes
        fakeConfig.fontWeight = fontWeight
        fakeConfig.fontTypes = fontTypes
        fakeConfig.supportsInteractivity = supportsInteractivity
        fakeConfig.imageBaseUrl = imageBaseUrl
        fakeConfig.imageSizes = imageSizes
        fakeConfig.image = image
        fakeConfig.separator = separator
        fakeConfig.spacing = spacing
        fakeConfig.adaptiveCard = adaptiveCard
        fakeConfig.imageSet = imageSet
        fakeConfig.factSet = factSet
        fakeConfig.actions = actions
        fakeConfig.containerStyles = containerStyles
        fakeConfig.media = media
        fakeConfig.inputs = inputs
        return fakeConfig
    }
}
