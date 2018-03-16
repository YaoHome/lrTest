login()
{
	web_set_max_html_param_len("1000");
	lr_save_string("http://localhost/phpwind/","url");

   	web_reg_save_param("token",
		"LB=csrf_token\" value=\"",
		"RB=\"/",
		LAST);
	
	lr_start_transaction("登录事务");

	web_url("Login", 
    "URL={url}index.php?m=u&c=login",  
    LAST ); 

	web_submit_data("checkusername", 
		"Action={url}index.php?m=u&c=register&a=checkusername", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}index.php?m=u&c=register", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=csrf_token", "Value={token}", ENDITEM, 
		"Name=username", "Value={login_username}", ENDITEM, 
		LAST);

	web_reg_save_param("login_vp",
		"LB=_statu=",
		"RB=\"",
		LAST);
	
	web_custom_request("submit", 
					   "Method=POST", 
					   "URL={url}index.php?m=u&c=login&a=dologin", 
					   "Body=username={login_username}&password={login_pwd}&csrf_token={token}&csrf_token={token}", 
					   LAST ); 
	web_reg_find("SaveCount=count",
		"Text={login_username}",
		LAST);
	web_url("index.php_3", 
		"URL={url}index.php?m=u&c=login&a=welcome&_statu={login_vp}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}index.php", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=themes/site/default/images/message/msg.wav", ENDITEM, 
		"Url=res/js/dev/pages/common/global.js?v=20130227", ENDITEM, 
		"Url=res/js/dev/jquery.js?v=20130227", ENDITEM, 
		"Url=res/js/dev/util_libs/lazySlide.js?v=20130227", ENDITEM, 
		"Url=res/js/dev/pages/common/sidebarMain.js?v=20130227", ENDITEM, 
		"Url=res/js/dev/pages/bbs/postGuide.js?v=20130227", ENDITEM, 
		LAST);
	if(strcmp(lr_eval_string("{login_vp}"),"") == 0){
		lr_output_message("登录失败");
		lr_end_transaction("登录事务", LR_FAIL);
	
	}else{
		lr_output_message("登录成功，用户名为：%s",lr_eval_string("{login_username}"));
		lr_end_transaction("登录事务", LR_PASS);
	}
	return 0;
}
