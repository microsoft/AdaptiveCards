package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import java.lang.reflect.Array;
import java.util.List;

import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;

public class TestUtil
{
    public static<T> T[] concat(Class<T> c, T[] ... arrays)
    {
        int totalArrayLength = 0;
        for (T[] array : arrays)
        {
            totalArrayLength += array.length;
        }

        T[] concatenation = (T[]) Array.newInstance(c, totalArrayLength);
        int acumLength = 0;
        for (T[] array : arrays)
        {
            System.arraycopy(array, 0, concatenation, acumLength, array.length);
            acumLength += array.length;
        }

        return concatenation;
    }

    public interface Command<T extends BaseCardElement, E>
    {
        E get(T element);
        void set(E value, T element);

        T getMockObject();
        T castTo(BaseCardElement baseCardElement);
    }

    public static <T extends BaseCardElement, E> void executeTests(TestUtil.Command<T, E> command, String templateJson, E[] testCases) throws Exception
    {
        for (int i = 0; i < testCases.length; ++i)
        {
            String inputJson = String.format(templateJson, testCases[i]);

            T cardElement = command.getMockObject();
            command.set(testCases[i], cardElement);
            String outputJson = cardElement.Serialize();
            Assert.assertEquals(inputJson, outputJson);

            String fullCard = TestUtil.encloseElementJsonInCard(inputJson);
            ParseResult result = AdaptiveCard.DeserializeFromString(fullCard, "1.0");
            T parsedInput = command.castTo(result.GetAdaptiveCard().GetBody().get(0));
            String serializedPostParse = parsedInput.Serialize();
            E getResult = command.get(parsedInput);
            Assert.assertEquals(testCases[i], getResult);
        }
    }

    public static  <T extends BaseCardElement, E> void executeDefaultTestCase(TestUtil.Command<T, E> command, String json, E defaultValue) throws Exception
    {
        executeTests(command, json, (E[])new Object[]{defaultValue});
    }

    public static <T extends BaseCardElement> void executeBooleanTests(TestUtil.Command<T, Boolean> command, String defaultJson, String templateJson, Boolean defaultValue) throws Exception
    {
        executeDefaultTestCase(command, defaultJson, defaultValue);

        executeTests(command, templateJson, new Boolean[]{!defaultValue});
    }

    public static String encloseElementJsonInCard(String elementJson)
    {
        return "{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ " + elementJson + " ] }";
    }

    public static String encloseActionJsonInCard(String actionJson)
    {
        return "{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\":[], \"actions\": [ "  + actionJson + " ] }";
    }

    public static AdaptiveCard createMockCard()
    {
        AdaptiveCard adaptiveCard = new AdaptiveCard();
        return adaptiveCard;
    }

    public static AdaptiveCard createSampleCard()
    {
        AdaptiveCard adaptiveCard = createMockCard();
        adaptiveCard.SetVersion("1.0");
        adaptiveCard.GetBody().add(createMockTextBlock("Test"));
        adaptiveCard.GetActions().add(createSampleOpenUrlAction());
        return adaptiveCard;
    }

    public static TextBlock createMockTextBlock()
    {
        TextBlock textBlock = new TextBlock();
        return textBlock;
    }

    public static TextBlock createMockTextBlock(String text)
    {
        TextBlock textBlock = createMockTextBlock();
        textBlock.SetText(text);
        return textBlock;
    }

    public static Image createMockImage()
    {
        Image image = new Image();
        image.SetUrl("http://");
        return image;
    }

    public static Column createMockColumn()
    {
        Column column = new Column();
        return column;
    }

    public static ColumnSet createMockColumnSet()
    {
        ColumnSet columnSet = new ColumnSet();
        return columnSet;
    }

    public static ColumnSet createMockColumnSet(Column ... columns)
    {
        ColumnSet columnSet = createMockColumnSet();
        for (Column column : columns)
        {
            columnSet.GetColumns().add(column);
        }
        return columnSet;
    }

    public static Container createMockContainer()
    {
        Container container = new Container();
        return container;
    }

    public static BackgroundImage createMockBackgroundImage()
    {
        BackgroundImage backgroundImage = new BackgroundImage();
        backgroundImage.SetUrl("http://");
        return backgroundImage;
    }

    public static FactSet createMockFactSet()
    {
        FactSet factSet = new FactSet();
        return factSet;
    }

    public static FactSet createMockFactSet(Fact ... facts)
    {
        FactSet factSet = createMockFactSet();
        for (Fact fact : facts)
        {
            factSet.GetFacts().add(fact);
        }
        return factSet;
    }

    public static FactSet createMockFactSet(List<Fact> factList)
    {
        FactSet factSet = createMockFactSet();
        for (Fact fact : factList)
        {
            factSet.GetFacts().add(fact);
        }
        return factSet;
    }

    public static Fact createMockFact()
    {
        Fact fact = new Fact();
        return fact;
    }

    public static Fact createMockFact(String title, String value)
    {
        Fact fact = createMockFact();
        fact.SetTitle(title);
        fact.SetValue(value);
        return fact;
    }

    public static ImageSet createMockImageSet()
    {
        ImageSet imageSet = new ImageSet();
        return imageSet;
    }

    public static ImageSet createMockImageSet(Image ... images)
    {
        ImageSet imageSet = createMockImageSet();
        for (Image image : images)
        {
            imageSet.GetImages().add(image);
        }
        return imageSet;
    }

    public static RichTextBlock createMockRichTextBlock()
    {
        RichTextBlock richTextBlock = new RichTextBlock();
        return richTextBlock;
    }

    public static RichTextBlock createMockRichTextBlock(String ... textRuns)
    {
        RichTextBlock richTextBlock = createMockRichTextBlock();
        for (String textRunText : textRuns)
        {
            richTextBlock.GetInlines().add(createMockTextRun(textRunText));
        }
        return richTextBlock;
    }

    public static RichTextBlock createMockRichTextBlock(TextRun ... textRuns)
    {
        RichTextBlock richTextBlock = createMockRichTextBlock();
        for (TextRun textRun : textRuns)
        {
            richTextBlock.GetInlines().add(textRun);
        }
        return richTextBlock;
    }

    public static TextRun createMockTextRun()
    {
        TextRun textRun = new TextRun();
        return textRun;
    }

    public static TextRun createMockTextRun(String textRunText)
    {
        TextRun textRun = createMockTextRun();
        textRun.SetText(textRunText);
        return textRun;
    }

    public static TextInput createMockTextInput()
    {
        TextInput textInput = new TextInput();
        textInput.SetId("id");
        return textInput;
    }

    public static NumberInput createMockNumberInput()
    {
        NumberInput numberInput = new NumberInput();
        numberInput.SetId("id");
        return numberInput;
    }

    public static DateInput createMockDateInput()
    {
        DateInput dateInput = new DateInput();
        dateInput.SetId("id");
        return dateInput;
    }

    public static TimeInput createMockTimeInput()
    {
        TimeInput timeInput = new TimeInput();
        timeInput.SetId("id");
        return timeInput;
    }

    public static ToggleInput createMockToggleInput()
    {
        ToggleInput toggleInput = new ToggleInput();
        toggleInput.SetId("id");
        return toggleInput;
    }

    public static ChoiceSetInput createMockChoiceSetInput()
    {
        ChoiceSetInput choiceSetInput = new ChoiceSetInput();
        choiceSetInput.SetId("id");
        choiceSetInput.GetChoices().add(createChoiceInput("sample title", "sample value"));
        return choiceSetInput;
    }

    public static ChoiceInput createChoiceInput(String title, String value)
    {
        ChoiceInput choiceInput = new ChoiceInput();
        choiceInput.SetTitle(title);
        choiceInput.SetValue(value);
        return choiceInput;
    }

    public static SubmitAction createMockSubmitAction()
    {
        SubmitAction submitAction = new SubmitAction();
        return submitAction;
    }

    public static SubmitAction createMockSubmitAction(String dataJson)
    {
        SubmitAction submitAction = createMockSubmitAction();
        submitAction.SetDataJson(dataJson);
        return submitAction;
    }

    public static SubmitAction createSampleSubmitAction()
    {
        return createMockSubmitAction("{\"data\":\"Some data\"}");
    }

    public static OpenUrlAction createMockOpenUrlAction()
    {
        OpenUrlAction openUrlAction = new OpenUrlAction();
        return openUrlAction;
    }

    public static OpenUrlAction createSampleOpenUrlAction()
    {
        OpenUrlAction openUrlAction = createMockOpenUrlAction();
        openUrlAction.SetUrl("http://");
        return openUrlAction;
    }

    public static ShowCardAction createMockShowCardAction()
    {
        ShowCardAction showCardAction = new ShowCardAction();
        return showCardAction;
    }

    public static ShowCardAction createMockShowCardAction(AdaptiveCard card)
    {
        ShowCardAction showCardAction = createMockShowCardAction();
        showCardAction.SetCard(card);
        return showCardAction;
    }

    public static ToggleVisibilityTarget createTarget(String id, Boolean visibility)
    {
        ToggleVisibilityTarget target = new ToggleVisibilityTarget();
        target.SetElementId(id);

        if (visibility == null)
        {
            target.SetIsVisible(IsVisible.IsVisibleToggle);
        }
        else if (visibility == true)
        {
            target.SetIsVisible(IsVisible.IsVisibleTrue);
        }
        else
        {
            target.SetIsVisible(IsVisible.IsVisibleFalse);
        }

        return target;
    }

    public static ToggleVisibilityAction createMockToggleVisibilityAction()
    {
        ToggleVisibilityAction toggleVisibilityAction = new ToggleVisibilityAction();
        return toggleVisibilityAction;
    }

    public static ToggleVisibilityAction createMockToggleVisibilityAction(ToggleVisibilityTarget ... targets)
    {
        ToggleVisibilityAction toggleVisibilityAction = createMockToggleVisibilityAction();
        ToggleVisibilityTargetVector actionTargets = toggleVisibilityAction.GetTargetElements();
        for (ToggleVisibilityTarget target : targets)
        {
            actionTargets.add(target);
        }
        return toggleVisibilityAction;
    }

    public static ToggleVisibilityAction createSampleToggleVisibilityAction()
    {
        ToggleVisibilityAction toggleVisibilityAction =
            createMockToggleVisibilityAction(
                createTarget("id1", null),
                createTarget("id2", true),
                createTarget("id3", false));
        return toggleVisibilityAction;
    }

    public static ActionSet createMockActionSet()
    {
        ActionSet actionSet = new ActionSet();
        return actionSet;
    }

    public static ActionSet createMockActionSet(BaseActionElement ... actions)
    {
        ActionSet actionSet = createMockActionSet();
        for (BaseActionElement action : actions)
        {
            actionSet.GetActions().add(action);
        }
        return actionSet;
    }

    public static ActionSet createSampleActionSet()
    {
        ActionSet actionSet = createMockActionSet(
            createSampleOpenUrlAction(),
            createMockShowCardAction(createSampleCard()),
            createSampleSubmitAction(),
            createSampleToggleVisibilityAction());

        return actionSet;
    }

    public static BaseCardElement castToBaseCardElement(BaseElement baseElement)
    {
        BaseCardElement baseCardElement = null;

        if (baseElement instanceof BaseCardElement)
        {
            baseCardElement = (BaseCardElement) baseElement;
        }
        else if ((baseCardElement = BaseCardElement.dynamic_cast(baseElement)) == null)
        {
            throw new InternalError("Unable to convert BaseElement to BaseCardElement object model.");
        }

        return baseCardElement;
    }

    public static BaseActionElement castToBaseActionElement(BaseElement baseElement)
    {
        BaseActionElement baseActionElement = null;

        if (baseElement instanceof BaseActionElement)
        {
            baseActionElement = (BaseActionElement) baseElement;
        }
        else if ((baseActionElement = BaseActionElement.dynamic_cast(baseElement)) == null)
        {
            throw new InternalError("Unable to convert BaseElement to BaseActionElement object model.");
        }

        return baseActionElement;
    }

    public static TextBlock castToTextBlock(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, TextBlock.class);
    }

    public static RichTextBlock castToRichTextBlock(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, RichTextBlock.class);
    }

    public static TextRun castToTextRun(Inline inline)
    {
        TextRun textRun = null;

        if (inline instanceof TextRun)
        {
            textRun = (TextRun) inline;
        }
        else if ((textRun = TextRun.dynamic_cast(inline)) == null)
        {
            throw new InternalError("Unable to convert Inline to TextRun object model.");
        }

        return textRun;
    }

    public static Image castToImage(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, Image.class);
    }

    public static Container castToContainer(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, Container.class);
    }

    public static ColumnSet castToColumnSet(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, ColumnSet.class);
    }

    public static FactSet castToFactSet(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, FactSet.class);
    }

    public static ImageSet castToImageSet(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, ImageSet.class);
    }

    public static ActionSet castToActionSet(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, ActionSet.class);
    }

    public static TextInput castToTextInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, TextInput.class);
    }

    public static NumberInput castToNumberInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, NumberInput.class);
    }

    public static DateInput castToDateInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, DateInput.class);
    }

    public static TimeInput castToTimeInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, TimeInput.class);
    }

    public static ToggleInput castToToggleInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, ToggleInput.class);
    }

    public static ChoiceSetInput castToChoiceSetInput(BaseCardElement baseCardElement)
    {
        return Util.castTo(baseCardElement, ChoiceSetInput.class);
    }

    public static SubmitAction castToSubmitAction(BaseActionElement baseActionElement)
    {
        return Util.castTo(baseActionElement, SubmitAction.class);
    }

    public static ShowCardAction castToShowCardAction(BaseActionElement baseActionElement)
    {
        return Util.castTo(baseActionElement, ShowCardAction.class);
    }

    public static OpenUrlAction castToOpenUrlAction(BaseActionElement baseActionElement)
    {
        return Util.castTo(baseActionElement, OpenUrlAction.class);
    }

    public static ToggleVisibilityAction castToToggleVisibilityAction(BaseActionElement baseActionElement)
    {
        return Util.castTo(baseActionElement, ToggleVisibilityAction.class);
    }

    public static abstract class ValidationExecutor
    {
        public ValidationExecutor(BaseInputHandler inputHandler)
        {
            m_inputHandler = inputHandler;
        }

        public void BeforeTestPrep(Object i)
        {
            if (i instanceof Integer)
            {
                Integer a = (Integer)i;
                m_inputHandler.setInput(String.valueOf(a.intValue()));
            }
            else if (i instanceof String)
            {
                m_inputHandler.setInput((String)i);
            }
        }

        public abstract boolean ExecuteMethodToTest();

        protected BaseInputHandler m_inputHandler;
    }

    public static class GeneralValidationExecutor extends ValidationExecutor
    {
        public GeneralValidationExecutor(BaseInputHandler inputHandler)
        {
            super(inputHandler);
        }

        @Override
        public boolean ExecuteMethodToTest()
        {
            return m_inputHandler.isValid();
        }
    }

    public static class SpecificsValidationExecutor extends ValidationExecutor
    {
        public SpecificsValidationExecutor(BaseInputHandler inputHandler)
        {
            super(inputHandler);
        }

        @Override
        public boolean ExecuteMethodToTest()
        {
            return m_inputHandler.isValidOnSpecifics(m_inputHandler.getInput());
        }
    }

    public static void runValidationTests(Object[] array, boolean expectedResult, ValidationExecutor validationExecutor)
    {
        for (Object value : array)
        {
            validationExecutor.BeforeTestPrep(value);
            Assert.assertEquals(expectedResult, validationExecutor.ExecuteMethodToTest());
        }
    }

    public static final String c_regularStringTestCases[] = {"Sample text",
                                                            "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                                                            "The quick brown fox jumps over the lazy dog",
                                                            "This is some **bold** text"};

    public static final String c_dateStringTestCases[] = {"{{DATE(2017-02-14T06:08:39Z,LONG)}}"};

    public static final Double[] c_doubleTestCases = {-100.0, -25.0, -10.0, -5.0, -2.5, -1.0, -0.25,
                                                      0.0, 1.0, 5.0, 10.0, 25.0, 50.0};

}
