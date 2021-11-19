//
// Created by Meevere on 12.11.2021.
//

#include "taskA.h"

#include <iostream>

struct TestObj {
    int field;

    TestObj(int field): field(field){
//        std::cout << "TestObj construct : " << field << std::endl;
    }

    TestObj(const TestObj& other): TestObj(other.field){
        std::cout << "TestObj copy : " << field << std::endl;
    }

    TestObj& operator=(const TestObj& other) {
        this->field = other.field;
        std::cout << "TestObj copy-assign : " << field << std::endl;
        return *this;
    }

    bool operator!=(const TestObj& other) const {
        return other.field != this->field;
    }

    ~TestObj(){
//        std::cout << "TestObj destruct : " << field << std::endl;
    }
};

typedef TestObj handle_t;
const handle_t kNullHandle(0); // NOLINT(cert-err58-cpp)

void raw_write(handle_t handle, const std::string& content);

void raw_close(handle_t handle);

class IOWrapper {
    handle_t handle;
public:

    explicit IOWrapper(handle_t&& handle): handle(handle) {};

    // as task requires
    IOWrapper() = delete;
    IOWrapper(const IOWrapper& temp) = delete;
    IOWrapper& operator=(const IOWrapper& temp) = delete;

    IOWrapper(IOWrapper&& wrapper) noexcept :handle(wrapper.handle) {}

    IOWrapper& operator=(IOWrapper&& wrapper) noexcept{
        // closing previous resource
        raw_close(this->handle);
        // taking the other one
        this->handle = wrapper.handle;
        wrapper.handle = kNullHandle;
        return *this;
    }

    ~IOWrapper() {
        if(handle != kNullHandle) {
            raw_close(handle);
        }
    }

    void Write(const std::string& content) const{
        if(handle != kNullHandle)
            raw_write(handle, content);
    }
};

void raw_write(handle_t handle, const std::string& content){
    std::cout << "Handler : " << handle.field << ", content : " << content << std::endl;
}

void raw_close(handle_t handle) {
    std::cout << "Handler " << handle.field << " closed" << std::endl;
}

int taskA() {
    IOWrapper test(TestObj(1));
    IOWrapper test2(std::move(test));

    //test of correctness
    test.Write("Hello");

    test2.Write("Hello");

    test2 = IOWrapper(TestObj(2));
    test2.Write("Im with 2");

    return 0;
}