login()
{
	web_reg_save_param("userSession",
		"LB=userSession value=",
		"RB=>",
		LAST);
	lr_output_message("����lr�Դ���Ʊϵͳ");
	web_url("WebTours", 
		"URL={url}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("Search=Body",
		"SaveCount=login_vp",
		"Text=Using the menu to the left",
		LAST);

    lr_output_message("��ʼ����==��¼");
	lr_start_transaction("Login");
	
	web_submit_data("login.pl", 
		"Action={url}login.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={url}nav.pl?in=home", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=JSFormSubmit", "Value=on", ENDITEM, 
		"Name=login.x", "Value=58", ENDITEM, 
		"Name=login.y", "Value=9", ENDITEM, 
		LAST);
	
	if(atoi(lr_eval_string("{login_vp}"))==0){
		lr_end_transaction("Login", LR_FAIL);
		lr_output_message("��¼ʧ��");
	}else{

		lr_end_transaction("Login", LR_PASS);
		lr_output_message("��¼�ɹ�����¼����%s",lr_eval_string("{username}"));
	}
}
