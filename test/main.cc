//
// Created by Administrator on 2023/9/19 0019.
//

#include "handle/async_manage.h"
#include "gtest/gtest.h"

TEST(AsyncTaskLibTest, Test01)
{
    async::AsyncManage asyncManage;

    asyncManage.SetOnSuccess([](){
        std::cout << "OnSuccess" << std::endl;
    });

    asyncManage.SetOnComplete([](){
        std::cout << "OnComplete" << std::endl;
    });

    asyncManage.HandleTask();

    while (true);
}


int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}

