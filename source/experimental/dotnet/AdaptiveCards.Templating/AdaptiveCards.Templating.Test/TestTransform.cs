using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using Microsoft.Bot.Expressions;

namespace AdaptiveCards.Templating.Test
{
    [TestClass]
    public class TestTransform
    {
        [TestMethod]
        public void TestBasic()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();

            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""$data"": {
                ""person"": {
                    ""firstName"": ""Andrew"",
                    ""lastName"": ""Leader""
                }
     },
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello {person.firstName}""
        }
    ]
}";

            string jsonData = @"{
    ""person"": {
        ""firstName"": ""Andrew"",
        ""lastName"": ""Leader""
    }
}";

            string cardJson = transformer.Transform(jsonTemplate, jsonData);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello Andrew""
        }
    ]
}", cardJson);
        }

        private static void AssertJsonEqual(string jsonExpected, string jsonActual)
        {
            var expected = JObject.Parse(jsonExpected);
            var actual = JObject.Parse(jsonActual);

            Assert.IsTrue(JToken.DeepEquals(expected, actual), "JSON wasn't the same.\n\nExpected: " + expected.ToString() + "\n\nActual: " + actual.ToString());
        }

        [TestMethod]
        public void TestArray()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();
            var testString =
                @"{
                ""type"": ""AdaptiveCard"",
                ""$data"": {
                    ""employee"": {
                        ""name"": ""Matt"",
                        ""manager"": { ""name"": ""Thomas"" },
                        ""peers"": [{
                            ""name"": ""Andrew"" 
                        }, { 
                            ""name"": ""Lei""
                        }, { 
                            ""name"": ""Mary Anne""
                        }, { 
                            ""name"": ""Adam""
                        }]
                    }
                },
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Hi {employee.name}! Here's a bit about your org...""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Your manager is: {employee.manager.name}""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""3 of your peers are: {employee.peers[0].name}, {employee.peers[1].name}, {employee.peers[2].name}""
                    }
                ]
            }";

            var expectedString = @"{
                ""type"": ""AdaptiveCard"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Hi Matt! Here's a bit about your org...""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Your manager is: Thomas""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""3 of your peers are: Andrew, Lei, Mary Anne""
                    }
                ]
            }";

            string cardJson = transformer.Transform(testString, null);
            AssertJsonEqual(cardJson, expectedString);
        }

        [TestMethod]
        public void TestIteratioin()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();
            var testString =
                @"{
                    ""type"": ""AdaptiveCard"",
                    ""body"": [
                      {
                          ""type"": ""Container"",
                          ""items"": [
                              {
                                  ""type"": ""TextBlock"",
                                  ""$data"": [
                                      { ""name"": ""Matt"" }, 
                                      { ""name"": ""David"" }, 
                                      { ""name"": ""Thomas"" }
                                  ],
                                  ""text"": ""{name}""
                              }
                          ]
                      }
                    ]
                }";
            var expectedString =
                @"{
                    ""type"": ""AdaptiveCard"",
                    ""body"": [
                    {
                        ""type"": ""Container"",
                        ""items"": [ 
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""Matt""
                            },
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""David""
                            },
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""Thomas""
                            }
                        ]
                    }
                ]
            }";

            string cardJson = transformer.Transform(testString, null);
            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestExpression()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();

            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""$data"": {
                ""machines"": {
                    ""id"": ""primary"",
                    ""uptime"": 2231
                }
     },
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""{machines.id}"",
            ""color"": ""{if(machines.uptime >= 3000, 'good', 'attention')}""
        }
    ]
}";

            string cardJson = transformer.Transform(jsonTemplate, null);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""primary"",
            ""color"": ""attention""
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestInlineMemoryScope()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();
            var testString =
                @"{
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                      {
                          ""type"": ""Container"",
                          ""items"": [
                              {
                                  ""type"": ""TextBlock"",
                                  ""$data"": { ""name"": ""Matt"" }, 
                                  ""text"": ""{name}""
                              }
                          ]
                      }
                    ]
                }";
            var expectedString =
                @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
      {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Matt""
            }
            ]
        }
    ]
}"; 

            string cardJson = transformer.Transform(testString, null);
            AssertJsonEqual(cardJson, expectedString);
        }
        [TestMethod]
        public void TestInlineMemoryScope2()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();
            var testString =
                @"{
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                      {
                          ""type"": ""Container"",
                          ""$data"": { ""name"": ""Matt"" }, 
                          ""items"": [
                              {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""{name}""
                              }
                          ]
                      }
                    ]
                }";
            var expectedString =
                @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
      {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Matt""
            }
            ]
        }
    ]
}"; 

            string cardJson = transformer.Transform(testString, null);
            AssertJsonEqual(cardJson, expectedString);
        }

        [TestMethod]
        public void TestInlineMemoryScope3()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();
            var testString =
                @"{
                    ""type"": ""AdaptiveCard"",
                    ""version"": ""1.0"",
                    ""body"": [
                      {
                          ""type"": ""Container"",
                          ""$data"": { ""name"": ""Andrew"" }, 
                          ""items"": [
                              {
                                  ""type"": ""TextBlock"",
                                  ""$data"": { ""name"": ""Matt"" }, 
                                  ""text"": ""{name}""
                              }
                          ]
                      }
                    ]
                }";
            var expectedString =
                @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
      {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Matt""
            }
            ]
        }
    ]
}"; 

            string cardJson = transformer.Transform(testString, null);
            AssertJsonEqual(expectedString, cardJson);
        }
    }
    [TestClass]
    public class TestPartialResult
    {
        [TestMethod]
        public void TestCreation()
        {
            JSONTemplateVisitorResult result = new JSONTemplateVisitorResult();
            result.Append("hello world");
            Assert.AreEqual(result.ToString(), "hello world");
        }

        [TestMethod]
        public void TestMerging()
        {
            JSONTemplateVisitorResult result1 = new JSONTemplateVisitorResult();
            result1.Append("hello");

            JSONTemplateVisitorResult result2 = new JSONTemplateVisitorResult();
            result2.Append(" world");


            JSONTemplateVisitorResult result3 = new JSONTemplateVisitorResult();
            result3.Append("!");

            result1.Append(result2);
            result1.Append(result3);

            Assert.AreEqual(result1.ToString(), "hello world!");
        }

        [TestMethod]
        public void TestCreationOfPartialResult()
        {
            JSONTemplateVisitorResult result1 = new JSONTemplateVisitorResult();
            result1.Append("hello");

            JSONTemplateVisitorResult result2 = new JSONTemplateVisitorResult();
            result2.Append("name", false);

            JSONTemplateVisitorResult result3 = new JSONTemplateVisitorResult();
            result3.Append("!");

            result1.Append(result2);
            result1.Append(result3);

            Assert.AreEqual(result1.ToString(), "hello{name}!");
        }
    }

    [TestClass]
    public class TestCEL
    {
        [TestMethod]
        public void TestCreation()
        {
            string jsonData = @"{
            ""person"": {
                ""firstName"": ""Super"",
                ""lastName"": ""man""
                }
            }";

            JToken token = JToken.Parse(jsonData);
            var engine = new ExpressionEngine();
            var expr = engine.Parse("person.firstName");
            var result = expr.TryEvaluate(token);
            Assert.AreEqual("Super", result.value);
        }

        [TestMethod]
        public void TestSimpleToString()
        {
            string jsonData = @"{
            ""person"": {
                ""firstName"": ""Super"",
                ""lastName"": ""man"",
                ""age"" : 79 
                }
            }";

            JToken token = JToken.Parse(jsonData);
            var engine = new ExpressionEngine();
            var expr = engine.Parse("string(person.age)");
            var result = expr.TryEvaluate(token);
            Assert.AreEqual("79", result.value);
        }
    }
}
