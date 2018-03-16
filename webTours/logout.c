logout()
{
	lr_output_message("安全退出系统");
    
	lr_start_transaction("Logout");
	web_url("SignOff Button", 
		"URL={url}welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Logout",LR_AUTO);
}
