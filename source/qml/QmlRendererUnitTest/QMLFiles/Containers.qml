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
text:"New TextBlock"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
id:t1
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
id:container_auto_2
padding:0
property int minHeight:0
implicitHeight:Math.max(0, clayout_container_auto_2.implicitHeight)
readonly property string bgColor:'transparent'
background:Rectangle{
id:container_auto_2_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onMinHeightChanged:{adaptiveCard.generateStretchHeight( column_container_auto_2.children,minHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_container_auto_2.children) + 0}
width:parent.width
ColumnLayout{
id:clayout_container_auto_2
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_container_auto_2
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, container_auto_2.minHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, container_auto_2.minHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"New TextBlock"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
id:t2
font.family:"Segoe UI"
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
TextField{
id:i1
width:parent.width
selectByMouse:true
selectedTextColor:'white'
color:'#171B1F'
font.pixelSize:14
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:i1.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:i1.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

placeholderText:"Placeholder text"
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
Frame{
id:container_auto_3
padding:0
property int minHeight:0
implicitHeight:Math.max(0, clayout_container_auto_3.implicitHeight)
readonly property string bgColor:'transparent'
background:Rectangle{
id:container_auto_3_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onMinHeightChanged:{adaptiveCard.generateStretchHeight( column_container_auto_3.children,minHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_container_auto_3.children) + 0}
width:parent.width
ColumnLayout{
id:clayout_container_auto_3
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_container_auto_3
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, container_auto_3.minHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, container_auto_3.minHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"New TextBlock"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
id:t3
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
id:container_auto_4
padding:0
property int minHeight:0
implicitHeight:Math.max(0, clayout_container_auto_4.implicitHeight)
readonly property string bgColor:'transparent'
background:Rectangle{
id:container_auto_4_bgRect
clip:true
border.width:0
color:parent.bgColor
}

onMinHeightChanged:{adaptiveCard.generateStretchHeight( column_container_auto_4.children,minHeight - 0 )}
property int minWidth:{adaptiveCard.getMinWidth( column_container_auto_4.children) + 0}
width:parent.width
ColumnLayout{
id:clayout_container_auto_4
anchors.fill:parent
Column{
Layout.fillWidth:true
Layout.minimumHeight:1
Layout.alignment:Qt.AlignTop
id:column_container_auto_4
onImplicitHeightChanged:{adaptiveCard.generateStretchHeight(children, container_auto_4.minHeight - 0 )}
onImplicitWidthChanged:{adaptiveCard.generateStretchHeight(children, container_auto_4.minHeight - 0 )}
Text{
width:parent.width
elide:Text.ElideRight
clip:true
textFormat:Text.MarkdownText
text:"New TextBlock"
horizontalAlignment:Qt.AlignLeft
color:'#171B1F'
font.pixelSize:14
font.weight:Font.Normal
id:t4
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
