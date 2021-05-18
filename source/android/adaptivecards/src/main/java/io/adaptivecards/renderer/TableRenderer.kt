package io.adaptivecards.renderer

import android.content.Context
import android.view.View
import android.view.ViewGroup
import android.widget.TableLayout
import android.widget.TableRow
import android.widget.TextView
import androidx.fragment.app.FragmentManager
import io.adaptivecards.objectmodel.BaseCardElement
import io.adaptivecards.objectmodel.HostConfig
import io.adaptivecards.objectmodel.Table
import io.adaptivecards.renderer.actionhandler.ICardActionHandler

object TableRenderer : BaseCardElementRenderer() {
    override fun render(renderedCard: RenderedAdaptiveCard?, context: Context?, fragmentManager: FragmentManager?, viewGroup: ViewGroup?, baseCardElement: BaseCardElement?, cardActionHandler: ICardActionHandler?, hostConfig: HostConfig?, renderArgs: RenderArgs?): View {
        viewGroup ?: throw IllegalArgumentException("Parent should not be null")

        val table = Util.castTo(baseCardElement, Table::class.java)
//        val tableCellRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.TableCell.toString())
//                ?: throw IllegalStateException("No renderer registered for ${CardElementType.TableCell.toString()}")
        val tableLayout = TableLayout(context)
        tableLayout.tag = TagContent(table)

        for ((i, row) in table.GetRows().withIndex()) {
            val rowLayout = TableRow(context)
            for ((j, cell) in row.GetCells().withIndex()) {
                val cellLayout = TextView(context)
                cellLayout.text = "Row $i, Cell $j"
                rowLayout.addView(cellLayout)
            }
            tableLayout.addView(rowLayout)
        }

        viewGroup.addView(tableLayout)

        return tableLayout;
    }
}