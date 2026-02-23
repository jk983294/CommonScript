#include <iostream>
#include <vector>
#include <fstream>
#include <arrow/api.h>
#include <arrow/result.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>
#include <parquet/arrow/reader.h>
#include <parquet/file_reader.h>
#include <parquet/column_reader.h>
#include <arrow/util/type_fwd.h>
#include <zerg/io/feather_helper.h>

/**
 * g++ -std=c++17 parquet_reader.cpp -o parquet_reader -I/opt/3rd/common/include -I/opt/version/latest/zerg/include/ -L/opt/version/latest/zerg/lib -lzergio -lzerg -I/opt/3rd/arrow/include -L/opt/3rd/arrow/lib -lparquet -larrow -larrow_bundled_dependencies -lthrift -ldl
 */

namespace {
void CheckStatus(const arrow::Status& status, const std::string& msg = "") {
    if (!status.ok()) {
        std::cerr << (msg.empty() ? "" : msg + ": ") << status.ToString() << std::endl;
        exit(EXIT_FAILURE);
    }
}
}

const char* const path_to_file = "/tmp/test.pa";

void write() {
    std::vector<int> ids = {1, 2, 3};
    std::vector<double> values = {1.0, 2.0, 3.0};
    std::vector<std::string> names = {"A", "B", "C"};

    arrow::Int32Builder id_builder;
    arrow::DoubleBuilder value_builder;
    arrow::StringBuilder name_builder;
    std::ignore = id_builder.AppendValues(ids);
    std::ignore = value_builder.AppendValues(values);
    std::ignore = name_builder.AppendValues(names);

    std::shared_ptr<arrow::Array> id_array;
    std::shared_ptr<arrow::Array> value_array;
    std::shared_ptr<arrow::Array> name_array;

    CheckStatus(id_builder.Finish(&id_array), "Finishing ID array");
    CheckStatus(value_builder.Finish(&value_array), "Finishing Value array");
    CheckStatus(name_builder.Finish(&name_array), "Finishing Name array");

    auto schema = arrow::schema({
        arrow::field("id", arrow::int32()),
        arrow::field("value", arrow::float64()),
        arrow::field("name", arrow::utf8())
    });

    std::vector<std::shared_ptr<arrow::Array>> arrays = {id_array, value_array, name_array};
    auto table = arrow::Table::Make(schema, arrays);

    std::shared_ptr<arrow::io::FileOutputStream> outfile = arrow::io::FileOutputStream::Open(path_to_file).ValueOrDie();
    PARQUET_THROW_NOT_OK(
        parquet::arrow::WriteTable(*table.get(), arrow::default_memory_pool(), outfile)
    );
    std::cout << "Successfully wrote Parquet file\n";
}

void read() {
    std::ifstream file(path_to_file);
    if (!file.good()) {
        std::cerr << "File does not exist or is not accessible: " << path_to_file << std::endl;
        return;
    }
    file.close();
    
    std::unique_ptr<parquet::ParquetFileReader> parquet_reader;
    auto in_file_result = arrow::io::ReadableFile::Open(path_to_file);
    if (!in_file_result.ok()) {
        std::cerr << "Failed to open file for parquet reader: " << in_file_result.status().ToString() << std::endl;
        return;
    }
    auto in_file = in_file_result.ValueOrDie();
    
    parquet_reader = parquet::ParquetFileReader::Open(in_file);
    
    auto file_metadata = parquet_reader->metadata();
    std::cout << "Parquet file has " << file_metadata->num_row_groups() 
                << " row groups and " << file_metadata->num_columns() << " columns\n";
    
    // Just print basic column information
    auto row_group_reader = parquet_reader->RowGroup(0);
    for (int i = 0; i < file_metadata->num_columns(); i++) {
        auto column_reader = row_group_reader->Column(i);
        auto col_descr = column_reader->descr();
        std::cout << "Column " << i << ": " << col_descr->name() 
                    << ", type: " << col_descr->physical_type() << "\n";
    }
    std::cout << "Successfully read file metadata!\n";
}

void read_table() {
    std::ifstream file(path_to_file);
    if (!file.good()) {
        std::cerr << "File does not exist or is not accessible: " << path_to_file << std::endl;
        return;
    }
    file.close();

    arrow::MemoryPool* pool = arrow::default_memory_pool();
    std::shared_ptr<arrow::io::RandomAccessFile> input = arrow::io::ReadableFile::Open(path_to_file).ValueOrDie();

    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    CheckStatus(parquet::arrow::OpenFile(input, pool, &arrow_reader), "OpenFile failed");

    std::shared_ptr<arrow::Table> table;
    CheckStatus(arrow_reader->ReadTable(&table), "ReadTable failed");

    zerg::InputData id;
    zerg::FeatherReader::table2id(table, id);

    for (auto& col : id.cols) {
        if (col.type == 1) {
            auto& vec = *reinterpret_cast<std::vector<double>*>(col.data);
            printf("col %s type=%d data=%f,%f\n", col.name.c_str(), col.type, vec.front(), vec.back());
        } else if (col.type == 3) {
            auto& vec = *reinterpret_cast<std::vector<int>*>(col.data);
            printf("col %s type=%d data=%d,%d\n", col.name.c_str(), col.type, vec.front(), vec.back());
        } else if (col.type == 4) {
            auto& vec = *reinterpret_cast<std::vector<std::string>*>(col.data);
            printf("col %s type=%d data=%s,%s\n", col.name.c_str(), col.type, vec.front().c_str(), vec.back().c_str());
        } else if (col.type == 5) {
            auto& vec = *reinterpret_cast<std::vector<bool>*>(col.data);
            printf("col %s type=%d data=%d,%d\n", col.name.c_str(), col.type, (int)vec.front(), (int)vec.back());
        }
    }
}

int main() {
    write();
    read();
    read_table();
    return 0;
}