//
// Created by Administrator on 2023/9/19 0019.
//

#include "http_test.h"

HttpTest::HttpTest() {

}

HttpTest::~HttpTest() {

}


void HttpTest::OnNetError(int e) {
    if(onNetErrorCallback_){
        onNetErrorCallback_(e);
    }
}

void HttpTest::SetOnNetErrorCallback(HttpTest::OnNetErrorCallback onNetErrorCallback) {
    onNetErrorCallback_ = std::move(onNetErrorCallback);
}

void HttpTest::SetOnResultCallback(HttpTest::OnResultCallback onResultCallback) {
    onResultCallback_ = std::move(onResultCallback);
}

void HttpTest::SetOnHttpErrorCallback(HttpTest::OnHttpErrorCallback onHttpErrorCallback) {
    onHttpErrorCallback_ = std::move(onHttpErrorCallback);
}

void HttpTest::HandleTask() {
    AsyncTask::HandleTask();

    //开始请求...

    //成功
    {
        OnSuccess();
    }

    //失败
//    {
//        OnNetError(1);
//    }

    //完成
    OnComplete();

}

void HttpTest::OnSuccess() {

    //请求成功但是 是正确的数据-比如登录成功等等...
    {
        if(onResultCallback_){
            onResultCallback_(this,std::make_unique<std::string>("body"));
        }
    }


    //请求成功但是 不是正确的数据-比如密码错误等...
    {
        if(onHttpErrorCallback_){
            onHttpErrorCallback_(this,std::make_unique<std::string>("body"));
        }
    }

    AsyncTask::OnSuccess();
}


