using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class BindingEvaluatorTests
    {
        private const string DATA_1 = @"{
    ""summary"": ""This is a summary"",
    ""manager"": {
        ""name"": {
            ""first"": ""Thomas"",
            ""last"": ""Fennel""
        },
        ""full name"": ""Theron Fennel""
    },
    ""employees"": [
        {
            ""name"": ""Andrew Leader""
        },
        {
            ""name"": ""Matt Hidinger""
        }
    ]
}";

        [TestMethod]
        public void EvaluateBindingStringTests()
        {
            AssertEvaluateBinding("This is a summary", DATA_1, "{data.summary}");
            AssertEvaluateBinding("Thomas", DATA_1, "{data.manager['name'].first}");
            AssertEvaluateBinding("Thomas Fennel", DATA_1, "{data.manager['name'].first} {data.manager['name'].last}");
        }

        [TestMethod]
        public void EvalulatePropertyExpressionData1Tests()
        {
            AssertEvalulatePropertyExpression("This is a summary", DATA_1, ".summary");
            AssertEvalulatePropertyExpression(JObject.Parse(@"{
        ""name"": {
            ""first"": ""Thomas"",
            ""last"": ""Fennel""
        },
        ""full name"": ""Theron Fennel""
    }"), DATA_1, ".manager");

            AssertEvalulatePropertyExpression("Thomas", DATA_1, ".manager.name.first");
            AssertEvalulatePropertyExpression("Fennel", DATA_1, ".manager.name['last']");
            AssertEvalulatePropertyExpression("Fennel", DATA_1, ".manager['name']['last']");
            AssertEvalulatePropertyExpression("Fennel", DATA_1, ".manager['name'].last");
        }

        public void AssertEvalulatePropertyExpression(object expected, string dataJson, string propertyExpression)
        {
            object actual = BindingEvaluator.EvalulatePropertyExpression(JObject.Parse(dataJson), propertyExpression);

            if (expected is JObject expObj && actual is JObject actObj)
            {
                Assert.AreEqual(expObj.ToString(), actObj.ToString());
                return;
            }

            Assert.AreEqual(expected, actual);
        }

        public void AssertEvaluateBinding<T>(T expected, string dataJson, string bindingExpression)
        {
            JObject data = JObject.Parse(dataJson);

            T result = BindingEvaluator.EvaluateBinding<T>(data, bindingExpression);
            Assert.AreEqual<T>(expected, result);
        }
    }
}
