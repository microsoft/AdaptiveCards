using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using AdaptiveExpressions.Properties;
using AdaptiveExpressions;
using System.Diagnostics;
using System;

namespace AdaptiveCards.Templating.Test
{
    [TestClass]
    public class TestTemplate
    {
        [TestMethod]
        public void TestBasic()
        {
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
            ""text"": ""Hello ${person.firstName}""
        }
    ]
}";

            string jsonData = @"{
    ""person"": {
        ""firstName"": ""Andrew"",
        ""lastName"": ""Leader""
    }
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

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

        [TestMethod]
        public void TestIntInExpression()
        {
            string jsonTemplate = @"{
        ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
        ""type"": ""AdaptiveCard"",
        ""version"": ""1.0"",
        ""body"": [
                {
                    ""type"": ""Input.Number"",
                    ""id"": ""number"",
                    ""placeholder"": ""Enter Estimated Mileage"",
                    ""min"": 1,
                    ""max"": 10,
                    ""value"": ""${car_type_1.average_mileage}"" 
                }
        ],
        ""actions"": [
              {
                  ""type"": ""Action.Submit"",
                  ""title"": ""OK""
              }
        ]
}";

            string jsonData = @"{
    ""car_type_1"": {
        ""average_mileage"": 120000, 
        ""average_mpg"" : 28.5
    }
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
        ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
        ""type"": ""AdaptiveCard"",
        ""version"": ""1.0"",
        ""body"": [
                {
                    ""type"": ""Input.Number"",
                    ""id"": ""number"",
                    ""placeholder"": ""Enter Estimated Mileage"",
                    ""min"": 1,
                    ""max"": 10,
                    ""value"": 120000
                }
        ],
        ""actions"": [
              {
                  ""type"": ""Action.Submit"",
                  ""title"": ""OK""
              }
        ]
}", cardJson);
        }

        [TestMethod]
        public void TestExternalDataContext()
        {
            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello ${person.firstName}""
        }
    ]
}";

            string jsonData = @"{
    ""person"": {
        ""firstName"": ""Andrew"",
        ""lastName"": ""Leader""
    }
}";
            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);
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

        [TestMethod]
        public void TestExternalDataContextInternalReference()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${LineItems}"",
                    ""type"": ""TextBlock"",
                    ""$when"": ""${Milage > 0}"",
                    ""text"": ""${Milage}""
                  }
                ]
              }
            ]
        }";

            string jsonData = @"{
              ""LineItems"": [
                {
                    ""Milage"": 10
                },
                {
                    ""Milage"": 0
                }
              ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);
            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": 10
                }
            ]
        }
    ]
}", cardJson);
        }

        public static void AssertJsonEqual(string jsonExpected, string jsonActual)
        {
            var expected = JObject.Parse(jsonExpected);
            var actual = JObject.Parse(jsonActual);

            Assert.IsTrue(JToken.DeepEquals(expected, actual), "JSON wasn't the same.\n\nExpected: " + expected.ToString() + "\n\nActual: " + actual.ToString());
        }

        [TestMethod]
        public void TestArray()
        {
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
                        ""text"": ""Hi ${employee.name}! Here's a bit about your org...""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Your manager is: ${employee.manager.name}""
                    },
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""3 of your peers are: ${employee.peers[0].name}, ${employee.peers[1].name}, ${employee.peers[2].name}""
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

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();

            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestIteratioinWithFacts()
        {
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
                                    ""text"": ""Header""
                                },
                                {
                                    ""type"": ""FactSet"",
                                    ""facts"": [
                                        {
                                            ""$data"": [
                                                {
                                                    ""name"": ""Star"",
                                                    ""nickname"": ""Dust""
                                                },
                                                {
                                                    ""name"": ""Death"",
                                                    ""nickname"": ""Star""
                                                }
                                            ],
                                            ""title"": ""${name}"",
                                            ""value"": ""${nickname}""
                                        }
                                    ]
                                }
                            ]
                        }
                    ],
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json""
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
                                    ""text"": ""Header""
                                },
                                {
                                    ""type"": ""FactSet"",
                                    ""facts"": [
                                        {
                                            ""title"": ""Star"",
                                            ""value"": ""Dust""
                                        },
                                        {
                                            ""title"": ""Death"",
                                            ""value"": ""Star""
                                        }
                                    ]
                                }
                            ]
                        }
                    ],
                    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json""
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();

            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestIteratioin()
        {
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
                                  ""text"": ""${name}""
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

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();

            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestIteratioinFalsePositive()
        {
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
                                  ""text"": ""Hello World!""
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
                                ""text"": ""Hello World!""
                            }
                        ]
                    }
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestIteratioinRealDdata()
        {
            var templateData =
                @" [
                        { ""name"": ""Object-1"", ""lastPrice"": 1.10762, ""changePriceRatio"": -0.17 },
                        { ""name"": ""Object-2"", ""lastPrice"": 1578.205, ""changePriceRatio"": -0.68 },
                        { ""name"": ""Object-3"", ""lastPrice"": 51.475, ""changePriceRatio"": -0.23 },
                        { ""name"": ""Object-4"", ""lastPrice"": 28324, ""changePriceRatio"": 0.35 },
                        { ""name"": ""Object-5"", ""lastPrice"": 9338.87, ""changePriceRatio"": -1.04 }
                    ]";
                var testString =
                    @"{
        ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
        ""type"": ""AdaptiveCard"",
        ""version"": ""1.0"",
        ""body"": [
        {
            ""type"": ""Container"",
            ""items"": [
                {
                    ""type"": ""ColumnSet"",
                    ""columns"": [
                        {
                            ""type"": ""Column"",
                            ""width"": ""auto"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""${if(changePriceRatio >= 0, '▲', '▼')}"",
                                    ""color"": ""${if(changePriceRatio >= 0, 'good', 'attention')}""
                                }
                            ]
                        },
                        {
                            ""type"": ""Column"",
                            ""width"": ""stretch"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""${name}""
                                } ]
                        },
                        {
                            ""type"": ""Column"",
                            ""width"": ""stretch"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""${lastPrice} "",
                                    ""horizontalAlignment"": ""Center""
                                }
                            ],
                            ""horizontalAlignment"": ""Center""
                        },
                        {
                            ""type"": ""Column"",
                            ""width"": ""auto"",
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""${changePriceRatio}%"",
                                    ""color"": ""${if(changePriceRatio >= 0, 'good', 'attention')}""
                                }
                            ],
                            ""horizontalAlignment"": ""Right""
                        }
                    ]
                }
            ] ,
            ""$data"":""{$root}""
        }
    ]
}";
        var expectedString =
        @"{ ""$schema"":""http://adaptivecards.io/schemas/adaptive-card.json"",""type"":""AdaptiveCard"",""version"":""1.0"",""body"":[{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-1""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""1.10762 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.17%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-2""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""1578.205 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.68%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-3""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""51.475 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.23%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▲"",""color"":""good""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-4""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""28324 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""0.35%"",""color"":""good""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-5""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""9338.87 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-1.04%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]}]}"; 
            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = templateData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestIteratioinRealDdata2()
        {
            var templateData =
                @"{
    ""attribution"": {
                ""iconAltText"": ""more in Outlook"",
        ""linkLabel"": ""more in Outlook"",
        ""linkAltText"": ""more in Outlook"",
        ""linkUrl"": ""https://outlook.office365.com/owa/""
    },
    ""emails"": [
        {
            ""name"": ""Jim Kirk"",
            ""flag"": true,
            ""date"": ""6/2/2017"",
            ""attachment"": false,
            ""link"": ""https://outlook.office365.com/owa/?ItemID=1"",
            ""linkTitle"": ""Email from Jim Kirk about RE: First Email Subject"",
            ""subject"": ""RE: First Email Subject"",
            ""preview"": ""First Email Preview""
        },
        {
            ""name"": ""Jim Kirk"",
            ""flag"": false,
            ""date"": ""6/1/2017"",
            ""attachment"": true,
            ""link"": ""https://outlook.office365.com/owa/?ItemID=1"",
            ""linkTitle"": ""Email from Jim Kirk about Second Email Subject"",
            ""subject"": ""Second Email Subject"",
            ""preview"": ""Second Email Preview""
        }
    ]
}";
                var testString =
                @"{
    ""type"": ""AdaptiveCard"",
    ""speak"": ""${speak}"",
    ""body"": [
        {
            ""type"": ""Container"",
            ""items"": [
                {
                    ""type"": ""ColumnSet"",
                    ""$data"": ""${emails}"",
                    ""columns"": [
                        {
                            ""type"": ""Column"",
                            ""width"": ""auto"",
                            ""items"": [
                                {
                                    ""type"": ""Image"",
                                    ""altText"": ""Envelope"",
                                    ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAyNJREFUeAHt2OtqE0EYBuB3WksiqEnVCxBEEOqlpZUewOqvFTxEaBLb5NIMCCJ4AWpS9UdCSdaZXb80Wbe7O5k2mYR3IUwO++1+82SOC/CgAAUoQAEKUIACFKAABShAAQpQgAIUoAAFKEABClCAAusvoHKrePwpzD1nnU+oP8s02ljnui+ibgR0VCagI+At63ilfiJUTWxvnOHF09/W8T4GBF/uYXixh3B8oNPbtkkxc4CMLnTVJLIOkB8+30VvvAcVHiAM76fC5Uwi8wPK3VYRsgic1O/GAeVGBhJooLrZ9rZr28BJvXIA55hEVACFvlx/UpouEIZv0R99w8vuK5hkfTlMLiYnkxvGb1K7a1QnXTfLwx6wvvMalduPgBWAnIYzf27aOCdwpk6mbpaH/Rg43aTrXys4HzwHwn2EqKbeW6kf+rcGymgj2PmTes51f2ng+qNdfdnDVDRzvxiuhUr5FMePzycpJCfN6fpOTrp84wYo1/EF0sD1RjWNc3QlHNCDUh//g5O6LAVQbm7WU4OhbpHY16/09dRNtMigewcD7Go40+IeSDqJsqc/t1AunSJ48ivx2+XHpQJKGouCLAqnNpoobZ1lwknuXgBKMkVW+KZFAicooVN4jDRwQ9R0nOmq6S0uWlapVmE4ydkrQEkqapEXuotlrPiLQBaFM1vN8paetDK6quSWLL0ElCSjQT5n6wT1XY9ljZkWaQPnukf3GnAaMm+ZYSARnsQh6ki/fyjhM+V174AsAe2fxsxkP+eH+CnOO71baf9br5nNfGIsi8Dq8R1SHorHXb657K3jcgDFfRoyXr9lLUPiKFkGVTc7Puy5lws4C/keQbeNgUpfzxWZZOR6Cyz9AJQKx1u9GHKoanoLeBj9lJxU5HwPSr8ABSSGrOsW2Ym+WtQeWu5vUfoJKBXwGE5StH+cJZEsIwECOjYEAhLQUcAxnC2QgI4CjuFsgQR0FHAMZwskoKOAYzhbIAEdBRzD7R8mJB95Oyaw6uHswo7/IAEJ6CjAcApQgAIUoAAFKEABClCAAhSgAAUoQAEKUIACFKAABShAgVyBvyaVcRhWOA8BAAAAAElFTkSuQmCC"",
                                    ""width"": ""20px"",
                                    ""horizontalAlignment"": ""Center""
                                }
                            ]
                        },
                        {
                            ""type"": ""Column"",
                            ""width"": ""stretch"",
                            ""items"": [
                                {
                                    ""type"": ""ColumnSet"",
                                    ""columns"": [
                                        {
                                            ""type"": ""Column"",
                                            ""width"": ""stretch"",
                                            ""items"": [
                                                {
                                                    ""type"": ""TextBlock"",
                                                    ""text"": ""${name}"",
                                                    ""weight"": ""Bolder"",
                                                    ""horizontalAlignment"": ""Left""
                                                }
                                            ],
                                            ""spacing"": ""None"",
                                            ""verticalContentAlignment"": ""Center""
                                        },
                                        {
                                            ""type"": ""Column"",
                                            ""$when"": ""${attachment == true}"",
                                            ""width"": ""auto"",
                                            ""items"": [
                                                {
                                                    ""type"": ""Image"",
                                                    ""altText"": ""Paperclip"",
                                                    ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAERlWElmTU0AKgAAAAgAAYdpAAQAAAABAAAAGgAAAAAAA6ABAAMAAAABAAEAAKACAAQAAAABAAAAUKADAAQAAAABAAAAUAAAAAAx4ExPAAAEv0lEQVR4Ae2cTUhUURTHZ8aR0NB9tbWlNKDOpogIqU0tWgtDCSI6s2vRrkjaFLSbGTGVJIiWhbopIsZFUH6Q2ta17TWRwXGm/xnevdx3eeLoee/dgc6Dxz333HPuu+c35773BM9LJOQQAkJACAgBISAEhIAQ+B8JJNsh6EajkSqXy8Nos8lkchDtkLeudbRr0K1OTk5+RVtvh/Waa3AOsFQq9QHYAhZ13VxYgPwdAB/m8/mdgDFnqpSzK+PCyLo8mi2cp8GjZZLNludD/bY4nGUggajX68XzUEilUgVs6dJ5fMP2cQKQti0C2cLW7VYBYXs2IM8BziLODdID8MDx8fF9jI3B1lzrAXSZdtjOaRVAXC1ApABwAdfT8CDvAtrIxMREBbJ5LKOzPD09/QEg30O+7A1epPsmzpsA6fTBYv6q5sIjkwHvDgL/rC5AmQd4twPgKZNmC4i3kJHf4KvXDN+7yMIvPsOYO7E/RAAga8aI/uxp8MiebMjW8vXNZY7FJccOEIGpd7xmjB0dHUutBhtg65ur1XnCtHMBcNAMQD0wTN1JcoCtb66T/KLUuwCoHgTNuMbHx/+0GmCArW+uVucJ084FwDDX73yu2F9joo64WCzS+6Q+CoWCfmprZYiCZCATpgAUgEwCTPe2uwfGfQ9j8kvIFmYSFIACkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjusWcg6tv+mmuen5/31Xpg3Fc3gho5Xc5lyjSHbRswl+9a5nXDkl38iy8BuqoCqFarVG20qPqoh6NS13uqjwLD1wD3mPokKz21nq1WHR4e2qVfvh9DG4YoxJ6BWPuutX5f0MgqDZPsAOkGSl1/0kmy6WvbohTMLv2yr2W6hyLHDhAQVsyVo6+3KOlRiT6HpkLyKUfFs9Vm9lz2tbRhiELsAFFx+clcP4IcxhbV30xAVjW6urpGYFMx7Sy5QjZkq/Q0B82l+tRi/KPZj0KOtAzqpAWjlGEbY/1qHIHu9PT0ZHK53IHSAUYSUMZw36OS/wHSQ7eBbbqE2uFZE97MzEx3rVajTwj0KX+Mb6MY+5rqR9W6eIgkAOERwPxAUM3rU+B7e3sv0S+oQD1Ab9Cn03dg6/r6R0dHr6DQ8CDX4D/qM4qo4yQDKRZk4XM0T1VcBAxHube394mZiWo8qKXM8+DR51PMYwpFhs9MRVRy7PdAFUhnZ+cLQNtUfcCjHzO/v7+/ad4T1bjdkg1tW/Ixx2hOmtvURSk7y0AKChnUjwxag3jBCrIOEPSpp1Vs9XU8MMgm4b0zDgF2FucwVHYCVHF7yGKL0z02lsMpQIqQICKT3gFIhhMxZV46nc6hqv03Z56z+tq/4Fn92fYUMAKnd8EpnLVzTEg+UzRH3PBorc4z0ASGz0ENYMu+hU6/4pjjtoys28Y5ii1Lf/45OdoKoCKAj/NksKUfoE9fJrqC9pI3Rn/b7mJshV7I8T74y9NLIwSEgBAQAkJACAgBISAEYiXwDzdEhNQ/vBCCAAAAAElFTkSuQmCC"",
                                                    ""width"": ""20px""
                                                }
                                            ],
                                            ""spacing"": ""None""
                                        },
                                        {
                                            ""type"": ""Column"",
                                            ""$when"": ""${flag == true}"",
                                            ""width"": ""auto"",
                                            ""items"": [
                                                {
                                                    ""type"": ""Image"",
                                                    ""altText"": ""Flag"",
                                                    ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAERlWElmTU0AKgAAAAgAAYdpAAQAAAABAAAAGgAAAAAAA6ABAAMAAAABAAEAAKACAAQAAAABAAAAUKADAAQAAAABAAAAUAAAAAAx4ExPAAABkklEQVR4Ae3ZQY7CQAxEUQbNcXOc3Bf2Kam/Sm5QRvPZxeUm4aVjIXg8fCmggAIKKKCAAgr8R4Gf6Yc+z/M1fY9m/XEc42tuzke9T2owXwsIuPbBVEAkWjf8ruM+3T2jvj1j20/sDmzFLv0CXkDaQwFbsUv/9hl4ef/th5+eie0MdwcOb7GAAg4Fhsv/3AxsZxT5TGeqjzAJQy4gAFEsIAlBLiAAUSwgCUEuIABRLCAJQS4gAFEsIAlBLiAAUSwgCUEuIABRLCAJQS4gAFEsIAlBvv33wOnva3C9t4vdgcNbIqCAQ4Hh8u0z8G7/WQx9cLmPMBKtGwRc+2AqIBKtG7bPwPXp5undvme6A4f3VEABhwLD5befgbu/Vw69YrmPcJB0BQE7r+gWMEi6goCdV3QLGCRdQcDOK7oFDJKuIGDnFd0CBklXELDzim4Bg6QrCNh5RbeAQdIVBOy8olvAIOkKAnZe0S1gkHQFATuv6BYwSLqCgJ1XdAsYJF1BwM4rugUMEgsKKKCAAgoooIACCrDAG3AuG0nc+SeBAAAAAElFTkSuQmCC"",
                                                    ""width"": ""20px""
                                                }
                                            ],
                                            ""spacing"": ""Small""
                                        }
                                    ]
                                },
                                {
                                    ""type"": ""ColumnSet"",
                                    ""columns"": [
                                        {
                                            ""type"": ""Column"",
                                            ""width"": ""stretch"",
                                            ""items"": [
                                                {
                                                    ""type"": ""TextBlock"",
                                                    ""text"": ""${subject}"",
                                                    ""spacing"": ""None"",
                                                    ""size"": ""default""
                                                }
                                            ],
                                            ""verticalContentAlignment"": ""Center""
                                        },
                                        {
                                            ""type"": ""Column"",
                                            ""width"": ""auto"",
                                            ""items"": [
                                                {
                                                    ""type"": ""TextBlock"",
                                                    ""text"": ""${date}"",
                                                    ""spacing"": ""None"",
                                                    ""isSubtle"": true,
                                                    ""size"": ""Small"",
                                                    ""horizontalAlignment"": ""Right""
                                                }
                                            ],
                                            ""verticalContentAlignment"": ""Center""
                                        }
                                    ],
                                    ""spacing"": ""None""
                                },
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""${preview}"",
                                    ""spacing"": ""None"",
                                    ""isSubtle"": true,
                                    ""size"": ""default""
                                }
                            ]
                        }
                    ],
                    ""selectAction"": {
                        ""type"": ""Action.OpenUrl"",
                        ""title"": ""${linkTitle}"",
                        ""url"": ""${link}""
                    },
                    ""spacing"": ""ExtraLarge"",
                    ""separator"": true
                }
            ]
        },
        {
            ""type"": ""Container"",
            ""spacing"": ""Padding""
        },
        {
            ""type"": ""Container"",
            ""separator"": true,
            ""spacing"": ""None""
        },
        {
            ""type"": ""ColumnSet"",
            ""columns"": [
                {
                    ""type"": ""Column"",
                    ""width"": ""auto"",
                    ""items"": [
                        {
                            ""type"": ""Image"",
                            ""altText"": ""${attribution.iconAltText}"",
                            ""url"": ""data:image/png;base64,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"",
                            ""spacing"": ""None"",
                            ""width"": ""16px"",
                            ""horizontalAlignment"": ""Left""
                        }
                    ],
                    ""spacing"": ""None"",
                    ""verticalContentAlignment"": ""Center""
                },
                {
                    ""type"": ""Column"",
                    ""width"": ""stretch"",
                    ""items"": [
                        {
                            ""type"": ""TextBlock"",
                            ""text"": ""Outlook"",
                            ""horizontalAlignment"": ""Left"",
                            ""size"": ""Small"",
                            ""spacing"": ""None""
                        }
                    ],
                    ""verticalContentAlignment"": ""Center""
                },
                {
                    ""type"": ""Column"",
                    ""width"": ""auto"",
                    ""items"": [
                        {
                            ""type"": ""RichTextBlock"",
                            ""horizontalAlignment"": ""Right"",
                            ""inlines"": [
                                {
                                    ""type"": ""TextRun"",
                                    ""text"": ""${attribution.linkLabel}"",
                                    ""size"": ""Small"",
                                    ""selectAction"": {
                                        ""title"": ""${attribution.linkAltText}"",
                                        ""type"": ""Action.OpenUrl"",
                                        ""url"": ""${attribution.linkUrl}""
                                    }
                                }
                            ]
                        }
                    ],
                    ""verticalContentAlignment"": ""Center""
                }
            ],
            ""spacing"": ""Medium""
        }
    ],
    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""version"": ""1.2""
}";
            var expectedString = @"{
      ""type"": ""AdaptiveCard"",
      ""speak"": ""${speak}"",
      ""body"": [
        {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""ColumnSet"",
              ""columns"": [
                {
                  ""type"": ""Column"",
                  ""width"": ""auto"",
                  ""items"": [
                    {
                      ""type"": ""Image"",
                      ""altText"": ""Envelope"",
                      ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAyNJREFUeAHt2OtqE0EYBuB3WksiqEnVCxBEEOqlpZUewOqvFTxEaBLb5NIMCCJ4AWpS9UdCSdaZXb80Wbe7O5k2mYR3IUwO++1+82SOC/CgAAUoQAEKUIACFKAABShAAQpQgAIUoAAFKEABClCAAusvoHKrePwpzD1nnU+oP8s02ljnui+ibgR0VCagI+At63ilfiJUTWxvnOHF09/W8T4GBF/uYXixh3B8oNPbtkkxc4CMLnTVJLIOkB8+30VvvAcVHiAM76fC5Uwi8wPK3VYRsgic1O/GAeVGBhJooLrZ9rZr28BJvXIA55hEVACFvlx/UpouEIZv0R99w8vuK5hkfTlMLiYnkxvGb1K7a1QnXTfLwx6wvvMalduPgBWAnIYzf27aOCdwpk6mbpaH/Rg43aTrXys4HzwHwn2EqKbeW6kf+rcGymgj2PmTes51f2ng+qNdfdnDVDRzvxiuhUr5FMePzycpJCfN6fpOTrp84wYo1/EF0sD1RjWNc3QlHNCDUh//g5O6LAVQbm7WU4OhbpHY16/09dRNtMigewcD7Go40+IeSDqJsqc/t1AunSJ48ivx2+XHpQJKGouCLAqnNpoobZ1lwknuXgBKMkVW+KZFAicooVN4jDRwQ9R0nOmq6S0uWlapVmE4ydkrQEkqapEXuotlrPiLQBaFM1vN8paetDK6quSWLL0ElCSjQT5n6wT1XY9ljZkWaQPnukf3GnAaMm+ZYSARnsQh6ki/fyjhM+V174AsAe2fxsxkP+eH+CnOO71baf9br5nNfGIsi8Dq8R1SHorHXb657K3jcgDFfRoyXr9lLUPiKFkGVTc7Puy5lws4C/keQbeNgUpfzxWZZOR6Cyz9AJQKx1u9GHKoanoLeBj9lJxU5HwPSr8ABSSGrOsW2Ym+WtQeWu5vUfoJKBXwGE5StH+cJZEsIwECOjYEAhLQUcAxnC2QgI4CjuFsgQR0FHAMZwskoKOAYzhbIAEdBRzD7R8mJB95Oyaw6uHswo7/IAEJ6CjAcApQgAIUoAAFKEABClCAAhSgAAUoQAEKUIACFKAABShAgVyBvyaVcRhWOA8BAAAAAElFTkSuQmCC"",
                      ""width"": ""20px"",
                      ""horizontalAlignment"": ""Center""
                    }
                  ]
                },
                {
                  ""type"": ""Column"",
                  ""width"": ""stretch"",
                  ""items"": [
                    {
                      ""type"": ""ColumnSet"",
                      ""columns"": [
                        {
                          ""type"": ""Column"",
                          ""width"": ""stretch"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""Jim Kirk"",
                              ""weight"": ""Bolder"",
                              ""horizontalAlignment"": ""Left""
                            }
                          ],
                          ""spacing"": ""None"",
                          ""verticalContentAlignment"": ""Center""
                        },
                        {
                          ""type"": ""Column"",
                          ""width"": ""auto"",
                          ""items"": [
                            {
                              ""type"": ""Image"",
                              ""altText"": ""Flag"",
                              ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAERlWElmTU0AKgAAAAgAAYdpAAQAAAABAAAAGgAAAAAAA6ABAAMAAAABAAEAAKACAAQAAAABAAAAUKADAAQAAAABAAAAUAAAAAAx4ExPAAABkklEQVR4Ae3ZQY7CQAxEUQbNcXOc3Bf2Kam/Sm5QRvPZxeUm4aVjIXg8fCmggAIKKKCAAgr8R4Gf6Yc+z/M1fY9m/XEc42tuzke9T2owXwsIuPbBVEAkWjf8ruM+3T2jvj1j20/sDmzFLv0CXkDaQwFbsUv/9hl4ef/th5+eie0MdwcOb7GAAg4Fhsv/3AxsZxT5TGeqjzAJQy4gAFEsIAlBLiAAUSwgCUEuIABRLCAJQS4gAFEsIAlBLiAAUSwgCUEuIABRLCAJQS4gAFEsIAlBvv33wOnva3C9t4vdgcNbIqCAQ4Hh8u0z8G7/WQx9cLmPMBKtGwRc+2AqIBKtG7bPwPXp5undvme6A4f3VEABhwLD5befgbu/Vw69YrmPcJB0BQE7r+gWMEi6goCdV3QLGCRdQcDOK7oFDJKuIGDnFd0CBklXELDzim4Bg6QrCNh5RbeAQdIVBOy8olvAIOkKAnZe0S1gkHQFATuv6BYwSLqCgJ1XdAsYJF1BwM4rugUMEgsKKKCAAgoooIACCrDAG3AuG0nc+SeBAAAAAElFTkSuQmCC"",
                              ""width"": ""20px""
                            }
                          ],
                          ""spacing"": ""Small""
                        }
                      ]
                    },
                    {
                      ""type"": ""ColumnSet"",
                      ""columns"": [
                        {
                          ""type"": ""Column"",
                          ""width"": ""stretch"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""RE: First Email Subject"",
                              ""spacing"": ""None"",
                              ""size"": ""default""
                            }
                          ],
                          ""verticalContentAlignment"": ""Center""
                        },
                        {
                          ""type"": ""Column"",
                          ""width"": ""auto"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""6/2/2017"",
                              ""spacing"": ""None"",
                              ""isSubtle"": true,
                              ""size"": ""Small"",
                              ""horizontalAlignment"": ""Right""
                            }
                          ],
                          ""verticalContentAlignment"": ""Center""
                        }
                      ],
                      ""spacing"": ""None""
                    },
                    {
                      ""type"": ""TextBlock"",
                      ""text"": ""First Email Preview"",
                      ""spacing"": ""None"",
                      ""isSubtle"": true,
                      ""size"": ""default""
                    }
                  ]
                }
              ],
              ""selectAction"": {
                ""type"": ""Action.OpenUrl"",
                ""title"": ""Email from Jim Kirk about RE: First Email Subject"",
                ""url"": ""https://outlook.office365.com/owa/?ItemID=1""
              },
              ""spacing"": ""ExtraLarge"",
              ""separator"": true
            },
            {
              ""type"": ""ColumnSet"",
              ""columns"": [
                {
                  ""type"": ""Column"",
                  ""width"": ""auto"",
                  ""items"": [
                    {
                      ""type"": ""Image"",
                      ""altText"": ""Envelope"",
                      ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAyNJREFUeAHt2OtqE0EYBuB3WksiqEnVCxBEEOqlpZUewOqvFTxEaBLb5NIMCCJ4AWpS9UdCSdaZXb80Wbe7O5k2mYR3IUwO++1+82SOC/CgAAUoQAEKUIACFKAABShAAQpQgAIUoAAFKEABClCAAusvoHKrePwpzD1nnU+oP8s02ljnui+ibgR0VCagI+At63ilfiJUTWxvnOHF09/W8T4GBF/uYXixh3B8oNPbtkkxc4CMLnTVJLIOkB8+30VvvAcVHiAM76fC5Uwi8wPK3VYRsgic1O/GAeVGBhJooLrZ9rZr28BJvXIA55hEVACFvlx/UpouEIZv0R99w8vuK5hkfTlMLiYnkxvGb1K7a1QnXTfLwx6wvvMalduPgBWAnIYzf27aOCdwpk6mbpaH/Rg43aTrXys4HzwHwn2EqKbeW6kf+rcGymgj2PmTes51f2ng+qNdfdnDVDRzvxiuhUr5FMePzycpJCfN6fpOTrp84wYo1/EF0sD1RjWNc3QlHNCDUh//g5O6LAVQbm7WU4OhbpHY16/09dRNtMigewcD7Go40+IeSDqJsqc/t1AunSJ48ivx2+XHpQJKGouCLAqnNpoobZ1lwknuXgBKMkVW+KZFAicooVN4jDRwQ9R0nOmq6S0uWlapVmE4ydkrQEkqapEXuotlrPiLQBaFM1vN8paetDK6quSWLL0ElCSjQT5n6wT1XY9ljZkWaQPnukf3GnAaMm+ZYSARnsQh6ki/fyjhM+V174AsAe2fxsxkP+eH+CnOO71baf9br5nNfGIsi8Dq8R1SHorHXb657K3jcgDFfRoyXr9lLUPiKFkGVTc7Puy5lws4C/keQbeNgUpfzxWZZOR6Cyz9AJQKx1u9GHKoanoLeBj9lJxU5HwPSr8ABSSGrOsW2Ym+WtQeWu5vUfoJKBXwGE5StH+cJZEsIwECOjYEAhLQUcAxnC2QgI4CjuFsgQR0FHAMZwskoKOAYzhbIAEdBRzD7R8mJB95Oyaw6uHswo7/IAEJ6CjAcApQgAIUoAAFKEABClCAAhSgAAUoQAEKUIACFKAABShAgVyBvyaVcRhWOA8BAAAAAElFTkSuQmCC"",
                      ""width"": ""20px"",
                      ""horizontalAlignment"": ""Center""
                    }
                  ]
                },
                {
                  ""type"": ""Column"",
                  ""width"": ""stretch"",
                  ""items"": [
                    {
                      ""type"": ""ColumnSet"",
                      ""columns"": [
                        {
                          ""type"": ""Column"",
                          ""width"": ""stretch"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""Jim Kirk"",
                              ""weight"": ""Bolder"",
                              ""horizontalAlignment"": ""Left""
                            }
                          ],
                          ""spacing"": ""None"",
                          ""verticalContentAlignment"": ""Center""
                        },
                        {
                          ""type"": ""Column"",
                          ""width"": ""auto"",
                          ""items"": [
                            {
                              ""type"": ""Image"",
                              ""altText"": ""Paperclip"",
                              ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAABQCAYAAACOEfKtAAAAAXNSR0IArs4c6QAAAERlWElmTU0AKgAAAAgAAYdpAAQAAAABAAAAGgAAAAAAA6ABAAMAAAABAAEAAKACAAQAAAABAAAAUKADAAQAAAABAAAAUAAAAAAx4ExPAAAEv0lEQVR4Ae2cTUhUURTHZ8aR0NB9tbWlNKDOpogIqU0tWgtDCSI6s2vRrkjaFLSbGTGVJIiWhbopIsZFUH6Q2ta17TWRwXGm/xnevdx3eeLoee/dgc6Dxz333HPuu+c35773BM9LJOQQAkJACAgBISAEhIAQ+B8JJNsh6EajkSqXy8Nos8lkchDtkLeudbRr0K1OTk5+RVtvh/Waa3AOsFQq9QHYAhZ13VxYgPwdAB/m8/mdgDFnqpSzK+PCyLo8mi2cp8GjZZLNludD/bY4nGUggajX68XzUEilUgVs6dJ5fMP2cQKQti0C2cLW7VYBYXs2IM8BziLODdID8MDx8fF9jI3B1lzrAXSZdtjOaRVAXC1ApABwAdfT8CDvAtrIxMREBbJ5LKOzPD09/QEg30O+7A1epPsmzpsA6fTBYv6q5sIjkwHvDgL/rC5AmQd4twPgKZNmC4i3kJHf4KvXDN+7yMIvPsOYO7E/RAAga8aI/uxp8MiebMjW8vXNZY7FJccOEIGpd7xmjB0dHUutBhtg65ur1XnCtHMBcNAMQD0wTN1JcoCtb66T/KLUuwCoHgTNuMbHx/+0GmCArW+uVucJ084FwDDX73yu2F9joo64WCzS+6Q+CoWCfmprZYiCZCATpgAUgEwCTPe2uwfGfQ9j8kvIFmYSFIACkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjukoECkEmA6S4ZKACZBJjusWcg6tv+mmuen5/31Xpg3Fc3gho5Xc5lyjSHbRswl+9a5nXDkl38iy8BuqoCqFarVG20qPqoh6NS13uqjwLD1wD3mPokKz21nq1WHR4e2qVfvh9DG4YoxJ6BWPuutX5f0MgqDZPsAOkGSl1/0kmy6WvbohTMLv2yr2W6hyLHDhAQVsyVo6+3KOlRiT6HpkLyKUfFs9Vm9lz2tbRhiELsAFFx+clcP4IcxhbV30xAVjW6urpGYFMx7Sy5QjZkq/Q0B82l+tRi/KPZj0KOtAzqpAWjlGEbY/1qHIHu9PT0ZHK53IHSAUYSUMZw36OS/wHSQ7eBbbqE2uFZE97MzEx3rVajTwj0KX+Mb6MY+5rqR9W6eIgkAOERwPxAUM3rU+B7e3sv0S+oQD1Ab9Cn03dg6/r6R0dHr6DQ8CDX4D/qM4qo4yQDKRZk4XM0T1VcBAxHube394mZiWo8qKXM8+DR51PMYwpFhs9MRVRy7PdAFUhnZ+cLQNtUfcCjHzO/v7+/ad4T1bjdkg1tW/Ixx2hOmtvURSk7y0AKChnUjwxag3jBCrIOEPSpp1Vs9XU8MMgm4b0zDgF2FucwVHYCVHF7yGKL0z02lsMpQIqQICKT3gFIhhMxZV46nc6hqv03Z56z+tq/4Fn92fYUMAKnd8EpnLVzTEg+UzRH3PBorc4z0ASGz0ENYMu+hU6/4pjjtoys28Y5ii1Lf/45OdoKoCKAj/NksKUfoE9fJrqC9pI3Rn/b7mJshV7I8T74y9NLIwSEgBAQAkJACAgBISAEYiXwDzdEhNQ/vBCCAAAAAElFTkSuQmCC"",
                              ""width"": ""20px""
                            }
                          ],
                          ""spacing"": ""None""
                        }
                      ]
                    },
                    {
                      ""type"": ""ColumnSet"",
                      ""columns"": [
                        {
                          ""type"": ""Column"",
                          ""width"": ""stretch"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""Second Email Subject"",
                              ""spacing"": ""None"",
                              ""size"": ""default""
                            }
                          ],
                          ""verticalContentAlignment"": ""Center""
                        },
                        {
                          ""type"": ""Column"",
                          ""width"": ""auto"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""6/1/2017"",
                              ""spacing"": ""None"",
                              ""isSubtle"": true,
                              ""size"": ""Small"",
                              ""horizontalAlignment"": ""Right""
                            }
                          ],
                          ""verticalContentAlignment"": ""Center""
                        }
                      ],
                      ""spacing"": ""None""
                    },
                    {
                      ""type"": ""TextBlock"",
                      ""text"": ""Second Email Preview"",
                      ""spacing"": ""None"",
                      ""isSubtle"": true,
                      ""size"": ""default""
                    }
                  ]
                }
              ],
              ""selectAction"": {
                ""type"": ""Action.OpenUrl"",
                ""title"": ""Email from Jim Kirk about Second Email Subject"",
                ""url"": ""https://outlook.office365.com/owa/?ItemID=1""
              },
              ""spacing"": ""ExtraLarge"",
              ""separator"": true
            }
          ]
        },
        {
          ""type"": ""Container"",
          ""spacing"": ""Padding""
        },
        {
          ""type"": ""Container"",
          ""separator"": true,
          ""spacing"": ""None""
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""width"": ""auto"",
              ""items"": [
                {
                  ""type"": ""Image"",
                  ""altText"": ""more in Outlook"",
                  ""url"": ""data:image/png;base64,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"",
                  ""spacing"": ""None"",
                  ""width"": ""16px"",
                  ""horizontalAlignment"": ""Left""
                }
              ],
              ""spacing"": ""None"",
              ""verticalContentAlignment"": ""Center""
            },
            {
              ""type"": ""Column"",
              ""width"": ""stretch"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Outlook"",
                  ""horizontalAlignment"": ""Left"",
                  ""size"": ""Small"",
                  ""spacing"": ""None""
                }
              ],
              ""verticalContentAlignment"": ""Center""
            },
            {
              ""type"": ""Column"",
              ""width"": ""auto"",
              ""items"": [
                {
                  ""type"": ""RichTextBlock"",
                  ""horizontalAlignment"": ""Right"",
                  ""inlines"": [
                    {
                      ""type"": ""TextRun"",
                      ""text"": ""more in Outlook"",
                      ""size"": ""Small"",
                      ""selectAction"": {
                        ""title"": ""more in Outlook"",
                        ""type"": ""Action.OpenUrl"",
                        ""url"": ""https://outlook.office365.com/owa/""
                      }
                    }
                  ]
                }
              ],
              ""verticalContentAlignment"": ""Center""
            }
          ],
          ""spacing"": ""Medium""
        }
      ],
      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
      ""version"": ""1.2""
}";
            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = templateData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestExpression()
        {
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
            ""text"": ""${machines.id}"",
            ""color"": ""${if(machines.uptime >= 3000, 'good', 'attention')}""
        }
    ]
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

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

        /// <summary>
        /// Test that when expression fails to evaluate, it leaves the expression stirng untouched
        /// </summary>
        [TestMethod]
        public void TestCanHandleFailedExpressionEvaluation()
        {
            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""$data"": {
                ""machines"": {
                    ""id"": ""primary""
                }
     },
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""${machines.id}"",
            ""color"": ""${if(machines.uptime >= 3000, 'good', 'attention')}""
        }
    ]
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

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

        /// <summary>
        /// Test that when expression fails to evaluate, it leaves the expression stirng untouched
        /// </summary>
        [TestMethod]
        public void TestCanHandleUndefinedFunctions()
        {
            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""$data"": {
                ""firstname"": ""David"",
                ""lastName"" : ""Claux""
    },
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""${firstName} ${if(unknownFunction(lastName), 'yes', 'no'}""
        }
    ]
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""David ${if(unknownFunction(lastName), 'yes', 'no'}""
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestWhen()
        {
            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""$data"": {
                ""machines"": {
                    ""id"": ""primary"",
                    ""uptime"": 3231
                }
     },
    ""body"": [
        {
            ""$when"": ""${(machines.uptime >= 3000)}"",
            ""type"": ""TextBlock"",
            ""text"": ""${machines.id}""
        }
    ]
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""primary""
        }
    ]
}", cardJson);
        }
        [TestMethod]
        public void TestWhenWithArray()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${LineItems}"",
                    ""type"": ""TextBlock"",
                    ""$when"": ""${Milage > 0}"",
                    ""text"": ""${Milage}""
                  }
                ]
              }
            ]
        }";

            string jsonData = @"{
              ""LineItems"": [
                    {""Milage"" : 1},
                    {""Milage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": 1
                },
                {
                    ""type"": ""TextBlock"",
                    ""text"": 10
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestWhenWithArrayWithPropoerCommanRemoval()
        {
            string jsonTemplate =
                @"{
                     ""type"": ""AdaptiveCard"",
                     ""body"": [
                         {
                             ""type"": ""TextBlock"",
                             ""size"": ""Medium"",
                             ""weight"": ""Bolder"",
                             ""text"": ""${title}""
                         },
                         {
                             ""type"": ""FactSet"",
                             ""facts"": [
                                 {
                                     ""$data"": ""${people}"",
                                     ""$when"": ""${age > 12}"",
                                     ""title"": ""${firstName} ${lastName}"",
                                     ""value"": ""${string(age)}""
                                 }
                             ]
                         }
                     ],
                     ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                     ""version"": ""1.0""
                 }";

            string jsonData =
                @"{
                    ""title"": ""My list of people:"",
                    ""count"": 4,
                    ""people"": [
                        {
                            ""firstName"": ""Micky"",
                            ""lastName"": ""Mouse"",
                            ""age"": 44
                        },
                        {
                            ""firstName"": ""Donald"",
                            ""lastName"": ""Duck"",
                            ""age"": 12
                        },
                        {
                            ""firstName"": ""Harry"",
                            ""lastName"": ""Potter"",
                            ""age"": 18
                        },
                        {
                            ""firstName"": ""Matt"",
                            ""lastName"": ""Hidinger"",
                            ""age"": ""28""
                        }
                    ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
                 {
                     ""type"": ""TextBlock"",
                     ""size"": ""Medium"",
                     ""weight"": ""Bolder"",
                     ""text"": ""My list of people:""
                 },
                 {
                     ""type"": ""FactSet"",
                     ""facts"": [
                         {
                             ""title"": ""Micky Mouse"",
                             ""value"": ""44""
                         },
                         {
                             ""title"": ""Harry Potter"",
                             ""value"": ""18""
                         },
                         {
                             ""title"": ""Matt Hidinger"",
                             ""value"": ""28""
                         }
                     ]
                 }
            ],
     ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
     ""version"": ""1.0""

}", cardJson);
        }

        [TestMethod]
        public void TestIndex()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": [{""Milage"" : 1}, {""Milage"" : 10}],
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired${$index}"",
                    ""text"": ""${Milage}""
                  }
                ]
              }
            ]
        }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired0"",
                    ""text"": 1
                },
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired1"",
                    ""text"": 10
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestInlineMemoryScope()
        {
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
                                  ""text"": ""${name}""
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

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);
            AssertJsonEqual(cardJson, expectedString);
        }
        [TestMethod]
        public void TestInlineMemoryScope2()
        {
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
                                  ""text"": ""${name}""
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

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);
            AssertJsonEqual(cardJson, expectedString);
        }

        [TestMethod]
        public void TestInlineMemoryScope3()
        {
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
                                  ""text"": ""${name}""
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

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(testString);
            var context = new AdaptiveCardsEvaluationContext();
            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }
    }
    [TestClass]
    public class TestRootKeyword
    {
        [TestMethod]
        public void TestRootInDataContext()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${$root.LineItems}"",
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired${$index}"",
                    ""text"": ""${string(Milage)}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""LineItems"": [
                    {""Milage"" : 1},
                    {""Milage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired0"",
                    ""text"": ""1""
                },
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired1"",
                    ""text"": ""10""
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestCanAccessByAEL()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""type"": ""TextBlock"",
                    ""text"": ""${$root.LineItems[0].Milage}""
                  },
                  {
                    ""type"": ""TextBlock"",
                    ""text"": ""${$root.LineItems[1].Milage}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""LineItems"": [
                    {""Milage"" : 1},
                    {""Milage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": 1
                },
                {
                    ""type"": ""TextBlock"",
                    ""text"": 10
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestWorkWithRepeatingItems()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${$root.LineItems}"",
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: ${$root.Class}, Mileage: ${Mileage}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""Class"" : ""Ship"",
              ""LineItems"": [
                    {""Mileage"" : 1},
                    {""Mileage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: Ship, Mileage: 1""
                },
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: Ship, Mileage: 10""
                }
            ]
        }
    ]
}", cardJson);
        }
    }

    [TestClass]
    public class TestDataKeyword
    {
        [TestMethod]
        public void TestBasic()
        {
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
            ""text"": ""Hello ${$data.person.firstName}""
        }
    ]
}";

            string jsonData = @"{
    ""person"": {
        ""firstName"": ""Andrew"",
        ""lastName"": ""Leader""
    }
}";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
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

        [TestMethod]
        public void TestKeywordDataInRepeatingItems()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${LineItems}"",
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired${$index}"",
                    ""text"": ""${string(Milage)}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""LineItems"": [
                    {""Milage"" : 1},
                    {""Milage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired0"",
                    ""text"": ""1""
                },
                {
                    ""type"": ""TextBlock"",
                    ""id"": ""ReceiptRequired1"",
                    ""text"": ""10""
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestCanAccessByAEL()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""type"": ""TextBlock"",
                    ""text"": ""${$data.LineItems[0].Milage}""
                  },
                  {
                    ""type"": ""TextBlock"",
                    ""text"": ""${$data.LineItems[1].Milage}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""LineItems"": [
                    {""Milage"" : 1},
                    {""Milage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": 1
                },
                {
                    ""type"": ""TextBlock"",
                    ""text"": 10
                }
            ]
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestRootAndDataWorkInRepeatingItems()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                  {
                    ""$data"": ""${$root.LineItems}"",
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: ${$root.Class}, Mileage: ${$data.Mileage}""
                  }
                ]
              }
            ]
        }";
            string jsonData = @"{
              ""Class"" : ""Ship"",
              ""LineItems"": [
                    {""Mileage"" : 1},
                    {""Mileage"" : 10}
                ]
            }";

            AdaptiveCardsTemplate transformer = new AdaptiveCardsTemplate(jsonTemplate);
            var context = new AdaptiveCardsEvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            TestTemplate.AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: Ship, Mileage: 1""
                },
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""Class: Ship, Mileage: 10""
                }
            ]
        }
    ]
}", cardJson);
        }
    }

    [TestClass]
    public class TestPartialResult
    {
        [TestMethod]
        public void TestCreation()
        {
            AdaptiveCardsTemplateResult result = new AdaptiveCardsTemplateResult();
            result.Append("hello world");
            Assert.AreEqual(result.ToString(), "hello world");
        }

        [TestMethod]
        public void TestMerging()
        {
            AdaptiveCardsTemplateResult result1 = new AdaptiveCardsTemplateResult();
            result1.Append("hello");

            AdaptiveCardsTemplateResult result2 = new AdaptiveCardsTemplateResult();
            result2.Append(" world");


            AdaptiveCardsTemplateResult result3 = new AdaptiveCardsTemplateResult();
            result3.Append("!");

            result1.Append(result2);
            result1.Append(result3);

            Assert.AreEqual(result1.ToString(), "hello world!");
        }

        [TestMethod]
        public void TestCreationOfPartialResult()
        {
            AdaptiveCardsTemplateResult result1 = new AdaptiveCardsTemplateResult();
            result1.Append("hello");

            AdaptiveCardsTemplateResult result2 = new AdaptiveCardsTemplateResult();
            result2.Append("name", false);

            AdaptiveCardsTemplateResult result3 = new AdaptiveCardsTemplateResult();
            result3.Append("!");

            result1.Append(result2);
            result1.Append(result3);

            Assert.AreEqual(result1.ToString(), "hello{name}!");
        }
        public void TestCreationOfWhen()
        {
            AdaptiveCardsTemplateResult result1 = new AdaptiveCardsTemplateResult();
            result1.Append("hello");

            AdaptiveCardsTemplateResult result2 = new AdaptiveCardsTemplateResult();
            result2.Append("name", false);

            AdaptiveCardsTemplateResult result3 = new AdaptiveCardsTemplateResult();
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
            var (value, error) = new ValueExpression("${person.firstName}man").TryGetValue(token as JObject);
            Assert.AreEqual("Superman", value);
        }

        [TestMethod]
        public void TestIndex()
        {
            string jsonData = @"{
            ""$index"": 0
            }";

            JToken token = JToken.Parse(jsonData);
            var (value, error) = new ValueExpression("${$index}").TryGetValue(token as JObject);
            Assert.AreEqual("0", value);
        }

        [TestMethod]
        public void TestEqual()
        {
            string jsonData = @"{
            ""attachment"": false 
            }";

            JToken token = JToken.Parse(jsonData);
            var expr = Expression.Parse("attachment == true");
            var result =  expr.TryEvaluate(token); 
            Assert.IsNull(result.error);
            Assert.AreEqual(false, result.value);
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

            Stopwatch.StartNew();
            var beginTime0 = Stopwatch.GetTimestamp();
            JToken token = JToken.Parse(jsonData);
            var endTime0 = Stopwatch.GetTimestamp();
            Console.WriteLine("time0 took: " + (endTime0 - beginTime0));
            var beginTime1 = Stopwatch.GetTimestamp();
            var (value, error) = new ValueExpression("${string(person.age)}").TryGetValue(token as JObject);
            var endTime1 = Stopwatch.GetTimestamp();
            Console.WriteLine("time1 took: " + (endTime1 - beginTime1));
            Assert.AreEqual("79", value);
        }
    }
}
