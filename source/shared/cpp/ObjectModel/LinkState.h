
class LinkState
{
public:
    LinkState() : m_look_behind(0), m_state(LinkInit), 
        m_current_delimiter_type(None), m_IsWhiteSpaceDetected(false) {};
    bool IsItNewToken() const { return m_state == LinkTextOpening; }
    bool IsItLink() const { return m_state == LinkDetected; }
    void UpdateState(int ch);
private:
    enum LinkStateEnum
    {
        LinkInit,
        LinkTextOpening = 0x1,
        LinkTextDetecting,
        LinkTextClosing = 0x4,
        LinkDestinationOpening,
        LinkDetected,
    };
    enum DelimiterType
    {
        None,
        Bracket,
        Parenthesis,
    };

    int m_look_behind;
    int m_state;
    int m_current_delimiter_type;
    bool m_IsWhiteSpaceDetected;
    void UpdateWithOpeningSqureBracket(int ch);
    void UpdateWithClosingSqureBracket(int ch);
    void UpdateWithEverythingElse(int ch);
    void UpdateWithWhiteSpace(int ch);
    void UpdateWithOpeningParenthesis(int ch);
    void UpdateWithClosingParenthesis(int ch);
};

