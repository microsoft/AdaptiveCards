// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdpativeCollectionTypeTest
    {
        const AdaptiveContainerStyle style = AdaptiveContainerStyle.Accent;
        const AdaptiveVerticalContentAlignment verticalContentAlignment = AdaptiveVerticalContentAlignment.Center;
        const bool bleed = true;
        const AdaptiveHorizontalContentAlignment tableRowHorizontalContentAlignment = AdaptiveHorizontalContentAlignment.Trailing;
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
            Assert.AreEqual(0U, definition.PixelWidth);
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Leading, definition.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, definition.VerticalContentAlignment);
        }

        [TestMethod]
        public void TestTable()
        {
            AdaptiveTable table = new AdaptiveTable();
            Assert.AreEqual("AdaptiveCards.AdaptiveTable", table.GetType().ToString());
            Assert.AreEqual(0, table.Columns.Count);
            Assert.AreEqual(0, table.Rows.Count);
            Assert.IsFalse(table.ShowGridLine);
            Assert.IsFalse(table.FirstRowAsHeader);
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
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Leading, tableRow.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, tableRow.VerticalContentAlignment);

            AdaptiveTableCell tableCell = new AdaptiveTableCell();
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, tableCell.VerticalContentAlignment);

            AdaptiveTableColumnDefinition definition = new AdaptiveTableColumnDefinition();
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Leading, definition.HorizontalContentAlignment);
            Assert.AreEqual(AdaptiveVerticalContentAlignment.Top, definition.VerticalContentAlignment);

            AdaptiveTable table = new AdaptiveTable();
            Assert.AreEqual(AdaptiveHorizontalContentAlignment.Leading, table.HorizontalContentAlignment);
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
        public void TestRoundTripTest()
        {
            var expectedJson = Utilities.GetSampleJSON("v1.5", "elements", "Table.json");
            Assert.IsNotNull(expectedJson);
            var parseResult = AdaptiveCard.FromJson(expectedJson);
            Assert.AreEqual(0, parseResult.Warnings.Count);
            Assert.AreEqual(expectedJson, parseResult.Card.ToJson());
        }
    }
}
