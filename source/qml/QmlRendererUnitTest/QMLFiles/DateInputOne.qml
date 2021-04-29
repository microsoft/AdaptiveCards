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
id:d1
width:parent.width
font.family:"Segoe UI"
font.pixelSize:14
selectByMouse:true
selectedTextColor:'white'
color:'#171B1F'
property string selectedDate:""
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:d1.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:d1.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

onTextChanged:{d1TextChanged(text);setValidDate(text);}
placeholderText:"Select date in dd\/mmm\/yyyy"
validator:RegExpValidator { regExp: /^([-0123]-|0\d|[12]\d|3[01])\/(---|[JFMASOND]--|Ja-|Jan|Fe-|Feb|Ma-|Mar|Ap-|Apr|May|Ju--|Jun|Jul|Au-|Aug|Se-|Sep|Oc-|Oct|No-|Nov|De-|Dec)\/(-{4}|\d-{3}|\d{2}-{2}|\d{3}-|\d{4})$/}
onFocusChanged:{if(focus===true) inputMask="xx\/>x<xx\/xxxx;-";if(focus === false){ z=0;if(text === "\/\/"){ inputMask = "" ; } if( d1_cal_box.visible === true){ d1_cal_box.visible=false}}} 
signal d1TextChanged(var dateText)
function setValidDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var d=new Date(getText(7,11),Months[getText(3,6)],getText(0,2));if( d.getFullYear().toString() === getText(7,11)&& d.getMonth()===Months[getText(3,6)] && d.getDate().toString()===getText(0,2)){selectedDate = d.toLocaleString(Qt.locale("en_US"),"yyyy-MM-dd");}else { selectedDate = '' };}
MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{ parent.forceActiveFocus(); d1_cal_box.visible=!d1_cal_box.visible; parent.z=d1_cal_box.visible?1:0; }
Image{
id:d1_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMzIiIGhlaWdodD0iMzIiIHZpZXdCb3g9IjAgMCAzMiAzMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bWVldGluZ3MvY2FsZW5kYXItZW1wdHlfMzI8L3RpdGxlPjxwYXRoIGQ9Ik0zMCAyM2wwIDEgMCA0LjAwOEMzMCAyOS4xMDUgMjkuMTAzIDMwIDI4IDMwTDQgMzBjLTEuMTA1IDAtMi0uODkzLTItMS45OTJMMiAyNGwwLTFMMiA2Ljk5MkMyIDUuODk1IDIuODk3IDUgNCA1bDI0IDBjMS4xMDUgMCAyIC44OTMgMiAxLjk5MkwzMCAyM3pNMjggNGwtNSAwIDAtMi41MDVjMC0uMjc5LS4yMjQtLjQ5NS0uNS0uNDk1LS4yNjggMC0uNS4yMjItLjUuNDk1TDIyIDQgMTAgNGwwLTIuNTA1QzEwIDEuMjE2IDkuNzc2IDEgOS41IDFjLS4yNjggMC0uNS4yMjItLjUuNDk1TDkgNCA0IDRDMi4zNDcgNCAxIDUuMzQgMSA2Ljk5MmwwIDIxLjAxNkMxIDI5LjY2MSAyLjM0MyAzMSA0IDMxbDI0IDBjMS42NTMgMCAzLTEuMzQgMy0yLjk5MmwwLTIxLjAxNkMzMSA1LjMzOSAyOS42NTcgNCAyOCA0eiIgZmlsbC1ydWxlPSJldmVub2RkIi8+PC9zdmc+"
}
ColorOverlay{
anchors.fill:d1_icon
source:d1_icon
color:'#171B1F'
}
}
Rectangle{
id:d1_cal_box
visible:false
anchors.left:parent.left
anchors.top:parent.bottom
width:300
height:300
Component.onCompleted:{ Qt.createQmlObject('import QtQuick.Controls 1.4
import QtQuick 2.15
Calendar{
anchors.fill:parent
Component.onCompleted:{d1.d1TextChanged.connect(setCalendarDate);d1.d1TextChanged( d1.text)}
onReleased:{parent.visible=false; d1.text=selectedDate.toLocaleString(Qt.locale("en_US"),"dd\/MMM\/yyyy")}
function setCalendarDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var y=dateString.match(/\\d{4}/);dateString=dateString.replace(y,"");var m=dateString.match(/[a-zA-Z]{3}/);var d=dateString.match(/\\d{2}/);if (d!==null && m!==null && y!==null){selectedDate=new Date(y[0],Months[m[0]],d[0]) }}
}
',d1_cal_box,'calendar')}
}
}
Rectangle{
readonly property bool seperator:true
width:parent.width
height:4
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
id:d2
width:parent.width
font.family:"Segoe UI"
font.pixelSize:14
selectByMouse:true
selectedTextColor:'white'
color:'#171B1F'
property string selectedDate:""
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:d2.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:d2.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

onTextChanged:{d2TextChanged(text);setValidDate(text);}
placeholderText:"Select date in dd\/mmm\/yyyy"
validator:RegExpValidator { regExp: /^([-0123]-|0\d|[12]\d|3[01])\/(---|[JFMASOND]--|Ja-|Jan|Fe-|Feb|Ma-|Mar|Ap-|Apr|May|Ju--|Jun|Jul|Au-|Aug|Se-|Sep|Oc-|Oct|No-|Nov|De-|Dec)\/(-{4}|\d-{3}|\d{2}-{2}|\d{3}-|\d{4})$/}
onFocusChanged:{if(focus===true) inputMask="xx\/>x<xx\/xxxx;-";if(focus === false){ z=0;if(text === "\/\/"){ inputMask = "" ; } if( d2_cal_box.visible === true){ d2_cal_box.visible=false}}} 
signal d2TextChanged(var dateText)
function setValidDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var d=new Date(getText(7,11),Months[getText(3,6)],getText(0,2));if( d.getFullYear().toString() === getText(7,11)&& d.getMonth()===Months[getText(3,6)] && d.getDate().toString()===getText(0,2)){selectedDate = d.toLocaleString(Qt.locale("en_US"),"yyyy-MM-dd");}else { selectedDate = '' };}
MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{ parent.forceActiveFocus(); d2_cal_box.visible=!d2_cal_box.visible; parent.z=d2_cal_box.visible?1:0; }
Image{
id:d2_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMzIiIGhlaWdodD0iMzIiIHZpZXdCb3g9IjAgMCAzMiAzMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bWVldGluZ3MvY2FsZW5kYXItZW1wdHlfMzI8L3RpdGxlPjxwYXRoIGQ9Ik0zMCAyM2wwIDEgMCA0LjAwOEMzMCAyOS4xMDUgMjkuMTAzIDMwIDI4IDMwTDQgMzBjLTEuMTA1IDAtMi0uODkzLTItMS45OTJMMiAyNGwwLTFMMiA2Ljk5MkMyIDUuODk1IDIuODk3IDUgNCA1bDI0IDBjMS4xMDUgMCAyIC44OTMgMiAxLjk5MkwzMCAyM3pNMjggNGwtNSAwIDAtMi41MDVjMC0uMjc5LS4yMjQtLjQ5NS0uNS0uNDk1LS4yNjggMC0uNS4yMjItLjUuNDk1TDIyIDQgMTAgNGwwLTIuNTA1QzEwIDEuMjE2IDkuNzc2IDEgOS41IDFjLS4yNjggMC0uNS4yMjItLjUuNDk1TDkgNCA0IDRDMi4zNDcgNCAxIDUuMzQgMSA2Ljk5MmwwIDIxLjAxNkMxIDI5LjY2MSAyLjM0MyAzMSA0IDMxbDI0IDBjMS42NTMgMCAzLTEuMzQgMy0yLjk5MmwwLTIxLjAxNkMzMSA1LjMzOSAyOS42NTcgNCAyOCA0eiIgZmlsbC1ydWxlPSJldmVub2RkIi8+PC9zdmc+"
}
ColorOverlay{
anchors.fill:d2_icon
source:d2_icon
color:'#171B1F'
}
}
Rectangle{
id:d2_cal_box
visible:false
anchors.left:parent.left
anchors.top:parent.bottom
width:300
height:300
Component.onCompleted:{ Qt.createQmlObject('import QtQuick.Controls 1.4
import QtQuick 2.15
Calendar{
anchors.fill:parent
Component.onCompleted:{d2.d2TextChanged.connect(setCalendarDate);d2.d2TextChanged( d2.text)}
onReleased:{parent.visible=false; d2.text=selectedDate.toLocaleString(Qt.locale("en_US"),"dd\/MMM\/yyyy")}
function setCalendarDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var y=dateString.match(/\\d{4}/);dateString=dateString.replace(y,"");var m=dateString.match(/[a-zA-Z]{3}/);var d=dateString.match(/\\d{2}/);if (d!==null && m!==null && y!==null){selectedDate=new Date(y[0],Months[m[0]],d[0]) }}
}
',d2_cal_box,'calendar')}
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
id:d3
width:parent.width
font.family:"Segoe UI"
font.pixelSize:14
selectByMouse:true
selectedTextColor:'white'
color:'#171B1F'
property string selectedDate:""
background:Rectangle{
radius:5
color:'#FFFFFF'
border.color:d3.activeFocus? 'black' : 'grey'
border.width:1
layer.enabled:d3.activeFocus ? true : false
layer.effect:Glow{
samples:25
color:'skyblue'
}

}

onTextChanged:{d3TextChanged(text);setValidDate(text);}
placeholderText:"Select date in dd\/mmm\/yyyy"
validator:RegExpValidator { regExp: /^([-0123]-|0\d|[12]\d|3[01])\/(---|[JFMASOND]--|Ja-|Jan|Fe-|Feb|Ma-|Mar|Ap-|Apr|May|Ju--|Jun|Jul|Au-|Aug|Se-|Sep|Oc-|Oct|No-|Nov|De-|Dec)\/(-{4}|\d-{3}|\d{2}-{2}|\d{3}-|\d{4})$/}
onFocusChanged:{if(focus===true) inputMask="xx\/>x<xx\/xxxx;-";if(focus === false){ z=0;if(text === "\/\/"){ inputMask = "" ; } if( d3_cal_box.visible === true){ d3_cal_box.visible=false}}} 
signal d3TextChanged(var dateText)
function setValidDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var d=new Date(getText(7,11),Months[getText(3,6)],getText(0,2));if( d.getFullYear().toString() === getText(7,11)&& d.getMonth()===Months[getText(3,6)] && d.getDate().toString()===getText(0,2)){selectedDate = d.toLocaleString(Qt.locale("en_US"),"yyyy-MM-dd");}else { selectedDate = '' };}
MouseArea{
height:parent.height
width:height
anchors.right:parent.right
enabled:true
onClicked:{ parent.forceActiveFocus(); d3_cal_box.visible=!d3_cal_box.visible; parent.z=d3_cal_box.visible?1:0; }
Image{
id:d3_icon
anchors.fill:parent
anchors.margins:5
fillMode:Image.PreserveAspectFit
mipmap:true
source:"data:image/svg+xml;base64,PHN2ZyB3aWR0aD0iMzIiIGhlaWdodD0iMzIiIHZpZXdCb3g9IjAgMCAzMiAzMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+bWVldGluZ3MvY2FsZW5kYXItZW1wdHlfMzI8L3RpdGxlPjxwYXRoIGQ9Ik0zMCAyM2wwIDEgMCA0LjAwOEMzMCAyOS4xMDUgMjkuMTAzIDMwIDI4IDMwTDQgMzBjLTEuMTA1IDAtMi0uODkzLTItMS45OTJMMiAyNGwwLTFMMiA2Ljk5MkMyIDUuODk1IDIuODk3IDUgNCA1bDI0IDBjMS4xMDUgMCAyIC44OTMgMiAxLjk5MkwzMCAyM3pNMjggNGwtNSAwIDAtMi41MDVjMC0uMjc5LS4yMjQtLjQ5NS0uNS0uNDk1LS4yNjggMC0uNS4yMjItLjUuNDk1TDIyIDQgMTAgNGwwLTIuNTA1QzEwIDEuMjE2IDkuNzc2IDEgOS41IDFjLS4yNjggMC0uNS4yMjItLjUuNDk1TDkgNCA0IDRDMi4zNDcgNCAxIDUuMzQgMSA2Ljk5MmwwIDIxLjAxNkMxIDI5LjY2MSAyLjM0MyAzMSA0IDMxbDI0IDBjMS42NTMgMCAzLTEuMzQgMy0yLjk5MmwwLTIxLjAxNkMzMSA1LjMzOSAyOS42NTcgNCAyOCA0eiIgZmlsbC1ydWxlPSJldmVub2RkIi8+PC9zdmc+"
}
ColorOverlay{
anchors.fill:d3_icon
source:d3_icon
color:'#171B1F'
}
}
Rectangle{
id:d3_cal_box
visible:false
anchors.left:parent.left
anchors.top:parent.bottom
width:300
height:300
Component.onCompleted:{ Qt.createQmlObject('import QtQuick.Controls 1.4
import QtQuick 2.15
Calendar{
anchors.fill:parent
Component.onCompleted:{d3.d3TextChanged.connect(setCalendarDate);d3.d3TextChanged( d3.text)}
onReleased:{parent.visible=false; d3.text=selectedDate.toLocaleString(Qt.locale("en_US"),"dd\/MMM\/yyyy")}
function setCalendarDate(dateString){var Months = {Jan: 0,Feb: 1,Mar: 2,Apr: 3,May: 4,Jun: 5,July: 6,Aug: 7,Sep: 8,Oct: 9,Nov: 10,Dec: 11};var y=dateString.match(/\\d{4}/);dateString=dateString.replace(y,"");var m=dateString.match(/[a-zA-Z]{3}/);var d=dateString.match(/\\d{2}/);if (d!==null && m!==null && y!==null){selectedDate=new Date(y[0],Months[m[0]],d[0]) }}
}
',d3_cal_box,'calendar')}
}
}
}
}
}
}
