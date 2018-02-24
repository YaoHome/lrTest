/*
Created on 2018.1.25
By yao
*/

/*

	获取一个字符串中，两个子串之间的内容
	char * src ：  原始字符串
	char * left：  左边界，为""则从头开始
	char * right： 右边界，为""则到结尾

*/
char * y_substr(const char * src,char * left,char * right)
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

/*

	重写strcpy接口，实现将字符串赋值给一个字符数组
	char * dest ：  被赋值的字符数组
	char * source :  字符串

*/
char * y_strcpy(char * dest,const char * source){
	int i = 0;
	while(*(source+i) != '\0'){
		*(dest+i) = *(source+i);
		i++;
	}
	*(dest+i) = '\0';
	return dest;	
}

/*

	当字符为字母时，大小写互换，当字符为数字时，原样输出，当有其它字符出现时，结束操作，返回已处理的字符串
	char * str ：  需要处理的字符串

*/
char * y_exchange(char * str){
	char * p = (char *)malloc(1024);
	int i = 0;
	strcpy(p,str);
	while (*(p+i) != '\0') {
		i++;
		if(*(p+i-1) <= 122 && *(p+i-1) >= 97) {
			*(p+i-1) = putchar(toupper(*(p+i-1)));
		}
		else if(*(p+i-1) <= 90 && *(p+i-1) >= 65) {
			*(p+i-1) = putchar(tolower(*(p+i-1)));
		}
		else if(*(p+i-1) <= 57 && *(p+i-1) >= 48) {
			continue;
		}else{
			break;
		}

	} 
	return p;
}

/*

	重写strcat接口，实现将字符串追加到字符数组后面
	char * to ：  被追加的字符数组
	char * from :  字符串

*/
char * y_strcat(char *to, const char *from){
	int i = 0;
	while(*to++ != '\0'){}
	to--;
	while(*(from+i) != '\0'){
		*(to+i) = *(from+i);
		i++;
	}
	*(to+i) = '\0';
	return to;
}

/*

	重写srtrchr函数，实现查找字符串中指定字符最后一次出现时，所有的字符输出，将其中指定字符串的小写字母
	变成对应的大写字母并输出。如字符串“testroad”,指定字符串为't'，则输出"Troad"
	char * str ：  被查找的字符串
	char c :  字符关键字

*/
char * y_strrchr(const char *str, char c ){
	char *p = (char *)malloc(50);
	int i = 0;

	strcpy(p,str);
	while(*p++ != '\0'){
		i++;
	}
	while(*p-- != c){
		i--;
		if(i+1<0){
			return;
		}
	}
	p++;
	*p = putchar(toupper(*p));
	return p;
}



































