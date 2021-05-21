package io.adaptivecards.renderer.readonly

import android.content.Context
import android.graphics.Color
import android.graphics.drawable.GradientDrawable
import android.view.View
import android.view.ViewGroup
import android.widget.LinearLayout
import android.widget.TableLayout
import android.widget.TableRow
import androidx.core.view.updateLayoutParams
import androidx.fragment.app.FragmentManager
import io.adaptivecards.objectmodel.BaseCardElement
import io.adaptivecards.objectmodel.HostConfig
import io.adaptivecards.objectmodel.Table
import io.adaptivecards.objectmodel.TableCell
import io.adaptivecards.renderer.*
import io.adaptivecards.renderer.actionhandler.ICardActionHandler
import io.adaptivecards.renderer.registration.CardRendererRegistration

open class TableCellRenderArgs(renderArgs: RenderArgs, val rowIndex: Int, val colIndex: Int, val table: Table, val tableLayout: TableLayout) : RenderArgs(renderArgs)

object TableCellRenderer : BaseCardElementRenderer() {
    override fun render(renderedCard: RenderedAdaptiveCard, context: Context, fragmentManager: FragmentManager, viewGroup: ViewGroup, baseCardElement: BaseCardElement, cardActionHandler: ICardActionHandler?, hostConfig: HostConfig, renderArgs: RenderArgs): View {
        if (renderArgs !is TableCellRenderArgs) throw IllegalArgumentException("renderArgs must be instance of TableCellRenderArgs")

        val row = renderArgs.table.GetRows()[renderArgs.rowIndex]
        val col = renderArgs.table.GetColumns()[renderArgs.colIndex]

        val cell = Util.castTo(baseCardElement, TableCell::class.java)
        val cellLayout = LinearLayout(context).apply {
            orientation = LinearLayout.VERTICAL
            tag = TagContent(cell)
            layoutParams = TableRow.LayoutParams(0, TableLayout.LayoutParams.MATCH_PARENT)
        }

        cellLayout.updateLayoutParams<ViewGroup.MarginLayoutParams> {
            val isFirst = renderArgs.colIndex == 0
            val isLast = renderArgs.colIndex == renderArgs.table.GetColumns().size - 1

            if (renderArgs.table.GetShowGridLines()) {
                // For grid lines, draw rectangle
                cellLayout.background = GradientDrawable().apply {
                    shape = GradientDrawable.RECTANGLE
                    setColor(Color.TRANSPARENT)

                    // border color from config
                    val borderColor = Color.parseColor(hostConfig.GetBorderColor(renderArgs.table.GetGridStyle()))
                    setStroke(Util.dpToPixels(context, 1f), borderColor)
                }
            } else if (cell.GetBleed()) {
                // To bleed, negate margins of first/last cells
                val padding = Util.dpToPixels(context, hostConfig.GetSpacing().paddingSpacing.toFloat())
                if (isFirst) marginStart = -padding
                if (isLast) marginEnd = -padding
            } else {
                // Otherwise, add spacing between cells
                val spacing = Util.dpToPixels(context, hostConfig.GetTable().cellSpacing.toFloat())
                if (!isFirst) marginStart = spacing / 2
                if (!isLast) marginEnd = spacing / 2
            }
        }

        if (col.GetWidth() != null) {
            // Weighted columns can stretch/shrink
            cellLayout.updateLayoutParams<TableRow.LayoutParams> { width = 0; weight = col.GetWidth()!!.toFloat() }
            renderArgs.tableLayout.setColumnShrinkable(renderArgs.colIndex, true)
            renderArgs.tableLayout.setColumnStretchable(renderArgs.colIndex, true)
        } else if (col.GetPixelWidth() != null) {
            // Pixel columns are fixed width
            cellLayout.updateLayoutParams<TableRow.LayoutParams> { width = Util.dpToPixels(context, col.GetPixelWidth()!!.toFloat()) }
            renderArgs.tableLayout.setColumnShrinkable(renderArgs.colIndex, false)
            renderArgs.tableLayout.setColumnStretchable(renderArgs.colIndex, false)
        }

        setVisibility(cell.GetIsVisible(), cellLayout)
        setMinHeight(cell.GetMinHeight(), cellLayout, context)
        applyRtl(cell.GetRtl(), cellLayout)

        ContainerRenderer.applyPadding(ContainerRenderer.getLocalContainerStyle(cell, renderArgs.containerStyle), renderArgs.containerStyle, cellLayout, hostConfig, renderArgs.table.GetShowGridLines())
        ContainerRenderer.applyContainerStyle(ContainerRenderer.getLocalContainerStyle(cell, renderArgs.containerStyle), cellLayout, hostConfig)
        ContainerRenderer.applyVerticalContentAlignment(cellLayout, cell.GetVerticalContentAlignment()
                ?: row.GetVerticalCellContentAlignment()
                ?: col.GetVerticalCellContentAlignment()
                ?: renderArgs.table.GetVerticalCellContentAlignment())
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