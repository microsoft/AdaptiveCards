using System.Text;

namespace AdaptiveCards.Templating
{
    public sealed class AdaptiveCardsTemplateResult
    {
        public enum EvaluationResult
        {
            NotEvaluated = 0,
            EvaluatedToTrue,
            EvaluatedToFalse
        }

        private readonly StringBuilder stringResult;

        public bool HasItBeenDropped { get; set; }
        public bool IsWhen { get; }
        public string Predicate { get; }
        public EvaluationResult WhenEvaluationResult { get; set;  }

        public AdaptiveCardsTemplateResult()
        {
            stringResult = new StringBuilder("");
            HasItBeenDropped = false;
            IsWhen = false;
            Predicate = "";
            WhenEvaluationResult = EvaluationResult.NotEvaluated;
        }

        public AdaptiveCardsTemplateResult(bool indicateIfDropped) : this()
        {
            HasItBeenDropped = indicateIfDropped;
        }

        public AdaptiveCardsTemplateResult(string capturedString) : this()
        {
            stringResult.Append(capturedString);
        }

        public AdaptiveCardsTemplateResult(string capturedString, string predicate) : this()
        {
            Predicate = predicate;
            IsWhen = true;
            stringResult.Append(capturedString);
        }

        public void Append(string capturedString = "")
        {
            stringResult.Append(capturedString);
        }

        public void Append(AdaptiveCardsTemplateResult result)
        {
            if (result == null)
            {
                return;
            }

            if (!result.IsWhen)
            {
                stringResult.Append(result.stringResult);
            }
        }

        public override string ToString()
        {
            return stringResult.ToString();
        }
    }
}
