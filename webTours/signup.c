/*
	�ýű�Ŀ��Ϊȷ��0128��ҵ��ʹ���û�������
	
	By��yao
*/
Action()
{

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/WebTours/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	web_url("login.pl", 
		"URL=http://127.0.0.1:1080/WebTours/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/home.html", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("SaveCount=signup",
		"Text=Thank you,",
		LAST);
	
	web_reg_find("SaveCount=signed",
		"Text=Please choose another",
		LAST);
	
	lr_start_transaction("ע���û�");

	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:1080/WebTours/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={username}", ENDITEM, 
		"Name=firstName", "Value={username}", ENDITEM, 
		"Name=lastName", "Value={username}", ENDITEM, 
		"Name=address1", "Value={username}", ENDITEM, 
		"Name=address2", "Value={username}", ENDITEM, 
		"Name=register.x", "Value=49", ENDITEM, 
		"Name=register.y", "Value=5", ENDITEM, 
		LAST);
	if(atoi(lr_eval_string("{signup}"))==0 && atoi(lr_eval_string("{signed}"))==0)
	{
		lr_end_transaction("ע���û�", LR_FAIL);
	}else{
		lr_output_message("�û���ע��ɹ������Ѵ��ڣ��û��� �� %s",lr_eval_string("{username}"));
		lr_end_transaction("ע���û�", LR_PASS);
	}
	return 0;
}