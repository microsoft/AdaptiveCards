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
SpinBox{
id:i1
width:parent.width
padding:0
stepSize:1
editable:true
validator:DoubleValidator{
}

valueFromText:function(text, locale){
return Number(text)
}
readonly property bool hasDefaultValue:true
readonly property int defaultValue:0
from:0
to:5
value:0
contentItem:TextField{
id:i1_contentItem
font.pixelSize:14
anchors.left:parent.left
selectByMouse:true
selectedTextColor:'white'
readOnly:!i1.editable
validator:i1.validator
inputMethodHints:Qt.ImhFormattedNumbersOnly
text:i1.value
placeholderText:"Placeholder text"
background:Rectangle{
color:'transparent'
}

onEditingFinished:{ if(text < i1.from || text > i1.to){
remove(0,length)
if(i1.hasDefaultValue)
insert(0, i1.defaultValue)
else
insert(0, i1.from)
}
}
color:'#171B1F'
}

background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:i1_contentItem.activeFocus? 'black' : 'grey'
layer.enabled:i1_contentItem.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

up.indicator:Rectangle{
width:20
height:parent.height/2
x:i1.mirrored ? 0 : parent.width - width
radius:5
color:i1.up.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#708;</div>"
textFormat:Text.RichText
font.pixelSize:i1.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
}
}

down.indicator:Rectangle{
width:20
height:parent.height/2
x:i1.mirrored ? 0 : parent.width - width
y:parent.height/2
radius:5
color:i1.down.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#709;</div>"
textFormat:Text.RichText
font.pixelSize:i1.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
}
}

}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:12
color:"transparent"
visible:false
}
SpinBox{
id:i2
width:parent.width
padding:0
stepSize:1
editable:true
validator:DoubleValidator{
}

valueFromText:function(text, locale){
return Number(text)
}
readonly property bool hasDefaultValue:true
readonly property int defaultValue:2
from:1
to:4
value:2
visible:false
contentItem:TextField{
id:i2_contentItem
font.pixelSize:14
anchors.left:parent.left
selectByMouse:true
selectedTextColor:'white'
readOnly:!i2.editable
validator:i2.validator
inputMethodHints:Qt.ImhFormattedNumbersOnly
text:i2.value
placeholderText:"placeholder2"
background:Rectangle{
color:'transparent'
}

onEditingFinished:{ if(text < i2.from || text > i2.to){
remove(0,length)
if(i2.hasDefaultValue)
insert(0, i2.defaultValue)
else
insert(0, i2.from)
}
}
color:'#171B1F'
}

background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:i2_contentItem.activeFocus? 'black' : 'grey'
layer.enabled:i2_contentItem.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

up.indicator:Rectangle{
width:20
height:parent.height/2
x:i2.mirrored ? 0 : parent.width - width
radius:5
color:i2.up.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#708;</div>"
textFormat:Text.RichText
font.pixelSize:i2.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
}
}

down.indicator:Rectangle{
width:20
height:parent.height/2
x:i2.mirrored ? 0 : parent.width - width
y:parent.height/2
radius:5
color:i2.down.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#709;</div>"
textFormat:Text.RichText
font.pixelSize:i2.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
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
SpinBox{
id:i3
width:parent.width
padding:0
stepSize:1
editable:true
validator:DoubleValidator{
}

valueFromText:function(text, locale){
return Number(text)
}
readonly property bool hasDefaultValue:true
readonly property int defaultValue:1
from:-10
to:10
value:1
contentItem:TextField{
id:i3_contentItem
font.pixelSize:14
anchors.left:parent.left
selectByMouse:true
selectedTextColor:'white'
readOnly:!i3.editable
validator:i3.validator
inputMethodHints:Qt.ImhFormattedNumbersOnly
text:i3.value
placeholderText:"placeholder3"
background:Rectangle{
color:'transparent'
}

onEditingFinished:{ if(text < i3.from || text > i3.to){
remove(0,length)
if(i3.hasDefaultValue)
insert(0, i3.defaultValue)
else
insert(0, i3.from)
}
}
color:'#171B1F'
}

background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:i3_contentItem.activeFocus? 'black' : 'grey'
layer.enabled:i3_contentItem.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

up.indicator:Rectangle{
width:20
height:parent.height/2
x:i3.mirrored ? 0 : parent.width - width
radius:5
color:i3.up.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#708;</div>"
textFormat:Text.RichText
font.pixelSize:i3.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
}
}

down.indicator:Rectangle{
width:20
height:parent.height/2
x:i3.mirrored ? 0 : parent.width - width
y:parent.height/2
radius:5
color:i3.down.pressed ? '#08000000' : 'transparent'
Text{
text:"<div>&#709;</div>"
textFormat:Text.RichText
font.pixelSize:i3.font.pixelSize
anchors.fill:parent
fontSizeMode:Text.Fit
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:'#171B1F'
}
}

}
}
}
}
}
