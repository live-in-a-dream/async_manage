#ifndef ASYNC_TASK_GLOBAL_H
#define ASYNC_TASK_GLOBAL_H
#include <functional>
#define ASYNC_TASK __declspec(dllexport)


using OnceClosure = std::function<void()>;

#endif //ASYNC_TASK_GLOBAL_H
