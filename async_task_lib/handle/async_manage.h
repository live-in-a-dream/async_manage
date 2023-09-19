//
// Created by Administrator on 2023/9/18 0018.
//

#ifndef ASYNC_TASK_ASYNC_MANAGE_H
#define ASYNC_TASK_ASYNC_MANAGE_H
#include "async_task.h"

namespace async{
    class AsyncManage {
    public:
        explicit AsyncManage();

        AsyncManage(const AsyncManage&) = delete;
        AsyncManage& operator=(const AsyncManage&) = delete;

        ~AsyncManage();
    public:
        //TODO FUN_EXPLAIN(添加异步任务,@author LXC) 2023/9/12 0012 21:39
        void AddTask(std::unique_ptr<AsyncTask> asyncTask);

        //TODO FUN_EXPLAIN(当成功的时候回调,@author LXC) 2023/9/18 0018 19:36
        void OnAsyncSuccess();

        //TODO FUN_EXPLAIN(当完成的时候回调,@author LXC) 2023/9/18 0018 19:36
        void OnAsyncComplete();

        //TODO FUN_EXPLAIN(成功请求后-1,@author LXC) 2023/9/7 0007 9:18
        void HandleTask();

        //TODO FUN_EXPLAIN(设置完成的回调,@author LXC) 2023/9/7 0007 9:18
        void SetOnComplete(OnceClosure onComplete);

        //TODO FUN_EXPLAIN(设置成功的回调,@author LXC) 2023/9/7 0007 9:18
        void SetOnSuccess(OnceClosure onSuccess);

        //TODO FUN_EXPLAIN(设置失败的回调,@author LXC) 2023/9/7 0007 9:18
        void SetOnFail(OnceClosure onFail);

    private:
        OnceClosure onComplete_;

        OnceClosure onSuccess_;

        OnceClosure onFail_;

        std::set<std::unique_ptr<AsyncTask>> asyncTasks_;

        bool isHandle_;
    };
}


#endif //ASYNC_TASK_ASYNC_MANAGE_H
