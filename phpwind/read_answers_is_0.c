/*
���� http://www.testroad.org/questions ҳ�棬�ѵ�ǰҳ�����лش���Ϊ0�����ӱ��������Ȼ���������������һ��ҳ�档

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

	//��ȡδ���ش�������б��ش���==0��
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

	//��ȡδ���ش������������
	len = lr_paramarr_len("list");

	//�ж���������ڻش���Ϊ0�����⣬������ű�
	if(len == 0){
		lr_output_message("û�лش���Ϊ0������");
		return 0;
	}

	for(i = 1 ; i<=len/2;i++)
	{
		//ѭ����ȡ��������
		str = lr_paramarr_idx("list",i);

		//��ȡ�����а�����ַid�ͱ���Ĳ��֣���ת��
		str = (char *)my_substr(str,"question/","</a>");
		lr_convert_string_encoding(str,LR_ENC_UTF8,LR_ENC_SYSTEM_LOCALE,"info");

		str = lr_eval_string("{info}");

		//ѡȡ�����У�id��
		id = (char *)my_substr(str,"","\"");

		//��ȡ�����У����������
		name = (char *)my_substr(str,"blank\" >  ","");
		lr_output_message("�ش���Ϊ0�ı��� �� %s",name);
		strcpy(ulist[i-1],id);
	}
	//���ѡȡid�ţ�ƴװ��Ҫ�򿪵�����
	index = rand()%(i-1);
	strcpy(url,"URL=http://www.testroad.org/question/");
	strcat(url,ulist[index]);
	lr_output_message("���ѡȡ������Ϊ �� %s",url);

	web_url("����򿪵���ҳ",
			url,
			LAST);
	return 0;
}

/*

	��ȡһ���ַ����У������Ӵ�֮�������
	char * src ��  ԭʼ�ַ���
	char * left��  ��߽磬Ϊ""���ͷ��ʼ
	char * right�� �ұ߽磬Ϊ""�򵽽�β

*/
char * my_substr(const char * src,char * left,char * right)
{
	char *dst = (char *)malloc(sizeof(char)*strlen(src)+1);
	int left_len = strlen(left);
	int i = 0,j = 0, k = 0;
	strcpy(dst,src);
	
	//��ȡ��ʼλ�úͽ���λ��
	if(left == ""){
		i = 0;
	}else{
		i = (int)((char *)strstr(dst,left)-dst)+left_len;
	}	
	//�����ʼλ��С��0�����ߴ����ַ������ȣ����ؿ�ֵ
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
