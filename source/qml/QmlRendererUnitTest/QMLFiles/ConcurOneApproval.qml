import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
Rectangle{
id:adaptiveCard
readonly property int margins:12
implicitHeight:adaptiveCardLayout.implicitHeight
Layout.fillWidth:true
readonly property string bgColor:'#FFFFFF'
color:bgColor
signal buttonClicked(var title, var type, var data)
function generateStretchHeight(childrens,minHeight){
var n = childrens.length
var implicitHt = 0;
var stretchCount = 0;
var stretchMinHeight = 0;
for(var i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator !== 'undefined')
{
implicitHt += childrens[i].height;
stretchMinHeight += childrens[i].height;
}
else
{
implicitHt += childrens[i].implicitHeight;
if(typeof childrens[i].stretch !== 'undefined')
{
stretchCount++;
}
else
{
stretchMinHeight += childrens[i].implicitHeight;
}
}
}
stretchMinHeight = (minHeight - stretchMinHeight)/stretchCount
for(i=0;(i<childrens.length);i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined' && typeof childrens[i].minHeight !== 'undefined')
{
childrens[i].minHeight = Math.max(childrens[i].minHeight,stretchMinHeight)
}
}
}
if(stretchCount > 0 && implicitHt < minHeight)
{
var stretctHeight = (minHeight - implicitHt)/stretchCount
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined')
{
childrens[i].height = childrens[i].implicitHeight + stretctHeight
}
}
}
}
else
{
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined')
{
childrens[i].height = childrens[i].implicitHeight
}
}
}
}
}
function generateStretchWidth(childrens,width){
var implicitWid = 0
var autoWid = 0
var autoCount = 0
var weightSum = 0
var stretchCount = 0
var weightPresent = 0
for(var i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator !== 'undefined')
{
implicitWid += childrens[i].width
}
else
{
if(childrens[i].widthProperty.endsWith("px"))
{
childrens[i].width = parseInt(childrens[i].widthProperty.slice(0,-2))
implicitWid += childrens[i].width
}
else
{
if(childrens[i].widthProperty === "auto")
{
autoCount++
}
else if(childrens[i].widthProperty === "stretch")
{
stretchCount++
implicitWid += 50;
}
else
{
weightPresent = 1
weightSum += parseInt(childrens[i].widthProperty)
}
}
}
}
autoWid = (width - implicitWid)/(weightPresent + autoCount)
var flags = new Array(childrens.length).fill(0)
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === "auto")
{
if(childrens[i].minWidth < autoWid)
{
childrens[i].width = childrens[i].minWidth
implicitWid += childrens[i].width
flags[i] = 1;
autoCount--;
autoWid = (width - implicitWid)/(weightPresent + autoCount)
}
}
}
}
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === "auto")
{
if(flags[i] === 0)
{
childrens[i].width = autoWid
implicitWid += childrens[i].width
}
}
else if(childrens[i].widthProperty !== "stretch" && !childrens[i].widthProperty.endsWith("px"))
{
if(weightSum !== 0)
{
childrens[i].width = ((parseInt(childrens[i].widthProperty)/weightSum) * autoWid)
implicitWid += childrens[i].width
}
}
}
}
var stretchWidth = (width - implicitWid)/stretchCount
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === 'stretch')
{
childrens[i].width = 50+stretchWidth
}
}
}
}
function getMinWidth(childrens){
var min = 0
for(var j =0;j<childrens.length;j++)
{
if(typeof childrens[j].minWidth === 'undefined')
{
min = Math.max(min,Math.ceil(childrens[j].implicitWidth))
}
else
{
min = Math.max(min,Math.ceil(childrens[j].minWidth))
}
}
return min
}
function getMinWidthActionSet(childrens,spacing){
var min = 0
for(var j =0;j<childrens.length;j++)
{
min += Math.ceil(childrens[j].implicitWidth)
}
min += ((childrens.length - 1)*spacing)
return min
}
function getMinWidthFactSet(childrens, spacing){
var min = 0
for(var j=0;j<childrens.length;j+=2)
{
min = Math.max(min,childrens[j].implicitWidth + childrens[j+1].implicitWidth + spacing)
}
return min;
}
ColumnLayout{
id:adaptiveCardLayout
width:parent.width
Rectangle{
id:adaptiveCardRectangle
color:'transparent'
Layout.topMargin:margins
Layout.bottomMargin:margins
Layout.leftMargin:margins
Layout.rightMargin:margins
Layout.fillWidth:true
Layout.preferredHeight:bodyLayout.height
Layout.minimumHeight:1
Column{
id:bodyLayout
width:parent.width
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children,-24)}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children,-24)}
Frame{
id:container_auto_1
padding:0
property int minHeight:0
implicitHeight:Math.max(0, clayout_container_auto_1.implicitHeight)
readonly property string bgColor:'transparent'
background:Rectangle{
id:container_auto_1_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onMinHeightChanged:{adaptiveCard.generateStretchHeight( column_container_auto_1.children,minHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_container_auto_1.children) + 0}
width:parent.width
ColumnLayout{
id:clayout_container_auto_1
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_container_auto_1
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, container_auto_1.minHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, container_auto_1.minHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"1 Pending approval"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:17
font.weight:Font.Bold
wrapMode:Text.Wrap
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Here's the last report pending your approval:"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
wrapMode:Text.Wrap
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Frame{
property int minHeight:0
readonly property string bgColor:'transparent'
id:columnSet_auto_1
implicitHeight:getColumnSetHeight()
padding:0
background:Rectangle{
id:columnSet_auto_1_bgRect
border.width:0
color:parent.bgColor
}

property int stretchMinHeight:0
onMinHeightChanged:{ stretchMinHeight = Math.max(minHeight - 0, stretchMinHeight)}
width:parent.width
onWidthChanged:{adaptiveCard.generateStretchWidth( row_columnSet_auto_1.children, parent.width - (0))}
function getColumnSetHeight(){ var calculatedHeight = getColumnHeight(true);if(calculatedHeight >= minHeight - (0)){return calculatedHeight + (0)}else{return minHeight;}}
function getColumnHeight(bleed){var calculatedHeight =  Math.max(clayout_column_auto_1.implicitHeight - 0,column_auto_1.minHeight, clayout_column_auto_2.implicitHeight - 0,column_auto_2.minHeight); if(calculatedHeight < minHeight - (0)){return minHeight - (0)}else{if(calculatedHeight === 0 && !bleed){return calculatedHeight + 0 }else{return calculatedHeight}}}
RowLayout{
id:rlayout_columnSet_auto_1
width:parent.width
Row{
Layout.alignment:Qt.AlignLeft
id:row_columnSet_auto_1
Frame{
id:column_auto_1
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_1.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_1_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_1.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_1.children) + 0}
implicitWidth:minWidth
property string widthProperty:'20px'
property int stretchMinHeight:Math.max(columnSet_auto_1.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_1
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
id:column_column_auto_1
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_1.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_1.stretchMinHeight - 0 )}
}
}
}
Rectangle{
readonly property bool seperator:true
width:12
height:columnSet_auto_1.getColumnHeight(false)
color:"transparent"
visible:true
}
Frame{
id:column_auto_2
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_1.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_2_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_2.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_2.children) + 0}
implicitWidth:minWidth
property string widthProperty:'stretch'
property int stretchMinHeight:Math.max(columnSet_auto_1.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_2
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_column_auto_2
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_2.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_2.stretchMinHeight - 0 )}
Frame{
property int minHeight:0
readonly property string bgColor:'transparent'
id:columnSet_auto_2
implicitHeight:getColumnSetHeight()
padding:0
background:Rectangle{
id:columnSet_auto_2_bgRect
border.width:0
color:parent.bgColor
}

property int stretchMinHeight:0
onMinHeightChanged:{ stretchMinHeight = Math.max(minHeight - 0, stretchMinHeight)}
width:parent.width
onWidthChanged:{adaptiveCard.generateStretchWidth( row_columnSet_auto_2.children, parent.width - (0))}
function getColumnSetHeight(){ var calculatedHeight = getColumnHeight(true);if(calculatedHeight >= minHeight - (0)){return calculatedHeight + (0)}else{return minHeight;}}
function getColumnHeight(bleed){var calculatedHeight =  Math.max(clayout_column_auto_3.implicitHeight - 0,column_auto_3.minHeight, clayout_column_auto_4.implicitHeight - 0,column_auto_4.minHeight); if(calculatedHeight < minHeight - (0)){return minHeight - (0)}else{if(calculatedHeight === 0 && !bleed){return calculatedHeight + 0 }else{return calculatedHeight}}}
RowLayout{
id:rlayout_columnSet_auto_2
width:parent.width
Row{
Layout.alignment:Qt.AlignLeft
id:row_columnSet_auto_2
Frame{
id:column_auto_3
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_2.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_3_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_3.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_3.children) + 0}
implicitWidth:minWidth
property string widthProperty:'auto'
property int stretchMinHeight:Math.max(columnSet_auto_2.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_3
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_column_auto_3
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_3.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_3.stretchMinHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Employee"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
readonly property bool stretch:true
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:4
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Andrew Davis"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Bold
font.family:"Segoe UI"
readonly property bool stretch:true
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Report Date"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Amount due to employee"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Claimed Amount"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
}
}
}
Rectangle{
readonly property bool seperator:true
width:12
height:columnSet_auto_2.getColumnHeight(false)
color:"transparent"
visible:true
}
Frame{
id:column_auto_4
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_2.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_4_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_4.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_4.children) + 0}
implicitWidth:minWidth
property string widthProperty:'auto'
property int stretchMinHeight:Math.max(columnSet_auto_2.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_4
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_column_auto_4
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_4.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_4.stretchMinHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Report Name:"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
readonly property bool stretch:true
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"Team offsite in Seattle"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Bold
font.family:"Segoe UI"
readonly property bool stretch:true
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"2019-06-09"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"$2039.12"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"$2039.12"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:"Segoe UI"
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:true
}
Flow{
width:parent.width
spacing:8
layoutDirection:Qt.LeftToRight
Button{
id:button_auto_1
background:Rectangle{
id:button_auto_1_bg
anchors.fill:parent
radius:button_auto_1.height / 2
border.width:1
border.color:button_auto_1.pressed ? '#0A5E7D' : '#007EA8'
color:button_auto_1.pressed ? '#0A5E7D' : button_auto_1.hovered ? '#007EA8' : 'white'
}

contentItem:Item{
implicitHeight:button_auto_1_row.implicitHeight
implicitWidth:button_auto_1_row.implicitWidth
Row{
id:button_auto_1_row
spacing:5
leftPadding:5
rightPadding:5
Row{
spacing:5
Text{
text:"Approve"
font.pixelSize:14
color:button_auto_1.hovered ? '#FFFFFF' : '#007EA8'
}
}
}
}

onClicked:{
var paramJson = {};
var parmStr = "{\"buttonId\":\"lastApproveBtn\"}";
paramJson = JSON.parse(parmStr);
var paramslist = JSON.stringify(paramJson);
adaptiveCard.buttonClicked("Approve", "Action.Submit", paramslist);
console.log(paramslist);
}

}
Button{
id:button_auto_2
property bool showCard:false
background:Rectangle{
id:button_auto_2_bg
anchors.fill:parent
radius:button_auto_2.height / 2
border.width:1
border.color:button_auto_2.showCard ? '#0A5E7D' : button_auto_2.pressed ? '#0A5E7D' : '#007EA8'
color:button_auto_2.showCard ? '#0A5E7D' : button_auto_2.pressed ? '#0A5E7D' : button_auto_2.hovered ? '#007EA8' : 'white'
}

contentItem:Item{
implicitHeight:button_auto_2_row.implicitHeight
implicitWidth:button_auto_2_row.implicitWidth
Row{
id:button_auto_2_row
spacing:5
leftPadding:5
rightPadding:5
Row{
spacing:5
Text{
text:"Send back"
font.pixelSize:14
color:button_auto_2.showCard ? '#FFFFFF' : button_auto_2.hovered ? '#FFFFFF' : '#007EA8'
}
Item{
height:14
width:14
Image{
id:button_auto_2_icon
anchors.fill:parent
fillMode:Image.PreserveAspectFit
mipmap:true
anchors.verticalCenter:parent.verticalCenter
source:"data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bmF2aWdhdGlvbi9hcnJvdy1kb3duXzEyPC90aXRsZT48cGF0aCBkPSJNMS4wMDA0MSAzLjQ5OTc0ODc2NGMwLS4xMzcuMDU2LS4yNzMuMTY1LS4zNzIuMjA2LS4xODUwMDAwMDAxLjUyMi0uMTY4MDAwMDAwMS43MDcuMDM3bDQuMTI4IDQuNTg2OTk5OTk2IDQuMTI4LTQuNTg2OTk5OTk2Yy4xODUtLjIwNTAwMDAwMDEuNTAxLS4yMjIwMDAwMDAxLjcwNy0uMDM3LjIwNC4xODUuMjIxLjUwMS4wMzcuNzA2bC00LjUgNC45OTk5OTk5OTZjLS4wOTYuMTA2LS4yMy4xNjYtLjM3Mi4xNjYtLjE0MiAwLS4yNzYtLjA2LS4zNzItLjE2NmwtNC41LTQuOTk5OTk5OTk2Yy0uMDg2LS4wOTUtLjEyOC0uMjE1LS4xMjgtLjMzNCIgZmlsbD0iIzAwMCIgZmlsbC1ydWxlPSJldmVub2RkIi8+PC9zdmc+"
}
ColorOverlay{
anchors.fill:button_auto_2_icon
source:button_auto_2_icon
color:button_auto_2.showCard ? '#FFFFFF' : button_auto_2.hovered ? '#FFFFFF' : '#007EA8'
}
}
}
}
}

onClicked:{

button_auto_2.showCard = !button_auto_2.showCard
button_auto_2_loader.visible = button_auto_2.showCard
button_auto_2_icon.source = button_auto_2.showCard ? "data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bmF2aWdhdGlvbi9hcnJvdy11cF8xMjwvdGl0bGU+PHBhdGggZD0iTTEuMDAwNDEgOC41MDAyNTEyMzZjMCAuMTM3LjA1Ni4yNzMuMTY1LjM3Mi4yMDYuMTg1MDAwMDAwMS41MjIuMTY4MDAwMDAwMS43MDctLjAzN2w0LjEyOC00LjU4Njk5OTk5NiA0LjEyOCA0LjU4Njk5OTk5NmMuMTg1LjIwNTAwMDAwMDEuNTAxLjIyMjAwMDAwMDEuNzA3LjAzNy4yMDQtLjE4NS4yMjEtLjUwMS4wMzctLjcwNmwtNC41LTQuOTk5OTk5OTk2Yy0uMDk2LS4xMDYtLjIzLS4xNjYtLjM3Mi0uMTY2LS4xNDIgMC0uMjc2LjA2LS4zNzIuMTY2bC00LjUgNC45OTk5OTk5OTZjLS4wODYuMDk1LS4xMjguMjE1LS4xMjguMzM0IiBmaWxsPSIjMDAwIiBmaWxsLXJ1bGU9ImV2ZW5vZGQiLz48L3N2Zz4=":"data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMTIiIGhlaWdodD0iMTIiIHZpZXdCb3g9IjAgMCAxMiAxMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bmF2aWdhdGlvbi9hcnJvdy1kb3duXzEyPC90aXRsZT48cGF0aCBkPSJNMS4wMDA0MSAzLjQ5OTc0ODc2NGMwLS4xMzcuMDU2LS4yNzMuMTY1LS4zNzIuMjA2LS4xODUwMDAwMDAxLjUyMi0uMTY4MDAwMDAwMS43MDcuMDM3bDQuMTI4IDQuNTg2OTk5OTk2IDQuMTI4LTQuNTg2OTk5OTk2Yy4xODUtLjIwNTAwMDAwMDEuNTAxLS4yMjIwMDAwMDAxLjcwNy0uMDM3LjIwNC4xODUuMjIxLjUwMS4wMzcuNzA2bC00LjUgNC45OTk5OTk5OTZjLS4wOTYuMTA2LS4yMy4xNjYtLjM3Mi4xNjYtLjE0MiAwLS4yNzYtLjA2LS4zNzItLjE2NmwtNC41LTQuOTk5OTk5OTk2Yy0uMDg2LS4wOTUtLjEyOC0uMjE1LS4xMjgtLjMzNCIgZmlsbD0iIzAwMCIgZmlsbC1ydWxlPSJldmVub2RkIi8+PC9zdmc+"}

}
Button{
id:button_auto_3
background:Rectangle{
id:button_auto_3_bg
anchors.fill:parent
radius:button_auto_3.height / 2
border.width:1
border.color:button_auto_3.pressed ? '#0A5E7D' : '#007EA8'
color:button_auto_3.pressed ? '#0A5E7D' : button_auto_3.hovered ? '#007EA8' : 'white'
}

contentItem:Item{
implicitHeight:button_auto_3_row.implicitHeight
implicitWidth:button_auto_3_row.implicitWidth
Row{
id:button_auto_3_row
spacing:5
leftPadding:5
rightPadding:5
Row{
spacing:5
Text{
text:"View in Concur"
font.pixelSize:14
color:button_auto_3.hovered ? '#FFFFFF' : '#007EA8'
}
}
}
}

onClicked:{
adaptiveCard.buttonClicked("View in Concur", "Action.OpenUrl", "https://www.concur.co.in/");
console.log("https://www.concur.co.in/");
}

}
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:button_auto_2_loader.visible
}
Loader{
id:button_auto_2_loader
x:-margins
sourceComponent:button_auto_2_component
visible:false
width:adaptiveCard.width
}
}
}
}
Component{
id:button_auto_2_component
ColumnLayout{
id:button_auto_2_component_component_layout
property string showCard:"import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
Rectangle{
id:adaptiveCard
readonly property int margins:12
implicitHeight:adaptiveCardLayout.implicitHeight
Layout.fillWidth:true
readonly property string bgColor:'#FFFFFF'
color:'#F2F4F5'
signal buttonClicked(var title, var type, var data)
function generateStretchHeight(childrens,minHeight){
var n = childrens.length
var implicitHt = 0;
var stretchCount = 0;
var stretchMinHeight = 0;
for(var i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator !== 'undefined')
{
implicitHt += childrens[i].height;
stretchMinHeight += childrens[i].height;
}
else
{
implicitHt += childrens[i].implicitHeight;
if(typeof childrens[i].stretch !== 'undefined')
{
stretchCount++;
}
else
{
stretchMinHeight += childrens[i].implicitHeight;
}
}
}
stretchMinHeight = (minHeight - stretchMinHeight)/stretchCount
for(i=0;(i<childrens.length);i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined' && typeof childrens[i].minHeight !== 'undefined')
{
childrens[i].minHeight = Math.max(childrens[i].minHeight,stretchMinHeight)
}
}
}
if(stretchCount > 0 && implicitHt < minHeight)
{
var stretctHeight = (minHeight - implicitHt)/stretchCount
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined')
{
childrens[i].height = childrens[i].implicitHeight + stretctHeight
}
}
}
}
else
{
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(typeof childrens[i].stretch !== 'undefined')
{
childrens[i].height = childrens[i].implicitHeight
}
}
}
}
}
function generateStretchWidth(childrens,width){
var implicitWid = 0
var autoWid = 0
var autoCount = 0
var weightSum = 0
var stretchCount = 0
var weightPresent = 0
for(var i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator !== 'undefined')
{
implicitWid += childrens[i].width
}
else
{
if(childrens[i].widthProperty.endsWith(\"px\"))
{
childrens[i].width = parseInt(childrens[i].widthProperty.slice(0,-2))
implicitWid += childrens[i].width
}
else
{
if(childrens[i].widthProperty === \"auto\")
{
autoCount++
}
else if(childrens[i].widthProperty === \"stretch\")
{
stretchCount++
implicitWid += 50;
}
else
{
weightPresent = 1
weightSum += parseInt(childrens[i].widthProperty)
}
}
}
}
autoWid = (width - implicitWid)/(weightPresent + autoCount)
var flags = new Array(childrens.length).fill(0)
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === \"auto\")
{
if(childrens[i].minWidth < autoWid)
{
childrens[i].width = childrens[i].minWidth
implicitWid += childrens[i].width
flags[i] = 1;
autoCount--;
autoWid = (width - implicitWid)/(weightPresent + autoCount)
}
}
}
}
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === \"auto\")
{
if(flags[i] === 0)
{
childrens[i].width = autoWid
implicitWid += childrens[i].width
}
}
else if(childrens[i].widthProperty !== \"stretch\" && !childrens[i].widthProperty.endsWith(\"px\"))
{
if(weightSum !== 0)
{
childrens[i].width = ((parseInt(childrens[i].widthProperty)/weightSum) * autoWid)
implicitWid += childrens[i].width
}
}
}
}
var stretchWidth = (width - implicitWid)/stretchCount
for(i=0;i<childrens.length;i++)
{
if(typeof childrens[i].seperator === 'undefined')
{
if(childrens[i].widthProperty === 'stretch')
{
childrens[i].width = 50+stretchWidth
}
}
}
}
function getMinWidth(childrens){
var min = 0
for(var j =0;j<childrens.length;j++)
{
if(typeof childrens[j].minWidth === 'undefined')
{
min = Math.max(min,Math.ceil(childrens[j].implicitWidth))
}
else
{
min = Math.max(min,Math.ceil(childrens[j].minWidth))
}
}
return min
}
function getMinWidthActionSet(childrens,spacing){
var min = 0
for(var j =0;j<childrens.length;j++)
{
min += Math.ceil(childrens[j].implicitWidth)
}
min += ((childrens.length - 1)*spacing)
return min
}
function getMinWidthFactSet(childrens, spacing){
var min = 0
for(var j=0;j<childrens.length;j+=2)
{
min = Math.max(min,childrens[j].implicitWidth + childrens[j+1].implicitWidth + spacing)
}
return min;
}
ColumnLayout{
id:adaptiveCardLayout
width:parent.width
Rectangle{
id:adaptiveCardRectangle
color:'transparent'
Layout.topMargin:margins
Layout.bottomMargin:margins
Layout.leftMargin:margins
Layout.rightMargin:margins
Layout.fillWidth:true
Layout.preferredHeight:bodyLayout.height
Layout.minimumHeight:1
Column{
id:bodyLayout
width:parent.width
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children,-24)}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children,-24)}
Frame{
id:container_auto_1
padding:0
property int minHeight:0
implicitHeight:Math.max(0, clayout_container_auto_1.implicitHeight)
readonly property string bgColor:'transparent'
background:Rectangle{
id:container_auto_1_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onMinHeightChanged:{adaptiveCard.generateStretchHeight( column_container_auto_1.children,minHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_container_auto_1.children) + 0}
width:parent.width
ColumnLayout{
id:clayout_container_auto_1
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_container_auto_1
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, container_auto_1.minHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, container_auto_1.minHeight - 0 )}
Frame{
property int minHeight:0
readonly property string bgColor:'transparent'
id:columnSet_auto_1
implicitHeight:getColumnSetHeight()
padding:0
background:Rectangle{
id:columnSet_auto_1_bgRect
border.width:0
color:parent.bgColor
}

property int stretchMinHeight:0
onMinHeightChanged:{ stretchMinHeight = Math.max(minHeight - 0, stretchMinHeight)}
width:parent.width
onWidthChanged:{adaptiveCard.generateStretchWidth( row_columnSet_auto_1.children, parent.width - (0))}
function getColumnSetHeight(){ var calculatedHeight = getColumnHeight(true);if(calculatedHeight >= minHeight - (0)){return calculatedHeight + (0)}else{return minHeight;}}
function getColumnHeight(bleed){var calculatedHeight =  Math.max(clayout_column_auto_1.implicitHeight - 0,column_auto_1.minHeight, clayout_column_auto_2.implicitHeight - 0,column_auto_2.minHeight); if(calculatedHeight < minHeight - (0)){return minHeight - (0)}else{if(calculatedHeight === 0 && !bleed){return calculatedHeight + 0 }else{return calculatedHeight}}}
RowLayout{
id:rlayout_columnSet_auto_1
width:parent.width
Row{
Layout.alignment:Qt.AlignLeft
id:row_columnSet_auto_1
Frame{
id:column_auto_1
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_1.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_1_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_1.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_1.children) + 0}
implicitWidth:minWidth
property string widthProperty:'auto'
property int stretchMinHeight:Math.max(columnSet_auto_1.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_1
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_column_auto_1
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_1.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_1.stretchMinHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:\"Reason:\"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
font.family:\"Segoe UI\"
}
}
}
}
Rectangle{
readonly property bool seperator:true
width:12
height:columnSet_auto_1.getColumnHeight(false)
color:\"transparent\"
visible:true
}
Frame{
id:column_auto_2
padding:0
property int minHeight:0
implicitHeight:columnSet_auto_1.getColumnHeight( 0 ) + 0
readonly property string bgColor:'transparent'
background:Rectangle{
id:column_auto_2_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onStretchMinHeightChanged:{adaptiveCard.generateStretchHeight( column_column_auto_2.children,stretchMinHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_column_auto_2.children) + 0}
implicitWidth:minWidth
property string widthProperty:'stretch'
property int stretchMinHeight:Math.max(columnSet_auto_1.stretchMinHeight, implicitHeight - 1)
ColumnLayout{
id:clayout_column_auto_2
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_column_auto_2
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, column_auto_2.stretchMinHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, column_auto_2.stretchMinHeight - 0 )}
ScrollView{
width:parent.width
height:comment.visible ? 100 : 0
ScrollBar.vertical.interactive:true
TextArea{
id:comment
wrapMode:Text.Wrap
selectByMouse:true
selectedTextColor:'white'
padding:10
color:'#171B1F'
font.pixelSize:14
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:comment.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:comment.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

placeholderText:\"Optional comment\"
}
}
}
}
}
}
}
}
}
}
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:\"transparent\"
visible:true
}
Flow{
width:parent.width
spacing:8
layoutDirection:Qt.LeftToRight
Button{
id:button_auto_1
background:Rectangle{
id:button_auto_1_bg
anchors.fill:parent
radius:button_auto_1.height / 2
border.width:1
border.color:button_auto_1.pressed ? '#0A5E7D' : '#007EA8'
color:button_auto_1.pressed ? '#0A5E7D' : button_auto_1.hovered ? '#007EA8' : 'white'
}

contentItem:Item{
implicitHeight:button_auto_1_row.implicitHeight
implicitWidth:button_auto_1_row.implicitWidth
Row{
id:button_auto_1_row
spacing:5
leftPadding:5
rightPadding:5
Row{
spacing:5
Text{
text:\"Submit Send Back\"
font.pixelSize:14
color:button_auto_1.hovered ? '#FFFFFF' : '#007EA8'
}
}
}
}

onClicked:{
var paramJson = {};
var parmStr = \"{\\\"buttonId\\\":\\\"sendBackBtn\\\"}\";
paramJson = JSON.parse(parmStr);
paramJson[\"comment\"] = comment.text;
var paramslist = JSON.stringify(paramJson);
adaptiveCard.buttonClicked(\"Submit Send Back\", \"Action.Submit\", paramslist);
console.log(paramslist);
}

}
}
}
}
}
}
"
Component.onCompleted:reload(showCard)
property var card
function reload(mCard)
{

if (card)
{ 
card.destroy()
 }

card = Qt.createQmlObject(mCard, button_auto_2_component_component_layout, 'card')

if (card)
{ 
card.buttonClicked.connect(adaptiveCard.buttonClicked)
 }
}
}
}
}
