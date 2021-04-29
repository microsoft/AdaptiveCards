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
TextField{
id:t1
selectByMouse:true
selectedTextColor:'white'
property string selectedTime:"20:15"
width:parent.width
placeholderText:"Select time"
color:'#171B1F'
validator:RegExpValidator { regExp: /^(--|[01][0-9|-]|2[0-3|-]):(--|[0-5][0-9|-])$/}
text:"20:15"
onFocusChanged:{ if (focus===true) inputMask="xx:xx;-"; if(focus===false){ z=0;if(text===":") { inputMask="" }if(t1_timeBox.visible===true)t1_timeBox.visible=false ;}}
onTextChanged:{t1_hours.currentIndex=parseInt(getText(0,2));t1_min.currentIndex=parseInt(getText(3,5));if(getText(0,2) === '--' || getText(3,5) === '--'){t1.selectedTime ='';} else{t1.selectedTime =t1.text;}}
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:t1.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:t1.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{t1.forceActiveFocus();
t1_timeBox.visible=!t1_timeBox.visible;
parent.z=t1_timeBox.visible?1:0;
t1_hours.currentIndex=parseInt(parent.getText(0,2));
t1_min.currentIndex=parseInt(parent.getText(3,5));
}
Image{
id:t1_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4NCjxzdmcgd2lkdGg9IjMwcHgiIGhlaWdodD0iMzBweCIgdmlld0JveD0iMCAwIDMwIDMwIiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiPg0KICAgIDwhLS0gR2VuZXJhdG9yOiBTa2V0Y2ggNjAuMSAoODgxMzMpIC0gaHR0cHM6Ly9za2V0Y2guY29tIC0tPg0KICAgIDx0aXRsZT5waG9uZS9yZWNlbnRzLXByZXNlbmNlLXN0cm9rZV8zMDwvdGl0bGU+DQogICAgPGRlc2M+Q3JlYXRlZCB3aXRoIFNrZXRjaC48L2Rlc2M+DQogICAgPGcgaWQ9InBob25lL3JlY2VudHMtcHJlc2VuY2Utc3Ryb2tlXzMwIiBzdHJva2U9Im5vbmUiIHN0cm9rZS13aWR0aD0iMSIgZmlsbD0ibm9uZSIgZmlsbC1ydWxlPSJldmVub2RkIj4NCiAgICAgICAgPHBhdGggZD0iTTE1LjAwMDIsMC4wMDAxIEM2LjcyNzkxNTI1LDAuMDAwMSAwLjAwMDIsNi43Mjc4MTUyNSAwLjAwMDIsMTUuMDAwMSBDMC4wMDAyLDIzLjI3MjM4NDcgNi43Mjc5MTUyNSwzMC4wMDAxIDE1LjAwMDIsMzAuMDAwMSBDMjMuMjcyNDg0NywzMC4wMDAxIDMwLjAwMDIsMjMuMjcyMzg0NyAzMC4wMDAyLDE1LjAwMDEgQzMwLjAwMDIsNi43Mjc4MTUyNSAyMy4yNzI0ODQ3LDAuMDAwMSAxNS4wMDAyLDAuMDAwMSBaIE0xNS4wMDAyLDEuMDAwMSBDMjIuNzIwMiwxLjAwMDEgMjkuMDAwMiw3LjI4MDEgMjkuMDAwMiwxNS4wMDAxIEMyOS4wMDAyLDIyLjcyMDEgMjIuNzIwMiwyOS4wMDAxIDE1LjAwMDIsMjkuMDAwMSBDNy4yODAyLDI5LjAwMDEgMS4wMDAyLDIyLjcyMDEgMS4wMDAyLDE1LjAwMDEgQzEuMDAwMiw3LjI4MDEgNy4yODAyLDEuMDAwMSAxNS4wMDAyLDEuMDAwMSBaIE0xOS4zMjQyLDIwLjkxMjEgQzE5LjIyNjIsMjEuMDEwMSAxOS4wOTgyLDIxLjA1ODEgMTguOTcwMiwyMS4wNTgxIEMxOC44NDMyLDIxLjA1ODEgMTguNzE1MiwyMS4wMTAxIDE4LjYxNzIsMjAuOTEyMSBMMTQuODc5MiwxNy4xNzQxIEMxNC42MzgyLDE2LjkzMzEgMTQuNTAwMiwxNi42MDAxIDE0LjUwMDIsMTYuMjYwMSBMMTQuNTAwMiw3Ljg1MzEgQzE0LjUwMDIsNy41NzYxIDE0LjcyMzIsNy4zNTMxIDE1LjAwMDIsNy4zNTMxIEMxNS4yNzYyLDcuMzUzMSAxNS41MDAyLDcuNTc2MSAxNS41MDAyLDcuODUzMSBMMTUuNTAwMiwxNi4yNjAxIEMxNS41MDAyLDE2LjMzNzEgMTUuNTMxMiwxNi40MTIxIDE1LjU4NjIsMTYuNDY3MSBMMTkuMzI0MiwyMC4yMDUxIEMxOS41MTkyLDIwLjQwMDEgMTkuNTE5MiwyMC43MTcxIDE5LjMyNDIsMjAuOTEyMSIgaWQ9ImZpbGwiIGZpbGw9IiMxNzFCMUYiPjwvcGF0aD4NCiAgICA8L2c+DQo8L3N2Zz4="
}
ColorOverlay{
anchors.fill:t1_icon
source:t1_icon
color:'#171B1F'
}
}
Rectangle{
id:t1_timeBox
anchors.topMargin:1
anchors.left:parent.left
anchors.top:parent.bottom
width:105
height:200
visible:false
layer.enabled:true
layer.effect:Glow{
samples:25
color:'skyblue'
}

ListView{
id:t1_hours
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:parent.left
model:24
delegate:Rectangle{
width:45
height:45
color:t1_hours.currentIndex==index ? "blue" : t1_hoursmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t1_hoursmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t1_hours.currentIndex=index;var x=String(index).padStart(2, '0') ;t1.insert(0,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t1_hours.currentIndex==index ? "white" : "black"
}
}

}
ListView{
id:t1_min
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:t1_hours.right
model:60
delegate:Rectangle{
width:45
height:45
color:t1_min.currentIndex==index ? "blue" : t1_minmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t1_minmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t1_min.currentIndex=index;var x=String(index).padStart(2, '0') ;t1.insert(2,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t1_min.currentIndex==index ? "white" : "black"
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
visible:false
}
TextField{
id:t2
selectByMouse:true
selectedTextColor:'white'
property string selectedTime:"10:15"
width:parent.width
placeholderText:"Select time"
color:'#171B1F'
validator:RegExpValidator { regExp: /^(--|[01][0-9|-]|2[0-3|-]):(--|[0-5][0-9|-])$/}
text:"10:15"
visible:false
onFocusChanged:{ if (focus===true) inputMask="xx:xx;-"; if(focus===false){ z=0;if(text===":") { inputMask="" }if(t2_timeBox.visible===true)t2_timeBox.visible=false ;}}
onTextChanged:{t2_hours.currentIndex=parseInt(getText(0,2));t2_min.currentIndex=parseInt(getText(3,5));if(getText(0,2) === '--' || getText(3,5) === '--'){t2.selectedTime ='';} else{t2.selectedTime =t2.text;}}
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:t2.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:t2.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{t2.forceActiveFocus();
t2_timeBox.visible=!t2_timeBox.visible;
parent.z=t2_timeBox.visible?1:0;
t2_hours.currentIndex=parseInt(parent.getText(0,2));
t2_min.currentIndex=parseInt(parent.getText(3,5));
}
Image{
id:t2_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4NCjxzdmcgd2lkdGg9IjMwcHgiIGhlaWdodD0iMzBweCIgdmlld0JveD0iMCAwIDMwIDMwIiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiPg0KICAgIDwhLS0gR2VuZXJhdG9yOiBTa2V0Y2ggNjAuMSAoODgxMzMpIC0gaHR0cHM6Ly9za2V0Y2guY29tIC0tPg0KICAgIDx0aXRsZT5waG9uZS9yZWNlbnRzLXByZXNlbmNlLXN0cm9rZV8zMDwvdGl0bGU+DQogICAgPGRlc2M+Q3JlYXRlZCB3aXRoIFNrZXRjaC48L2Rlc2M+DQogICAgPGcgaWQ9InBob25lL3JlY2VudHMtcHJlc2VuY2Utc3Ryb2tlXzMwIiBzdHJva2U9Im5vbmUiIHN0cm9rZS13aWR0aD0iMSIgZmlsbD0ibm9uZSIgZmlsbC1ydWxlPSJldmVub2RkIj4NCiAgICAgICAgPHBhdGggZD0iTTE1LjAwMDIsMC4wMDAxIEM2LjcyNzkxNTI1LDAuMDAwMSAwLjAwMDIsNi43Mjc4MTUyNSAwLjAwMDIsMTUuMDAwMSBDMC4wMDAyLDIzLjI3MjM4NDcgNi43Mjc5MTUyNSwzMC4wMDAxIDE1LjAwMDIsMzAuMDAwMSBDMjMuMjcyNDg0NywzMC4wMDAxIDMwLjAwMDIsMjMuMjcyMzg0NyAzMC4wMDAyLDE1LjAwMDEgQzMwLjAwMDIsNi43Mjc4MTUyNSAyMy4yNzI0ODQ3LDAuMDAwMSAxNS4wMDAyLDAuMDAwMSBaIE0xNS4wMDAyLDEuMDAwMSBDMjIuNzIwMiwxLjAwMDEgMjkuMDAwMiw3LjI4MDEgMjkuMDAwMiwxNS4wMDAxIEMyOS4wMDAyLDIyLjcyMDEgMjIuNzIwMiwyOS4wMDAxIDE1LjAwMDIsMjkuMDAwMSBDNy4yODAyLDI5LjAwMDEgMS4wMDAyLDIyLjcyMDEgMS4wMDAyLDE1LjAwMDEgQzEuMDAwMiw3LjI4MDEgNy4yODAyLDEuMDAwMSAxNS4wMDAyLDEuMDAwMSBaIE0xOS4zMjQyLDIwLjkxMjEgQzE5LjIyNjIsMjEuMDEwMSAxOS4wOTgyLDIxLjA1ODEgMTguOTcwMiwyMS4wNTgxIEMxOC44NDMyLDIxLjA1ODEgMTguNzE1MiwyMS4wMTAxIDE4LjYxNzIsMjAuOTEyMSBMMTQuODc5MiwxNy4xNzQxIEMxNC42MzgyLDE2LjkzMzEgMTQuNTAwMiwxNi42MDAxIDE0LjUwMDIsMTYuMjYwMSBMMTQuNTAwMiw3Ljg1MzEgQzE0LjUwMDIsNy41NzYxIDE0LjcyMzIsNy4zNTMxIDE1LjAwMDIsNy4zNTMxIEMxNS4yNzYyLDcuMzUzMSAxNS41MDAyLDcuNTc2MSAxNS41MDAyLDcuODUzMSBMMTUuNTAwMiwxNi4yNjAxIEMxNS41MDAyLDE2LjMzNzEgMTUuNTMxMiwxNi40MTIxIDE1LjU4NjIsMTYuNDY3MSBMMTkuMzI0MiwyMC4yMDUxIEMxOS41MTkyLDIwLjQwMDEgMTkuNTE5MiwyMC43MTcxIDE5LjMyNDIsMjAuOTEyMSIgaWQ9ImZpbGwiIGZpbGw9IiMxNzFCMUYiPjwvcGF0aD4NCiAgICA8L2c+DQo8L3N2Zz4="
}
ColorOverlay{
anchors.fill:t2_icon
source:t2_icon
color:'#171B1F'
}
}
Rectangle{
id:t2_timeBox
anchors.topMargin:1
anchors.left:parent.left
anchors.top:parent.bottom
width:105
height:200
visible:false
layer.enabled:true
layer.effect:Glow{
samples:25
color:'skyblue'
}

ListView{
id:t2_hours
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:parent.left
model:24
delegate:Rectangle{
width:45
height:45
color:t2_hours.currentIndex==index ? "blue" : t2_hoursmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t2_hoursmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t2_hours.currentIndex=index;var x=String(index).padStart(2, '0') ;t2.insert(0,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t2_hours.currentIndex==index ? "white" : "black"
}
}

}
ListView{
id:t2_min
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:t2_hours.right
model:60
delegate:Rectangle{
width:45
height:45
color:t2_min.currentIndex==index ? "blue" : t2_minmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t2_minmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t2_min.currentIndex=index;var x=String(index).padStart(2, '0') ;t2.insert(2,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t2_min.currentIndex==index ? "white" : "black"
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
Rectangle{
width:parent.width
height:1
anchors.centerIn:parent
color:"#EEEEEE"
}
}
TextField{
id:t3
selectByMouse:true
selectedTextColor:'white'
property string selectedTime:""
width:parent.width
placeholderText:"Select time"
color:'#171B1F'
validator:RegExpValidator { regExp: /^(--|[01][0-9|-]|2[0-3|-]):(--|[0-5][0-9|-])$/}
onFocusChanged:{ if (focus===true) inputMask="xx:xx;-"; if(focus===false){ z=0;if(text===":") { inputMask="" }if(t3_timeBox.visible===true)t3_timeBox.visible=false ;}}
onTextChanged:{t3_hours.currentIndex=parseInt(getText(0,2));t3_min.currentIndex=parseInt(getText(3,5));if(getText(0,2) === '--' || getText(3,5) === '--'){t3.selectedTime ='';} else{t3.selectedTime =t3.text;}}
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:t3.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:t3.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{t3.forceActiveFocus();
t3_timeBox.visible=!t3_timeBox.visible;
parent.z=t3_timeBox.visible?1:0;
t3_hours.currentIndex=parseInt(parent.getText(0,2));
t3_min.currentIndex=parseInt(parent.getText(3,5));
}
Image{
id:t3_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4NCjxzdmcgd2lkdGg9IjMwcHgiIGhlaWdodD0iMzBweCIgdmlld0JveD0iMCAwIDMwIDMwIiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiPg0KICAgIDwhLS0gR2VuZXJhdG9yOiBTa2V0Y2ggNjAuMSAoODgxMzMpIC0gaHR0cHM6Ly9za2V0Y2guY29tIC0tPg0KICAgIDx0aXRsZT5waG9uZS9yZWNlbnRzLXByZXNlbmNlLXN0cm9rZV8zMDwvdGl0bGU+DQogICAgPGRlc2M+Q3JlYXRlZCB3aXRoIFNrZXRjaC48L2Rlc2M+DQogICAgPGcgaWQ9InBob25lL3JlY2VudHMtcHJlc2VuY2Utc3Ryb2tlXzMwIiBzdHJva2U9Im5vbmUiIHN0cm9rZS13aWR0aD0iMSIgZmlsbD0ibm9uZSIgZmlsbC1ydWxlPSJldmVub2RkIj4NCiAgICAgICAgPHBhdGggZD0iTTE1LjAwMDIsMC4wMDAxIEM2LjcyNzkxNTI1LDAuMDAwMSAwLjAwMDIsNi43Mjc4MTUyNSAwLjAwMDIsMTUuMDAwMSBDMC4wMDAyLDIzLjI3MjM4NDcgNi43Mjc5MTUyNSwzMC4wMDAxIDE1LjAwMDIsMzAuMDAwMSBDMjMuMjcyNDg0NywzMC4wMDAxIDMwLjAwMDIsMjMuMjcyMzg0NyAzMC4wMDAyLDE1LjAwMDEgQzMwLjAwMDIsNi43Mjc4MTUyNSAyMy4yNzI0ODQ3LDAuMDAwMSAxNS4wMDAyLDAuMDAwMSBaIE0xNS4wMDAyLDEuMDAwMSBDMjIuNzIwMiwxLjAwMDEgMjkuMDAwMiw3LjI4MDEgMjkuMDAwMiwxNS4wMDAxIEMyOS4wMDAyLDIyLjcyMDEgMjIuNzIwMiwyOS4wMDAxIDE1LjAwMDIsMjkuMDAwMSBDNy4yODAyLDI5LjAwMDEgMS4wMDAyLDIyLjcyMDEgMS4wMDAyLDE1LjAwMDEgQzEuMDAwMiw3LjI4MDEgNy4yODAyLDEuMDAwMSAxNS4wMDAyLDEuMDAwMSBaIE0xOS4zMjQyLDIwLjkxMjEgQzE5LjIyNjIsMjEuMDEwMSAxOS4wOTgyLDIxLjA1ODEgMTguOTcwMiwyMS4wNTgxIEMxOC44NDMyLDIxLjA1ODEgMTguNzE1MiwyMS4wMTAxIDE4LjYxNzIsMjAuOTEyMSBMMTQuODc5MiwxNy4xNzQxIEMxNC42MzgyLDE2LjkzMzEgMTQuNTAwMiwxNi42MDAxIDE0LjUwMDIsMTYuMjYwMSBMMTQuNTAwMiw3Ljg1MzEgQzE0LjUwMDIsNy41NzYxIDE0LjcyMzIsNy4zNTMxIDE1LjAwMDIsNy4zNTMxIEMxNS4yNzYyLDcuMzUzMSAxNS41MDAyLDcuNTc2MSAxNS41MDAyLDcuODUzMSBMMTUuNTAwMiwxNi4yNjAxIEMxNS41MDAyLDE2LjMzNzEgMTUuNTMxMiwxNi40MTIxIDE1LjU4NjIsMTYuNDY3MSBMMTkuMzI0MiwyMC4yMDUxIEMxOS41MTkyLDIwLjQwMDEgMTkuNTE5MiwyMC43MTcxIDE5LjMyNDIsMjAuOTEyMSIgaWQ9ImZpbGwiIGZpbGw9IiMxNzFCMUYiPjwvcGF0aD4NCiAgICA8L2c+DQo8L3N2Zz4="
}
ColorOverlay{
anchors.fill:t3_icon
source:t3_icon
color:'#171B1F'
}
}
Rectangle{
id:t3_timeBox
anchors.topMargin:1
anchors.left:parent.left
anchors.top:parent.bottom
width:105
height:200
visible:false
layer.enabled:true
layer.effect:Glow{
samples:25
color:'skyblue'
}

ListView{
id:t3_hours
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:parent.left
model:24
delegate:Rectangle{
width:45
height:45
color:t3_hours.currentIndex==index ? "blue" : t3_hoursmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t3_hoursmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t3_hours.currentIndex=index;var x=String(index).padStart(2, '0') ;t3.insert(0,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t3_hours.currentIndex==index ? "white" : "black"
}
}

}
ListView{
id:t3_min
width:45
height:parent.height-10
anchors.margins:5
anchors.top:parent.top
flickableDirection:Flickable.VerticalFlick
boundsBehavior:Flickable.StopAtBounds
clip:true
anchors.left:t3_hours.right
model:60
delegate:Rectangle{
width:45
height:45
color:t3_min.currentIndex==index ? "blue" : t3_minmouseArea.containsMouse?"lightblue":"white"
MouseArea{
id:t3_minmouseArea
anchors.fill:parent
enabled:true
hoverEnabled:true
onClicked:{t3_min.currentIndex=index;var x=String(index).padStart(2, '0') ;t3.insert(2,x);}
}
Text{
text:String(index).padStart(2, '0')
anchors.fill:parent
horizontalAlignment:Text.AlignHCenter
verticalAlignment:Text.AlignVCenter
color:t3_min.currentIndex==index ? "white" : "black"
}
}

}
}
}
}
}
}
}
