var card = AdaptiveCard.FromJson("{JSON}");
var xaml = card.Render();
MyChatCanvas.Children.Add(xaml);



OR


var parser = new JsonParser();
var card = parser.Parse("{JSON"});




var adaptiveRenderer = new AdaptiveCardRenderer();
adaptiveRenderer.ResourceDictionary = "./Path/SkypeAdaptiveCardStyles.xaml";
adaptiveRenderer.SupportsActionBar = false;
adaptiveRenderer.MaximumForms = 1;
adaptiveRenderer.ActionTapped += (s, e) => {
    if(e.Type == "Submit") {
        

    }
};

var xaml = adaptiveRenderer.GenerateXaml(card);




public class AdaptiveCardRenderer : ICardRenderer
{
    public bool SupportsActionBar { get; set;}

    public ImageWatcher;

    void Render()
    {
        foreach(var element in Items)
        {
            element.Render(this);
        }
    }
}



public class XamlTextBlockRenderer : IAdaptiveRenderer
{
    void Render();
}




public class XamlTextBlock : IAdaptiveElement
{
    private readonly Style _style;

    public void XamlTextBlock(Style style)
    {
        _style = style;   
    }

    public string Text {get; set;}

    public bool RemoveTopMarginForFirstItem
    {
        get { return true;}
    }
    
    public void Render()
    {
        var tb = new TextBlock();
        tb.SetStyle(_style);

        tb.Margin.Top = 5px;
        // special bug fix

        return tb;
    }
}