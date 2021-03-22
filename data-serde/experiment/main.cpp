#include <iostream>
#include <proto/test.pb.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

using themis::benchmarks::Test;
using themis::benchmarks::TestList;
using themis::benchmarks::TestWrapper;
using namespace rapidjson;

auto buildSingleProto() {
    Test obj;
    obj.set_a("works as a charm");
    return obj;
}

size_t testSingleProto() {
    return buildSingleProto().ByteSizeLong();
}

size_t testMultiProto() {
    TestWrapper testData;
    auto testList = new TestList();

    for (auto idx = 0; idx < 8; idx++) {
        auto data = testList->add_data();
        data->set_a("works as a charm");
    }

    testData.set_allocated_a(testList);
    return testData.ByteSizeLong();
}

size_t testSingleJson() {
    Document document;
    document.Parse("{\"a\":\"works as a charm\"}");

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetSize();
}

size_t testMultiJson() {
    std::string str = "{\"a\":["
                      "{\"a\":\"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"},"
                      "{\"a\": \"works as a charm\"}"
                      "]}";

    Document document;
    document.Parse(str.c_str());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetSize();
}

int main() {
    auto singleProtoSize = testSingleProto();
    auto singleJsonSize = testSingleJson();
    std::cout << "Single proto size: " << singleProtoSize << std::endl;
    std::cout << "Single json size: " << singleJsonSize << std::endl;

    auto multiProtoSize = testMultiProto();
    auto multiJsonSize = testMultiJson();
    std::cout << "Multiple proto size: " << multiProtoSize << std::endl;
    std::cout << "Multiple json size: " << multiJsonSize << std::endl;
    return 0;
}
