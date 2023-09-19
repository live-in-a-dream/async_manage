//
// Created by Administrator on 2023/9/18 0018.
//

#include "async_task_util.h"
#include "async_task.h"


namespace async{


    bool AsyncTaskUtil::CheckTaskComplete(const std::set<std::unique_ptr<AsyncTask>> &asyncTasks) {
        uint64_t complete_num = 0;
        for (const auto& childAsyncTask: asyncTasks) {
            if(childAsyncTask->complete_num() == 0){
                complete_num++;
            }
        }
        return complete_num == asyncTasks.size();
    }

    bool AsyncTaskUtil::CheckTaskSuccess(const std::set<std::unique_ptr<AsyncTask>> &asyncTasks) {
        uint64_t success_num = 0;
        for (const auto& childAsyncTask: asyncTasks) {
            if(childAsyncTask->success_num() == 0){
                success_num++;
            }
        }
        return success_num == asyncTasks.size();
    }

}
