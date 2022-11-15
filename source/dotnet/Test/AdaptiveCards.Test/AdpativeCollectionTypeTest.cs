// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdpativeCollectionTypeTest
    {
        const AdaptiveContainerStyle style = AdaptiveContainerStyle.Accent;
        const AdaptiveVerticalContentAlignment verticalContentAlignment = AdaptiveVerticalContentAlignment.Center;
        const bool bleed = true;
        const AdaptiveHorizontalContentAlignment tableRowHorizontalContentAlignment = AdaptiveHorizontalContentAlignment.Right;
        const AdaptiveVerticalContentAlignment tableRowVerticalContentAlignment = AdaptiveVerticalContentAlignment.Bottom;
        const bool tableRowBleed = true;
        const int tableCellCounts = 5;
        const int tableColumnDefinitionCounts = 3;

        public AdaptiveTableCell BuildASampleTableCell()
        {
            AdaptiveTableCell tableCell = new AdaptiveTableCell
            {
                Style = style,
                VerticalContentAlignment = verticalContentAlignment,
                Bleed = bleed,
            };

            var testTextBlocks = new List<AdaptiveTextBlock> { new AdaptiveTextBlock(),  new AdaptiveTextBlock(), new AdaptiveTextBlock()};
            foreach (var block in testTextBlocks)
            {
                tableCell.Add(new AdaptiveRichTextBlock());
            }

            return tableCell;
        }

        public AdaptiveTableRow BuildASampleTableRow(int cellCounts = tableCellCounts)
        {
            AdaptiveTableRow tableRow = new AdaptiveTableRow();

            for (int i = 0; i < cellCounts; i++)
            {
                tableRow.Cells.Add(BuildASampleTableCell());
            }

            return tableRow;
        }

        [TestMethod]
        public void TestTableCell()
        {
            AdaptiveTableCell tableCell = BuildASampleTableCell();

            Assert.AreEqual("AdaptiveCards.AdaptiveTableCell", tableCell.GetType().ToString());

            Assert.AreEqual(3, tableCell.Items.Count);
            Assert.AreEqual(style, tableCell.Style);
            Assert.AreEqual(verticalContentAlignment, tableCell.VerticalContentAlignment);
            Assert.AreEqual(bleed, tableCell.Bleed);
        }

        [TestMethod]
        public void TestTableRow()
        {
            AdaptiveTableRow tableRow = BuildASampleTableRow(10);
            Assert.AreEqual("AdaptiveCards.AdaptiveTableRow", tableRow.GetType().ToString());
            Assert.AreEqual(10, tableRow.Cells.Count);
        }

        [TestMethod]
        public void TestTableColumnDefinition()
        {
            AdaptiveTableColumnDefinition definition = new AdaptiveTableColumnDefinition();
            Assert.AreEqual("AdaptiveCards.AdaptiveTableColumnDefinition", definition.GetType().ToString());
            Assert.AreEqual(0U, definition.Width);
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Left, definition.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, definition.VerticalContentAlignment);
        }

        [TestMethod]
        public void TestTable()
        {
            AdaptiveTable table = new AdaptiveTable();
            Assert.AreEqual("AdaptiveCards.AdaptiveTable", table.GetType().ToString());
            Assert.AreEqual(0, table.Columns.Count);
            Assert.AreEqual(0, table.Rows.Count);
            Assert.IsTrue(table.ShowGridLines);
            Assert.IsFalse(table.FirstRowAsHeaders);
            Assert.AreEqual(null, table.GridStyle);
        }

        [TestMethod]
        public void TestTableCanAddTableRows()
        {
            var table = new AdaptiveTable();
            table.Rows.Add(BuildASampleTableRow());
            table.Rows.Add(BuildASampleTableRow(3));
            table.Rows.Add(BuildASampleTableRow(10));
            Assert.AreEqual(3, table.Rows.Count);
            Assert.AreEqual(10, table.Rows[2].Cells.Count);
        }

        [TestMethod]
        public void TestCanAddTableColumnDefinition()
        {
            var table = new AdaptiveTable();
            table.Columns.Add(new AdaptiveTableColumnDefinition());
            table.Columns.Add(new AdaptiveTableColumnDefinition());
            table.Columns.Add(new AdaptiveTableColumnDefinition());
            Assert.AreEqual(3, table.Columns.Count);
        }

        [TestMethod]
        public void TestTableDefaultAlignments()
        {
            AdaptiveTableRow tableRow = new AdaptiveTableRow();
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Left, tableRow.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, tableRow.VerticalContentAlignment);

            AdaptiveTableCell tableCell = new AdaptiveTableCell();
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, tableCell.VerticalContentAlignment);

            AdaptiveTableColumnDefinition definition = new AdaptiveTableColumnDefinition();
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Left, definition.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, definition.VerticalContentAlignment);

            AdaptiveTable table = new AdaptiveTable();
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Left, table.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, table.VerticalContentAlignment);
        }

        [TestMethod]
        public void TestTableDefaultRTL()
        {
            AdaptiveTableRow tableRow = new AdaptiveTableRow();
            Assert.AreEqual(null, tableRow.Rtl);
            Assert.AreEqual(null, tableRow.Rtl);

            AdaptiveTableCell tableCell = new AdaptiveTableCell();
            Assert.AreEqual(null, tableCell.Rtl);
        }

        [TestMethod]
        public void TestTableColumnDefintionSeserializationWithPixelWidth()
        {
            AdaptiveTable table = new AdaptiveTable();
            table.Columns.Add(new AdaptiveTableColumnDefinition()
            {
                PixelWidth = 200.50,
            });

            var card = new AdaptiveCard(AdaptiveCard.KnownSchemaVersion);
            card.Body.Add(table);

            var json = card.ToJson();
            const string ExpectedJSON = @"{
                                      ""type"": ""AdaptiveCard"",
                                      ""version"": ""1.5"",
                                      ""body"": [
                                        {
                                          ""type"": ""Table"",
                                          ""rows"": [],
                                          ""columns"": [
                                            {
                                              ""width"": ""200.5px""
                                            }
                                          ]
                                        }
                                      ]
                                    }";

            Assert.AreEqual(Utilities.RemoveWhiteSpacesFromJSON(ExpectedJSON), Utilities.RemoveWhiteSpacesFromJSON(json));
        }

        [TestMethod]
        public void TestTableColumnDefintionSeserializationWithRelativeWidth()
        {
            AdaptiveTable table = new AdaptiveTable();
            table.Columns.Add(new AdaptiveTableColumnDefinition()
            {
                Width = 200
            });

            var card = new AdaptiveCard(AdaptiveCard.KnownSchemaVersion);
            card.Body.Add(table);

            var json = card.ToJson();
            const string ExpectedJSON = @"{
                                      ""type"": ""AdaptiveCard"",
                                      ""version"": ""1.5"",
                                      ""body"": [
                                        {
                                          ""type"": ""Table"",
                                          ""rows"": [],
                                          ""columns"": [
                                            {
                                              ""width"": 200
                                            }
                                          ]
                                        }
                                      ]
                                    }";

            Assert.AreEqual(Utilities.RemoveWhiteSpacesFromJSON(ExpectedJSON), Utilities.RemoveWhiteSpacesFromJSON(json));
        }

        [TestMethod]
        public void TestTableColumnDefintionDeserialization()
        {
            const string json = @"{
                                      ""type"": ""AdaptiveCard"",
                                      ""version"": ""1.0"",
                                      ""body"": [
                                        {
                                          ""type"": ""Table"",
                                           ""id"":""table"",
                                          ""rows"": [],
                                          ""columns"": [
                                            {
                                              ""width"": 200
                                            },
                                            {
                                              ""width"": ""100px""
                                            },
                                            {
                                              ""width"": 50
                                            }
                                          ]
                                        }
                                      ]
                                    }";

            var parseResult = AdaptiveCard.FromJson(json);
            Assert.IsTrue(parseResult.Warnings.Count == 0);
            var table = Utilities.GetAdaptiveElementWithId(parseResult.Card, "table") as AdaptiveTable;
            Assert.IsNotNull(table);
            Assert.AreEqual(3, table.Columns.Count);
            Assert.AreEqual(200, table.Columns[0].Width);
            Assert.AreEqual(0, table.Columns[1].Width);
            Assert.AreEqual(100, table.Columns[1].PixelWidth);
            Assert.AreEqual(50, table.Columns[2].Width);
            Assert.AreEqual(0, table.Columns[2].PixelWidth);
        }

        [TestMethod]
        public void TestTableColumnDefintionDeserializationWithInvlidWidthValues()
        {
            const string json = @"{
                                      ""type"": ""AdaptiveCard"",
                                      ""version"": ""1.0"",
                                      ""body"": [
                                        {
                                          ""type"": ""Table"",
                                           ""id"":""table"",
                                          ""rows"": [],
                                          ""columns"": [
                                            {
                                              ""width"": -200
                                            },
                                            {
                                              ""width"": ""100""
                                            },
                                            {
                                              ""width"": ""50ppx"" 
                                            }
                                          ]
                                        }
                                      ]
                                    }";

            var parseResult = AdaptiveCard.FromJson(json);
            Assert.AreEqual(3, parseResult.Warnings.Count);
            var table = Utilities.GetAdaptiveElementWithId(parseResult.Card, "table") as AdaptiveTable;
            Assert.IsNotNull(table);
            Assert.AreEqual(3, table.Columns.Count);
            Assert.AreEqual(0, table.Columns[0].Width);
            Assert.AreEqual(0, table.Columns[1].Width);
            Assert.AreEqual(0, table.Columns[1].PixelWidth);
            Assert.AreEqual(0, table.Columns[2].Width);
            Assert.AreEqual(0, table.Columns[2].PixelWidth);
        }

        [TestMethod]
        public void TestTableDeserialization()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.ShowGridLines.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            Assert.AreEqual(0, parseResult.Warnings.Count);
            var table1 = parseResult.Card.Body[1] as AdaptiveTable;
            Assert.IsNotNull(table1);
            Assert.IsTrue(table1.ShowGridLines);
            var table2 = parseResult.Card.Body[3] as AdaptiveTable;
            Assert.IsNotNull(table2);
            Assert.IsTrue(!table2.ShowGridLines);
            Assert.AreEqual(1, table1.Columns[0].Width);
            Assert.AreEqual(0, table1.Columns[0].PixelWidth);
            Assert.AreEqual(1, table1.Columns[1].Width);
            Assert.AreEqual(0, table1.Columns[1].PixelWidth);

            Assert.AreEqual(1, table1.Columns[0].Width);
            Assert.AreEqual(0, table1.Columns[0].PixelWidth);
            Assert.AreEqual(1, table1.Columns[1].Width);
            Assert.AreEqual(0, table2.Columns[1].PixelWidth);

            Assert.AreEqual(2, table1.Columns.Count);
            Assert.AreEqual(2, table2.Columns.Count);

            Assert.AreEqual(3, table1.Rows.Count);
            Assert.AreEqual(3, table2.Rows.Count);

            Assert.AreEqual(AdaptiveContainerStyle.Accent, table1.Rows[1].Cells[0].Style);
            Assert.AreEqual(AdaptiveContainerStyle.Accent, table2.Rows[1].Cells[0].Style);
        }

        [TestMethod]
        public void TestTableDeserializationWithVerticalContentAlignment()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.VerticalCellContentAlignment.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            Assert.AreEqual(0, parseResult.Warnings.Count);
            var table = parseResult.Card.Body[1] as AdaptiveTable;
            Assert.IsNotNull(table);

            var innerTable1 = table.Rows[0].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable1);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top,innerTable1.VerticalContentAlignment);

            var innerTable2 = table.Rows[1].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable2);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Center, innerTable2.VerticalContentAlignment);

            var innerTable3 = table.Rows[2].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable3);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Bottom, innerTable3.VerticalContentAlignment);
        }

        [TestMethod]
        public void TestTableDeserializationWithHorizontalContentAlignment()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.HorizontalCellContentAlignment.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            Assert.AreEqual(0, parseResult.Warnings.Count);
            var table = parseResult.Card.Body[1] as AdaptiveTable;
            Assert.IsNotNull(table);

            var innerTable1 = table.Rows[0].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable1);
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Left, innerTable1.HorizontalContentAlignment);

            var innerTable2 = table.Rows[1].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable2);
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Center, innerTable2.HorizontalContentAlignment);

            var innerTable3 = table.Rows[2].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(innerTable3);
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Right, innerTable3.HorizontalContentAlignment);
        }

        [TestMethod]
        public void TestTableDeserializationWithFirstRowAsHeader()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.FirstRowAsHeaders.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            Assert.AreEqual(0, parseResult.Warnings.Count);

            var table1 = parseResult.Card.Body[1] as AdaptiveTable;
            Assert.IsNotNull(table1);
            Assert.AreEqual(true, table1.FirstRowAsHeaders);

            var table2 = parseResult.Card.Body[3] as AdaptiveTable;
            Assert.IsNotNull(table2);
            Assert.AreEqual(false, table2.FirstRowAsHeaders);
        }

        [TestMethod]
        public void TestTableDeserializationWithGridStyle()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.GridStyle.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            Assert.AreEqual(0, parseResult.Warnings.Count);

            var rootTable = parseResult.Card.Body[1] as AdaptiveTable;
            Assert.IsNotNull(rootTable);

            var table1 = rootTable.Rows[1].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(table1);
            Assert.AreEqual(AdaptiveContainerStyle.Good, table1.GridStyle);

            var table2 = rootTable.Rows[2].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(table2);
            Assert.AreEqual(AdaptiveContainerStyle.Warning, table2.GridStyle);

            var table3 = rootTable.Rows[3].Cells[1].Items[0] as AdaptiveTable;
            Assert.IsNotNull(table3);
            Assert.AreEqual(AdaptiveContainerStyle.Attention, table3.GridStyle);
        }

        [TestMethod]
        public void TestRoundTrip()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Table.json", "v1.5", "Elements");
            var parseResult = AdaptiveCard.FromJson(sampleJSON);
            var expectedJSON = parseResult.Card.ToJson();
            var parsedCard = AdaptiveCard.FromJson(expectedJSON);
            Assert.AreEqual(Utilities.RemoveWhiteSpacesFromJSON(expectedJSON), Utilities.RemoveWhiteSpacesFromJSON(parsedCard.Card.ToJson()));
        }
    }
}
