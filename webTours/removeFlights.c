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

	lr_output_message("开始事务==退票");

	//开始事务：退票
	lr_start_transaction("RemoveFlights");

	//获取当前用户存在的机票数
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

	lr_output_message("已存在票数为 : %s",lr_eval_string("{flightID_count}"));
	
	
	//验证是否退票成功
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

		//随机选择一张机票
		no = rand()%flNum;
		no = no+1;
	
		lr_output_message("要取消的机票号为 : %d",no);

		
		for(i=1;i<=flNum;i++){
			//增加选中机票的标示字段
			if(i==no){
				lr_save_int(no,"id");
				pt=lr_eval_string("{id}");
				strcat(rbTemp,pt);
				strcat(rbTemp,"=on&");	
			}

			sprintf(flID,"{flightID_%d}",i);

			//递归添加flightID
			strcat(rbTemp,"flightID=");
			strcat(rbTemp,lr_eval_string(flID));
			strcat(rbTemp,"&");

			//递归添加数据的后半段
			lr_save_int(i,"i");
			strI = lr_eval_string("{i}");
			strcat(rbTemp2,".cgifields=");
			strcat(rbTemp2,strI);
			strcat(rbTemp2,"&");

	//	lr_output_message("flight index : %d,flight id : %s",i,lr_eval_string(flID));

		}
	//	lr_output_message("rbTemp1 : %s,rbTemp2 : %s",rbTemp,rbTemp2);

		//补全要提交的数据内容
		strcpy(requestBody,rbTemp);
		strcat(requestBody,rbTemp2);
		strcat(requestBody,"removeFlights.x=39&removeFlights.y=2");
	}
	else if(flNum==1){
		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("当前只有一张机票，不做退票操作，直接退出");
		return 0;
	}else{

		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("当前不存在机票，直接退出");
		return 0;
	}
	
    lr_output_message("提交的退票数据为 : %s",requestBody);

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
		lr_output_message("取消订单失败");
	}else{
		lr_end_transaction("RemoveFlights", LR_PASS);
		lr_output_message("取消订单成功");
	}

}
