/*
访问 http://www.testroad.org/questions 页面，把当前页面所有回答数为0的帖子标题输出。然后再随机访问其中一个页面。

By : yao

*/
Action()
{
	int i = 1;
	int len = 0;
	int index = 0;
	char * str = (char *)malloc(1000);
	char * id = (char *)malloc(200);
	char * name = (char *)malloc(1000);
	char url[200];
	char ulist[10][20];
	
    web_set_max_html_param_len("2000");

	//获取未被回答的问题列表（回答数==0）
	web_reg_save_param("list",
		"LB=<div class=\"answers \"",
		"RB=<ul class=\"taglist-inline ib\">",
		"Ord=all",
		LAST);

	web_url("questions", 
		"URL=http://www.testroad.org/questions", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	//获取未被回答过的问题条数
	len = lr_paramarr_len("list");

	//判断如果不存在回答数为0的问题，则结束脚本
	if(len == 0){
		lr_output_message("没有回答数为0的问题");
		return 0;
	}

	for(i = 1 ; i<=len/2;i++)
	{
		//循环获取问题内容
		str = lr_paramarr_idx("list",i);

		//获取内容中包含网址id和标题的部分，并转码
		str = (char *)my_substr(str,"question/","</a>");
		lr_convert_string_encoding(str,LR_ENC_UTF8,LR_ENC_SYSTEM_LOCALE,"info");

		str = lr_eval_string("{info}");

		//选取内容中，id号
		id = (char *)my_substr(str,"","\"");

		//获取内容中，标题的内容
		name = (char *)my_substr(str,"blank\" >  ","");
		lr_output_message("回答数为0的标题 ： %s",name);
		strcpy(ulist[i-1],id);
	}
	//随机选取id号，拼装成要打开的链接
	index = rand()%(i-1);
	strcpy(url,"URL=http://www.testroad.org/question/");
	strcat(url,ulist[index]);
	lr_output_message("随机选取的链接为 ： %s",url);

	web_url("随机打开的网页",
			url,
			LAST);
	return 0;
}

/*

	获取一个字符串中，两个子串之间的内容
	char * src ：  原始字符串
	char * left：  左边界，为""则从头开始
	char * right： 右边界，为""则到结尾

*/
char * my_substr(const char * src,char * left,char * right)
{
	char *dst = (char *)malloc(sizeof(char)*strlen(src)+1);
	int left_len = strlen(left);
	int i = 0,j = 0, k = 0;
	strcpy(dst,src);
	
	//获取开始位置和结束位置
	if(left == ""){
		i = 0;
	}else{
		i = (int)((char *)strstr(dst,left)-dst)+left_len;
	}	
	//如果开始位置小于0，或者大于字符串长度，返回空值
	if(i<0 || i>strlen(dst)){
		return "error";
	}
	dst = dst+i;
	if(right == ""){
		return dst;
	}else{
		j = (int)((char *)strstr(dst,right)-dst);
	}	

	*(dst+j) = '\0';
	return dst;
}
