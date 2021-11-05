#include <arrow/api.h>

void builder();
void better_builder();
void chunked_array();

int main() {
    builder();
    better_builder();
    chunked_array();
    return 0;
}

void chunked_array(){
    std::vector<std::shared_ptr<arrow::Array>> chunks;
    std::shared_ptr<arrow::Array> array;

    // Build first chunk
    arrow::Int64Builder builder;
    builder.Append(1);
    builder.Append(2);
    builder.Append(3);
    if (!builder.Finish(&array).ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }
    chunks.push_back(std::move(array));

    // Build second chunk
    builder.Reset();
    builder.AppendNull();
    builder.Append(5);
    builder.Append(6);
    builder.Append(7);
    builder.Append(8);
    if (!builder.Finish(&array).ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }
    chunks.push_back(std::move(array));

    auto chunked_array = std::make_shared<arrow::ChunkedArray>(std::move(chunks));
    printf("num_chunks=%d\n", chunked_array->num_chunks() ); // 2
    printf("length=%ld\n", chunked_array->length() ); // 8
    printf("num_chunks=%ld\n", chunked_array->null_count() ); // 1
}

void builder() {
    arrow::Int64Builder builder;
    builder.Append(1);
    builder.Append(2);
    builder.Append(3);
    builder.AppendNull();
    builder.Append(5);
    builder.Append(6);
    builder.Append(7);
    builder.Append(8);

    auto maybe_array = builder.Finish();
    if (!maybe_array.ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }
    std::shared_ptr<arrow::Array> array = *maybe_array;

    // Cast the Array to its actual type to access its data
    auto int64_array = std::static_pointer_cast<arrow::Int64Array>(array);

    // Get the pointer to the null bitmap.
    const uint8_t* null_bitmap = int64_array->null_bitmap_data();
    printf("%u\n", null_bitmap[0]); // "1|1|1|1|0|1|1|1"

    // Get the pointer to the actual data
    const int64_t* data = int64_array->raw_values();
    printf("%ld,%ld\n", data[0], data[1]);

    int index = 2;
    if (!int64_array->IsNull(index)) {
        int64_t value = int64_array->Value(index);
        printf("data[%d] = %ld\n", index,  value);
    }
}

void better_builder() {
    arrow::Int64Builder builder;
    // Make place for 8 values in total
    builder.Reserve(8);
    // Bulk append the given values (with a null in 4th place as indicated by the validity vector)
    std::vector<bool> validity = {true, true, true, false, true, true, true, true};
    std::vector<int64_t> values = {1, 2, 3, 0, 5, 6, 7, 8};
    builder.AppendValues(values, validity);

    auto maybe_array = builder.Finish();
    if (!maybe_array.ok()) {
        printf("maybe_buffer allocation error\n");
        exit(1);
    }
    std::shared_ptr<arrow::Array> array = *maybe_array;

    // Cast the Array to its actual type to access its data
    auto int64_array = std::static_pointer_cast<arrow::Int64Array>(array);

    // Get the pointer to the null bitmap.
    const uint8_t* null_bitmap = int64_array->null_bitmap_data();
    printf("%u\n", null_bitmap[0]); // "1|1|1|1|0|1|1|1"

    // Get the pointer to the actual data
    const int64_t* data = int64_array->raw_values();
    printf("%ld,%ld\n", data[0], data[1]);

    int index = 2;
    if (!int64_array->IsNull(index)) {
        int64_t value = int64_array->Value(index);
        printf("data[%d] = %ld\n", index,  value);
    }
}