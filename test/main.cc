//
// Created by Administrator on 2023/9/19 0019.
//

#include "handle/async_manage.h"
#include "http_test.h"
#include "gtest/gtest.h"


void HttpTest01_01OnResultCallback(HttpTest * httpTest01_01,std::unique_ptr<std::string> body){
    std::cout << "HttpTest01_01OnResultCallback" << std::endl;
}

void HttpTest01OnResultCallback(HttpTest * httpTest01,std::unique_ptr<std::string> body){
    std::cout << "HttpTest01OnResultCallback" << std::endl;

    std::unique_ptr<HttpTest> httpTest01_01 = std::make_unique<HttpTest>();

    httpTest01_01->SetOnResultCallback(HttpTest01_01OnResultCallback);

    httpTest01->AddChildTask(std::move(httpTest01_01));
}

TEST(AsyncTaskLibTest, Test01)
{
    async::AsyncManage asyncManage;

    asyncManage.SetOnSuccess([](){
        std::cout << "OnSuccess" << std::endl;
    });

    asyncManage.SetOnComplete([](){
        std::cout << "OnComplete" << std::endl;
    });

    std::unique_ptr<HttpTest> httpTest01 = std::make_unique<HttpTest>();

    httpTest01->SetOnResultCallback(HttpTest01OnResultCallback);

    asyncManage.AddTask(std::move(httpTest01));

    asyncManage.HandleTask();

    while (true);
}


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}

