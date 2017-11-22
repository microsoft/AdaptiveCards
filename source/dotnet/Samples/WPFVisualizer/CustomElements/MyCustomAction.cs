using AdaptiveCards;

namespace WpfVisualizer
{
    public class MyCustomAction : AdaptiveAction
    {
        public override string Type { get; protected set; } = "Action.MyCustomAction";

    }
}
