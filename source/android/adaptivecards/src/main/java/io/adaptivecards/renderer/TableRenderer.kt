package io.adaptivecards.renderer

import android.content.Context
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.graphics.drawable.GradientDrawable
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TableLayout
import android.widget.TableRow
import androidx.core.view.updateLayoutParams
import androidx.fragment.app.FragmentManager
import io.adaptivecards.objectmodel.*
import io.adaptivecards.renderer.actionhandler.ICardActionHandler
import io.adaptivecards.renderer.readonly.ContainerRenderer
import io.adaptivecards.renderer.registration.CardRendererRegistration

object TableRenderer : BaseCardElementRenderer() {

    override fun render(renderedCard: RenderedAdaptiveCard, context: Context, fragmentManager: FragmentManager, viewGroup: ViewGroup, baseCardElement: BaseCardElement, cardActionHandler: ICardActionHandler?, hostConfig: HostConfig, renderArgs: RenderArgs): View {

        val table = Util.castTo(baseCardElement, Table::class.java)
        val tableCellRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.TableCell.toString())
                ?: throw IllegalStateException("No renderer registered for ${CardElementType.TableCell}")
        val tableLayout = TableLayout(context).apply {
            tag = TagContent(table)
            layoutParams = ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT)
            clipChildren = false
            clipToPadding = false
        }

        for (i in table.GetRows().indices) {
            val row = table.GetRows()[i]
            val rowLayout = TableRow(context).apply {
                clipChildren = false
                clipToPadding = false
            }

            for (j in table.GetColumns().indices) {
                val cell = row.GetCells().getOrNull(j) ?: break
                val cellArgs = TableCellRenderArgs(renderArgs, i, j, table, tableLayout).apply {
                    isHeader = (i == 0) && table.GetFirstRowAsHeaders()
                }
                tableCellRenderer.render(renderedCard, context, fragmentManager, rowLayout, cell, cardActionHandler, hostConfig, cellArgs)
            }
            tableLayout.addView(rowLayout)
        }

        viewGroup.addView(tableLayout)
        return tableLayout
    }
}

open class TableCellRenderArgs(renderArgs: RenderArgs, val rowIndex: Int, val colIndex: Int, val table: Table, val tableLayout: TableLayout) : RenderArgs(renderArgs)

object TableCellRenderer : BaseCardElementRenderer() {
    override fun render(renderedCard: RenderedAdaptiveCard, context: Context, fragmentManager: FragmentManager, viewGroup: ViewGroup, baseCardElement: BaseCardElement, cardActionHandler: ICardActionHandler?, hostConfig: HostConfig, renderArgs: RenderArgs): View {
        if (renderArgs !is TableCellRenderArgs) throw IllegalArgumentException("renderArgs must be instance of TableCellRenderArgs")

        val cell = Util.castTo(baseCardElement, TableCell::class.java)
        val cellLayout = LinearLayout(context).apply {
            orientation = LinearLayout.VERTICAL
            tag = TagContent(cell)
            layoutParams = TableRow.LayoutParams(0, TableLayout.LayoutParams.MATCH_PARENT)
        }
        val index = renderArgs.colIndex
        val row = renderArgs.table.GetRows()[renderArgs.rowIndex]
        val col = renderArgs.table.GetColumns()[index]

        cell.SetStyle(ContainerRenderer.getLocalContainerStyle(cell, row.GetStyle()))
        ContainerRenderer.applyVerticalContentAlignment(cellLayout, cell.GetVerticalContentAlignment())
        ContainerRenderer.applyPadding(ContainerRenderer.getLocalContainerStyle(cell, renderArgs.containerStyle), renderArgs.containerStyle, cellLayout, context, hostConfig)

        val spacing = Util.dpToPixels(context, getSpacingSize(cell.GetSpacing(), hostConfig.GetSpacing()).toFloat())
        val padding = Util.dpToPixels(context, hostConfig.GetSpacing().paddingSpacing.toFloat())
        cellLayout.updateLayoutParams<ViewGroup.MarginLayoutParams> {
            // No bleeding or spacing when showing grid lines
            if (renderArgs.table.GetShowGridLines()) {
                cellLayout.background = GradientDrawable().apply {
                    shape = GradientDrawable.RECTANGLE
                    // border color from config
                    setStroke(1, Color.parseColor(hostConfig.GetBorderColor(renderArgs.table.GetGridStyle())))
                    // preserve fill color from existing drawable
                    setColor((cellLayout.background as? ColorDrawable)?.color ?: Color.TRANSPARENT)
                }
            }
            // To bleed, negate margins of first/last cells
            else if (cell.GetBleed()) {
                if (index == 0) marginStart = -padding
                if (index == renderArgs.table.GetColumns().size - 1) marginEnd = -padding
            }
            // Otherwise, add margin between cells
            else if (index != 0) {
                marginStart = spacing
            }
        }

        if (col.GetWidth() != null) {
            cellLayout.updateLayoutParams<TableRow.LayoutParams> { width = 0; weight = col.GetWidth().toFloat() }
            renderArgs.tableLayout.setColumnShrinkable(index, true)
            renderArgs.tableLayout.setColumnStretchable(index, true)
        }
        else if (col.GetPixelWidth() != null)
        {
            cellLayout.updateLayoutParams<TableRow.LayoutParams> { width = Util.dpToPixels(context, col.GetPixelWidth().toFloat()) }
            renderArgs.tableLayout.setColumnShrinkable(index, false)
            renderArgs.tableLayout.setColumnStretchable(index, false)
        }

        cell.SetVerticalContentAlignment(cell.GetVerticalContentAlignment()
                ?: (if (row.GetVerticalCellContentAlignment() != null) VerticalContentAlignment.values()[row.GetVerticalCellContentAlignment().ordinal] else null)
                ?: (if (row.GetVerticalCellContentAlignment() != null) VerticalContentAlignment.values()[col.GetVerticalCellContentAlignment().ordinal] else null)
                ?: (if (row.GetVerticalCellContentAlignment() != null) VerticalContentAlignment.values()[renderArgs.table.GetVerticalCellContentAlignment().ordinal] else null))

        setVisibility(cell.GetIsVisible(), cellLayout)
        setMinHeight(cell.GetMinHeight(), cellLayout, context)
        applyRtl(cell.GetRtl(), cellLayout)
        ContainerRenderer.applyVerticalContentAlignment(cellLayout, cell.GetVerticalContentAlignment())
        ContainerRenderer.setSelectAction(renderedCard, cell.GetSelectAction(), cellLayout, cardActionHandler, renderArgs)

        CardRendererRegistration.getInstance().renderElements(renderedCard,
                context,
                fragmentManager,
                cellLayout,
                cell.GetItems(),
                cardActionHandler,
                hostConfig,
                RenderArgs(renderArgs).apply {
                    containerStyle = cell.GetStyle()
                })

        viewGroup.addView(cellLayout)
        return cellLayout
    }
}