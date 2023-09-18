//
// Created by Administrator on 2023/9/18 0018.
//

#ifndef ASYNC_TASK_ASYNC_TASK_UTIL_H
#define ASYNC_TASK_ASYNC_TASK_UTIL_H
#include <iostream>
#include <set>
#include <functional>
#include <memory>
#include <atomic>
#include "../async_task_global.h"


namespace async{

    class AsyncTask;

    class ASYNC_TASK AsyncTaskUtil {
    public:

        //TODO FUN_EXPLAIN(校验任务完成,@author LXC) 2023/9/13 0013 14:33
        static bool CheckTaskComplete(const std::set<std::unique_ptr<AsyncTask>>& asyncTasks);

        //TODO FUN_EXPLAIN(校验任务成功,@author LXC) 2023/9/13 0013 14:33
        static bool CheckTaskSuccess(const std::set<std::unique_ptr<AsyncTask>>& asyncTasks);

    };

}


#endif //ASYNC_TASK_ASYNC_TASK_UTIL_H
