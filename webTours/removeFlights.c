removeFlights()
{
	int flNum;
	int i;
	int no;
	char requestBody[1000]={'\0'};
	char rbTemp[1000]={'\0'};
	char rbTemp2[1000]={'\0'};
	char flID[256]={'\0'};
	char *pt;
	char *strI;

	lr_output_message("��ʼ����==��Ʊ");

	//��ʼ������Ʊ
	lr_start_transaction("RemoveFlights");

	//��ȡ��ǰ�û����ڵĻ�Ʊ��
	web_reg_save_param("flightID",
		"LB=name=\"flightID\" value=\"",
		"RB=\"",
		"Notfound=warning",
		"Ord=All",
		LAST);

	web_url("Itinerary Button", 
		"URL={url}welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={url}nav.pl?page=menu&in=home", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);

	lr_output_message("�Ѵ���Ʊ��Ϊ : %s",lr_eval_string("{flightID_count}"));
	
	
	//��֤�Ƿ���Ʊ�ɹ�
	web_reg_find("Search=Body",
		"SaveCount=remove_vp",
		"Text=Flight Transaction Summary",
		LAST);

	web_reg_find("Search=Body",
		"SaveCount=remove_vp2",
		"Text=No flights have been reserved",
		LAST);

	flNum = atoi(lr_eval_string("{flightID_count}"));

	strcpy(rbTemp,"Body=");
	if(flNum>1){

		//���ѡ��һ�Ż�Ʊ
		no = rand()%flNum;
		no = no+1;
	
		lr_output_message("Ҫȡ���Ļ�Ʊ��Ϊ : %d",no);

		
		for(i=1;i<=flNum;i++){
			//����ѡ�л�Ʊ�ı�ʾ�ֶ�
			if(i==no){
				lr_save_int(no,"id");
				pt=lr_eval_string("{id}");
				strcat(rbTemp,pt);
				strcat(rbTemp,"=on&");	
			}

			sprintf(flID,"{flightID_%d}",i);

			//�ݹ����flightID
			strcat(rbTemp,"flightID=");
			strcat(rbTemp,lr_eval_string(flID));
			strcat(rbTemp,"&");

			//�ݹ�������ݵĺ���
			lr_save_int(i,"i");
			strI = lr_eval_string("{i}");
			strcat(rbTemp2,".cgifields=");
			strcat(rbTemp2,strI);
			strcat(rbTemp2,"&");

	//	lr_output_message("flight index : %d,flight id : %s",i,lr_eval_string(flID));

		}
	//	lr_output_message("rbTemp1 : %s,rbTemp2 : %s",rbTemp,rbTemp2);

		//��ȫҪ�ύ����������
		strcpy(requestBody,rbTemp);
		strcat(requestBody,rbTemp2);
		strcat(requestBody,"removeFlights.x=39&removeFlights.y=2");
	}
	else if(flNum==1){
		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("��ǰֻ��һ�Ż�Ʊ��������Ʊ������ֱ���˳�");
		return 0;
	}else{

		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("��ǰ�����ڻ�Ʊ��ֱ���˳�");
		return 0;
	}
	
    lr_output_message("�ύ����Ʊ����Ϊ : %s",requestBody);

	web_custom_request("itinerary.pl",
		"URL={url}itinerary.pl",
		"Method=POST",
		"Referer={url}itinerary.pl",
		"Mode=HTML",
		"RecContentType=text/html",
		"Snapshot=t20.inf",
		requestBody,
		LAST);

	if(atoi(lr_eval_string("{remove_vp}"))==0 && atoi(lr_eval_string("{remove_vp2}"))==0){
		lr_end_transaction("RemoveFlights", LR_FAIL);
		lr_output_message("ȡ������ʧ��");
	}else{
		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("ȡ�������ɹ�");
	}

}
