#include "https_bilibili.h"
#include "main.h"
#include "https.h"


int https_get_bilibili_fensi(void)
{
  int res = 0;
  char buf[50];
  
  res = HTTP_Get_bilibili(system_data.bilibili_Data.id,&system_data.bilibili_Data);
  if(res)
  {
    https_bilibili_DEBUG("获取失败\r\n");
    return -1;
  }
  return 0;
}

int https_get_bilibili_bofang(void)
{
  int res = 0;
  char buf[50];
  
  res = HTTP_Get_bilibili_bofang(system_data.bilibili_Data.id,&system_data.bilibili_Data);
  if(res)
  {
    https_bilibili_DEBUG("获取失败\r\n");
    return -1;
  }
  return 0;
}

int HTTP_Get_bilibili_bofang(char * id,_bilibili_Data  *read_buf)
{

  int res=0;
  int i=0;
  int return_dat=0;
  char *http_recv_buff=NULL;
  char buf[256];
  if(read_buf==NULL)
   return 1;

  http_recv_buff = (char*)os_malloc(1024*2);


  https_bilibili_DEBUG("开始获取播放量\r\n");
  sprintf(buf,"%s%s",HTTPS_bilibili_bofang,id);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  { 

    char *str=strstr((char *)http_recv_buff, "}}"); 
    if(str==NULL)
    {     
      https_bilibili_DEBUG("播放量据错误\r\n");
      return_dat= -1;
    }else
    {
      https_bilibili_DEBUG("开始解析播放量\r\n");
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄 
      cJSON *data = cJSON_GetObjectItem(json_A,"data");
      cJSON *archive = cJSON_GetObjectItem(data,"archive");//视频
      cJSON *archive_view = cJSON_GetObjectItem(archive,"view");

      cJSON *article = cJSON_GetObjectItem(data,"article");//文章
      cJSON *article_view = cJSON_GetObjectItem(article,"view");
     

      https_bilibili_DEBUG("code: %s\n",cJSON_Print(cJSON_GetObjectItem(json_A, "code")));
      https_bilibili_DEBUG("archive_view: %s\n",cJSON_Print(cJSON_GetObjectItem(archive_view, "view")));
      https_bilibili_DEBUG("article_view: %s\n",cJSON_Print(cJSON_GetObjectItem(article_view, "view")));

      char * str = cJSON_Print(cJSON_GetObjectItem(archive_view, "view"));
      if(str!=NULL)
      {
        https_bilibili_DEBUG("视频播放量:%s\r\n",str);
        sprintf(read_buf->bofang,"%s",str);
      }else
      {
        https_bilibili_DEBUG("视频播放量:%s\r\n","NULL");
        sprintf(read_buf->bofang,"%s","NULL");        
      } 

      str = cJSON_Print(cJSON_GetObjectItem(article_view, "view"));
      if(str!=NULL)
      {
        https_bilibili_DEBUG("文章播放量:%s\r\n",str);
        sprintf(read_buf->wenzhang,"%s",str);
      }else
      {
        https_bilibili_DEBUG("文章播放量:%s\r\n","view");
        sprintf(read_buf->wenzhang,"%s","NULL");        
      }      

      cJSON_Delete(json_A); 
    }
  }else
  {
    https_bilibili_DEBUG("获取播放量失败:%d\r\n", res);
    return_dat= -3;
  }
  os_free(http_recv_buff);
  return return_dat;
}


int HTTP_Get_bilibili(char * id,_bilibili_Data  *read_buf)
{

  int res=0;
  int i=0;
  int return_dat=0;
  char *http_recv_buff=NULL;
  char buf[256];
  if(read_buf==NULL)
   return 1;

  http_recv_buff = (char*)os_malloc(1024*2);


  https_bilibili_DEBUG("开始获取粉丝\r\n");
  sprintf(buf,"%s%s",HTTPS_bilibili_fensi,id);
  res = HTTP_Read_Data(buf,NULL,http_recv_buff,GET_REQ);
  if(res==0)
  { 

    char *str=strstr((char *)http_recv_buff, "}}"); 
    if(str==NULL)
    {     
      https_bilibili_DEBUG("粉丝数据错误\r\n");
      return_dat= -1;
    }else
    {
      https_bilibili_DEBUG("开始解析粉丝\r\n");
      char *json_data = http_recv_buff;
      cJSON *json_A = cJSON_Parse(os_strchr(json_data, '{'));//获取整个大的句柄 
      cJSON *data = cJSON_GetObjectItem(json_A,"data");


      https_bilibili_DEBUG("code: %s\n",cJSON_Print(cJSON_GetObjectItem(json_A, "code")));
      https_bilibili_DEBUG("mid: %s\n",cJSON_Print(cJSON_GetObjectItem(data, "mid")));
      https_bilibili_DEBUG("following: %s\n",cJSON_Print(cJSON_GetObjectItem(data, "following")));
      https_bilibili_DEBUG("follower: %s\n",cJSON_Print(cJSON_GetObjectItem(data, "follower")));




      char * str = cJSON_Print(cJSON_GetObjectItem(data, "following"));
      if(str!=NULL)
      {
        https_bilibili_DEBUG("关注:%s\r\n",str);
        sprintf(read_buf->guanzhu,"%s",str);
      }else
      {
        https_bilibili_DEBUG("关注:%s\r\n","NULL");
        sprintf(read_buf->guanzhu,"%s","NULL");        
      } 

      str = cJSON_Print(cJSON_GetObjectItem(data, "follower"));
      if(str!=NULL)
      {
        https_bilibili_DEBUG("粉丝:%s\r\n",str);
        sprintf(read_buf->fensi,"%s",str);
      }else
      {
        https_bilibili_DEBUG("粉丝:%s\r\n","NULL");
        sprintf(read_buf->fensi,"%s","NULL");        
      }      

      cJSON_Delete(json_A); 
    }
  }else
  {
    https_bilibili_DEBUG("获取粉丝失败:%d\r\n", res);
    return_dat= -3;
  }
  os_free(http_recv_buff);
  return return_dat;
}