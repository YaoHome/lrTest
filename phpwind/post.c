/*

	登录后在论坛首页随机选择板块发帖 --参数化

*/
post()
{
	char * title = (char *)malloc(1000);
	char * ref_url = (char *)malloc(1000);

	lr_save_datetime("%m%d %H:%M:%S",TIME_NOW,"time_now");
	title = lr_eval_string("{login_username} send info in {time_now}");
	lr_save_string(title,"title");
	
	lr_start_transaction("发帖子");
	lr_output_message("开始发帖子操作");
	web_submit_data("minilist", 
		"Action={url}index.php?m=message&c=notice&a=minilist", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}index.php", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={token}", ENDITEM, 
		EXTRARES, 
		"Url=res/js/dev/util_libs/ajaxForm.js?v=20130227", ENDITEM, 
		"Url=res/js/dev/util_libs/scrollFixed.js?v=20130227", ENDITEM, 
		LAST);

	web_submit_data("list", 
		"Action={url}index.php?c=forum&a=list", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}index.php", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={token}", ENDITEM, 
		"Name=withMyforum", "Value=1", ENDITEM, 
		LAST);

	web_url("index.php_6", 
		"URL={url}index.php?c=post&fid={fid}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}index.php", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=res/js/dev/jquery.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/global.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/util_libs/ajaxForm.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/windeditor.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/ui_libs/dialog/dialog.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/themes/buyiui/buyiui.css?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/css/editor_content.css?v=", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/bbcode/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/insertFile/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/insertEmoticons/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/insertPhoto/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/insertCode/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/openApp/plugin.js?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		"Url=res/js/dev/windeditor/plugins/insertCode/syntaxHihglighter/styles/shCoreDefault.css?v=20130227", "Referer={url}index.php?c=post&fid={fid}", ENDITEM, 
		LAST);

	web_url("index.php_7", 
		"URL={url}index.php?m=emotion&type=bbs&csrf_token={token}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}index.php?c=post&fid={fid}", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param("state",
		"LB=state\":\"",
		"RB=\",",
		"Search=Body",
		LAST);

	web_reg_save_param("tid",
		"LB=tid=",
		"RB=&",
		"Search=Body",
		LAST);
	web_submit_data("index.php_8", 
		"Action={url}index.php?c=post&a=doadd&_json=1&fid={fid}", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}index.php?c=post&fid={fid}", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=atc_title", "Value={title}", ENDITEM, 
		"Name=atc_content", "Value={title}", ENDITEM, 
		"Name=pid", "Value=", ENDITEM, 
		"Name=tid", "Value=", ENDITEM, 
		"Name=special", "Value=default", ENDITEM, 
		"Name=reply_notice", "Value=1", ENDITEM, 
		"Name=csrf_token", "Value={token}", ENDITEM, 
		LAST);

	web_url("read.php", 
		"URL={url}read.php?tid={tid}&fid={fid}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}index.php?c=post&fid={fid}", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=res/js/dev/jquery.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/global.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/ui_libs/dialog/dialog.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		LAST);

	web_submit_data("index.php_9", 
		"Action={url}?m=u&a=showcredit", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}read.php?tid={tid}&fid={fid}", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={token}", ENDITEM, 
		EXTRARES, 
		"Url=res/js/dev/pages/common/insertEmotions.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/sendMsgPop.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/likePlus.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/bbs/read.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/bbs/threadManage.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/userTag.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/pages/common/report.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		"Url=res/js/dev/util_libs/localStorage.js?v=20130227", "Referer={url}read.php?tid={tid}&fid={fid}", ENDITEM, 
		LAST);
	if(strcmp(lr_eval_string("{state}"),"success") == 0){
		lr_output_message("发帖成功，帖子标题为：%s",lr_eval_string("{title}"));
		lr_end_transaction("发帖子", LR_PASS);
	}else{
		lr_output_message("发帖失败");
		lr_end_transaction("发帖子", LR_FAIL);
	}
	return 0;
}