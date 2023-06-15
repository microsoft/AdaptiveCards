// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly

import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.TableLayout
import android.widget.TableRow
import androidx.fragment.app.FragmentManager
import io.adaptivecards.objectmodel.*
import io.adaptivecards.renderer.*
import io.adaptivecards.renderer.actionhandler.ICardActionHandler
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

        val isFirstRowHeader = table.GetFirstRowAsHeaders()
        val computedGridStyle = if (table.GetGridStyle() == ContainerStyle.None) {
            renderArgs.containerStyle
        } else {
            table.GetGridStyle()
        }

        for (i in table.GetRows().indices) {
            val row = table.GetRows()[i]
            val rowLayout = TableRow(context).apply {
                clipChildren = false
                clipToPadding = false
            }
            val rowStyle = ContainerRenderer.computeContainerStyle(row.GetStyle(), renderArgs.containerStyle)
            ContainerRenderer.applyContainerStyle(rowStyle, renderArgs.containerStyle, rowLayout, hostConfig)

            for (j in table.GetColumns().indices) {
                val cell = row.GetCells().getOrNull(j) ?: break
                val cellArgs = TableCellRenderArgs(renderArgs, table, tableLayout, i, j, computedGridStyle).apply {
                    containerStyle = rowStyle
                    isColumnHeader = (i == 0) && isFirstRowHeader
                }
                tableCellRenderer.render(renderedCard, context, fragmentManager, rowLayout, cell, cardActionHandler, hostConfig, cellArgs)
            }
            tableLayout.addView(rowLayout)
        }

        viewGroup.addView(tableLayout)
        return tableLayout
    }
}