//
// Created by Administrator on 2023/9/19 0019.
//

#ifndef ASYNC_TASK_HTTP_TEST_H
#define ASYNC_TASK_HTTP_TEST_H

#include "handle/async_task.h"

class HttpTest :public async::AsyncTask{

public:
    HttpTest();

    HttpTest(const HttpTest&) = delete;
    HttpTest& operator=(const HttpTest&) = delete;

    ~HttpTest() override;
public:

    using OnResultCallback = std::function<void(
            HttpTest* httpTest,
            std::unique_ptr<std::string> body
    )>;
    using OnHttpErrorCallback = std::function<void(
            HttpTest* httpTest,
            std::unique_ptr<std::string> body
    )>;

    using OnNetErrorCallback = std::function<void(int e)>;



    void SetOnNetErrorCallback(OnNetErrorCallback onNetErrorCallback);

    void SetOnHttpErrorCallback(OnHttpErrorCallback onHttpErrorCallback);

    void SetOnResultCallback(OnResultCallback onResultCallback);

    void HandleTask() override;

    void OnSuccess() override;

    virtual void OnNetError(int e);

protected:
    OnResultCallback onResultCallback_;

    OnHttpErrorCallback onHttpErrorCallback_;

    OnNetErrorCallback onNetErrorCallback_;

};


#endif //ASYNC_TASK_HTTP_TEST_H
