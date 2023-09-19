//
// Created by Administrator on 2023/9/18 0018.
//

#include "async_task.h"
#include "async_task_util.h"


namespace async{

    AsyncTask::AsyncTask() {

    }

    AsyncTask::~AsyncTask() {

    }

    void AsyncTask::HandleTask() {
        complete_num_.fetch_add(1);
        success_num_.fetch_add(1);
    }

    void AsyncTask::OnComplete() {
        NotificationComplete();
    }

    void AsyncTask::OnSuccess() {
        isHandle_ = false;

        //TODO LOGIC(运行成功后再运行子任务,@author LXC) 2023/9/13 0013 10:53
        for (const auto& childAsyncTask: childAsyncTasks_) {
            childAsyncTask->HandleTask();
        }

        isHandle_ = true;

        bool complete = AsyncTaskUtil::CheckTaskComplete(childAsyncTasks_);
        if(complete){
            childAsyncTasks_.clear();
        }

        //TODO LOGIC(当子任务都成功后-则-1,@author LXC) 2023/9/13 0013 14:32
        NotificationSuccess();
    }

    void AsyncTask::AddChildTask(std::unique_ptr<AsyncTask> childAsyncTask) {
        auto onAsyncTaskSuccessCallback = [this] { OnAsyncSuccess(); };
        childAsyncTask->SetOnAsyncTaskSuccessCallback(onAsyncTaskSuccessCallback);

        auto onAsyncTaskCompleteCallback = [this] { OnAsyncComplete(); };
        childAsyncTask->SetOnAsyncTaskCompleteCallback(onAsyncTaskCompleteCallback);

        childAsyncTasks_.insert(std::move(childAsyncTask));
    }

    void AsyncTask::SetOnAsyncTaskSuccessCallback(AsyncTask::OnAsyncTaskSuccessCallback onAsyncTaskSuccessCallback) {
        onAsyncTaskSuccessCallback_ = std::move(onAsyncTaskSuccessCallback);
    }

    void AsyncTask::SetOnAsyncTaskCompleteCallback(AsyncTask::OnAsyncTaskCompleteCallback onAsyncTaskCompleteCallback) {
        onAsyncTaskCompleteCallback_ = std::move(onAsyncTaskCompleteCallback);
    }

    int AsyncTask::complete_num() {
        return complete_num_.load();
    }

    int AsyncTask::success_num() {
        return success_num_.load();
    }

    void AsyncTask::OnAsyncSuccess() {
        NotificationSuccess();
    }

    void AsyncTask::OnAsyncComplete() {
        NotificationComplete();
    }

    void AsyncTask::NotificationSuccess() {
        if(!AsyncTaskUtil::CheckTaskSuccess(childAsyncTasks_)){
            return;
        }
        success_num_.fetch_sub(1);
        if(onAsyncTaskSuccessCallback_){
            onAsyncTaskSuccessCallback_();
        }
    }

    void AsyncTask::NotificationComplete() {
        if(!AsyncTaskUtil::CheckTaskComplete(childAsyncTasks_)){
            return;
        }

        if(isHandle_){
            childAsyncTasks_.clear();
        }

        complete_num_.fetch_sub(1);
        if(onAsyncTaskCompleteCallback_){
            onAsyncTaskCompleteCallback_();
        }
    }
}