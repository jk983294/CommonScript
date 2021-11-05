#include <arrow/api.h>
#include <arrow/dataset/api.h>
#include <arrow/filesystem/api.h>
#include <arrow/io/file.h>
#include <parquet/api/schema.h>
#include <parquet/arrow/writer.h>

std::shared_ptr<arrow::Table> CreateTable();

std::string CreateExampleParquetDataset(const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
                                        const std::string& root_path);
std::shared_ptr<arrow::Table> ScanWholeDataset(const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
                                               const std::shared_ptr<arrow::dataset::FileFormat>& format,
                                               const std::string& base_dir);

int main() {
    std::shared_ptr<arrow::fs::FileSystem> fs = std::make_shared<arrow::fs::LocalFileSystem>();
    std::shared_ptr<arrow::dataset::FileFormat> format = std::make_shared<arrow::dataset::ParquetFileFormat>();
    auto base_dir = CreateExampleParquetDataset(fs, "/tmp/");
    ScanWholeDataset(fs, format, base_dir);
    //    read_file();
    return 0;
}

// Read the whole dataset with the given format, without partitioning.
std::shared_ptr<arrow::Table> ScanWholeDataset(const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
                                               const std::shared_ptr<arrow::dataset::FileFormat>& format,
                                               const std::string& base_dir) {
    // Create a dataset by scanning the filesystem for files
    arrow::fs::FileSelector selector;
    selector.base_dir = base_dir;
    auto factory = arrow::dataset::FileSystemDatasetFactory::Make(filesystem, selector, format,
                                                                  arrow::dataset::FileSystemFactoryOptions())
                       .ValueOrDie();
    auto dataset = factory->Finish().ValueOrDie();

    // Print out the fragments
    for (const auto& fragment : dataset->GetFragments().ValueOrDie()) {
        printf("Found fragment:  %s\n", (*fragment)->ToString().c_str());
    }
    // Read the entire dataset as a Table
    auto scan_builder = dataset->NewScan().ValueOrDie();
    scan_builder->Project({"b"});
    scan_builder->Filter(arrow::compute::less(arrow::compute::field_ref("b"), arrow::compute::literal(4)));
    auto scanner = scan_builder->Finish().ValueOrDie();
    return scanner->ToTable().ValueOrDie();
}

// Generate some data for the rest of this example.
std::shared_ptr<arrow::Table> CreateTable() {
    auto schema = arrow::schema(
        {arrow::field("a", arrow::int64()), arrow::field("b", arrow::int64()), arrow::field("c", arrow::int64())});
    std::shared_ptr<arrow::Array> array_a;
    std::shared_ptr<arrow::Array> array_b;
    std::shared_ptr<arrow::Array> array_c;
    arrow::NumericBuilder<arrow::Int64Type> builder;
    builder.AppendValues({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    builder.Finish(&array_a);
    builder.Reset();
    builder.AppendValues({9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    builder.Finish(&array_b);
    builder.Reset();
    builder.AppendValues({1, 2, 1, 2, 1, 2, 1, 2, 1, 2});
    builder.Finish(&array_c);
    return arrow::Table::Make(schema, {array_a, array_b, array_c});
}

// Set up a dataset by writing two Parquet files.
std::string CreateExampleParquetDataset(const std::shared_ptr<arrow::fs::FileSystem>& filesystem,
                                        const std::string& root_path) {
    auto base_path = root_path + "/parquet_dataset_cpp_dir";
    filesystem->CreateDir(base_path);
    auto table = CreateTable();
    // Write it into two Parquet files
    auto output = filesystem->OpenOutputStream(base_path + "/data1.parquet").ValueOrDie();
    parquet::arrow::WriteTable(*table->Slice(0, 5), arrow::default_memory_pool(), output, /*chunk_size=*/2048);
    output = filesystem->OpenOutputStream(base_path + "/data2.parquet").ValueOrDie();
    parquet::arrow::WriteTable(*table->Slice(5), arrow::default_memory_pool(), output, /*chunk_size=*/2048);
    return base_path;
}
