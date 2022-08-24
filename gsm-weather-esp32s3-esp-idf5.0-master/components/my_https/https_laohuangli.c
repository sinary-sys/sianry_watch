#include "https_laohuangli.h"
#include "main.h"
#include "https.h"




uint8_t https_laohuangli_file_write(char *buf)
{

	const char *config_fime_path = "/spiffs/laohuangli.json";
	uint32_t file_size=0;

	laohuangli_DEBUG("保存文件");
	file_size = system_get_file_size(config_fime_path);
    FILE* file = fopen(config_fime_path, "w+");
    if (file == NULL)
	{
        laohuangli_DEBUG("打开文件失败");
        return 1;
    }
	laohuangli_DEBUG("打开文件成功");
	fwrite(buf, 1, strlen(buf), file);

    fclose(file);
	return 0;

}

uint8_t https_laohuangli_file_read(char *buf,char *riqi)
{
	uint8_t r_dat = 0;
	const char *config_fime_path = "/spiffs/laohuangli.json";
	uint32_t file_size=0;

	laohuangli_DEBUG("读取文件");
	file_size = system_get_file_size(config_fime_path);
    FILE* file = fopen(config_fime_path, "r");
    if (file == NULL)
	{
        laohuangli_DEBUG("打开文件失败");
        r_dat = 1;
		goto exit;
    }
	laohuangli_DEBUG("打开文件成功");

    fread(buf, 1, file_size, file);

    fclose(file);

	if(strstr(buf,riqi))
	{
		r_dat = 0;
		laohuangli_DEBUG("匹配到老黄历数据");
		goto exit;
	}else
	{
		laohuangli_DEBUG("日期错误");
		r_dat = 2;
		goto exit;
	}

exit:
	return r_dat;
}

const char *json_laohuangli ="{\"reason\":\"successed\",\
\"result\":{\"id\":\"3872\",\"yangli\":\"2020-11-11\",\"yinli\":\"庚子(鼠)年九月廿六\",\"wuxing\":\"天上火 危执位\",\"\
chongsha\":\"冲鼠(壬子)煞北\",\"baiji\":\"戊不受田田主不祥 午不苫盖屋主更张\",\"jishen\":\"普护 青龙\",\"yi\":\
\"嫁娶 纳采 订盟 祭祀 冠笄 裁衣 伐木 作梁 架马 定磉 开柱眼 作灶 移徙 安床 畋猎 结网 开池 开厕 除服 成服 启钻 入殓 移柩 安葬\",\
\"xiongshen\":\"天吏 五虚\",\"ji\":\"盖屋 造船 动土 破土\"},\"error_code\":0}";

//获取老黄历
int https_get_LaoHuangLi(char * riqi,_laohuangli_data  *read_buf)
{

	int res=0;
	int i=0;
	int return_dat=0;
	char *http_recv_buff=NULL;
	char buf[256];
	uint8_t file_status = 0;
	if(read_buf==NULL)
		return 1;

	http_recv_buff = (char*)heap_caps_malloc(1024*2, MALLOC_CAP_SPIRAM);
	file_status = https_laohuangli_file_read(http_recv_buff,riqi);
	if(file_status == 0)
	{
		laohuangli_DEBUG("文件中找到数据不再从网络获取\r\n");
		goto enter;

	}
	memset(http_recv_buff,0x00,1024*2);
	laohuangli_DEBUG("开始获取\r\n");
	sprintf(buf,"%s%s",HTTPS_laohuangli,riqi);
	//sprintf(buf,"%s2014-09-09",HTTPS_laohuangli);

	res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
	//sprintf(http_recv_buff,"%s",json_laohuangli);

enter:
	if(res==0)
	{

		if(strstr((char *)http_recv_buff, "successed")==NULL)
		{
			laohuangli_DEBUG("数据错误\r\n");
			if(strstr((char *)http_recv_buff, "日志不能为空"))
			{
				return_dat= -2;
			}
			if(strstr((char *)http_recv_buff, "超过每日可允许请求次数"))
			{
				return_dat= -1;
			}

		}else
		{
			if(file_status != 0)
			{
				https_laohuangli_file_write(http_recv_buff);
			}


			laohuangli_DEBUG("获取到的数据:%s\r\n",http_recv_buff);
			laohuangli_DEBUG("开始解析数据\r\n");
			char *json_data = http_recv_buff;
			cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄
			cJSON *results = cJSON_GetObjectItem(json_A,"result");

			cJSON *data;

			data = cJSON_GetObjectItem(results, "id");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->id,"%s",data->valuestring);
			}else
			{

				sprintf(read_buf->id,"%s","NULL");
			}
			laohuangli_DEBUG("id:%s\r\n",read_buf->id);


			data = cJSON_GetObjectItem(results, "yangli");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->yangli,"%s",data->valuestring);
			}else
			{

				sprintf(read_buf->yangli,"%s","NULL");
			}
			laohuangli_DEBUG("阳历:%s\r\n",read_buf->yangli);


			data = cJSON_GetObjectItem(results, "yinli");
			if(data->valuestring!=NULL)
			{
				laohuangli_DEBUG("阴历:%s\r\n",data->valuestring);
				sprintf(read_buf->yinli,"%s",data->valuestring);
			}else
			{
				laohuangli_DEBUG("阴历:%s\r\n","NULL");
				sprintf(read_buf->yinli,"%s","NULL");
			}

			data = cJSON_GetObjectItem(results, "wuxing");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->wuxing,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->wuxing,"%s","NULL");
			}
			laohuangli_DEBUG("五行:%s\r\n",read_buf->wuxing);

			data = cJSON_GetObjectItem(results, "chongsha");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->chongsha,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->chongsha,"%s","NULL");
			}
			laohuangli_DEBUG("冲煞:%s\r\n",read_buf->chongsha);

			data = cJSON_GetObjectItem(results, "baiji");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->baiji,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->baiji,"%s","NULL");
			}
			laohuangli_DEBUG("彭祖百忌:%s\r\n",read_buf->baiji);

			data = cJSON_GetObjectItem(results, "jishen");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->jishen,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->jishen,"%s","NULL");
			}
			laohuangli_DEBUG("吉神宜趋:%s\r\n",read_buf->jishen);

			data = cJSON_GetObjectItem(results, "yi");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->yi,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->yi,"%s","NULL");
			}
			laohuangli_DEBUG("宜:%s\r\n",read_buf->yi);

			data = cJSON_GetObjectItem(results, "xiongshen");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->xiongshen,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->xiongshen,"%s","NULL");
			}
			laohuangli_DEBUG("凶神宜忌:%s\r\n",read_buf->xiongshen);

			data = cJSON_GetObjectItem(results, "ji");
			if(data->valuestring!=NULL)
			{
				sprintf(read_buf->ji,"%s",data->valuestring);
			}else
			{
				sprintf(read_buf->ji,"%s","NULL");
			}
			laohuangli_DEBUG("忌:%s\r\n",read_buf->ji);


			cJSON_Delete(json_A);
		}
	}else
	{
		laohuangli_DEBUG("获取失败:%d\r\n", res);
		return_dat= -3;
	}
	heap_caps_free(http_recv_buff);
	return return_dat;
}



