//
// Created by Administrator on 2023/9/18 0018.
//

#include "async_manage.h"
#include "async_task_util.h"

namespace async{

    AsyncManage::AsyncManage() {

    }

    AsyncManage::~AsyncManage() {

    }

    void AsyncManage::AddTask(std::unique_ptr<AsyncTask> asyncTask) {
        auto onAsyncTaskSuccessCallback = [this] { OnAsyncSuccess(); };
        asyncTask->SetOnAsyncTaskSuccessCallback(onAsyncTaskSuccessCallback);

        auto onAsyncTaskCompleteCallback = [this] { OnAsyncComplete(); };
        asyncTask->SetOnAsyncTaskCompleteCallback(onAsyncTaskCompleteCallback);

        asyncTasks_.insert(std::move(asyncTask));
    }

    void AsyncManage::OnAsyncSuccess() {
        bool success = AsyncTaskUtil::CheckTaskSuccess(asyncTasks_);

        if(success){
            if(onSuccess_){
                onSuccess_();
            }
        }

        if(!success){
            if(onFail_){
                onFail_();
            }
        }
    }

    void AsyncManage::OnAsyncComplete() {
        bool complete = AsyncTaskUtil::CheckTaskComplete(asyncTasks_);

        if(complete){
            if(isHandle_){
                asyncTasks_.clear();
            }

            if(onComplete_){
                onComplete_();
            }
        }
    }

    void AsyncManage::HandleTask() {
        isHandle_ = false;
        //TODO LOGIC(如何没有任务直接返回,@author LXC) 2023/9/19 0019 15:38
        if(asyncTasks_.empty()){
            OnAsyncSuccess();

            OnAsyncComplete();
            return;
        }

        for (const auto& asyncTask: asyncTasks_) {
            asyncTask->HandleTask();
        }

        isHandle_ = true;

        bool complete = AsyncTaskUtil::CheckTaskComplete(asyncTasks_);
        if(complete){
            asyncTasks_.clear();
        }

    }

    void AsyncManage::SetOnComplete(OnceClosure onComplete) {
        onComplete_ = std::move(onComplete);
    }

    void AsyncManage::SetOnSuccess(OnceClosure onSuccess) {
        onSuccess_ = std::move(onSuccess);
    }

    void AsyncManage::SetOnFail(OnceClosure onFail) {
        onFail_ = std::move(onFail);
    }
}