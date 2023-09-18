# 以HTTP异步请求为例子-

1.先设置全部异步请求完成和成功后的回调函数

```
//TODO LOGIC(设置完成回调函数,@author LXC) 2023/9/7 0007 10:11
asyncManage_->SetOnComplete(...);

//TODO LOGIC(设置成功回调函数,@author LXC) 2023/9/7 0007 10:11
asyncManage_->SetOnSuccess(...);
```



2.添加任务

```
下面的01，02是同时请求。

//添加01任务
HttpRequestTask httpTask01 = std::make_unique<HttpRequestTask>();

//设置这个请求的成功结果回调函数-伪代码-表示回调到Test类的HttpTask01Result函数
httpTask01->SetOnResultCallback(&Test::HttpTask01Result);

asyncManage_->AddTask(std::move(httpTask01));

//添加02任务
HttpRequestTask httpTask02 = std::make_unique<HttpRequestTask>();

//设置这个请求的成功结果回调函数-伪代码-表示回调到Test类的HttpTask02Result函数
httpTask02->SetOnResultCallback(&Test::HttpTask02Result);

asyncManage_->AddTask(std::move(httpTask02));
```



3.子任务

```
void Test::HttpTask01Result(HttpRequestTask* httpTask01){
	HttpRequestTask httpTask01_01 = std::make_unique<HttpRequestTask>();
	
	//设置这个请求的成功结果回调函数-伪代码-表示回调到Test类的HttpTask01_01Result函数
	httpTask01_01->SetOnResultCallback(&Test::HttpTask01_01Result);
	
	//在这个01任务下面添加01子任务
	httpTask01->AddTask(std::move(httpTask01_01));
	
	HttpRequestTask httpTask01_02 = std::make_unique<HttpRequestTask>();
	
	//设置这个请求的成功结果回调函数-伪代码-表示回调到Test类的HttpTask01_02Result函数
	httpTask01_02->SetOnResultCallback(&Test::HttpTask01_02Result);
	
	//在这个01任务下面添加02子任务
	httpTask01->AddTask(std::move(httpTask01_02));
}

//....以此类推-嵌套任务
```



4.开始任务

```
asyncManage_->HandleTask()
```