#include <arrow/api.h>

void basic() {
    arrow::Result<std::unique_ptr<arrow::Buffer>> maybe_buffer = arrow::AllocateBuffer(4096);
    if (!maybe_buffer.ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }

    std::shared_ptr<arrow::Buffer> buffer = *std::move(maybe_buffer);
    uint8_t* buffer_data = buffer->mutable_data();
    std::string data = "hello world!\n";
    memcpy(buffer_data, data.data(), data.size());
    printf("%s", buffer_data);
}

void builder() {
    // allocate and build a Buffer incrementally
    arrow::BufferBuilder builder;
    builder.Resize(128);
    builder.Append("hello ", 6);
    builder.Append("world!\n", 7);

    auto maybe_buffer = builder.Finish();
    if (!maybe_buffer.ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }
    std::shared_ptr<arrow::Buffer> buffer = *maybe_buffer;
    printf("%s", buffer->data());
}

int main() {
    basic();
    builder();
    return 0;
}