var scrollt=0;
var tflag=0;//���ʱ��͸�ʵ�������±�
/*var lytextN=new Array();//
var lytimeN=new Array();//��ʱ�����ʾ����ǰ������ĸ��Ҳ������ں���ĸ����У���ʹ�ö�ά���鷽�����������ֶ��һ�٣�������*/
var lytext=new Array();//�Ŵ溺�ֵĸ��
var lytime=new Array();//���ʱ��
var delay=10;
var line=0;
var scrollh=0;

var StartTime=0;
var FinishTime=0;



/*���鸳�ַ�ֵʱ���ִ�����ʾ����ʱ�ǿո����⣬ֻҪ�����ַ���ʾ��һ���к��ھͶ���*/
var songLy=new Array();
songLy[0]="[00:00]Take Me to Your Heart.[00:01]�ݳ���Michael Learns To Rock.[00:02].[00:17]Hiding from the rain and snow.[00:20]Trying to forget but I won't let go.[00:24].[00:25]Looking at a crowded street.[00:28]Listening to my own heart beat.[00:32]So many people.[00:36]All around the world.[00:40]Tell me where do I find.[00:44]Someone like you girl.[00:47]Take me to your heart.[00:49]Take me to your soul.[00:51]Give me your hand before I'm old.[00:55]Show me what love is.[00:57]Haven't got a clue.[00:59]Show me that wonders can be true.[01:03]They say nothing lasts forever.[01:08]We are only here today.[01:12]Love's now or never.[01:16]Bring me far away.[01:19]Take me to your heart.[01:22]Take me to your soul.[01:24]Give me your hand and hold me.[01:27]Show me what love.[01:29]Is be my guiding star.[01:32]It is easy.[01:33]Take me to your heart.[01:39].[02:11]Standing on a mountain high.[02:14]Looking at the moon through a clear blue sky.[02:19]I should go and see some friends.[02:22]But they don't really comprehend.[02:27]Don't need too much talking.[02:30]Without saying anything.[02:34]All I need is someone.[02:38]Who makes me wanna sing.[02:41]Take me to your heart.[02:43]Take me to your soul.[02:45]Give me your hand before I'm old.[02:49]Show me what love is.[02:52]Haven't got a clue.[02:53]Show me that wonders can be true.[02:57]They say nothing lasts forever.[03:02]We are only here today.[03:06]Love's now or never.[03:10]Bring me far away.[03:13]Take me to your heart.[03:15]Take me to your soul.[03:18]Give me your hand and hold me.[03:21]Show me what love.[03:23]Is be my guiding star.[03:26]It is easy.[03:28]Take me to your heart.[03:30]Take me Take me Take me.[03:33]Take me to your heart.[03:35]Take me to your soul.[03:38]Give me your hand and hold me.[03:40]Show me what love.[03:43]Is be my guiding star.[03:45]It is easy.[03:47]Take me to your heart.[03:53]..";

/*songLy[1]="[00:01]�Ҹ���������.[00:04]�ݳ�������.[00:07]�ж�2007����ů�����.[00:10]���������硶�Ҹ��������ӡ������.[00:13]��������è.[00:16].[00:25]�ǵ��������ȹ��. [00:28]����ϲ����Ĵ����.[00:32]�㰮����ɵЦ������.[00:36]˵�����㰮���к���.[00:39]�������ں��ߵ�����.[00:43]�ҵ�һ�α���Ů����.[00:46]����һ����Ǯ����.[00:50]��Ҫһ�������ֶ���.[00:54].[00:56]�Ҳ��������������.[00:59]����һ����Ŀ�����.[01:03]����һ���మһ����.[01:06]����Զ���ҵ�С����.[01:11].[01:40]�ǵù���һ�������.[01:44]һ���ˮ�õĲ����.[01:48]վ�ں�����Ž�Ѿ��.[01:51]������շɹ�������.[01:55]��Ц�ұ������ͷ��.[01:58]��Ц������������.[02:02]�������ű˴˵�����.[02:06]��Զ�������İ�ȹ��.[02:09].[02:11]�ȵ��ҳ����˰׺���.[02:15]һ�����ڼҵ���Ժ��.[02:18]����������ˣ�ĺ���.[02:22]�����������������.[02:27]�Ҳ��������������.[02:31]����һ����Ŀ�����.[02:34]����һ���మһ����.[02:38]����Զ���ҵ�С����.[02:42]�ȵ��ҳ����˰׺���.[02:45]һ�����ڼҵ���Ժ��.[02:49]����������ˣ�ĺ���.[02:53]�����������������.[02:57].[03:00]�ǵ��������ȹ��.[03:03]����ϲ����Ĵ����.[03:07]�㰮����ɵЦ������[03:11]˵�����㰮���к���.[03:14]��Ц�ұ������ͷ��.[03:18]��Ц������������.[03:21]�������ű˴˵�����.[03:25]��Զ�������İ�ȹ��.[03:30].";
*/

songLy[1]="[00:01]ҹ������������(Remix��).[00:04]�ݳ������ܼƻ��ֶ�.[00:12].[00:18]ҹ������������.[00:22]�ܷ�����.[00:26]����������.[00:29]�ĵ׵Ĺ¶���̾Ϣ.[00:35]ҹ������������.[00:40]�ܷ����.[00:44]������ͬ��.[00:47]��ʧ�ڷ������Ӱ.[00:52]����ӵ��һ��͸��������.[00:57]�ͻ�������۾�.[01:03]������ȥ���ŵ�����.[01:06]ohԽ������ȥӵ����.[01:10]ÿ�����Ҳ������ڵ�����.[01:15]ÿ������ʧ�ں�ҹ��.[01:21]oh...ҹ������������.[01:24]��ָ���ҿ�����.[01:30].[01:38]ҹ������������.[01:42]�Ƿ�֪��.[01:47]��������ͬ�е���Ӱ.[01:50]���������.[01:56]ohҹ������������.[02:00]�Ƿ�����.[02:04]�ǵ�̫������.[02:07]��������������.[02:13]����Ը����ʹ�඼��������.[02:18]Ҳ��Ը��������۾�.[02:23]������ȥ���ŵ�����.[02:27]ohԽ������ȥӵ����.[02:31]ÿ�����Ҳ������ڵ�����.[02:35]ÿ������ʧ�ں�ҹ��.[02:41]oh...ҹ������������.[02:44]oh��������ǰ��.[03:02].[03:06]����ӵ��һ��͸��������.[03:11]�ͻ�������۾�.[03:17]������ȥ���ŵ�����.[03:20]ohԽ������ȥӵ����.[03:24]ÿ�����Ҳ������ڵ�����.[03:29]ÿ������ʧ�ں�ҹ��.[03:34]oh...ҹ������������.[03:38]oh��������ǰ��.[03:43].";

songLy[2]="[00:01].[00:05]Summertrain.[00:07].[00:17]Come with me for a little ride, see the shadows passing by.[00:25]Look at the sun and see the clouds turn to faces in the sky.[00:34]We've been awake all night, shattered dreams all around.[00:42]Close your sad, sad eyes we will be safe and sound.[00:50].[00:51]Come with me for a little ride, see the shadows passing by.[01:00]Look at the sun and see the clouds turn to faces in the sky.[01:08]Daydreaming lightly through the rainAll's forgiven on a summer train.[01:16].[01:17]Come with me for a little ride, see the shadows passing by.[01:25]Seems we are a thousand miles away from last night.[01:34]As you sigh in my ear, kiss the rain goodbye.[01:42].[01:43]Come with me for a little ride, see the shadows passing by.[01:51]Look at the sun and see the clouds turn to faces in the sky.[02:00]Daydreaming lightly through the rain.[02:04]All's forgiven on a summer train.[02:08].[02:09]Come with me for a little ride, see the shadows passing by.[02:16]Come away with me, it's gonna be all right just breathe.[02:25]Come away with me, it's gonna be all right you'll see.[02:34].[02:34]And the wind .... this train is flying us all through the rain, I fear.[02:42]And the sky is getting brighter with every mile.[02:47]And it all seems clear.[02:51].[03:00]Come with me for a little ride, see the shadows passing by.[03:09]Look at the sun and see the clouds turn to faces in the sky.[03:17]Daydreaming lightly through the rain.[03:22]All's forgiven on a summer train.[03:25].[03:26]Come with me for a little ride, see the shadows passing by.[03:34]Come away with me, it's gonna be all right just breathe.[03:42]Come away with me, it's gonna be all right you'll see.[03:50].[03:51]Come away with me, it's gonna be all right just breathe.[03:59]Come away with me, it's gonna be all right you'll see, you'll see.[04:24]Come away with me.[04:28].";
songLy[3]="[00:01]��������.[00:03]�ݳ������ľ�.[00:06].[00:34]�ҵ����籩��ѩ.[00:38]���浽������Ե.[00:42]��������۾����ű�����.[00:50]���������һҶ.[00:54]�����麣���ǳ.[00:58]���Ц��΢���������ǰ.[01:05]����ע�� ��������.[01:15]���ǲ��ݴ����Ψһ.[01:23]�ҽ�������ֻ����.[01:27]ȫ��ȫ��ֻ����.[01:31]��֪���� ����˵�����.[01:39]�ҽ�������ֻ����.[01:44]��������Ҳ����.[01:48]�������� ���������ĺ���.[01:54].[02:13]���������һҶ.[02:17]�����麣���ǳ.[02:21]���Ц��΢���������ǰ.[02:28]����ע�� ��������.[02:38]���ǲ��ݴ����Ψһ.[02:46]�ҽ�������ֻ����.[02:50]ȫ��ȫ��ֻ����.[02:54]��֪���� ����˵�����.[03:02]�ҽ�������ֻ����.[03:06]��������Ҳ����.[03:11]�������� ���������ĺ���.[03:15].[03:23]�ҽ�������ֻ����.[03:27]ȫ��ȫ��ֻ����.[03:31]��֪���� ����˵�����.[03:39]�ҽ�������ֻ����.[03:44]��������Ҳ����.[03:48]�������� ���������ĺ���.[03:54].";
songLy[4]="[00:02]Marry You.[00:03]Bruno Mars.[00:03].[00:13]it's a beautiful night we're looking for something dumb to do.[00:19]hey baby i think i wanna marry you.[00:26]is it the look in your eyes or is it this dancing juice.[00:33]who cares baby, i think i wanna marry you.[00:39]well i know this little chapel on the boulevard.[00:43]we can go whoa whoa.[00:45]no one will no whoa.[00:49]oh come on girl.[00:52].[00:53]who cares if we're trashed.[00:54]got a pocket full of cash we can blow whoa whoa.[00:58]shots of patrol whoa whoa.[01:02]and guitar girl.[01:05].[01:06]don't say no no no no no.[01:09]just say yeah yeah yeah yeah yeah.[01:12]and we'll go go go go go.[01:15]if you're ready, like i'm ready.[01:18].[01:19]cos it's a beautiful nigt we're looking for something dumb to do.[01:25]hey baby i think i wanna marry you.[01:32]is it the look in your eyes or is it this dancing juice.[01:39]who cares baby, i think i wanna marry you.[01:43].[01:45]oh.[01:46]i'll go get the ring.[01:47]let the choir bell sing like ooh ooh ooh.[01:51]so what you wanna do ooh ooh.[01:55]lets just run girl.[01:59]if we wake up and you want to break up.[02:02]that's cool ooh ooh.[02:04]no i won't blame you ooh ooh.[02:08]it was fun girl.[02:12].[02:12]don't say no no no no no.[02:15]just say yeah yeah yeah yeah yeah.[02:18]and we'll go go go go go.[02:22]if you're ready, like i'm ready.[02:25].[02:25]cos it's a beautiful nigt we're looking for something dumb to do.[02:31]hey baby i think i wanna marry you.[02:38]is it the look in your eyes or is it this dancing juice.[02:45]who cares baby, i think i wanna marry you.[02:49].[02:51]just say i do ooh ooh ooh.[02:58]tell me right now baby.[03:01]tell me right now baby, baby.[03:04]just say i do ooh ooh ooh.[03:11]tell me right now baby.[03:14]tell me right now baby, baby.[03:17]oh.[03:17].[03:18]it's a beautiful nigt we're looking for something dumb to do.[03:24]hey baby i think i wanna marry you.[03:31]is it the look in your eyes or is it this dancing juice.[03:38]who cares baby, i think i wanna marry you.[03:42].";
songLy[5]="[00:00]��������.[00:03]����:���Ӻ� ����:���Ӻ�.[00:06]�ݳ����ܻ���.[00:12].[00:20]�����ҵ�ȫ��.[00:24]�����ҽ���Ψһ�Ķ�ע.[00:28]ֻ����һ������.[00:31]������Թ�޻�ȫ�ĵĸ���.[00:37]�������������.[00:41]����µ������Ϳ.[00:45]�쳾ǧɽ����·.[00:49]�ҿ��Գ���ĺĺ.[00:53]����һ���ҵ�·.[00:57]������һ����ͣ�ĽŲ�.[01:01]�����߳�һƬ���.[01:04]���㾡�������ĵ�׷��.[01:10]������������;.[01:14]���п�������ʹ��.[01:18]��������˼�·.[01:22]�ҿ��Է�첹��.[01:28]������������ǧ�����.[01:31]�����컻һЩ�������Ҹ�.[01:37]���㹻������.[01:39]���㹻������.[01:41]����Ҫ��Ҫ���ں�.[01:45]��Ը���㿴���ҵ��˴�.[01:48]�������޻ڵķ�������.[01:54]ӵ�й�������.[01:55]�εĹ�������.[01:57]����׷������.[02:05].[02:18]����һ���ҵ�·.[02:22]������һ����ͣ�ĽŲ�.[02:26]�����߳�һƬ���.[02:29]���㾡�������ĵ�׷��.[02:34]������������;.[02:39]���п�������ʹ��.[02:43]��������˼�·.[02:47]�ҿ��Է�첹��.[02:53]������������ǧ�����.[02:56]�����컻һЩ�������Ҹ�.[03:02]���㹻������.[03:04]���㹻������.[03:06]����Ҫ��Ҫ���ں�.[03:10]��Ը���㿴���ҵ��˴�.[03:12]�������޻ڵķ�������.[03:18]ӵ�й�������.[03:20]�εĹ�������.[03:22]����׷������.[03:29].[03:31]������������ǧ�����.[03:33]�����컻һЩ�������Ҹ�.[03:38]���㹻������.[03:41]���㹻������.[03:43]����Ҫ��Ҫ���ں�.[03:47]��Ը���㿴���ҵ��˴�.[03:50]�������޻ڵķ�������.[03:55]ӵ�й�������.[03:57]�εĹ�������.[03:59]����׷������.[04:06].";
songLy[6]="";
function show(t)//��ʾ���  ����Ϊ���ֲ��ŵ�ʱ��
{
var div1=document.getElementById("lyr");//ȡ�ò�
document.getElementById("lyr").innerHTML=" ";//ÿ�ε��������ǰ��һ��
if(t<lytime[lytime.length-1])//�����ʱ�䣩
{
for(var k=0;k<lytext.length;k++)
{
if(lytime[k]<=t&&t<lytime[k+1])
{
scrollh=k*25;//�õ�ǰ�Ĺ������Ķ����ı�һ�еĸ߶�
div1.innerHTML+="<font color=red style=font-weight:bold>"+lytext[k]+"</font><br>";
}
else if(t<lytime[lytime.length-1])//��ͨ��ʾ  ���ú�ɫ��ʾ
div1.innerHTML+=lytext[k]+"<br>";
}
}
else//���������󣬺�ɫ��ʾ���һ��
{
for(var j=0;j<lytext.length-1;j++)
div1.innerHTML+=lytext[j]+"<br>";
div1.innerHTML+="<font color=red style=font-weight:bold>"+lytext[lytext.length-1]+"</font><br>";
}


}

function scrollBar()//���ù������Ĺ���   ��ʾ���
{
if(document.getElementById("lyr").scrollTop<=scrollh)
document.getElementById("lyr").scrollTop+=1;
if(document.getElementById("lyr").scrollTop>=scrollh+50)
document.getElementById("lyr").scrollTop-=1;
window.setTimeout("scrollBar()",delay);//ʵ�ֻ���Ч��
}

function getReady(i)//����ʾ���ǰ����׼������
{


var myDate = new Date();
/*var mytime= myDate.toLocaleTimeString();
var a=mytime.split(":");
StartTime = a[1]*60+a[2];�������ַ�����ʱ����60���������䣬û�ҵ�ԭ��*/
 StartTime =myDate.getTime()*0.001 ;//�����û�ȡ�������ķ���ʵ�ֵģ��տ�ʼ�ó�����ȡ��������⣬��Ϊ�˷���������ʧ��

var ly=songLy[i];//�õ����
//alert(ly);
var arrly=ly.split(".");//ת��������  split�ָ�����
for(var i=0;i<arrly.length;i++)
sToArray(arrly[i]);//����  �ں���ʵ��
sortAr();//����  �ں���ʵ��
/*for(var j=0;j<lytext.length;j++)
{
document.getElementById("lyr").innerHTML+=lytime[j]+lytext[j]+"<br>";
}*/
scrollBar();
}

function sToArray(str)//�����硰[02:02][00:24]û�뵽���㡱���ַ���ǰ��������
{
var left=0;//"["�ĸ���
var leftAr=new Array();
for(var k=0;k<str.length;k++)
{
if(str.charAt(k)=="[")//charAt ����ָ��λ�õ��ַ�
{
leftAr[left]=k;
left++;
}
}
if(left!=0)
{
for(var i=0;i<leftAr.length;i++)
{
lytext[tflag]=str.substring(str.lastIndexOf("]")+1);//�Ÿ�ʣ�ȥ��ǰ���ʱ��  substring��ȡ�ַ����н�������ָ���±�֮����ַ�  
lytime[tflag]=conSeconds(str.substring(leftAr[i]+1,leftAr[i]+6));//��ʱ��  ��ʱ���ʽ����ת��
tflag++;
}
}
//alert(str.substring(leftAr[0]+1,leftAr[0]+6));
}

function sortAr()//��ʱ����������ʱ��͸�ʵ�����
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

function conSeconds(t)//�����磺01��25��ʱ��ת�����룻
{
var m=t.substring(0,t.indexOf(":"));
var s=t.substring(t.indexOf(":")+1);
s=parseInt(s.replace(/\b(0+)/gi,""));//ȥ��ǰ��0   ���ַ�������Ϊ����
if(isNaN(s))
s=0;
var totalt=parseInt(m)*60+s;//֮ǰ�����ﻭ�����������������ʽ  ʹʱ�������һֱ������  �����˺ܾò��ҵ��������    �Ժ���Դ���Ͼ�����Ҫ��   ��Ϊ��������ܿ���
//alert(parseInt(s.replace(/\b(0+)/gi,"")));
if(isNaN(totalt))
return 0;
return totalt;
}

//��ȡʱ��************************************ �Լ�����һ��   ��ʹ�ò�������ʱ��
/*function getSeconds()//�õ���ǰ����������λ�õ�ʱ��
{
var t=getPosition();
t=t.toString();//����ת�����ַ���
var s=t.substring(0,t.lastIndexOf("."));//�õ���ǰ����
//alert(s);
return s;
}
function getPosition()//���ص�ǰ���ŵ�ʱ��λ��
{
var mm=document.getElementById("MediaPlayer1");
//var mmt=;
//alert(mmt);
return mm.CurrentPosition;
}*/
function getSeconds()//����ʱ��
{ 
var myDate = new Date();
/*var mytime= myDate.toLocaleTimeString();
var a=mytime.split(":");
FinishTime = a[1]*60+a[2];*/
//alert(times);

 FinishTime=myDate.getTime()*0.001;//��ȥһ����ʱ�䣬Ϊ�˵�����ʣ���Ϊʱ�����Լ����õģ����ͬ���е�С���⣬�����ֶ����µ�����ʵ�ʱ����
 var s=FinishTime-StartTime;
return s;
}



function mPlay()//��ʼ����
{
 
var ms=getSeconds();//�޸�************************************

if(isNaN(ms))
show(0);
else
show(ms);


}

function comeOn(i)//��ʼ����
{
	for(var m=0;m<lytext.length;m++)
{ lytext[m]="";
  lytime[m]="";//ÿ�����һ��
}
   tflag=0;/*����ÿ����ǰ���һ�£���Ȼ��ʹǰ������ĸ�ʳ����ں���ĸ�������У��±�ҲҪ��գ���Ϊ��ȫ�ֱ�������Ȼ�±�һֱ������ʹ��������ĸ�ʲ���ʾ*/
    getReady(i);
	window.setInterval("mPlay()",1000);
	
	 }

