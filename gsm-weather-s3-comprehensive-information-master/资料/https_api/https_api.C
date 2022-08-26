//获取本机IP http://icanhazip.com/
GET / HTTP/1.1
Accept: */*
Host: icanhazip.com


返回
HTTP/1.1 200 OK
Server: nginx
Date: Thu, 08 Oct 2020 06:26:19 GMT
Content-Type: text/plain; charset=UTF-8
Content-Length: 14
Connection: close
Access-Control-Allow-Origin: *
Access-Control-Allow-Methods: GET
x-rtfm: Learn about this site at http://bit.ly/icanhazip-faq and do not abuse the service.
x-node: icanhazip-dfw-1
x-donation: This site is expensive to run. You can donate BTC to 3LSp89k9qnMJBpV7AUNF3M2Eo1vatpkYpm
x-duck: 馃

153.34.19.121



//获取天气
GET /v3/weather/daily.json?key=Spomv8m-PvaAm5XCA&location=suzhou&language=zh-Hans&unit=c&start=0&days=5 HTTP/1.1
Accept:*/*
Host:api.seniverse.com



//获取当前城市
http://ip.ws.126.net/ipquery?ip=	//(这里跟IP地址)

GET /ipquery?ip=112.87.138.78 HTTP/1.1
Accept:*/*
Host:ip.ws.126.net




//返回
var lo="江苏省", lc="苏州市"; var localAddress={city:"苏州市", province:"江苏省"}


//中华万年历获取天气
http://wthrcdn.etouch.cn/weather_mini?city=苏州市


//老黄历
http://v.juhe.cn/laohuangli/d?date=2020-10-10&key=a5d96310d1119465e6a5017c28d866c5
//万年历
http://v.juhe.cn/calendar/day?date=2020-10-10&key=a18c301354a5835c70d31ee43ce5b42b



哔哩哔哩api //USRID是用户id  430380301
//粉丝数
https://api.bilibili.com/x/relation/stat?vmid=USRID&jsonp=jsonp
//播放量
https://api.bilibili.com/x/space/upstat?mid=USRID