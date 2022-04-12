#include <arrow/api.h>
#include <arrow/dataset/api.h>
#include <arrow/filesystem/api.h>
#include <arrow/io/file.h>
#include <arrow/ipc/writer.h>

std::shared_ptr<arrow::Table> CreateTable();

bool write_feather(const std::shared_ptr<arrow::Table>& table, const std::string& path_) {
    std::shared_ptr<arrow::fs::FileSystem> fs = std::make_shared<arrow::fs::LocalFileSystem>();
    auto output = fs->OpenOutputStream(path_).ValueOrDie();
    auto writer = arrow::ipc::MakeFileWriter(output.get(), table->schema()).ValueOrDie();
    arrow::Status status_ = writer->WriteTable(*table);
    if (!status_.ok()) {
        printf("write table %s failed, error=%s\n", path_.c_str(), status_.message().c_str());
        return false;
    }
    status_ = writer->Close();
    if (!status_.ok()) {
        printf("writer close %s failed, error=%s\n", path_.c_str(), status_.message().c_str());
        return false;
    } else {
        printf("write %s success\n", path_.c_str());
        return true;
    }
}

std::shared_ptr<arrow::Table> read_feather(const std::string& path_) {
    auto format = std::make_shared<arrow::dataset::IpcFileFormat>();
    std::shared_ptr<arrow::fs::FileSystem> fs = std::make_shared<arrow::fs::LocalFileSystem>();
    std::string uri = "file://" + path_;
    auto factory =
        arrow::dataset::FileSystemDatasetFactory::Make(uri, format, arrow::dataset::FileSystemFactoryOptions())
            .ValueOrDie();
    auto dataset = factory->Finish().ValueOrDie();
    auto scan_builder = dataset->NewScan().ValueOrDie();
    auto scanner = scan_builder->Finish().ValueOrDie();
    return scanner->ToTable().ValueOrDie();
}

int main() {
    auto table = CreateTable();
    std::string path_ = "/tmp/data1.feather";
    write_feather(table, path_);

    auto table1 = read_feather(path_);
    printf("%s\n", table1->ToString().c_str());
    return 0;
}

// Generate some data for the rest of this example.
std::shared_ptr<arrow::Table> CreateTable() {
    auto schema = arrow::schema(
        {arrow::field("a", arrow::int64()), arrow::field("b", arrow::int64()),
         arrow::field("c", arrow::int64()), arrow::field("d", arrow::utf8())});
    std::shared_ptr<arrow::Array> array_a;
    std::shared_ptr<arrow::Array> array_b;
    std::shared_ptr<arrow::Array> array_c;
    arrow::NumericBuilder<arrow::Int64Type> builder;
    builder.AppendValues({0, 1, 2, 3, 4, 5, 6, 7, 8});
    builder.Append(9);
    builder.Finish(&array_a);
    builder.Reset();
    builder.AppendValues({9, 8, 7, 6, 5, 4, 3, 2, 1});
    builder.Append(0);
    builder.Finish(&array_b);
    builder.Reset();
    builder.AppendValues({1, 2, 1, 2, 1, 2, 1, 2, 1});
    builder.Append(2);
    builder.Finish(&array_c);

    std::shared_ptr<arrow::Array> array_d;
    arrow::StringBuilder builder1;
    builder1.AppendValues({"0", "1", "2", "3", "4", "5", "6", "7", "8"});
    builder1.Append("9");
    builder1.Finish(&array_d);
    return arrow::Table::Make(schema, {array_a, array_b, array_c, array_d});
}
