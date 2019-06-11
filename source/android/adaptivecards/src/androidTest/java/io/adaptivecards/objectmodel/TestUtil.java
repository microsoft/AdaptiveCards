package io.adaptivecards.objectmodel;

import java.util.List;

public class TestUtil
{

    public static String encloseElementStringInCard(String elementJson)
    {
        return "{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ " + elementJson + " ] }";
    }

    public static String encloseActionJsonInCard(String actionJson)
    {
        return "{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\":[], \"actions\": [ "  + actionJson + " ] }";
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

    /*
    public static OpenUrlAction createMockOpenUrlAction()
    {
        OpenUrlAction openUrlAction = new OpenUrlAction();
        openUrlAction.SetUrl("http://");
        return openUrlAction;
    }
    */

    public static OpenUrlAction createSampleOpenUrlAction()
    {
        OpenUrlAction openUrlAction = new OpenUrlAction();
        openUrlAction.SetUrl("http://");
        return openUrlAction;
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

}
