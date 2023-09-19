//
// Created by Administrator on 2023/9/18 0018.
//

#ifndef ASYNC_TASK_ASYNC_TASK_H
#define ASYNC_TASK_ASYNC_TASK_H
#include <iostream>
#include <set>
#include <functional>
#include <memory>
#include <atomic>
#include "async.h"

namespace async{
    class AsyncTask {
    public:
        explicit AsyncTask();

        AsyncTask(const AsyncTask&) = delete;
        AsyncTask& operator=(const AsyncTask&) = delete;

        virtual ~AsyncTask();

        using OnAsyncTaskCompleteCallback = OnceClosure;
        using OnAsyncTaskSuccessCallback = OnceClosure;
        using AddChildTaskCallback = std::function<std::unique_ptr<AsyncTask>()>;

        //TODO FUN_EXPLAIN(运行任务,@author LXC) 2023/9/12 0012 21:55
        virtual void HandleTask();

        //TODO FUN_EXPLAIN(完成,@author LXC) 2023/9/12 0012 22:04
        virtual void OnComplete();

        //TODO FUN_EXPLAIN(成功,@author LXC) 2023/9/7 0007 9:18
        virtual void OnSuccess();

        //TODO FUN_EXPLAIN(该异步任务运行完后运行,@author LXC) 2023/9/12 0012 21:55
        void AddChildTask(std::unique_ptr<AsyncTask> childAsyncTask);

    public:
        //TODO FUN_EXPLAIN(设置任务成功的回调函数,@author LXC) 2023/9/13 0013 14:36
        void SetOnAsyncTaskSuccessCallback(OnAsyncTaskSuccessCallback onAsyncTaskSuccessCallback);

        //TODO FUN_EXPLAIN(设置任务完成的回调函数,@author LXC) 2023/9/13 0013 14:36
        void SetOnAsyncTaskCompleteCallback(OnAsyncTaskCompleteCallback onAsyncTaskCompleteCallback);

        int complete_num();

        int success_num();

    protected:
        std::set<std::unique_ptr<AsyncTask>> childAsyncTasks_;

        std::atomic<int> complete_num_{0};

        std::atomic<int> success_num_{0};

        bool isHandle_;

        OnAsyncTaskCompleteCallback onAsyncTaskCompleteCallback_;

        OnAsyncTaskSuccessCallback onAsyncTaskSuccessCallback_;
    private:
        void OnAsyncSuccess();

        void OnAsyncComplete();

        void NotificationSuccess();

        void NotificationComplete();
    };

}



#endif //ASYNC_TASK_ASYNC_TASK_H
