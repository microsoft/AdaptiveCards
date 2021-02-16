using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using AdaptiveExpressions.Properties;
using AdaptiveExpressions;
using System.Diagnostics;
using System;
using AdaptiveExpressions.Memory;

namespace AdaptiveCards.Templating.Test
{
    [TestClass]
    public sealed class TestTemplate
    {
        [TestMethod]
        public void TestPerf()
        {
            // Test with very large data
            string jsonTemplate = @"{
  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
  ""type"": ""AdaptiveCard"",
  ""originator"": ""b3bb9c26-77fc-4694-a14d-e5b9c2fffc73"",
  ""correlationId"": null,
  ""constrainWidth"": true,
  ""version"": ""1.0"",
  ""fallbackText"": ""This device does not support yet, please upgrade your outlook version"",
  ""hideOriginalBody"": true,
  ""autoInvokeAction"": {
    ""type"": ""Action.Http"",
    ""method"": ""POST"",
    ""hideCardOnInvoke"": true,
    ""url"": ""#MSApprovalsCoreServiceURL#/api/v1/AutoRefresh/#TenantId#?SessionId=#SessionId#"",
    ""body"": ""{\""ApproverList\"":\""#ApproverList#\"",\""DocumentNumber\"":\""#ApprovalIdentifier.DisplayDocumentNumber#\"", \""RequestVersion\"": \""#RequestVersion#\""}""
  },
  ""autoInvokeOptions"": {
    ""showCardOnFailure"": true
  },
  ""body"": [
    {
      ""type"": ""Container"",
      ""style"": ""emphasis"",
      ""verticalContentAlignment"": ""Center"",
      ""id"": ""MSAHeader"",
      ""items"": [
        {
          ""type"": ""TextBlock"",
          ""speak"": ""Approvals"",
          ""text"": ""Approvals"",
          ""weight"": ""Bolder"",
          ""size"": ""ExtraLarge"",
          ""horizontalAlignment"": ""Center""
        },
        {
          ""type"": ""TextBlock"",
          ""text"": ""${AppName}"",
          ""weight"": ""Bolder"",
          ""horizontalAlignment"": ""Center""
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""items"": [
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""width"": ""auto"",
              ""verticalContentAlignment"": ""center"",
              ""items"": [
                {
                  ""type"": ""Image"",
                  ""url"": ""data:image/jpeg;base64,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"",
                  ""style"": ""Person"",
                  ""size"": ""small"",
                  ""horizontalAlignment"": ""Left"",
                  ""altText"": """"
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""width"": ""stretch"",
              ""verticalContentAlignment"": ""center"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${Submitter.Name}"",
                  ""weight"": ""Bolder"",
                  ""wrap"": true,
                  ""size"": ""Large"",
                  ""spacing"": ""Small""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${ApprovalIdentifier.DisplayDocumentNumber}"",
                  ""wrap"": true,
                  ""isSubtle"": true,
                  ""spacing"": ""Small""
                },
                {
                  ""type"": ""TextBlock"",
                  ""$when"": ""${and(exists(DetailPageURL), DetailPageURL != '')}"",
                  ""text"": ""[View details in ${ToolName}](${DetailPageURL})""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${Title}"",
                  ""size"": ""None"",
                  ""wrap"": true,
                  ""spacing"": ""Small""
                },
                {
                  ""type"": ""TextBlock"",
                  ""$when"": ""${and(exists(CustomAttribute), CustomAttribute.CustomAttributeValue != '')}"",
                  ""text"": ""${CustomAttribute.CustomAttributeValue}"",
                  ""size"": ""Small"",
                  ""wrap"": true,
                  ""spacing"": ""Small""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""Container"",
          ""id"": ""ApproverNotesSection"",
          ""$when"": ""${and(exists(ApproverNotes), ApproverNotes != '')}"",
          ""style"": ""emphasis"",
          ""spacing"": ""Small"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Notes: ${ApproverNotes}"",
              ""size"": ""Small"",
              ""wrap"": true
            }
          ]
        },
        {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""Image"",
              ""url"": ""https://msapprovalsdevenv.blob.core.windows.net/outlookactionableemailicons/money-icon.png?sv=2015-12-11&sr=c&sig=HCMADhx7xD3%2F6fA8viVd3f3vcwGp%2BNc25XgiSZCNcIE%3D&se=2021-03-02T08%3A26%3A06Z&sp=r"",
              ""size"": ""Small"",
              ""horizontalAlignment"": ""Center"",
              ""spacing"": ""None"",
              ""altText"": """"
            },
            {
              ""type"": ""TextBlock"",
              ""text"": ""${UnitValue} ${UnitOfMeasure}"",
              ""weight"": ""Bolder"",
              ""color"": ""Accent"",
              ""size"": ""Large"",
              ""spacing"": ""None"",
              ""horizontalAlignment"": ""Center""
            },
            {
              ""type"": ""TextBlock"",
              ""text"": ""Total expense amount"",
              ""size"": ""Small"",
              ""isSubtle"": true,
              ""spacing"": ""None"",
              ""horizontalAlignment"": ""Center""
            }
          ]
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""style"": ""emphasis"",
      ""items"": [
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Delegate Submitter"",
                  ""weight"": ""Lighter""
                }
              ],
              ""width"": ""1""
            },
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${AdditionalData.MS_IT_Submitter}"",
                  ""horizontalAlignment"": ""Right""
                }
              ],
              ""width"": ""1""
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""$when"": ""${AdditionalData.MS_IT_PreApprovalNumber != ''}"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Pre-Approval Number"",
                  ""weight"": ""Lighter""
                }
              ],
              ""width"": ""1""
            },
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${AdditionalData.MS_IT_PreApprovalNumber}"",
                  ""horizontalAlignment"": ""Right""
                }
              ],
              ""width"": ""1""
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Submitted Date"",
                  ""weight"": ""Lighter""
                }
              ],
              ""width"": ""1""
            },
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""{{DATE(${formatDateTime(SubmittedDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                  ""horizontalAlignment"": ""Right""
                }
              ],
              ""width"": ""1""
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Status"",
                  ""weight"": ""Lighter""
                }
              ],
              ""width"": ""1""
            },
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Pending Approval"",
                  ""color"": ""warning"",
                  ""horizontalAlignment"": ""Right""
                }
              ],
              ""width"": ""1""
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""$data"": ""${Approvers}"",
          ""id"": ""ApprovalHierarchy${$index}"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${Type} Approver"",
                  ""weight"": ""Lighter""
                }
              ],
              ""width"": ""2""
            },
            {
              ""type"": ""Column"",
              ""id"": ""ActionDetail${$index}"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${Name} (${Alias})"",
                  ""wrap"": true,
                  ""horizontalAlignment"": ""Right""
                },
                {
                  ""type"": ""TextBlock"",
                  ""id"": ""Action${$index}"",
                  ""$when"": ""${Action != ''}"",
                  ""text"": ""${Action} on {{DATE(${formatDateTime(ActionDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                  ""wrap"": true,
                  ""horizontalAlignment"": ""Right"",
                  ""spacing"": ""None""
                }
              ],
              ""width"": ""3""
            },
            {
              ""type"": ""Column"",
              ""verticalContentAlignment"": ""Center"",
              ""id"": ""approverStatusIcons${$index}"",
              ""items"": [
                {
                  ""type"": ""Image"",
                  ""$when"": ""${or(equals(Action, 'Approval'), equals(Action, 'Complete'))}"",
                  ""url"": ""https://msapprovalsdevenv.blob.core.windows.net/outlookactionableemailicons/greenTick.png?sv=2015-12-11&sr=c&sig=HCMADhx7xD3%2F6fA8viVd3f3vcwGp%2BNc25XgiSZCNcIE%3D&se=2021-03-02T08%3A26%3A06Z&sp=r"",
                  ""horizontalAlignment"": ""Center"",
                  ""altText"": """"
                },
                {
                  ""type"": ""Image"",
                  ""$when"": ""${and(equals(Action, ''), not(_future))}"",
                  ""url"": ""https://msapprovalsdevenv.blob.core.windows.net/outlookactionableemailicons/refresh.png?sv=2015-12-11&sr=c&sig=HCMADhx7xD3%2F6fA8viVd3f3vcwGp%2BNc25XgiSZCNcIE%3D&se=2021-03-02T08%3A26%3A06Z&sp=r"",
                  ""horizontalAlignment"": ""Center"",
                  ""altText"": """"
                },
                {
                  ""type"": ""Image"",
                  ""$when"": ""${Action == 'Rejection'}"",
                  ""url"": ""https://msapprovalsdevenv.blob.core.windows.net/outlookactionableemailicons/error.png?sv=2015-12-11&sr=c&sig=HCMADhx7xD3%2F6fA8viVd3f3vcwGp%2BNc25XgiSZCNcIE%3D&se=2021-03-02T08%3A26%3A06Z&sp=r"",
                  ""horizontalAlignment"": ""Center"",
                  ""altText"": """"
                }
              ]
            }
          ]
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""id"": ""dataToToggle"",
      ""items"": [
        {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""## Line Items ##"",
              ""size"": ""Medium"",
              ""weight"": ""Bolder""
            }
          ]
        },
        {
          ""type"": ""Container"",
          ""items"": [
            {
              ""type"": ""Container"",
              ""separator"": true,
              ""$data"": ""${LineItems}"",
              ""items"": [
                {
                  ""type"": ""ColumnSet"",
                  ""id"": ""LineItemHeader${$index}"",
                  ""columns"": [
                    {
                      ""type"": ""Column"",
                      ""items"": [
                        {
                          ""type"": ""ColumnSet"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""id"": ""ReceiptsRequiredHeader${$index}"",
                              ""verticalContentAlignment"": ""Center"",
                              ""width"": ""1"",
                              ""items"": [
                                {
                                  ""$when"": ""${ReceiptsRequired}"",
                                  ""type"": ""Image"",
                                  ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAkAAAASCAYAAACJgPRIAAABJ0lEQVQoU2NkgAL72ff+H7z3jcFRkYthf5oSI0wcRIM58l23/vtp8jJM9pUE8xU6b/1/UK4GVwhm2M968P9gmgJcUKD+xv8PjRpoikBWpSKswGqSw+yH/w+kysN1whTFr3r8f2GYLCOKdYwVV/7/79BhxKuIofzyf4ZOXbiiuNWP/y8KhZrkOPPB//3pCowMlVf+M7TjMgnmcGIUYbrpyf+FYTKoDmeovPafoV2LERS4D8vUGONXYVFEnO+gJsGCIGH1k/8LQtGtq7j8n6EDKQhWPvq/KFwO4iaDSXf/X8hTZmSouPqfoUObUaDh2v8PDVqMAQsf/d8QD1UECx/0yBZsvP7/fb0mxCRsyUOx/eZ/X11+hkk+EghFMGsvPvvOIC/IxoCcngDOkN4TZSb/CgAAAABJRU5ErkJggg=="",
                                  ""horizontalAlignment"": ""Center"",
                                  ""altText"": """"
                                },
                                {
                                  ""isVisible"": false,
                                  ""type"": ""TextBlock"",
                                  ""text"": """"
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": ""14"",
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Transaction Date"",
                                  ""wrap"": true
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""{{DATE(${formatDateTime(TransDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                  ""color"": ""Accent"",
                                  ""wrap"": true,
                                  ""spacing"": ""None""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": ""13"",
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Category""
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${MS_IT_ExpSubCategory}"",
                                  ""color"": ""Accent"",
                                  ""wrap"": true,
                                  ""spacing"": ""None""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": ""10"",
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Amount""
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${AmountMST} ${MS_IT_ExchangeCode}"",
                                  ""color"": ""Accent"",
                                  ""wrap"": true,
                                  ""spacing"": ""None""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": ""auto"",
                              ""items"": [
                                {
                                  ""type"": ""Image"",
                                  ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAhklEQVQ4T2NkoBAwUqifYXAYwMrAwLCQgYGhhIGB4RmRXpJiYGDoYWBgiId5oZix4krP/w4daSIMkWKsuPL0f4cOyMJe5DAgxhAUzSDXogciPkMwNGMzACSGzRCsmnEZgG4IA7Kf0QMZXzoAuwSkARZg2GKIUEIqhmrqxRW9hAwgmCyGgQEA0UY6FkSob0cAAAAASUVORK5CYII="",
                                  ""altText"": ""Expand items""
                                }
                              ],
                              ""selectAction"": {
                                ""targetElements"": [
                                  ""LineItem${$index}"",
                                  ""LineItemsUp${$index}"",
                                  ""LineItemsDown${$index}""
                                ],
                                ""type"": ""Action.ToggleVisibility""
                              },
                              ""verticalContentAlignment"": ""Center"",
                              ""id"": ""LineItemsDown${$index}""
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": ""auto"",
                              ""items"": [
                                {
                                  ""type"": ""Image"",
                                  ""url"": ""data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAi0lEQVQ4T2NkoBAwUqifYZAbwFhx5T/Ii/87dHC6FLdExZX//zt0boIMYKy4oo7LEKwGgGyGanaCBvI+XIZgGICm+RnUACkGBgashqAYgEMzLKaxGgI3gIBmnIaADSBSM1ZDQAawMjAwLGRgYChhYGCA+ZlQAgV5p4eBgSF+kKdEQv4Ahx8xivCpAQCVhEAW7CBqiQAAAABJRU5ErkJggg=="",
                                  ""altText"": ""Collapse items""
                                }
                              ],
                              ""selectAction"": {
                                ""targetElements"": [
                                  ""LineItem${$index}"",
                                  ""LineItemsUp${$index}"",
                                  ""LineItemsDown${$index}""
                                ],
                                ""type"": ""Action.ToggleVisibility""
                              },
                              ""verticalContentAlignment"": ""Center"",
                              ""id"": ""LineItemsUp${$index}"",
                              ""isVisible"": false
                            }
                          ]
                        }
                      ],
                      ""width"": ""stretch""
                    }
                  ]
                },
                {
                  ""type"": ""ColumnSet"",
                  ""isVisible"": false,
                  ""id"": ""LineItem${$index}"",
                  ""columns"": [
                    {
                      ""type"": ""Column"",
                      ""width"": ""stretch"",
                      ""items"": [
                        {
                          ""type"": ""Container"",
                          ""style"": ""emphasis"",
                          ""items"": [
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${TransDate != ''}"",
                              ""id"": ""TransDate${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Transaction Date:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""{{DATE(${formatDateTime(TransDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${MS_IT_ExpSubCategory != ''}"",
                              ""id"": ""MS_IT_ExpSubCategory${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Category:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${MS_IT_ExpSubCategory}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${AmountMST != ''}"",
                              ""id"": ""AmountMST${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Amount:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${AmountMST} ${MS_IT_ExchangeCode}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${AmountCurr != ''}"",
                              ""id"": ""AmountCurr${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Transaction Amount:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${AmountCurr} ${ExchangeCode}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${ExchangeRate != ''}"",
                              ""id"": ""ExchangeRate${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Exchange Rate:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${string(ExchangeRate)}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${MS_IT_GLAccount != ''}"",
                              ""id"": ""MS_IT_GLAccount${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""GL Code:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${MS_IT_GLAccount}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${MS_IT_CodeValue != ''}"",
                              ""id"": ""MS_IT_CodeValue${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""CC/IO:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${MS_IT_CodeValue}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${PayMethod != ''}"",
                              ""id"": ""PayMethod${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Payment Method:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${PayMethod}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${MerchantID != ''}"",
                              ""id"": ""MerchantID${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Merchant:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${MerchantID}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${ExpenseDetails != ''}"",
                              ""id"": ""ExpenseDetails${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Additional Info:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${ExpenseDetails}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""wrap"": true,
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""$when"": ""${Project != ''}"",
                              ""id"": ""Project${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Project Name:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${Project}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""wrap"": true,
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            },
                            {
                              ""type"": ""ColumnSet"",
                              ""id"": ""Billable${$index}"",
                              ""columns"": [
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""Billable:"",
                                      ""weight"": ""Lighter"",
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                },
                                {
                                  ""type"": ""Column"",
                                  ""items"": [
                                    {
                                      ""type"": ""TextBlock"",
                                      ""text"": ""${if(Billable == true, 'Yes', 'No')}"",
                                      ""horizontalAlignment"": ""Right"",
                                      ""wrap"": true,
                                      ""size"": ""Small""
                                    }
                                  ],
                                  ""width"": ""1""
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""id"": ""ReceiptsRequired${$index}"",
                          ""$when"": ""${ReceiptsRequired}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""items"": [
                                {
                                  ""type"": ""Image"",
                                  ""url"": ""data:image/png;base64,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"",
                                  ""altText"": """"
                                }
                              ],
                              ""width"": ""1""
                            },
                            {
                              ""type"": ""Column"",
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Receipts Required""
                                }
                              ],
                              ""width"": ""20""
                            }
                          ]
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""id"": ""PolicyViolation${$index}"",
                          ""$when"": ""${PolicyViolation != ''}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""Image"",
                                          ""altText"": """",
                                          ""url"": ""data:image/png;base64,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""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Policies""
                                        }
                                      ],
                                      ""width"": ""20""
                                    }
                                  ]
                                },
                                {
                                  ""size"": ""Small"",
                                  ""text"": ""${PolicyViolation}"",
                                  ""weight"": ""Lighter"",
                                  ""wrap"": true,
                                  ""spacing"": ""None"",
                                  ""type"": ""TextBlock"",
                                  ""width"": ""auto""
                                },
                                {
                                  ""size"": ""Small"",
                                  ""text"": ""${EmployeeJustification}"",
                                  ""weight"": ""Lighter"",
                                  ""wrap"": true,
                                  ""spacing"": ""None"",
                                  ""type"": ""TextBlock"",
                                  ""width"": ""auto""
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""id"": ""AirlineServiceClass${$index}"",
                          ""$when"": ""${AirlineServiceClass != ''}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""Image"",
                                          ""altText"": """",
                                          ""url"": ""data:image/png;base64,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""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Airfare Details""
                                        }
                                      ],
                                      ""width"": ""20""
                                    }
                                  ]
                                },
                                {
                                  ""size"": ""Small"",
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Service Class:"",
                                  ""weight"": ""Lighter"",
                                  ""wrap"": true,
                                  ""spacing"": ""None"",
                                  ""width"": ""auto""
                                },
                                {
                                  ""size"": ""Small"",
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${AirlineServiceClass}"",
                                  ""wrap"": true,
                                  ""spacing"": ""None"",
                                  ""width"": ""auto""
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""id"": ""MilageKMOwnCar${$index}"",
                          ""$when"": ""${MilageKMOwnCar > 0}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""Image"",
                                          ""url"": ""data:image/png;base64,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"",
                                          ""altText"": """"
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Mileage Details""
                                        }
                                      ],
                                      ""width"": ""20""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""size"": ""Small"",
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Mileage:"",
                                          ""weight"": ""Lighter"",
                                          ""wrap"": true,
                                          ""spacing"": ""None"",
                                          ""width"": ""auto""
                                        },
                                        {
                                          ""size"": ""Small"",
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${string(MilageKMOwnCar)}"",
                                          ""wrap"": true,
                                          ""spacing"": ""None"",
                                          ""width"": ""auto""
                                        }
                                      ],
                                      ""width"": ""auto""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""size"": ""Small"",
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Vehicle type:"",
                                          ""weight"": ""Lighter"",
                                          ""wrap"": true,
                                          ""spacing"": ""None"",
                                          ""width"": ""auto""
                                        },
                                        {
                                          ""size"": ""Small"",
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${MilageVehicleType}"",
                                          ""wrap"": true,
                                          ""spacing"": ""None"",
                                          ""width"": ""auto""
                                        }
                                      ],
                                      ""width"": ""auto""
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""$data"": ""${Children}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Itemize category"",
                                  ""wrap"": true,
                                  ""isSubtle"": true
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${MS_IT_ExpSubCategory}"",
                                  ""wrap"": true,
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Date"",
                                  ""isSubtle"": true
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""{{DATE(${formatDateTime(TransDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": 1,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Amount"",
                                  ""isSubtle"": true,
                                  ""wrap"": true
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${AmountMST} ${MS_IT_ExchangeCode}"",
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""TextBlock"",
                          ""$when"": ""${not(empty(GuestDetails))}"",
                          ""text"": ""Guest Details"",
                          ""weight"": ""Bolder""
                        },
                        {
                          ""type"": ""ColumnSet"",
                          ""$data"": ""${GuestDetails}"",
                          ""columns"": [
                            {
                              ""type"": ""Column"",
                              ""width"": 17,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Guest ID"",
                                  ""wrap"": true
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${GuestId}"",
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": 17,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Org / Country""
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${Organization}"",
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            },
                            {
                              ""type"": ""Column"",
                              ""width"": 17,
                              ""items"": [
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""Title""
                                },
                                {
                                  ""type"": ""TextBlock"",
                                  ""text"": ""${Title}"",
                                  ""size"": ""Small"",
                                  ""spacing"": ""None"",
                                  ""weight"": ""Lighter""
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""Container"",
                          ""id"": ""DistributionDetail${$index}"",
                          ""$when"": ""${not(empty(DistributionDetails))}"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""Distribution Details"",
                              ""weight"": ""Bolder""
                            },
                            {
                              ""type"": ""Container"",
                              ""$data"": ""${DistributionDetails}"",
                              ""items"": [
                                {
                                  ""type"": ""Container"",
                                  ""items"": [
                                    {
                                      ""type"": ""Container"",
                                      ""items"": [
                                        {
                                          ""type"": ""ColumnSet"",
                                          ""columns"": [
                                            {
                                              ""type"": ""Column"",
                                              ""items"": [
                                                {
                                                  ""type"": ""ColumnSet"",
                                                  ""columns"": [
                                                    {
                                                      ""type"": ""Column"",
                                                      ""width"": 2,
                                                      ""items"": [
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""CC/IO"",
                                                          ""wrap"": true
                                                        },
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""${MS_IT_CodeValue}"",
                                                          ""color"": ""Accent"",
                                                          ""spacing"": ""None""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""Column"",
                                                      ""width"": 2,
                                                      ""items"": [
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""Percent""
                                                        },
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""${AllocationFactor}"",
                                                          ""color"": ""Accent"",
                                                          ""spacing"": ""None""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""Column"",
                                                      ""width"": 2,
                                                      ""items"": [
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""Amount""
                                                        },
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""${TransactionCurrencyAmount} ${TransactionCurrency}"",
                                                          ""color"": ""Accent"",
                                                          ""spacing"": ""None""
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ],
                                              ""width"": ""stretch""
                                            }
                                          ]
                                        },
                                        {
                                          ""type"": ""Container"",
                                          ""style"": ""emphasis"",
                                          ""items"": [
                                            {
                                              ""type"": ""ColumnSet"",
                                              ""columns"": [
                                                {
                                                  ""type"": ""Column"",
                                                  ""width"": ""stretch"",
                                                  ""items"": [
                                                    {
                                                      ""type"": ""ColumnSet"",
                                                      ""columns"": [
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""Project ID:"",
                                                              ""weight"": ""Lighter"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        },
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""${ProjName}"",
                                                              ""horizontalAlignment"": ""Right"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""ColumnSet"",
                                                      ""columns"": [
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""Billable:"",
                                                              ""weight"": ""Lighter"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        },
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""${if(Billable > 0, 'Yes', 'No')}"",
                                                              ""horizontalAlignment"": ""Right"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        },
                        {
                          ""type"": ""Container"",
                          ""id"": ""PerDiemDetail${$index}"",
                          ""$when"": ""${not(empty(PerdiemDetails))}"",
                          ""items"": [
                            {
                              ""type"": ""TextBlock"",
                              ""text"": ""Per Diem Details"",
                              ""weight"": ""Bolder""
                            },
                            {
                              ""type"": ""Container"",
                              ""style"": ""emphasis"",
                              ""items"": [
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Per diem from date:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""{{DATE(${formatDateTime(DateFrom, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Per diem to date:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""{{DATE(${formatDateTime(DateTo, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Location:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${Location}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Breakfast:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${string(DeductionBreakfast)}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Lunch:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${string(DeductionLunch)}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Dinner:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${string(DeductionDinner)}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Meal Reduction:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${Deduction} ${MS_IT_ExchangeCode}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                },
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""Amount:"",
                                          ""weight"": ""Lighter"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    },
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""TextBlock"",
                                          ""text"": ""${AmountCurr} ${ExchangeCode}"",
                                          ""horizontalAlignment"": ""Right"",
                                          ""size"": ""Small""
                                        }
                                      ],
                                      ""width"": ""1""
                                    }
                                  ]
                                }
                              ]
                            },
                            {
                              ""type"": ""Container"",
                              ""style"": ""emphasis"",
                              ""items"": [
                                {
                                  ""type"": ""ColumnSet"",
                                  ""columns"": [
                                    {
                                      ""type"": ""Column"",
                                      ""items"": [
                                        {
                                          ""type"": ""ColumnSet"",
                                          ""style"": ""emphasis"",
                                          ""columns"": [
                                            {
                                              ""type"": ""Column"",
                                              ""items"": [],
                                              ""width"": ""1""
                                            },
                                            {
                                              ""type"": ""Column"",
                                              ""items"": [],
                                              ""width"": ""1""
                                            }
                                          ]
                                        }
                                      ],
                                      ""width"": ""stretch""
                                    }
                                  ]
                                }
                              ]
                            },
                            {
                              ""type"": ""Container"",
                              ""$data"": ""${PerdiemDetails}"",
                              ""items"": [
                                {
                                  ""type"": ""Container"",
                                  ""items"": [
                                    {
                                      ""type"": ""Container"",
                                      ""items"": [
                                        {
                                          ""type"": ""ColumnSet"",
                                          ""columns"": [
                                            {
                                              ""type"": ""Column"",
                                              ""items"": [
                                                {
                                                  ""type"": ""ColumnSet"",
                                                  ""columns"": [
                                                    {
                                                      ""type"": ""Column"",
                                                      ""width"": 1,
                                                      ""items"": [
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""Transaction Date"",
                                                          ""wrap"": true
                                                        },
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""{{DATE(${formatDateTime(TransDate, 'yyyy-MM-ddTHH:mm:ssZ')}, COMPACT)}}"",
                                                          ""color"": ""Accent"",
                                                          ""spacing"": ""None""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""Column"",
                                                      ""width"": 1,
                                                      ""items"": [
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""Meal Reduction"",
                                                          ""wrap"": true
                                                        },
                                                        {
                                                          ""type"": ""TextBlock"",
                                                          ""text"": ""${MealDeduction} ${CurrencyCode}"",
                                                          ""color"": ""Accent"",
                                                          ""spacing"": ""None""
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ],
                                              ""width"": ""stretch""
                                            }
                                          ]
                                        },
                                        {
                                          ""type"": ""Container"",
                                          ""style"": ""emphasis"",
                                          ""items"": [
                                            {
                                              ""type"": ""ColumnSet"",
                                              ""columns"": [
                                                {
                                                  ""type"": ""Column"",
                                                  ""width"": ""stretch"",
                                                  ""items"": [
                                                    {
                                                      ""type"": ""ColumnSet"",
                                                      ""columns"": [
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""Breakfast:"",
                                                              ""weight"": ""Lighter"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        },
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""${string(NumberOfBreakfast)}"",
                                                              ""horizontalAlignment"": ""Right"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""ColumnSet"",
                                                      ""columns"": [
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""Lunch:"",
                                                              ""weight"": ""Lighter"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        },
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""${string(NumberOfLunch)}"",
                                                              ""horizontalAlignment"": ""Right"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        }
                                                      ]
                                                    },
                                                    {
                                                      ""type"": ""ColumnSet"",
                                                      ""columns"": [
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""Dinner:"",
                                                              ""weight"": ""Lighter"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        },
                                                        {
                                                          ""type"": ""Column"",
                                                          ""items"": [
                                                            {
                                                              ""type"": ""TextBlock"",
                                                              ""text"": ""${string(NumberOfDinner)}"",
                                                              ""horizontalAlignment"": ""Right"",
                                                              ""size"": ""Small""
                                                            }
                                                          ],
                                                          ""width"": ""auto""
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""separator"": true,
      ""items"": [
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""width"": 2,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Total expense amount"",
                  ""weight"": ""Lighter"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""width"": 1,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${UnitValue} ${UnitOfMeasure}"",
                  ""weight"": ""Lighter"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""width"": 2,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""Personal expense"",
                  ""weight"": ""Lighter"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""width"": 1,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${AdditionalData.MS_IT_PersonalAmount} ${UnitOfMeasure}"",
                  ""weight"": ""Lighter"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""width"": 2,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""To be reimbursed"",
                  ""size"": ""Medium"",
                  ""weight"": ""Lighter"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""width"": 1,
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""${UnitValue} ${UnitOfMeasure}"",
                  ""size"": ""Medium"",
                  ""weight"": ""Bolder"",
                  ""horizontalAlignment"": ""Right""
                }
              ]
            }
          ]
        }
      ]
    },
    {
      ""type"": ""ColumnSet"",
      ""columns"": [
        {
          ""type"": ""Column"",
          ""width"": ""auto"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""size"": ""Small"",
              ""text"": ""**Compliance Acknowledgement** - **By approving this expense report, I confirm that:** I have reviewed these expenses and associated receipts for business appropriateness and legitimacy, and confirm that these expenses comply with Microsoft's [Employee Expense Reimbursement Policy](https://aka.ms/eerp) requirements.\nIf any of these expenses relate to payments for or on behalf of [Government Officials](https://microsoft.sharepoint.com/sites/lcaweb/Home/Business-Conduct-and-Compliance/Government-Officials-and-Anti-Corruption/Identify-a-Government-Official), I have also reviewed these expenses and confirm that they comply with Microsoft's [Anti-Corruption Policy](https://aka.ms/a-c) and any identified questions or discrepancies with the expense report have been discussed with the employee directly, and have been resolved appropriately."",
              ""wrap"": true
            }
          ]
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""style"": ""emphasis"",
      ""items"": [
        {
          ""type"": ""ColumnSet"",
          ""id"": ""receiptAcknowledgementBlock"",
          ""$when"": ""${AdditionalData.MS_IT_ReceiptsRequired == 'True'}"",
          ""spacing"": ""None"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""type"": ""Input.ChoiceSet"",
                  ""isMultiSelect"": true,
                  ""isRequired"": true,
                  ""id"": ""receiptsAcknowledged"",
                  ""choices"": [
                    {
                      ""title"": "" "",
                      ""value"": ""false"",
                      ""isSelected"": false,
                      ""speak"": null
                    }
                  ]
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""spacing"": ""Small"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""size"": ""Small"",
                  ""text"": ""Receipt Acknowledgment - I have reviewed the required receipts attached to this report."",
                  ""weight"": ""Lighter"",
                  ""wrap"": true,
                  ""spacing"": ""None"",
                  ""width"": ""auto""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ColumnSet"",
          ""id"": ""antiCorruptionAcknowledgementBlock"",
          ""$when"": ""${AdditionalData.MS_IT_AntiCorruption == 'True'}"",
          ""spacing"": ""None"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                  ""isMultiSelect"": true,
                  ""isRequired"": true,
                  ""id"": ""antiCorruptionAcknowledged"",
                  ""type"": ""Input.ChoiceSet"",
                  ""choices"": [
                    {
                      ""title"": "" "",
                      ""value"": ""false"",
                      ""isSelected"": false,
                      ""speak"": null
                    }
                  ]
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""spacing"": ""Small"",
              ""items"": [
                {
                  ""type"": ""TextBlock"",
                  ""size"": ""Small"",
                  ""text"": ""Anti-Corruption - I have reviewed the expenses and confirm that they comply with Microsoft�s Anti-corruption policies."",
                  ""weight"": ""Lighter"",
                  ""wrap"": true,
                  ""spacing"": ""None"",
                  ""width"": ""auto""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""Input.Text"",
          ""id"": ""rejectComment"",
          ""isMultiline"": true,
          ""maxLength"": 1000,
          ""placeholder"": ""Notes (optional) - Max 1000 characters""
        },
        {
          ""id"": ""approveAction"",
          ""horizontalAlignment"": ""Left"",
          ""type"": ""ActionSet"",
          ""actions"": [
          ]
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""style"": ""emphasis"",
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
                  ""size"": ""Small"",
                  ""wrap"": true,
                  ""text"": ""[Same request can be viewed at MSApprovals Website](#MSApprovalsDetailPage#)""
                }
              ]
            },
            {
              ""type"": ""Column"",
              ""width"": ""stretch"",
              ""items"": [
                {
                  ""horizontalAlignment"": ""Right"",
                  ""type"": ""TextBlock"",
                  ""size"": ""Small"",
                  ""text"": ""[Share feedback](https://microsoftit.uservoice.com/forums/598696-msapprovals)""
                }
              ]
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
                  ""size"": ""Small"",
                  ""wrap"": true,
                  ""text"": ""** This is an automatically generated email, please do not reply or forward to this alias. **""
                }
              ]
            }
          ]
        }
      ]
    }
  ]
}";

            string jsonData = @"{
  ""DocumentTypeId"": ""e645b540-c621-4a33-a7a5-22319c873d1b"",
  ""Title"": ""Test ER 1"",
  ""UnitValue"": ""93.50"",
  ""UnitOfMeasure"": ""USD"",
  ""SubmittedDate"": ""2020-01-07T00:00:00"",
  ""DetailPageURL"": null,
  ""CompanyCode"": ""1010"",
  ""ApprovalIdentifier"": {
    ""DisplayDocumentNumber"": ""ER-0000014644286"",
    ""DocumentNumber"": ""{86A6DFDD-C570-44A7-923E-C36F3912BB25}"",
    ""FiscalYear"": null
  },
  ""Submitter"": {
    ""Alias"": ""japarame"",
    ""Name"": ""Jaya Prathap Parameswaran""
  },
  ""CustomAttribute"": {
    ""CustomAttributeName"": ""Description"",
    ""CustomAttributeValue"": ""test ER for outlook emails verification""
  },
  ""ApprovalHierarchy"": [
    {
      ""Approvers"": [
        {
          ""Alias"": ""niravk"",
          ""Name"": ""Nirav Khandhedia""
        },
        {
          ""Alias"": ""v-gaychi"",
          ""Name"": ""Gayatri Chiplunkar""
        }
      ],
      ""ApproverType"": ""Interim""
    },
    {
      ""Approvers"": [
        {
          ""Alias"": ""sumeetd"",
          ""Name"": ""Sumeet Malhar Deshpande""
        }
      ],
      ""ApproverType"": ""Final""
    }
  ],
  ""ApprovalActionsApplicable"": null,
  ""AdditionalData"": {
    ""MS_IT_Submitter"": ""v-gaychi"",
    ""MS_IT_ReceiptsRequired"": ""True"",
    ""MS_IT_PersonalAmount"": ""5.00"",
    ""MS_IT_Comments"": ""ER submitted"",
    ""MS_IT_PreApprovalNumber"": ""2"",
    ""MS_IT_TotalReceipts"": ""0"",
    ""MS_IT_AntiCorruption"": ""True"",
    ""MS_IT_AmexAmount"": ""0.00"",
    ""MS_IT_OOPAmount"": ""88.50"",
    ""MS_IT_ReceiptsAttached"": ""True"",
    ""MS_IT_Name"": ""Jaya Prathap Parameswaran"",
    ""ApprovalStatus"": ""In review""
  },
  ""Attachments"": [
    {
      ""ID"": ""104"",
      ""Name"": ""JPEGTestFile.jpg"",
      ""Url"": """"
    }
  ],
  ""ApproverNotes"": ""ER submitted"",
  ""RequestVersion"": ""f3959cb0-9aa3-40d2-9d58-55275e10fbc8"",
  ""Approvers"": [
    {
      ""Alias"": ""niravk"",
      ""Name"": ""Nirav Khandhedia"",
      ""ActionDate"": ""2020-01-24T03:57:59+05:30"",
      ""Action"": ""Approval"",
      ""Type"": ""Interim"",
      ""Justification"": """",
      ""Notes"": ""test"",
      ""_future"": false,
      ""DelegateUser"": """"
    },
    {
      ""Alias"": ""v-gaychi"",
      ""Name"": ""Gayatri Chiplunkar"",
      ""Action"": ""Rejection"",
      ""ActionDate"": ""2020-03-30T17:43:33+05:30"",
      ""Type"": ""Interim"",
      ""Justification"": """",
      ""Notes"": """",
      ""_future"": false,
      ""DelegateUser"": """"
    },
    {
      ""Alias"": ""sumeetd"",
      ""Name"": ""Sumeet Malhar Deshpande"",
      ""Action"": """",
      ""Type"": ""Final"",
      ""_future"": false
    }
  ],
  ""Actions"": {
    ""Primary"": [
      {
        ""Condition"": """",
        ""Code"": ""Complete"",
        ""Name"": ""Approve"",
        ""Text"": """",
        ""Justifications"": null,
        ""IsCommentMandatory"": false,
        ""IsJustificationApplicable"": true,
        ""IsInterimStateRequired"": true,
        ""CommentLength"": 1000,
        ""TargetPage"": [
          {
            ""Condition"": """",
            ""PageType"": ""SUMMARY"",
            ""DelayTime"": 0
          }
        ],
        ""Placements"": null,
        ""IsEnabled"": true,
        ""IsBulkAction"": false,
        ""ActionConfirmationMessage"": null,
        ""Comments"": null
      }
    ],
    ""Secondary"": [
      {
        ""Condition"": """",
        ""Code"": ""Deny"",
        ""Name"": ""Reject"",
        ""Text"": ""- Send back to submitter"",
        ""Justifications"": null,
        ""IsCommentMandatory"": false,
        ""IsJustificationApplicable"": true,
        ""IsInterimStateRequired"": true,
        ""CommentLength"": 1000,
        ""TargetPage"": [
          {
            ""Condition"": """",
            ""PageType"": ""SUMMARY"",
            ""DelayTime"": 0
          }
        ],
        ""Placements"": null,
        ""IsEnabled"": true,
        ""IsBulkAction"": false,
        ""ActionConfirmationMessage"": null,
        ""Comments"": null
      },
      {
        ""Condition"": ""IsOutOfSyncChallenged^IsOutOfSyncChallenged == false"",
        ""Code"": ""OutOfSync"",
        ""Name"": ""Out Of Sync"",
        ""Text"": "" - Request is Out of Sync"",
        ""Justifications"": [
          {
            ""Condition"": """",
            ""Code"": ""ActionTakenOnTenantSystem"",
            ""Name"": ""Already taken action on tenant system"",
            ""Key"": null,
            ""Description"": null,
            ""_default"": true
          },
          {
            ""Condition"": """",
            ""Code"": ""Other"",
            ""Name"": ""Other"",
            ""Key"": null,
            ""Description"": null,
            ""_default"": false
          }
        ],
        ""IsCommentMandatory"": false,
        ""IsJustificationApplicable"": true,
        ""IsInterimStateRequired"": true,
        ""CommentLength"": 255,
        ""TargetPage"": [
          {
            ""Condition"": """",
            ""PageType"": """",
            ""DelayTime"": 0
          }
        ],
        ""Placements"": null,
        ""IsEnabled"": true,
        ""IsBulkAction"": false,
        ""ActionConfirmationMessage"": null,
        ""Comments"": null
      }
    ]
  },
  ""AppName"": ""MSExpense 2.0"",
  ""CondensedAppName"": ""MSExpense2.0"",
  ""templateName"": ""MSExpense"",
  ""BusinessProcessName"": ""MSApprovals-MSExpense2.0-{0}-{1}"",
  ""DocumentNumberPrefix"": ""Exp#"",
  ""ToolName"": ""MSExpense 2.0"",
  ""EditableFields"": {

  },
  ""LineItems"": [
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Car Rental"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 7,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Uber"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Car Rental"",
      ""MS_IT_GLAccount"": ""723013"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648593,
      ""TransDate"": ""2019-09-15T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 40.0,
      ""AmountMST"": 40.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Home"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": """",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Home"",
      ""MS_IT_GLAccount"": ""742000"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648594,
      ""TransDate"": ""2019-09-10T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 20.0,
      ""AmountMST"": 20.0,
      ""Billable"": false,
      ""CostType"": ""Broadband - Travel"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test info"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""test2"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Broadband - Travel"",
      ""MS_IT_GLAccount"": ""742016"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648595,
      ""TransDate"": ""2019-09-08T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Cell Phone"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 1,
      ""GuestDetails"": [

      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Samsung"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Cell Phone"",
      ""MS_IT_GLAccount"": ""742001"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Allowable expense thresholds and eligibility vary by country. Before submitting an expense report verify the requirements for your country in the Employee Expense Reimbursement Procedure link http://aka.ms/EERPro;"",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648596,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [

      ],
      ""AirlineServiceClass"": """",
      ""AmountCurr"": 50.0,
      ""AmountMST"": 50.0,
      ""Billable"": false,
      ""CostType"": ""Entertainment"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [
        {
          ""AllocationFactor"": 30.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 15.0
        },
        {
          ""AllocationFactor"": 20.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 10.0
        },
        {
          ""AllocationFactor"": 50.0,
          ""Billable"": 0,
          ""MS_IT_CodeValue"": ""10203599"",
          ""ProjName"": """",
          ""TransactionCurrency"": ""USD"",
          ""TransactionCurrencyAmount"": 25.0
        }
      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test information"",
      ""ExpType"": 9,
      ""GuestDetails"": [
        {
          ""CountryRegion"": """",
          ""GuestId"": ""AAA"",
          ""Organization"": ""IND"",
          ""Title"": ""Mr""
        },
        {
          ""CountryRegion"": """",
          ""GuestId"": ""XYZ"",
          ""Organization"": ""USA"",
          ""Title"": ""Miss""
        }
      ],
      ""LineType"": 0,
      ""Location"": """",
      ""MerchantID"": ""Test Merchant"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Entertainment"",
      ""MS_IT_GLAccount"": ""723010"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": """",
      ""Project"": """",
      ""ReceiptsDetails"": [

      ],
      ""ReceiptsRequired"": false,
      ""RecID"": 5670648586,
      ""TransDate"": ""2019-09-18T12:00:00"",
      ""Children"": [

      ]
    },
    {
      ""Attachments"": [
      ],
      ""AirlineServiceClass"": ""Business class"",
      ""AmountCurr"": 90.0,
      ""AmountMST"": 90.0,
      ""Billable"": false,
      ""CostType"": ""Airfare"",
      ""DateFrom"": ""1900-01-01T00:00:00Z"",
      ""DateTo"": ""1900-01-01T00:00:00Z"",
      ""Deduction"": 0.0,
      ""DeductionBreakfast"": 0.0,
      ""DeductionDinner"": 0.0,
      ""DeductionLunch"": 0.0,
      ""DistributionDetails"": [

      ],
      ""EmployeeJustification"": """",
      ""EntertainmentLocation"": """",
      ""ExchangeCode"": ""USD"",
      ""ExchangeRate"": 1.0,
      ""ExpenseDetails"": ""test"",
      ""ExpType"": 6,
      ""GuestDetails"": [

      ],
      ""LineType"": 1,
      ""Location"": """",
      ""MerchantID"": ""Etihad"",
      ""MilageKMOwnCar"": 0.0,
      ""MilageVehicleType"": """",
      ""MS_IT_CodeValue"": ""10203599"",
      ""MS_IT_ExchangeCode"": ""USD"",
      ""MS_IT_ExpSubCategory"": ""Airfare"",
      ""MS_IT_GLAccount"": ""723009"",
      ""ParentRecID"": 0,
      ""PayMethod"": ""Cash"",
      ""PerdiemDetails"": [

      ],
      ""PolicyViolation"": ""Policy information only: Airfare, Hotel & Car Rental expenses should be paid with the corporate AMEX credit card. Refer to your local T&E policy for any additional mandatory requirements that apply to airline, hotel, car rental expenses.;"",
      ""Project"": """",
      ""ReceiptsDetails"": [
        {
          ""FileName"": ""JPEGTestFile"",
          ""FileType"": ""jpg"",
          ""ReceiptFile"": """",
          ""ReceiptRecId"": 5644202330
        }
      ],
      ""ReceiptsRequired"": true,
      ""RecID"": 5670648589,
      ""TransDate"": ""2019-09-16T12:00:00"",
      ""Children"": [
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 60.0,
          ""AmountMST"": 60.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Airline fare"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648590,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-15T12:00:00""
        },
        {
          ""AirlineServiceClass"": ""Economy class"",
          ""AmountCurr"": 20.0,
          ""AmountMST"": 20.0,
          ""Billable"": false,
          ""CostType"": ""Airfare"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 6,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Misc (baggage and change fee)"",
          ""MS_IT_GLAccount"": ""723009"",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648591,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-18T12:00:00""
        },
        {
          ""AirlineServiceClass"": """",
          ""AmountCurr"": 10.0,
          ""AmountMST"": 10.0,
          ""Billable"": false,
          ""CostType"": ""Personal"",
          ""DateFrom"": ""1900-01-01T00:00:00Z"",
          ""DateTo"": ""1900-01-01T00:00:00Z"",
          ""Deduction"": 0.0,
          ""DeductionBreakfast"": 0.0,
          ""DeductionDinner"": 0.0,
          ""DeductionLunch"": 0.0,
          ""DistributionDetails"": [

          ],
          ""EmployeeJustification"": """",
          ""EntertainmentLocation"": """",
          ""ExchangeCode"": ""USD"",
          ""ExchangeRate"": 1.0,
          ""ExpType"": 5,
          ""ExpenseDetails"": ""test"",
          ""GuestDetails"": [

          ],
          ""LineType"": 2,
          ""Location"": """",
          ""MS_IT_CodeValue"": ""10203599"",
          ""MS_IT_ExchangeCode"": ""USD"",
          ""MS_IT_ExpSubCategory"": ""Personal"",
          ""MS_IT_GLAccount"": """",
          ""MerchantID"": ""Etihad"",
          ""MilageKMOwnCar"": 0.0,
          ""MilageVehicleType"": """",
          ""ParentRecID"": 5670648589,
          ""PayMethod"": ""Cash"",
          ""PerdiemDetails"": [

          ],
          ""PolicyViolation"": """",
          ""Project"": """",
          ""RecID"": 5670648592,
          ""ReceiptsDetails"": [

          ],
          ""ReceiptsRequired"": false,
          ""TransDate"": ""2019-09-16T12:00:00""
        }
      ]
    }
  ],
  ""CallBackURLCollection"": [

  ],
  ""LastFailed"": false,
  ""LastFailedExceptionMessage"": null,
  ""LastFailedOutOfSyncMessage"": null,
  ""IsBackgroundApprovalSupportedUpfront"": false,
  ""IsHistoryClickable"": true,
  ""IsPictorialLineItemsEnabled"": true,
  ""LineItemFilterCategories"": ""{\""filters\"":[{\""MS_IT_ExpSubCategory\"":\""Expense Category\""},{\""AmountMST\"":\""Transaction Amount\""},{\""MerchantID\"":\""Merchant\""},{\""TransDate\"":\""Transaction Date\""},{\""PayMethod\"":\""Payment Method\""},{\""MS_IT_GLAccount\"":\""GL Accounts\""},{\""MS_IT_CodeValue\"":\""Cost Center/Internal Order\""},{\""Billable\"":\""Billable\""}]}""
}";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
            {
                Root = jsonData
            };
            string cardJson = transformer.Expand(context);
            var parseResult = AdaptiveCard.FromJson(cardJson);
            Assert.IsTrue(true);
        }
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
        public void TestDateConversion()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""version"": ""1.0"",
            ""$data"": {
                ""rfc3389"" : ""2017-02-14T06:08:00Z""
             },
            ""body"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""${rfc3389}""
                }
            ]
            }";
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);

            string cardJson = transformer.Expand(null);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""2017-02-14T06:08:00Z""
        }
    ]
}", cardJson);
        }

        [TestMethod]
        public void TestBoolConversion()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""version"": ""1.0"",
            ""$data"": {
                ""boolValue"" : true
             },
            ""body"": [
                {
                    ""type"": ""TextBlock"",
                    ""text"": ""Hello"",
                    ""IsVisible"" : true
                }
            ]
            }";
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);

            string cardJson = transformer.Expand(null);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Hello"",
            ""IsVisible"" : true
        }
    ]
}", cardJson);
        }
        [TestMethod]
        public void TestEvaluationContext()
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);

            string cardJson = transformer.Expand(jsonData);

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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

        [TestMethod]
        public void TestSortFunctionInDataCreateAnArray()
        {
            string jsonTemplate = @"{
            ""type"": ""AdaptiveCard"",
            ""version"": ""1.0"",
            ""body"": [
              {
                ""id"": ""Test"",
                ""type"": ""Input.ChoiceSet"",
                ""style"": ""expanded"",
                ""isMultiSelect"": true,
                ""choices"": [
                    {
                      ""$data"": ""${sortBy(createArray(4, 3, 1, 2))}"",
                      ""title"": ""Test"",
                      ""value"": ""Test""
                    }
                ]
              }
            ]
          }";

            string jsonData = @"{}";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
            {
                Root = jsonData
            };

            try
            {
                string cardJson = transformer.Expand(context);
            }
            catch (AdaptiveTemplateException e)
            {
                Assert.Fail("No exception should be thrown");
            }
        }
        
        [TestMethod]
        public void TestNullArgumentExceptionHandling()
        {
            // ${} is a null value
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);

            try
            {
                string cardJson = transformer.Expand(null);
                Assert.Fail("There should be an exception");
            }
            catch (ArgumentNullException e)
            {
                Assert.AreEqual("Check if parent data context is set, or please enter a non-null value for '${LineItems}' at line, '8'", e.ParamName);
            }
            catch
            {
                Assert.Fail();
                throw;
            }
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();

            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }

        [TestMethod]
        public void TestDataContextCommaRemoal()
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
                                  ""text"": ""${name}""
                              }
                          ],
                          ""$data"": ""${$root.LineItems}"" 
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
                            } ]
                    },
                    {
                        ""type"": ""Container"",
                        ""items"": [ 
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""David""
                            }
                        ]
                    },
                    {
                        ""type"": ""Container"",
                        ""items"": [ 
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""Thomas""
                            }
                        ]
                    }
                ]
            }";

            string jsonData = @"{
              ""LineItems"": [
                  { ""name"": ""Matt"" }, 
                  { ""name"": ""David"" }, 
                  { ""name"": ""Thomas"" }
                ]
            }";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            AdaptiveCardTemplate transformer2 = new AdaptiveCardTemplate(expectedString);
            var context = new EvaluationContext()
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);
            string expectedcardJson = transformer2.Expand(context);
            Assert.AreEqual(expectedcardJson, cardJson);
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();

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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();

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
                            },
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""Hello World!""
                            },
                            {
                                ""type"": ""TextBlock"",
                                ""text"": ""Hello World!""
                            }
                        ]
                    }
                ]
            }";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();
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
            ""$data"":""${$root}""
        }
    ]
}";
        var expectedString =
        @"{ ""$schema"":""http://adaptivecards.io/schemas/adaptive-card.json"",""type"":""AdaptiveCard"",""version"":""1.0"",""body"":[{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-1""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""1.10762 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.17%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-2""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""1578.205 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.68%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-3""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""51.475 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-0.23%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▲"",""color"":""good""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-4""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""28324 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""0.35%"",""color"":""good""}],""horizontalAlignment"":""Right""}]}]},{""type"":""Container"",""items"":[{""type"":""ColumnSet"",""columns"":[{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""▼"",""color"":""attention""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""Object-5""}]},{""type"":""Column"",""width"":""stretch"",""items"":[{""type"":""TextBlock"",""text"":""9338.87 "",""horizontalAlignment"":""Center""}],""horizontalAlignment"":""Center""},{""type"":""Column"",""width"":""auto"",""items"":[{""type"":""TextBlock"",""text"":""-1.04%"",""color"":""attention""}],""horizontalAlignment"":""Right""}]}]}]}"; 
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext
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
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
        public void TestWhenWithArrayWhenAllElementsOfArrayAreRemoved()
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
                    {""Milage"" : 0},
                    {""Milage"" : 0}
                ]
            }";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""body"": [
              {
                ""type"": ""Container"",
                ""items"": []
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
        public void TestNestedArray()
        {
            var jsonData =
            @"{
                  ""outerArray"": [
                        [ ""a"", ""b"", ""c""],
                        [ ""d"", ""e"", ""f""],
                        [ ""g"", ""h"", ""i""]
                  ]
                }";
            var jsonTemplate =
            @"{
                ""type"": ""AdaptiveCard"",
                ""body"": [
                    {
                        ""type"": ""Container"",
                        ""$data"": ""${$root.outerArray}"",
                        ""items"": [
                            {
                                ""text"": ""Container ${$index}"",
                                ""type"": ""TextBlock""
                            },
                            {
                                ""$data"": ""${$data}"",
                                ""text"": ""${$data}"",
                                ""type"": ""TextBlock""
                            }
                        ]
                    }
                ],
                ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                ""version"": ""1.2""
            }";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext()
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            var expectedString = @"{""type"":""AdaptiveCard"",""body"":[{""type"":""Container"",""items"":[{""text"":""Container 0"",""type"":""TextBlock""},{""text"":""a"",""type"":""TextBlock""},{""text"":""b"",""type"":""TextBlock""},{""text"":""c"",""type"":""TextBlock""}]},{""type"":""Container"",""items"":[{""text"":""Container 1"",""type"":""TextBlock""},{""text"":""d"",""type"":""TextBlock""},{""text"":""e"",""type"":""TextBlock""},{""text"":""f"",""type"":""TextBlock""}]},{""type"":""Container"",""items"":[{""text"":""Container 2"",""type"":""TextBlock""},{""text"":""g"",""type"":""TextBlock""},{""text"":""h"",""type"":""TextBlock""},{""text"":""i"",""type"":""TextBlock""}]}],""$schema"":""http://adaptivecards.io/schemas/adaptive-card.json"",""version"":""1.2""} ";
            AssertJsonEqual(cardJson, expectedString);
        }

        [TestMethod]
        public void TestNestedArrayWithoutDataReference()
        {
            var jsonData =
            @"{
                  ""outerArray"": [
                        [ ""a"", ""b"", ""c""],
                        [ ""d"", ""e"", ""f""],
                        [ ""g"", ""h"", ""i""]
                  ]
                }";
            var jsonTemplate =
            @"{
                ""type"": ""AdaptiveCard"",
                ""body"": [
                    {
                        ""type"": ""Container"",
                        ""$data"": ""${$root.outerArray}"",
                        ""items"": [
                            {
                                ""text"": ""Container ${$index}"",
                                ""type"": ""TextBlock""
                            },
                            {
                                ""$data"": ""${$data}"",
                                ""text"": ""test"",
                                ""type"": ""TextBlock""
                            }
                        ]
                    }
                ],
                ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                ""version"": ""1.2""
            }";

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext()
            {
                Root = jsonData
            };

            string cardJson = transformer.Expand(context);

            var expectedString = @"{""type"":""AdaptiveCard"",""body"":[{""type"":""Container"",""items"":[{""text"":""Container 0"",""type"":""TextBlock""},
            {""text"":""test"",""type"":""TextBlock""},{""text"":""test"",""type"":""TextBlock""},
            {""text"":""test"",""type"":""TextBlock""}]},{""type"":""Container"",""items"":[{""text"":""Container 1"",""type"":""TextBlock""},
            {""text"":""test"",""type"":""TextBlock""},{""text"":""test"",""type"":""TextBlock""},{""text"":""test"",""type"":""TextBlock""}]},
            {""type"":""Container"",""items"":[{""text"":""Container 2"",""type"":""TextBlock""},{""text"":""test"",""type"":""TextBlock""},
            {""text"":""test"",""type"":""TextBlock""},{""text"":""test"",""type"":""TextBlock""}]}],
            ""$schema"":""http://adaptivecards.io/schemas/adaptive-card.json"",""version"":""1.2""} ";
            AssertJsonEqual(expectedString, cardJson);
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(testString);
            var context = new EvaluationContext();
            string cardJson = transformer.Expand(context);
            AssertJsonEqual(expectedString, cardJson);
        }
        
        class Data
        { 
            public string title { get; set; }
        };
        [TestMethod]
        public void TestDoubleQuote()
        {
            string cardJson = "{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\"," +
                "\"size\": \"Medium\",\"weight\": \"Bolder\",\"text\": \"${title}\"}]," +
                "\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\"version\": \"1.2\"}";

            Data dt = new Data()
            {
                title = "Test with\n\r \"quotes\""
            };


            var template = new AdaptiveCardTemplate(cardJson);
            string st = template.Expand(dt);
            try
            {
                var jsonOb = Newtonsoft.Json.JsonConvert.DeserializeObject(st);
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine(ex.Message);
                Assert.Fail();
            }
        }
    }
    [TestClass]
    public sealed class TestRootKeyword
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
    public sealed class TestDataKeyword
    {
        [TestMethod]
        public void TestBasic()
        {
            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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

            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
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
    public sealed class TestPartialResult
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
            result2.Append("!");

            result1.Append(result2);

            Assert.AreEqual(result1.ToString(), "hello!");
        }

    }

    [TestClass]
    public sealed class TestAEL
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

        [TestMethod]
        public void TestMemoryInterface()
        {
            string jsonData = @"{
            ""person"": {
                ""firstName"": ""Super"",
                ""lastName"": ""man"",
                ""age"" : 79 
                }
            }";

            JToken token = JToken.Parse(jsonData);

            var memory = new SimpleObjectMemory(token);
            var (value, error) = new ValueExpression("${string(person.age)}").TryGetValue(memory);
            Assert.AreEqual("79", value);
        }

        [TestMethod]
        public void TestMemoryInterfaceWithDollarData()
        {
            string jsonData = @"{
            ""person"": {
                ""firstName"": ""Andrew"",
                ""lastName"": ""Leader""
              }
            }";

            JToken token = JToken.Parse(jsonData);
            var memory = new SimpleObjectMemory(token);
            memory.SetValue("$data", token);
            var (value, error) = new ValueExpression("${$data.person.firstName}").TryGetValue(memory);
            Assert.AreEqual("Andrew", value);
        }

        [TestMethod]
        public void TestMemoryInterfaceJValue()
        {
            JValue jval = new JValue("a");
            JObject jobj = new JObject();
            jobj["$data"] = jval;

            var memory = new SimpleObjectMemory(jobj);
            var (value, error) = new ValueExpression("${$data}").TryGetValue(memory);
            Assert.AreEqual("a", value);
        }

        [TestMethod]
        public void TestArrayTyepMemoryInterfaceWithDollarData()
        {
            string jsonData = @"{
            ""person"":[""Andrew"", ""Leader""]
            }";

            JToken token = JToken.Parse(jsonData);
            var memory = new SimpleObjectMemory(token);
            memory.SetValue("$data", token);
            var (value, error) = new ValueExpression("${$data.person}").TryGetValue(memory);
            Assert.AreEqual("Andrew", JToken.Parse(value as string)[0]);
        }

        [TestMethod]
        public void TestCustomFunction()
        {
            string jsonTemplate = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [{
                    ""type"": ""TextBlock"",
                    ""text"": ""${stringFormat(strings.myName, person.firstName, person.lastName)}""
                }]
            }";
            string jsonData = @"{
                ""strings"": {
                    ""myName"": ""My name is {0} {1}""
                },
                ""person"": {
                    ""firstName"": ""Andrew"",
                    ""lastName"": ""Leader""
                }
            }";
            AdaptiveCardTemplate transformer = new AdaptiveCardTemplate(jsonTemplate);
            var context = new EvaluationContext
            {
                Root = jsonData
            };
            Expression.Functions.Add("stringFormat", (args) =>
            {
                string formattedString = "";

                if (args[0] != null && args[1] != null && args[2] != null) 
                {
                    string format = args[0];
                    string[] stringArguments = {args[1], args[2] };
                    formattedString = string.Format(format, stringArguments);
                }
                return formattedString;
            });//, new ExpressionEvaluator(null, StringFormat, ReturnType.String));
            string cardJson = transformer.Expand(context);
            Test.TestTemplate.AssertJsonEqual(@"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""body"": [{
                    ""type"": ""TextBlock"",
                    ""text"": ""My name is Andrew Leader""
                }]
            }", cardJson);
        }        
    }
}
