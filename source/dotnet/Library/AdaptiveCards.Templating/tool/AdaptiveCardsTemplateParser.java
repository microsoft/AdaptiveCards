// Generated from AdaptiveCardsTemplateParser.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AdaptiveCardsTemplateParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		COMMA=1, COLON=2, LCB=3, RCB=4, LSB=5, RSB=6, TRUE=7, FALSE=8, NULL=9, 
		StringDeclOpen=10, NUMBER=11, WS=12, CLOSE=13, TEMPLATEDATA=14, TEMPLATEWHEN=15, 
		JPATH=16, TEMPLATELITERAL=17, TEMPLATEROOT=18, STRING=19;
	public static final int
		RULE_json = 0, RULE_obj = 1, RULE_pair = 2, RULE_array = 3, RULE_value = 4, 
		RULE_templateString = 5, RULE_templateRoot = 6, RULE_templateExpression = 7;
	private static String[] makeRuleNames() {
		return new String[] {
			"json", "obj", "pair", "array", "value", "templateString", "templateRoot", 
			"templateExpression"
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

	@Override
	public String getGrammarFileName() { return "AdaptiveCardsTemplateParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public AdaptiveCardsTemplateParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class JsonContext extends ParserRuleContext {
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public JsonContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_json; }
	}

	public final JsonContext json() throws RecognitionException {
		JsonContext _localctx = new JsonContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_json);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(16);
			value();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ObjContext extends ParserRuleContext {
		public TerminalNode LCB() { return getToken(AdaptiveCardsTemplateParser.LCB, 0); }
		public List<PairContext> pair() {
			return getRuleContexts(PairContext.class);
		}
		public PairContext pair(int i) {
			return getRuleContext(PairContext.class,i);
		}
		public TerminalNode RCB() { return getToken(AdaptiveCardsTemplateParser.RCB, 0); }
		public List<TerminalNode> COMMA() { return getTokens(AdaptiveCardsTemplateParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(AdaptiveCardsTemplateParser.COMMA, i);
		}
		public ObjContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_obj; }
	}

	public final ObjContext obj() throws RecognitionException {
		ObjContext _localctx = new ObjContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_obj);
		int _la;
		try {
			setState(31);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(18);
				match(LCB);
				setState(19);
				pair();
				setState(24);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(20);
					match(COMMA);
					setState(21);
					pair();
					}
					}
					setState(26);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(27);
				match(RCB);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(29);
				match(LCB);
				setState(30);
				match(RCB);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PairContext extends ParserRuleContext {
		public PairContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pair; }
	 
		public PairContext() { }
		public void copyFrom(PairContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class TemplateWhenContext extends PairContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TerminalNode TEMPLATEWHEN() { return getToken(AdaptiveCardsTemplateParser.TEMPLATEWHEN, 0); }
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public TerminalNode COLON() { return getToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public TemplateExpressionContext templateExpression() {
			return getRuleContext(TemplateExpressionContext.class,0);
		}
		public TemplateWhenContext(PairContext ctx) { copyFrom(ctx); }
	}
	public static class JsonPairContext extends PairContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public TerminalNode COLON() { return getToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public List<TerminalNode> STRING() { return getTokens(AdaptiveCardsTemplateParser.STRING); }
		public TerminalNode STRING(int i) {
			return getToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public JsonPairContext(PairContext ctx) { copyFrom(ctx); }
	}
	public static class TemplateDataContext extends PairContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TerminalNode TEMPLATEDATA() { return getToken(AdaptiveCardsTemplateParser.TEMPLATEDATA, 0); }
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public TerminalNode COLON() { return getToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public ValueContext value() {
			return getRuleContext(ValueContext.class,0);
		}
		public TemplateDataContext(PairContext ctx) { copyFrom(ctx); }
	}
	public static class TemplateRootDataContext extends PairContext {
		public List<TerminalNode> StringDeclOpen() { return getTokens(AdaptiveCardsTemplateParser.StringDeclOpen); }
		public TerminalNode StringDeclOpen(int i) {
			return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, i);
		}
		public TerminalNode TEMPLATEDATA() { return getToken(AdaptiveCardsTemplateParser.TEMPLATEDATA, 0); }
		public List<TerminalNode> CLOSE() { return getTokens(AdaptiveCardsTemplateParser.CLOSE); }
		public TerminalNode CLOSE(int i) {
			return getToken(AdaptiveCardsTemplateParser.CLOSE, i);
		}
		public TerminalNode COLON() { return getToken(AdaptiveCardsTemplateParser.COLON, 0); }
		public TemplateRootContext templateRoot() {
			return getRuleContext(TemplateRootContext.class,0);
		}
		public TemplateRootDataContext(PairContext ctx) { copyFrom(ctx); }
	}

	public final PairContext pair() throws RecognitionException {
		PairContext _localctx = new PairContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_pair);
		int _la;
		try {
			setState(61);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				_localctx = new JsonPairContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(33);
				match(StringDeclOpen);
				setState(37);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==STRING) {
					{
					{
					setState(34);
					match(STRING);
					}
					}
					setState(39);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(40);
				match(CLOSE);
				setState(41);
				match(COLON);
				setState(42);
				value();
				}
				break;
			case 2:
				_localctx = new TemplateRootDataContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(43);
				match(StringDeclOpen);
				setState(44);
				match(TEMPLATEDATA);
				setState(45);
				match(CLOSE);
				setState(46);
				match(COLON);
				setState(47);
				match(StringDeclOpen);
				setState(48);
				templateRoot();
				setState(49);
				match(CLOSE);
				}
				break;
			case 3:
				_localctx = new TemplateDataContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(51);
				match(StringDeclOpen);
				setState(52);
				match(TEMPLATEDATA);
				setState(53);
				match(CLOSE);
				setState(54);
				match(COLON);
				setState(55);
				value();
				}
				break;
			case 4:
				_localctx = new TemplateWhenContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(56);
				match(StringDeclOpen);
				setState(57);
				match(TEMPLATEWHEN);
				setState(58);
				match(CLOSE);
				setState(59);
				match(COLON);
				setState(60);
				templateExpression();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArrayContext extends ParserRuleContext {
		public TerminalNode LSB() { return getToken(AdaptiveCardsTemplateParser.LSB, 0); }
		public List<ValueContext> value() {
			return getRuleContexts(ValueContext.class);
		}
		public ValueContext value(int i) {
			return getRuleContext(ValueContext.class,i);
		}
		public TerminalNode RSB() { return getToken(AdaptiveCardsTemplateParser.RSB, 0); }
		public List<TerminalNode> COMMA() { return getTokens(AdaptiveCardsTemplateParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(AdaptiveCardsTemplateParser.COMMA, i);
		}
		public ArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_array; }
	}

	public final ArrayContext array() throws RecognitionException {
		ArrayContext _localctx = new ArrayContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_array);
		int _la;
		try {
			setState(76);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(63);
				match(LSB);
				setState(64);
				value();
				setState(69);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(65);
					match(COMMA);
					setState(66);
					value();
					}
					}
					setState(71);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(72);
				match(RSB);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(74);
				match(LSB);
				setState(75);
				match(RSB);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValueContext extends ParserRuleContext {
		public ValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_value; }
	 
		public ValueContext() { }
		public void copyFrom(ValueContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ValueObjectContext extends ValueContext {
		public ObjContext obj() {
			return getRuleContext(ObjContext.class,0);
		}
		public ValueObjectContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueNullContext extends ValueContext {
		public TerminalNode NULL() { return getToken(AdaptiveCardsTemplateParser.NULL, 0); }
		public ValueNullContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueTemplateStringContext extends ValueContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public List<TemplateStringContext> templateString() {
			return getRuleContexts(TemplateStringContext.class);
		}
		public TemplateStringContext templateString(int i) {
			return getRuleContext(TemplateStringContext.class,i);
		}
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateStringContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueNumberContext extends ValueContext {
		public TerminalNode NUMBER() { return getToken(AdaptiveCardsTemplateParser.NUMBER, 0); }
		public ValueNumberContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueTrueContext extends ValueContext {
		public TerminalNode TRUE() { return getToken(AdaptiveCardsTemplateParser.TRUE, 0); }
		public ValueTrueContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueFalseContext extends ValueContext {
		public TerminalNode FALSE() { return getToken(AdaptiveCardsTemplateParser.FALSE, 0); }
		public ValueFalseContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueStringContext extends ValueContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public List<TerminalNode> STRING() { return getTokens(AdaptiveCardsTemplateParser.STRING); }
		public TerminalNode STRING(int i) {
			return getToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public ValueStringContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueTemplateStringWithRootContext extends ValueContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TemplateRootContext templateRoot() {
			return getRuleContext(TemplateRootContext.class,0);
		}
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateStringWithRootContext(ValueContext ctx) { copyFrom(ctx); }
	}
	public static class ValueArrayContext extends ValueContext {
		public ArrayContext array() {
			return getRuleContext(ArrayContext.class,0);
		}
		public ValueArrayContext(ValueContext ctx) { copyFrom(ctx); }
	}

	public final ValueContext value() throws RecognitionException {
		ValueContext _localctx = new ValueContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_value);
		int _la;
		try {
			setState(106);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				_localctx = new ValueTemplateStringContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(78);
				match(StringDeclOpen);
				setState(79);
				templateString();
				setState(83);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==TEMPLATELITERAL || _la==STRING) {
					{
					{
					setState(80);
					templateString();
					}
					}
					setState(85);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(86);
				match(CLOSE);
				}
				break;
			case 2:
				_localctx = new ValueTemplateStringWithRootContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(88);
				match(StringDeclOpen);
				setState(89);
				templateRoot();
				setState(90);
				match(CLOSE);
				}
				break;
			case 3:
				_localctx = new ValueStringContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(92);
				match(StringDeclOpen);
				setState(96);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==STRING) {
					{
					{
					setState(93);
					match(STRING);
					}
					}
					setState(98);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(99);
				match(CLOSE);
				}
				break;
			case 4:
				_localctx = new ValueNumberContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(100);
				match(NUMBER);
				}
				break;
			case 5:
				_localctx = new ValueObjectContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(101);
				obj();
				}
				break;
			case 6:
				_localctx = new ValueArrayContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(102);
				array();
				}
				break;
			case 7:
				_localctx = new ValueTrueContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(103);
				match(TRUE);
				}
				break;
			case 8:
				_localctx = new ValueFalseContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(104);
				match(FALSE);
				}
				break;
			case 9:
				_localctx = new ValueNullContext(_localctx);
				enterOuterAlt(_localctx, 9);
				{
				setState(105);
				match(NULL);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TemplateStringContext extends ParserRuleContext {
		public TemplateStringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateString; }
	 
		public TemplateStringContext() { }
		public void copyFrom(TemplateStringContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class TemplatedStringContext extends TemplateStringContext {
		public TerminalNode TEMPLATELITERAL() { return getToken(AdaptiveCardsTemplateParser.TEMPLATELITERAL, 0); }
		public List<TerminalNode> STRING() { return getTokens(AdaptiveCardsTemplateParser.STRING); }
		public TerminalNode STRING(int i) {
			return getToken(AdaptiveCardsTemplateParser.STRING, i);
		}
		public TemplatedStringContext(TemplateStringContext ctx) { copyFrom(ctx); }
	}

	public final TemplateStringContext templateString() throws RecognitionException {
		TemplateStringContext _localctx = new TemplateStringContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_templateString);
		int _la;
		try {
			int _alt;
			_localctx = new TemplatedStringContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			{
			setState(111);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==STRING) {
				{
				{
				setState(108);
				match(STRING);
				}
				}
				setState(113);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(114);
			match(TEMPLATELITERAL);
			setState(118);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(115);
					match(STRING);
					}
					} 
				}
				setState(120);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,10,_ctx);
			}
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TemplateRootContext extends ParserRuleContext {
		public TemplateRootContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateRoot; }
	 
		public TemplateRootContext() { }
		public void copyFrom(TemplateRootContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class TemplateStringWithRootContext extends TemplateRootContext {
		public TerminalNode TEMPLATEROOT() { return getToken(AdaptiveCardsTemplateParser.TEMPLATEROOT, 0); }
		public TemplateStringWithRootContext(TemplateRootContext ctx) { copyFrom(ctx); }
	}

	public final TemplateRootContext templateRoot() throws RecognitionException {
		TemplateRootContext _localctx = new TemplateRootContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_templateRoot);
		try {
			_localctx = new TemplateStringWithRootContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(121);
			match(TEMPLATEROOT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TemplateExpressionContext extends ParserRuleContext {
		public TemplateExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_templateExpression; }
	 
		public TemplateExpressionContext() { }
		public void copyFrom(TemplateExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ValueTemplateExpressionContext extends TemplateExpressionContext {
		public TerminalNode StringDeclOpen() { return getToken(AdaptiveCardsTemplateParser.StringDeclOpen, 0); }
		public TerminalNode TEMPLATELITERAL() { return getToken(AdaptiveCardsTemplateParser.TEMPLATELITERAL, 0); }
		public TerminalNode CLOSE() { return getToken(AdaptiveCardsTemplateParser.CLOSE, 0); }
		public ValueTemplateExpressionContext(TemplateExpressionContext ctx) { copyFrom(ctx); }
	}

	public final TemplateExpressionContext templateExpression() throws RecognitionException {
		TemplateExpressionContext _localctx = new TemplateExpressionContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_templateExpression);
		try {
			_localctx = new ValueTemplateExpressionContext(_localctx);
			enterOuterAlt(_localctx, 1);
			{
			setState(123);
			match(StringDeclOpen);
			setState(124);
			match(TEMPLATELITERAL);
			setState(125);
			match(CLOSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\25\u0082\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\3\2\3\2\3\3\3"+
		"\3\3\3\3\3\7\3\31\n\3\f\3\16\3\34\13\3\3\3\3\3\3\3\3\3\5\3\"\n\3\3\4\3"+
		"\4\7\4&\n\4\f\4\16\4)\13\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4@\n\4\3\5\3\5\3\5\3\5\7\5"+
		"F\n\5\f\5\16\5I\13\5\3\5\3\5\3\5\3\5\5\5O\n\5\3\6\3\6\3\6\7\6T\n\6\f\6"+
		"\16\6W\13\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\7\6a\n\6\f\6\16\6d\13\6\3"+
		"\6\3\6\3\6\3\6\3\6\3\6\3\6\5\6m\n\6\3\7\7\7p\n\7\f\7\16\7s\13\7\3\7\3"+
		"\7\7\7w\n\7\f\7\16\7z\13\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\2\2\n\2\4\6\b\n"+
		"\f\16\20\2\2\2\u008d\2\22\3\2\2\2\4!\3\2\2\2\6?\3\2\2\2\bN\3\2\2\2\nl"+
		"\3\2\2\2\fq\3\2\2\2\16{\3\2\2\2\20}\3\2\2\2\22\23\5\n\6\2\23\3\3\2\2\2"+
		"\24\25\7\5\2\2\25\32\5\6\4\2\26\27\7\3\2\2\27\31\5\6\4\2\30\26\3\2\2\2"+
		"\31\34\3\2\2\2\32\30\3\2\2\2\32\33\3\2\2\2\33\35\3\2\2\2\34\32\3\2\2\2"+
		"\35\36\7\6\2\2\36\"\3\2\2\2\37 \7\5\2\2 \"\7\6\2\2!\24\3\2\2\2!\37\3\2"+
		"\2\2\"\5\3\2\2\2#\'\7\f\2\2$&\7\25\2\2%$\3\2\2\2&)\3\2\2\2\'%\3\2\2\2"+
		"\'(\3\2\2\2(*\3\2\2\2)\'\3\2\2\2*+\7\17\2\2+,\7\4\2\2,@\5\n\6\2-.\7\f"+
		"\2\2./\7\20\2\2/\60\7\17\2\2\60\61\7\4\2\2\61\62\7\f\2\2\62\63\5\16\b"+
		"\2\63\64\7\17\2\2\64@\3\2\2\2\65\66\7\f\2\2\66\67\7\20\2\2\678\7\17\2"+
		"\289\7\4\2\29@\5\n\6\2:;\7\f\2\2;<\7\21\2\2<=\7\17\2\2=>\7\4\2\2>@\5\20"+
		"\t\2?#\3\2\2\2?-\3\2\2\2?\65\3\2\2\2?:\3\2\2\2@\7\3\2\2\2AB\7\7\2\2BG"+
		"\5\n\6\2CD\7\3\2\2DF\5\n\6\2EC\3\2\2\2FI\3\2\2\2GE\3\2\2\2GH\3\2\2\2H"+
		"J\3\2\2\2IG\3\2\2\2JK\7\b\2\2KO\3\2\2\2LM\7\7\2\2MO\7\b\2\2NA\3\2\2\2"+
		"NL\3\2\2\2O\t\3\2\2\2PQ\7\f\2\2QU\5\f\7\2RT\5\f\7\2SR\3\2\2\2TW\3\2\2"+
		"\2US\3\2\2\2UV\3\2\2\2VX\3\2\2\2WU\3\2\2\2XY\7\17\2\2Ym\3\2\2\2Z[\7\f"+
		"\2\2[\\\5\16\b\2\\]\7\17\2\2]m\3\2\2\2^b\7\f\2\2_a\7\25\2\2`_\3\2\2\2"+
		"ad\3\2\2\2b`\3\2\2\2bc\3\2\2\2ce\3\2\2\2db\3\2\2\2em\7\17\2\2fm\7\r\2"+
		"\2gm\5\4\3\2hm\5\b\5\2im\7\t\2\2jm\7\n\2\2km\7\13\2\2lP\3\2\2\2lZ\3\2"+
		"\2\2l^\3\2\2\2lf\3\2\2\2lg\3\2\2\2lh\3\2\2\2li\3\2\2\2lj\3\2\2\2lk\3\2"+
		"\2\2m\13\3\2\2\2np\7\25\2\2on\3\2\2\2ps\3\2\2\2qo\3\2\2\2qr\3\2\2\2rt"+
		"\3\2\2\2sq\3\2\2\2tx\7\23\2\2uw\7\25\2\2vu\3\2\2\2wz\3\2\2\2xv\3\2\2\2"+
		"xy\3\2\2\2y\r\3\2\2\2zx\3\2\2\2{|\7\24\2\2|\17\3\2\2\2}~\7\f\2\2~\177"+
		"\7\23\2\2\177\u0080\7\17\2\2\u0080\21\3\2\2\2\r\32!\'?GNUblqx";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}