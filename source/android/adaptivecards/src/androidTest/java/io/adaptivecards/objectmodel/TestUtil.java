package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.w3c.dom.Text;

import java.sql.Time;
import java.util.List;

public class TestUtil
{
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
            Assert.assertEquals(inputJson, cardElement.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputJson), "1.0");
            T parsedInput = command.castTo(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testCases[i], command.get(parsedInput));
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
        TextBlock textBlock = null;

        if (baseCardElement instanceof TextBlock)
        {
            textBlock = (TextBlock) baseCardElement;
        }
        else if ((textBlock = TextBlock.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextBlock object model.");
        }

        return textBlock;
    }

    public static RichTextBlock castToRichTextBlock(BaseCardElement baseCardElement)
    {
        RichTextBlock richTextBlock = null;

        if (baseCardElement instanceof RichTextBlock)
        {
            richTextBlock = (RichTextBlock) baseCardElement;
        }
        else if ((richTextBlock = RichTextBlock.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to RichTextBlock object model.");
        }

        return richTextBlock;
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
        Image image = null;

        if (baseCardElement instanceof Image)
        {
            image = (Image) baseCardElement;
        }
        else if ((image = Image.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Image object model.");
        }

        return image;
    }

    public static Container castToContainer(BaseCardElement baseCardElement)
    {
        Container container = null;

        if (baseCardElement instanceof Container)
        {
            container = (Container) baseCardElement;
        }
        else if ((container = Container.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Container object model.");
        }

        return container;
    }

    public static ColumnSet castToColumnSet(BaseCardElement baseCardElement)
    {
        ColumnSet columnSet = null;

        if (baseCardElement instanceof ColumnSet)
        {
            columnSet = (ColumnSet) baseCardElement;
        }
        else if ((columnSet = ColumnSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ColumnSet object model.");
        }

        return columnSet;
    }

    public static FactSet castToFactSet(BaseCardElement baseCardElement)
    {
        FactSet factSet = null;

        if (baseCardElement instanceof FactSet)
        {
            factSet = (FactSet) baseCardElement;
        }
        else if ((factSet = FactSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to FactSet object model.");
        }

        return factSet;
    }

    public static ImageSet castToImageSet(BaseCardElement baseCardElement)
    {
        ImageSet imageSet = null;

        if (baseCardElement instanceof ImageSet)
        {
            imageSet = (ImageSet) baseCardElement;
        }
        else if ((imageSet = ImageSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ImageSet object model.");
        }

        return imageSet;
    }

    public static ActionSet castToActionSet(BaseCardElement baseCardElement)
    {
        ActionSet actionSet = null;

        if (baseCardElement instanceof ActionSet)
        {
            actionSet = (ActionSet) baseCardElement;
        }
        else if ((actionSet = ActionSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ActionSet object model.");
        }

        return actionSet;
    }

    public static TextInput castToTextInput(BaseCardElement baseCardElement)
    {
        TextInput textInput = null;

        if (baseCardElement instanceof TextInput)
        {
            textInput = (TextInput) baseCardElement;
        }
        else if ((textInput = TextInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextInput object model.");
        }

        return textInput;
    }

    public static NumberInput castToNumberInput(BaseCardElement baseCardElement)
    {
        NumberInput numberInput = null;

        if (baseCardElement instanceof NumberInput)
        {
            numberInput = (NumberInput) baseCardElement;
        }
        else if ((numberInput = NumberInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to NumberInput object model.");
        }

        return numberInput;
    }

    public static DateInput castToDateInput(BaseCardElement baseCardElement)
    {
        DateInput dateInput = null;

        if (baseCardElement instanceof DateInput)
        {
            dateInput = (DateInput) baseCardElement;
        }
        else if ((dateInput = DateInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to DateInput object model.");
        }

        return dateInput;
    }

    public static TimeInput castToTimeInput(BaseCardElement baseCardElement)
    {
        TimeInput timeInput = null;

        if (baseCardElement instanceof TimeInput)
        {
            timeInput = (TimeInput) baseCardElement;
        }
        else if ((timeInput = TimeInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TimeInput object model.");
        }

        return timeInput;
    }

    public static ToggleInput castToToggleInput(BaseCardElement baseCardElement)
    {
        ToggleInput toggleInput = null;

        if (baseCardElement instanceof ToggleInput)
        {
            toggleInput = (ToggleInput) baseCardElement;
        }
        else if ((toggleInput = ToggleInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ToggleInput object model.");
        }

        return toggleInput;
    }

    public static ChoiceSetInput castToChoiceSetInput(BaseCardElement baseCardElement)
    {
        ChoiceSetInput choiceSetInput = null;

        if (baseCardElement instanceof ChoiceSetInput)
        {
            choiceSetInput = (ChoiceSetInput) baseCardElement;
        }
        else if ((choiceSetInput = ChoiceSetInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ChoiceSetInput object model.");
        }

        return choiceSetInput;
    }

    public static SubmitAction castToSubmitAction(BaseActionElement baseActionElement)
    {
        SubmitAction submitAction = null;

        if (baseActionElement instanceof SubmitAction)
        {
            submitAction = (SubmitAction) baseActionElement;
        }
        else if ((submitAction = SubmitAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to SubmitAction object model.");
        }

        return submitAction;
    }

    public static ShowCardAction castToShowCardAction(BaseActionElement baseActionElement)
    {
        ShowCardAction showCardAction = null;

        if (baseActionElement instanceof ShowCardAction)
        {
            showCardAction = (ShowCardAction) baseActionElement;
        }
        else if ((showCardAction = ShowCardAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
        }

        return showCardAction;
    }

    public static OpenUrlAction castToOpenUrlAction(BaseActionElement baseActionElement)
    {
        OpenUrlAction openUrlAction = null;

        if (baseActionElement instanceof OpenUrlAction)
        {
            openUrlAction = (OpenUrlAction) baseActionElement;
        }
        else if ((openUrlAction = OpenUrlAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to OpenUrlAction object model.");
        }

        return openUrlAction;
    }

    public static ToggleVisibilityAction castToToggleVisibilityAction(BaseActionElement baseActionElement)
    {
        ToggleVisibilityAction toggleVisibilityAction = null;

        if (baseActionElement instanceof ToggleVisibilityAction)
        {
            toggleVisibilityAction = (ToggleVisibilityAction) baseActionElement;
        }
        else if ((toggleVisibilityAction = ToggleVisibilityAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to ToggleVisibilityAction object model.");
        }

        return toggleVisibilityAction;
    }

    public static final String c_regularStringTestCases[] = {"Sample text",
                                                            "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                                                            "The quick brown fox jumps over the lazy dog",
                                                            "This is some **bold** text"};

    public static final String c_dateStringTestCases[] = {"{{DATE(2017-02-14T06:08:39Z,LONG)}}"};

}
