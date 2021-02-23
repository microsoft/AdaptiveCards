import AdaptiveCards_bridge

class FakeRichTextBlock: ACSRichTextBlock {
    public var horizontalAlignment: ACSHorizontalAlignment?
    public var inlines: [ACSInline]?

    
    open override func getHorizontalAlignment() -> ACSHorizontalAlignment {
        return horizontalAlignment ?? ACSHorizontalAlignment.left
    }
    
    override func setHorizontalAlignment(_ value: ACSHorizontalAlignment) {
        horizontalAlignment = value
    }
    
    open override func getInlines() -> [ACSInline] {
        return inlines ?? []
    }
}

extension FakeRichTextBlock {
    static func make(textRun: FakeTextRun = FakeTextRun.make(), horizontalAlignment: ACSHorizontalAlignment = ACSHorizontalAlignment.left) -> FakeRichTextBlock {
        let fakeRichTextBlock = FakeRichTextBlock()
        fakeRichTextBlock.inlines = [textRun as ACSInline]
        fakeRichTextBlock.horizontalAlignment = horizontalAlignment
        return fakeRichTextBlock
    }
}

class FakeInline: ACSInline {
    static func make() -> FakeInline {
        return FakeInline()
    }
}

class FakeTextRun: ACSTextRun {
    var text: String?
    var language: String? = "EN"
    var textSize: ACSTextSize?
    var textWeight: ACSTextWeight?
    var fontType: ACSFontType?
    var textColor: ACSForegroundColor?
    var subtle: Bool?
    var italic: Bool?
    var strikethrough: Bool?
    var highlight: Bool?
    var underline: Bool?

    override func setText(_ value: String) {
        text = value
    }
    
    override func getText() -> String? {
        return text ?? ""
    }
    
    override func getLanguage() -> String? {
        return language
    }
    
    override func setLanguage(_ value: String) {
        language = value
    }
    
    override func getTextSize() -> ACSTextSize {
        return textSize ?? ACSTextSize.default
    }
    
    override func setTextSize(_ value: ACSTextSize) {
        textSize = value
    }
    
    override func getTextWeight() -> ACSTextWeight {
        return textWeight ?? ACSTextWeight.default
    }
    
    override func setTextWeight(_ value: ACSTextWeight) {
        textWeight = value
    }
    
    override func getFontType() -> ACSFontType {
        return fontType ?? ACSFontType.default
    }
    
    override func setFontType(_ value: ACSFontType) {
        fontType = value
    }
    
    override func getTextColor() -> ACSForegroundColor {
        return textColor ?? ACSForegroundColor.default
    }
    
    override func setTextColor(_ value: ACSForegroundColor) {
        textColor = value
    }
    
    override func getIsSubtle() -> Bool {
        subtle ?? false
    }
    
    override func setIsSubtle(_ value: Bool) {
        subtle = value
    }
    
    override func getItalic() -> Bool {
        return italic ?? false
    }
    
    override func setItalic(_ value: Bool) {
        italic = value
    }
    
    override func getStrikethrough() -> Bool {
        return strikethrough ?? false
    }
    
    override func setStrikethrough(_ value: Bool) {
        strikethrough = value
    }
    
    override func getHighlight() -> Bool {
        return highlight ?? false
    }
    
    override func setHighlight(_ value: Bool) {
        highlight = value
    }
    
    override func getUnderline() -> Bool {
        return underline ?? false
    }
    
    override func setUnderline(_ value: Bool) {
        underline = value
    }
    
    static func make(text: String? = "",
                     textSize: ACSTextSize? = ACSTextSize.default,
                     textWeight: ACSTextWeight = ACSTextWeight.default,
                     fontType: ACSFontType = ACSFontType.default,
                     textColor: ACSForegroundColor? = ACSForegroundColor.accent,
                     subtle: Bool? = false,
                     italic: Bool? = false,
                     strikethrough: Bool? = false,
                     highlight: Bool? = false,
                     underline: Bool? = false) -> FakeTextRun {
        let fakeTextRun = FakeTextRun()
        fakeTextRun.text = text
        fakeTextRun.textSize = textSize
        fakeTextRun.textWeight = textWeight
        fakeTextRun.fontType = fontType
        fakeTextRun.textColor = textColor
        fakeTextRun.subtle = subtle
        fakeTextRun.italic = italic
        fakeTextRun.strikethrough = strikethrough
        fakeTextRun.highlight = highlight
        fakeTextRun.underline = underline
        return fakeTextRun
    }
}

