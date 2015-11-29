var scrollt=0;
var tflag=0;//存放时间和歌词的数组的下标
/*var lytextN=new Array();//
var lytimeN=new Array();//当时歌词显示出现前面歌曲的歌词也会出现在后面的歌曲中，想使用二维数组方法，后来发现多此一举，不方便*/
var lytext=new Array();//放存汉字的歌词
var lytime=new Array();//存放时间
var delay=10;
var line=0;
var scrollh=0;

var StartTime=0;
var FinishTime=0;



/*数组赋字符值时出现错误提示，有时是空格问题，只要所有字符显示在一个行号内就对了*/
var songLy=new Array();
songLy[0]="[00:00]Take Me to Your Heart.[00:01]演唱：Michael Learns To Rock.[00:02].[00:17]Hiding from the rain and snow.[00:20]Trying to forget but I won't let go.[00:24].[00:25]Looking at a crowded street.[00:28]Listening to my own heart beat.[00:32]So many people.[00:36]All around the world.[00:40]Tell me where do I find.[00:44]Someone like you girl.[00:47]Take me to your heart.[00:49]Take me to your soul.[00:51]Give me your hand before I'm old.[00:55]Show me what love is.[00:57]Haven't got a clue.[00:59]Show me that wonders can be true.[01:03]They say nothing lasts forever.[01:08]We are only here today.[01:12]Love's now or never.[01:16]Bring me far away.[01:19]Take me to your heart.[01:22]Take me to your soul.[01:24]Give me your hand and hold me.[01:27]Show me what love.[01:29]Is be my guiding star.[01:32]It is easy.[01:33]Take me to your heart.[01:39].[02:11]Standing on a mountain high.[02:14]Looking at the moon through a clear blue sky.[02:19]I should go and see some friends.[02:22]But they don't really comprehend.[02:27]Don't need too much talking.[02:30]Without saying anything.[02:34]All I need is someone.[02:38]Who makes me wanna sing.[02:41]Take me to your heart.[02:43]Take me to your soul.[02:45]Give me your hand before I'm old.[02:49]Show me what love is.[02:52]Haven't got a clue.[02:53]Show me that wonders can be true.[02:57]They say nothing lasts forever.[03:02]We are only here today.[03:06]Love's now or never.[03:10]Bring me far away.[03:13]Take me to your heart.[03:15]Take me to your soul.[03:18]Give me your hand and hold me.[03:21]Show me what love.[03:23]Is be my guiding star.[03:26]It is easy.[03:28]Take me to your heart.[03:30]Take me Take me Take me.[03:33]Take me to your heart.[03:35]Take me to your soul.[03:38]Give me your hand and hold me.[03:40]Show me what love.[03:43]Is be my guiding star.[03:45]It is easy.[03:47]Take me to your heart.[03:53]..";

/*songLy[1]="[00:01]幸福的两口子.[00:04]演唱：庞龙.[00:07]感动2007最温暖的情歌.[00:10]电视连续剧《幸福的两口子》主题歌.[00:13]词曲：老猫.[00:16].[00:25]记得你最爱穿白裙子. [00:28]我最喜欢你的大辫子.[00:32]你爱看我傻笑的样子.[00:36]说我是你爱的男孩子.[00:39]静静坐在湖边的椅子.[00:43]我第一次抱着女孩子.[00:46]我们一起攒钱买房子.[00:50]还要一起生个胖儿子.[00:54].[00:56]我不能忘记你的样子.[00:59]我们一起过的苦日子.[01:03]我们一定相爱一辈子.[01:06]你永远是我的小娘子.[01:11].[01:40]记得过年一起包饺子.[01:44]一起喝水用的茶缸子.[01:48]站在河里光着脚丫子.[01:51]数着天空飞过的燕子.[01:55]你笑我变成了老头子.[01:58]我笑你变成了老婆子.[02:02]心里念着彼此的名字.[02:06]永远不能忘的白裙子.[02:09].[02:11]等到我长出了白胡子.[02:15]一起坐在家的老院子.[02:18]看着满地玩耍的孩子.[02:22]回想我们年轻的日子.[02:27]我不能忘记你的样子.[02:31]我们一起过的苦日子.[02:34]我们一定相爱一辈子.[02:38]你永远是我的小娘子.[02:42]等到我长出了白胡子.[02:45]一起坐在家的老院子.[02:49]看着满地玩耍的孩子.[02:53]回想我们年轻的日子.[02:57].[03:00]记得你最爱穿白裙子.[03:03]我最喜欢你的大辫子.[03:07]你爱看我傻笑的样子[03:11]说我是你爱的男孩子.[03:14]你笑我变成了老头子.[03:18]我笑你变成了老婆子.[03:21]心里念着彼此的名字.[03:25]永远不能忘的白裙子.[03:30].";
*/

songLy[1]="[00:01]夜空中最亮的星(Remix版).[00:04]演唱：逃跑计划乐队.[00:12].[00:18]夜空中最亮的星.[00:22]能否听清.[00:26]那仰望的人.[00:29]心底的孤独和叹息.[00:35]夜空中最亮的星.[00:40]能否记起.[00:44]曾与我同行.[00:47]消失在风里的身影.[00:52]我祈祷拥有一颗透明的心灵.[00:57]和会流泪的眼睛.[01:03]给我再去相信的勇气.[01:06]oh越过谎言去拥抱你.[01:10]每当我找不到存在的意义.[01:15]每当我迷失在黑夜里.[01:21]oh...夜空中最亮的星.[01:24]请指引我靠近你.[01:30].[01:38]夜空中最亮的星.[01:42]是否知道.[01:47]那曾与我同行的身影.[01:50]如今在哪里.[01:56]oh夜空中最亮的星.[02:00]是否在意.[02:04]是等太阳升起.[02:07]还是意外先来临.[02:13]我宁愿所有痛苦都留在心里.[02:18]也不愿忘记你的眼睛.[02:23]给我再去相信的勇气.[02:27]oh越过谎言去拥抱你.[02:31]每当我找不到存在的意义.[02:35]每当我迷失在黑夜里.[02:41]oh...夜空中最亮的星.[02:44]oh请照亮我前行.[03:02].[03:06]我祈祷拥有一颗透明的心灵.[03:11]和会流泪的眼睛.[03:17]给我再去相信的勇气.[03:20]oh越过谎言去拥抱你.[03:24]每当我找不到存在的意义.[03:29]每当我迷失在黑夜里.[03:34]oh...夜空中最亮的星.[03:38]oh请照亮我前行.[03:43].";

songLy[2]="[00:01].[00:05]Summertrain.[00:07].[00:17]Come with me for a little ride, see the shadows passing by.[00:25]Look at the sun and see the clouds turn to faces in the sky.[00:34]We've been awake all night, shattered dreams all around.[00:42]Close your sad, sad eyes we will be safe and sound.[00:50].[00:51]Come with me for a little ride, see the shadows passing by.[01:00]Look at the sun and see the clouds turn to faces in the sky.[01:08]Daydreaming lightly through the rainAll's forgiven on a summer train.[01:16].[01:17]Come with me for a little ride, see the shadows passing by.[01:25]Seems we are a thousand miles away from last night.[01:34]As you sigh in my ear, kiss the rain goodbye.[01:42].[01:43]Come with me for a little ride, see the shadows passing by.[01:51]Look at the sun and see the clouds turn to faces in the sky.[02:00]Daydreaming lightly through the rain.[02:04]All's forgiven on a summer train.[02:08].[02:09]Come with me for a little ride, see the shadows passing by.[02:16]Come away with me, it's gonna be all right just breathe.[02:25]Come away with me, it's gonna be all right you'll see.[02:34].[02:34]And the wind .... this train is flying us all through the rain, I fear.[02:42]And the sky is getting brighter with every mile.[02:47]And it all seems clear.[02:51].[03:00]Come with me for a little ride, see the shadows passing by.[03:09]Look at the sun and see the clouds turn to faces in the sky.[03:17]Daydreaming lightly through the rain.[03:22]All's forgiven on a summer train.[03:25].[03:26]Come with me for a little ride, see the shadows passing by.[03:34]Come away with me, it's gonna be all right just breathe.[03:42]Come away with me, it's gonna be all right you'll see.[03:50].[03:51]Come away with me, it's gonna be all right just breathe.[03:59]Come away with me, it's gonna be all right you'll see, you'll see.[04:24]Come away with me.[04:28].";
songLy[3]="[00:01]今生今世.[00:03]演唱：满文军.[00:06].[00:34]我的世界暴风雪.[00:38]跋涉到绝望边缘.[00:42]你的温柔眼睛藏着碧蓝天.[00:50]我心像孤舟一叶.[00:54]人在情海里搁浅.[00:58]你的笑容微风带着我往前.[01:05]这是注定 这是命运.[01:15]你是不容错过的唯一.[01:23]我今生今世只等你.[01:27]全心全意只爱你.[01:31]相知相惺 是最动人的美丽.[01:39]我今生今世只等你.[01:44]来生来世也爱你.[01:48]相偎相依 爱成最亮的恒星.[01:54].[02:13]我心像孤舟一叶.[02:17]人在情海里搁浅.[02:21]你的笑容微风带着我往前.[02:28]这是注定 这是命运.[02:38]你是不容错过的唯一.[02:46]我今生今世只等你.[02:50]全心全意只爱你.[02:54]相知相惺 是最动人的美丽.[03:02]我今生今世只等你.[03:06]来生来世也爱你.[03:11]相偎相依 爱成最亮的恒星.[03:15].[03:23]我今生今世只等你.[03:27]全心全意只爱你.[03:31]相知相惺 是最动人的美丽.[03:39]我今生今世只等你.[03:44]来生来世也爱你.[03:48]相偎相依 爱成最亮的恒星.[03:54].";
songLy[4]="[00:02]Marry You.[00:03]Bruno Mars.[00:03].[00:13]it's a beautiful night we're looking for something dumb to do.[00:19]hey baby i think i wanna marry you.[00:26]is it the look in your eyes or is it this dancing juice.[00:33]who cares baby, i think i wanna marry you.[00:39]well i know this little chapel on the boulevard.[00:43]we can go whoa whoa.[00:45]no one will no whoa.[00:49]oh come on girl.[00:52].[00:53]who cares if we're trashed.[00:54]got a pocket full of cash we can blow whoa whoa.[00:58]shots of patrol whoa whoa.[01:02]and guitar girl.[01:05].[01:06]don't say no no no no no.[01:09]just say yeah yeah yeah yeah yeah.[01:12]and we'll go go go go go.[01:15]if you're ready, like i'm ready.[01:18].[01:19]cos it's a beautiful nigt we're looking for something dumb to do.[01:25]hey baby i think i wanna marry you.[01:32]is it the look in your eyes or is it this dancing juice.[01:39]who cares baby, i think i wanna marry you.[01:43].[01:45]oh.[01:46]i'll go get the ring.[01:47]let the choir bell sing like ooh ooh ooh.[01:51]so what you wanna do ooh ooh.[01:55]lets just run girl.[01:59]if we wake up and you want to break up.[02:02]that's cool ooh ooh.[02:04]no i won't blame you ooh ooh.[02:08]it was fun girl.[02:12].[02:12]don't say no no no no no.[02:15]just say yeah yeah yeah yeah yeah.[02:18]and we'll go go go go go.[02:22]if you're ready, like i'm ready.[02:25].[02:25]cos it's a beautiful nigt we're looking for something dumb to do.[02:31]hey baby i think i wanna marry you.[02:38]is it the look in your eyes or is it this dancing juice.[02:45]who cares baby, i think i wanna marry you.[02:49].[02:51]just say i do ooh ooh ooh.[02:58]tell me right now baby.[03:01]tell me right now baby, baby.[03:04]just say i do ooh ooh ooh.[03:11]tell me right now baby.[03:14]tell me right now baby, baby.[03:17]oh.[03:17].[03:18]it's a beautiful nigt we're looking for something dumb to do.[03:24]hey baby i think i wanna marry you.[03:31]is it the look in your eyes or is it this dancing juice.[03:38]who cares baby, i think i wanna marry you.[03:42].";
songLy[5]="[00:00]风雨无阻.[00:03]作词:李子恒 作曲:李子恒.[00:06]演唱：周华健.[00:12].[00:20]给你我的全部.[00:24]你是我今生唯一的赌注.[00:28]只留下一段岁月.[00:31]让我无怨无悔全心的付出.[00:37]怕你忧伤怕你哭.[00:41]怕你孤单怕你糊涂.[00:45]红尘千山万里路.[00:49]我可以朝朝暮暮.[00:53]给你一条我的路.[00:57]你是我一生不停的脚步.[01:01]让我走出一片天空.[01:04]让你尽情飞舞放心的追逐.[01:10]爱是漫长的旅途.[01:14]梦有快乐梦有痛苦.[01:18]悲欢离合人间路.[01:22]我可以缝缝补补.[01:28]提着昨日种种千辛万苦.[01:31]向明天换一些美满和幸福.[01:37]爱你够不够多.[01:39]对你够不够好.[01:41]可以要求不要不在乎.[01:45]不愿让你看见我的伤处.[01:48]是曾经无悔的风雨无阻.[01:54]拥有够不够多.[01:55]梦的够不够好.[01:57]可以追求不认输.[02:05].[02:18]给你一条我的路.[02:22]你是我一生不停的脚步.[02:26]让我走出一片天空.[02:29]让你尽情飞舞放心的追逐.[02:34]爱是漫长的旅途.[02:39]梦有快乐梦有痛苦.[02:43]悲欢离合人间路.[02:47]我可以缝缝补补.[02:53]提着昨日种种千辛万苦.[02:56]向明天换一些美满和幸福.[03:02]爱你够不够多.[03:04]对你够不够好.[03:06]可以要求不要不在乎.[03:10]不愿让你看见我的伤处.[03:12]是曾经无悔的风雨无阻.[03:18]拥有够不够多.[03:20]梦的够不够好.[03:22]可以追求不认输.[03:29].[03:31]提着昨日种种千辛万苦.[03:33]向明天换一些美满和幸福.[03:38]爱你够不够多.[03:41]对你够不够好.[03:43]可以要求不要不在乎.[03:47]不愿让你看见我的伤处.[03:50]是曾经无悔的风雨无阻.[03:55]拥有够不够多.[03:57]梦的够不够好.[03:59]可以追求不认输.[04:06].";
songLy[6]="";
function show(t)//显示歌词  参数为音乐播放的时间
{
var div1=document.getElementById("lyr");//取得层
document.getElementById("lyr").innerHTML=" ";//每次调用清空以前的一次
if(t<lytime[lytime.length-1])//（歌词时间）
{
for(var k=0;k<lytext.length;k++)
{
if(lytime[k]<=t&&t<lytime[k+1])
{
scrollh=k*25;//让当前的滚动条的顶部改变一行的高度
div1.innerHTML+="<font color=red style=font-weight:bold>"+lytext[k]+"</font><br>";
}
else if(t<lytime[lytime.length-1])//普通显示  不用红色显示
div1.innerHTML+=lytext[k]+"<br>";
}
}
else//歌曲结束后，红色显示最后一句
{
for(var j=0;j<lytext.length-1;j++)
div1.innerHTML+=lytext[j]+"<br>";
div1.innerHTML+="<font color=red style=font-weight:bold>"+lytext[lytext.length-1]+"</font><br>";
}


}

function scrollBar()//设置滚动条的滚动   显示歌词
{
if(document.getElementById("lyr").scrollTop<=scrollh)
document.getElementById("lyr").scrollTop+=1;
if(document.getElementById("lyr").scrollTop>=scrollh+50)
document.getElementById("lyr").scrollTop-=1;
window.setTimeout("scrollBar()",delay);//实现缓动效果
}

function getReady(i)//在显示歌词前做好准备工作
{


var myDate = new Date();
/*var mytime= myDate.toLocaleTimeString();
var a=mytime.split(":");
StartTime = a[1]*60+a[2];采用这种方法，时间在60秒后出现跳变，没找到原因*/
 StartTime =myDate.getTime()*0.001 ;//还是用获取毫秒数的方法实现的，刚开始用除法获取秒出现问题，改为乘法后问题消失了

var ly=songLy[i];//得到歌词
//alert(ly);
var arrly=ly.split(".");//转化成数组  split分割作用
for(var i=0;i<arrly.length;i++)
sToArray(arrly[i]);//函数  在后面实现
sortAr();//函数  在后面实现
/*for(var j=0;j<lytext.length;j++)
{
document.getElementById("lyr").innerHTML+=lytime[j]+lytext[j]+"<br>";
}*/
scrollBar();
}

function sToArray(str)//解析如“[02:02][00:24]没想到是你”的字符串前放入数组
{
var left=0;//"["的个数
var leftAr=new Array();
for(var k=0;k<str.length;k++)
{
if(str.charAt(k)=="[")//charAt 返回指定位置的字符
{
leftAr[left]=k;
left++;
}
}
if(left!=0)
{
for(var i=0;i<leftAr.length;i++)
{
lytext[tflag]=str.substring(str.lastIndexOf("]")+1);//放歌词，去掉前面的时间  substring提取字符串中介于两个指定下标之间的字符  
lytime[tflag]=conSeconds(str.substring(leftAr[i]+1,leftAr[i]+6));//放时间  对时间格式进行转换
tflag++;
}
}
//alert(str.substring(leftAr[0]+1,leftAr[0]+6));
}

function sortAr()//按时间重新排序时间和歌词的数组
{
var temp=null;
var temp1=null;
for(var k=0;k<lytime.length;k++)
{
for(var j=0;j<lytime.length-k;j++)
{
if(lytime[j]>lytime[j+1])
{
temp=lytime[j];
temp1=lytext[j];
lytime[j]=lytime[j+1];
lytext[j]=lytext[j+1];
lytime[j+1]=temp;
lytext[j+1]=temp1;
}
}
}
}

function conSeconds(t)//把形如：01：25的时间转化成秒；
{
var m=t.substring(0,t.indexOf(":"));
var s=t.substring(t.indexOf(":")+1);
s=parseInt(s.replace(/\b(0+)/gi,""));//去除前导0   将字符串解析为数字
if(isNaN(s))
s=0;
var totalt=parseInt(m)*60+s;//之前在这里画蛇添足添加了正则表达式  使时间计算上一直有问题  调试了很久才找到这个问题    以后在源码上尽量不要改   因为画蛇添足很可怕
//alert(parseInt(s.replace(/\b(0+)/gi,"")));
if(isNaN(totalt))
return 0;
return totalt;
}

//获取时间************************************ 自己创建一下   不使用播放器的时间
/*function getSeconds()//得到当前播放器播放位置的时间
{
var t=getPosition();
t=t.toString();//数字转换成字符串
var s=t.substring(0,t.lastIndexOf("."));//得到当前的秒
//alert(s);
return s;
}
function getPosition()//返回当前播放的时间位置
{
var mm=document.getElementById("MediaPlayer1");
//var mmt=;
//alert(mmt);
return mm.CurrentPosition;
}*/
function getSeconds()//计算时间
{ 
var myDate = new Date();
/*var mytime= myDate.toLocaleTimeString();
var a=mytime.split(":");
FinishTime = a[1]*60+a[2];*/
//alert(times);

 FinishTime=myDate.getTime()*0.001;//减去一部分时间，为了调整歌词，因为时间是自己设置的，歌词同步有点小问题，可以手动重新调整歌词的时间轴
 var s=FinishTime-StartTime;
return s;
}



function mPlay()//开始播放
{
 
var ms=getSeconds();//修改************************************

if(isNaN(ms))
show(0);
else
show(ms);


}

function comeOn(i)//开始播放
{
	for(var m=0;m<lytext.length;m++)
{ lytext[m]="";
  lytime[m]="";//每次清空一下
}
   tflag=0;/*数组每次用前清空一下，不然会使前面歌曲的歌词出现在后面的歌曲歌词中，下标也要清空，因为是全局变量，不然下标一直增长，使后面歌曲的歌词不显示*/
    getReady(i);
	window.setInterval("mPlay()",1000);
	
	 }

