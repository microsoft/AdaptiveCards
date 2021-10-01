// Generated from AdaptiveCardsTemplateLexer.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AdaptiveCardsTemplateLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		COMMA=1, COLON=2, LCB=3, RCB=4, LSB=5, RSB=6, TRUE=7, FALSE=8, NULL=9, 
		StringDeclOpen=10, NUMBER=11, WS=12, CLOSE=13, TEMPLATEDATA=14, TEMPLATEWHEN=15, 
		JPATH=16, TEMPLATELITERAL=17, TEMPLATEROOT=18, STRING=19;
	public static final int
		INSIDE=1;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE", "INSIDE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"COMMA", "COLON", "LCB", "RCB", "LSB", "RSB", "TRUE", "FALSE", "NULL", 
			"StringDeclOpen", "NUMBER", "INT", "EXP", "WS", "CLOSE", "TEMPLATEDATA", 
			"TEMPLATEWHEN", "JPATH", "TEMPLATELITERAL", "TEMPLATEROOT", "STRING", 
			"ESC", "UNICODE", "HEX", "SAFECODEPOINT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "','", "':'", "'{'", "'}'", "'['", "']'", "'true'", "'false'", 
			"'null'", null, null, null, null, "'$data'", "'$when'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "COMMA", "COLON", "LCB", "RCB", "LSB", "RSB", "TRUE", "FALSE", 
			"NULL", "StringDeclOpen", "NUMBER", "WS", "CLOSE", "TEMPLATEDATA", "TEMPLATEWHEN", 
			"JPATH", "TEMPLATELITERAL", "TEMPLATEROOT", "STRING"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public AdaptiveCardsTemplateLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "AdaptiveCardsTemplateLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\25\u00c6\b\1\b\1"+
		"\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t"+
		"\n\4\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4"+
		"\22\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4"+
		"\31\t\31\4\32\t\32\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b"+
		"\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\13\3\13"+
		"\3\13\3\13\3\f\5\fX\n\f\3\f\3\f\3\f\6\f]\n\f\r\f\16\f^\5\fa\n\f\3\f\5"+
		"\fd\n\f\3\r\3\r\3\r\7\ri\n\r\f\r\16\rl\13\r\5\rn\n\r\3\16\3\16\5\16r\n"+
		"\16\3\16\3\16\3\17\6\17w\n\17\r\17\16\17x\3\17\3\17\3\20\3\20\3\20\3\20"+
		"\3\21\3\21\3\21\3\21\3\21\3\21\3\22\3\22\3\22\3\22\3\22\3\22\3\23\3\23"+
		"\3\23\3\23\3\23\3\23\6\23\u0093\n\23\r\23\16\23\u0094\3\23\3\23\3\24\3"+
		"\24\3\24\3\24\3\24\7\24\u009e\n\24\f\24\16\24\u00a1\13\24\3\24\3\24\3"+
		"\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\26\3\26\6\26\u00b1"+
		"\n\26\r\26\16\26\u00b2\3\26\5\26\u00b6\n\26\3\27\3\27\3\27\5\27\u00bb"+
		"\n\27\3\30\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3\32\3\32\3\u009f\2\33\4"+
		"\3\6\4\b\5\n\6\f\7\16\b\20\t\22\n\24\13\26\f\30\r\32\2\34\2\36\16 \17"+
		"\"\20$\21&\22(\23*\24,\25.\2\60\2\62\2\64\2\4\2\3\13\3\2\62;\3\2\63;\4"+
		"\2GGgg\4\2--//\5\2\13\f\17\17\"\"\3\2$$\n\2$$\61\61^^ddhhppttvv\5\2\62"+
		";CHch\6\2\2!$$&&^^\2\u00ce\2\4\3\2\2\2\2\6\3\2\2\2\2\b\3\2\2\2\2\n\3\2"+
		"\2\2\2\f\3\2\2\2\2\16\3\2\2\2\2\20\3\2\2\2\2\22\3\2\2\2\2\24\3\2\2\2\2"+
		"\26\3\2\2\2\2\30\3\2\2\2\2\36\3\2\2\2\3 \3\2\2\2\3\"\3\2\2\2\3$\3\2\2"+
		"\2\3&\3\2\2\2\3(\3\2\2\2\3*\3\2\2\2\3,\3\2\2\2\4\66\3\2\2\2\68\3\2\2\2"+
		"\b:\3\2\2\2\n<\3\2\2\2\f>\3\2\2\2\16@\3\2\2\2\20B\3\2\2\2\22G\3\2\2\2"+
		"\24M\3\2\2\2\26R\3\2\2\2\30W\3\2\2\2\32m\3\2\2\2\34o\3\2\2\2\36v\3\2\2"+
		"\2 |\3\2\2\2\"\u0080\3\2\2\2$\u0086\3\2\2\2&\u0092\3\2\2\2(\u0098\3\2"+
		"\2\2*\u00a4\3\2\2\2,\u00b5\3\2\2\2.\u00b7\3\2\2\2\60\u00bc\3\2\2\2\62"+
		"\u00c2\3\2\2\2\64\u00c4\3\2\2\2\66\67\7.\2\2\67\5\3\2\2\289\7<\2\29\7"+
		"\3\2\2\2:;\7}\2\2;\t\3\2\2\2<=\7\177\2\2=\13\3\2\2\2>?\7]\2\2?\r\3\2\2"+
		"\2@A\7_\2\2A\17\3\2\2\2BC\7v\2\2CD\7t\2\2DE\7w\2\2EF\7g\2\2F\21\3\2\2"+
		"\2GH\7h\2\2HI\7c\2\2IJ\7n\2\2JK\7u\2\2KL\7g\2\2L\23\3\2\2\2MN\7p\2\2N"+
		"O\7w\2\2OP\7n\2\2PQ\7n\2\2Q\25\3\2\2\2RS\7$\2\2ST\3\2\2\2TU\b\13\2\2U"+
		"\27\3\2\2\2VX\7/\2\2WV\3\2\2\2WX\3\2\2\2XY\3\2\2\2Y`\5\32\r\2Z\\\7\60"+
		"\2\2[]\t\2\2\2\\[\3\2\2\2]^\3\2\2\2^\\\3\2\2\2^_\3\2\2\2_a\3\2\2\2`Z\3"+
		"\2\2\2`a\3\2\2\2ac\3\2\2\2bd\5\34\16\2cb\3\2\2\2cd\3\2\2\2d\31\3\2\2\2"+
		"en\7\62\2\2fj\t\3\2\2gi\t\2\2\2hg\3\2\2\2il\3\2\2\2jh\3\2\2\2jk\3\2\2"+
		"\2kn\3\2\2\2lj\3\2\2\2me\3\2\2\2mf\3\2\2\2n\33\3\2\2\2oq\t\4\2\2pr\t\5"+
		"\2\2qp\3\2\2\2qr\3\2\2\2rs\3\2\2\2st\5\32\r\2t\35\3\2\2\2uw\t\6\2\2vu"+
		"\3\2\2\2wx\3\2\2\2xv\3\2\2\2xy\3\2\2\2yz\3\2\2\2z{\b\17\3\2{\37\3\2\2"+
		"\2|}\7$\2\2}~\3\2\2\2~\177\b\20\4\2\177!\3\2\2\2\u0080\u0081\7&\2\2\u0081"+
		"\u0082\7f\2\2\u0082\u0083\7c\2\2\u0083\u0084\7v\2\2\u0084\u0085\7c\2\2"+
		"\u0085#\3\2\2\2\u0086\u0087\7&\2\2\u0087\u0088\7y\2\2\u0088\u0089\7j\2"+
		"\2\u0089\u008a\7g\2\2\u008a\u008b\7p\2\2\u008b%\3\2\2\2\u008c\u008d\7"+
		"\60\2\2\u008d\u0093\5,\26\2\u008e\u008f\7]\2\2\u008f\u0090\5\32\r\2\u0090"+
		"\u0091\7_\2\2\u0091\u0093\3\2\2\2\u0092\u008c\3\2\2\2\u0092\u008e\3\2"+
		"\2\2\u0093\u0094\3\2\2\2\u0094\u0092\3\2\2\2\u0094\u0095\3\2\2\2\u0095"+
		"\u0096\3\2\2\2\u0096\u0097\7\177\2\2\u0097\'\3\2\2\2\u0098\u0099\7&\2"+
		"\2\u0099\u009a\7}\2\2\u009a\u009f\3\2\2\2\u009b\u009e\n\7\2\2\u009c\u009e"+
		"\5.\27\2\u009d\u009b\3\2\2\2\u009d\u009c\3\2\2\2\u009e\u00a1\3\2\2\2\u009f"+
		"\u00a0\3\2\2\2\u009f\u009d\3\2\2\2\u00a0\u00a2\3\2\2\2\u00a1\u009f\3\2"+
		"\2\2\u00a2\u00a3\7\177\2\2\u00a3)\3\2\2\2\u00a4\u00a5\7&\2\2\u00a5\u00a6"+
		"\7}\2\2\u00a6\u00a7\7&\2\2\u00a7\u00a8\7t\2\2\u00a8\u00a9\7q\2\2\u00a9"+
		"\u00aa\7q\2\2\u00aa\u00ab\7v\2\2\u00ab\u00ac\3\2\2\2\u00ac\u00ad\5&\23"+
		"\2\u00ad+\3\2\2\2\u00ae\u00b1\5.\27\2\u00af\u00b1\5\64\32\2\u00b0\u00ae"+
		"\3\2\2\2\u00b0\u00af\3\2\2\2\u00b1\u00b2\3\2\2\2\u00b2\u00b0\3\2\2\2\u00b2"+
		"\u00b3\3\2\2\2\u00b3\u00b6\3\2\2\2\u00b4\u00b6\7&\2\2\u00b5\u00b0\3\2"+
		"\2\2\u00b5\u00b4\3\2\2\2\u00b6-\3\2\2\2\u00b7\u00ba\7^\2\2\u00b8\u00bb"+
		"\t\b\2\2\u00b9\u00bb\5\60\30\2\u00ba\u00b8\3\2\2\2\u00ba\u00b9\3\2\2\2"+
		"\u00bb/\3\2\2\2\u00bc\u00bd\7w\2\2\u00bd\u00be\5\62\31\2\u00be\u00bf\5"+
		"\62\31\2\u00bf\u00c0\5\62\31\2\u00c0\u00c1\5\62\31\2\u00c1\61\3\2\2\2"+
		"\u00c2\u00c3\t\t\2\2\u00c3\63\3\2\2\2\u00c4\u00c5\n\n\2\2\u00c5\65\3\2"+
		"\2\2\24\2\3W^`cjmqx\u0092\u0094\u009d\u009f\u00b0\u00b2\u00b5\u00ba\5"+
		"\7\3\2\b\2\2\6\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}