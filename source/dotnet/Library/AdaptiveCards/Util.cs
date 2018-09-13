using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    static class Util
    {
        // iterates through each element of the body and sets the language on non-null ColumnSets, Containers, and TextBlocks
        internal static void PropagateLang(string lang, List<AdaptiveElement> body)
        {
            foreach (AdaptiveElement element in body)
            {
                string type = element.Type;

                if (type.Equals(AdaptiveColumnSet.TypeName))
                {
                    var columnSet = (AdaptiveColumnSet)element;
                    if (columnSet != null)
                    {
                        columnSet.SetLang(lang);
                    }
                }
                else if (type.Equals(AdaptiveContainer.TypeName))
                {
                    var container = (AdaptiveContainer)element;
                    if (container != null)
                    {
                        container.SetLang(lang);
                    }
                }
                else if (type.Equals(AdaptiveTextBlock.TypeName))
                {
                    var textBlock = (AdaptiveTextBlock)element;
                    if (textBlock != null)
                    {
                        textBlock.Lang = lang;
                    }
                }
            }
        }
    }
}
