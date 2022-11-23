#include <arrow/api.h>
#include <arrow/dataset/api.h>
#include <arrow/filesystem/api.h>
#include <arrow/io/file.h>

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

void get_data_by_arrow_type_helper(double val, int& out) { out = static_cast<int>(std::lround(val)); }
void get_data_by_arrow_type_helper(int val, int& out) { out = val; }
void get_data_by_arrow_type_helper(int64_t val, int& out) { out = val; }
void get_data_by_arrow_type_helper(double val, double& out) { out = val; }

template <typename TIn, typename TOut>
std::vector<TOut> get_array_data(std::shared_ptr<arrow::Table>& Tbl, int idx, int64_t rows) {
    std::vector<TOut> vec(rows);
    auto pChArray = Tbl->column(idx);
    int NChunks = pChArray->num_chunks();
    int i = 0;
    for (int n = 0; n < NChunks; n++) {
        auto pArray = pChArray->chunk(n);
        int64_t ArrayRows = pArray->length();
        auto pTypedArray = std::dynamic_pointer_cast<TIn>(pArray);
        const auto* pData = pTypedArray->raw_values();
        for (int64_t j = 0; j < ArrayRows; j++) {
            TOut tmp;
            get_data_by_arrow_type_helper(pData[j], tmp);
            vec[i++] = tmp;
        }
    }
    return vec;
}

std::vector<std::string> get_array_data_string(std::shared_ptr<arrow::Table>& Tbl, int idx, int64_t rows) {
    std::vector<std::string> vec(rows);
    auto pChArray = Tbl->column(idx);
    int NChunks = pChArray->num_chunks();
    int i = 0;
    for (int n = 0; n < NChunks; n++) {
        std::shared_ptr<arrow::Array> pArray = pChArray->chunk(n);
        int64_t ArrayRows = pArray->length();
        auto pTypedArray = std::dynamic_pointer_cast<arrow::StringArray>(pArray);
        for (int64_t j = 0; j < ArrayRows; j++) {
            std::string tmp = pTypedArray->GetString(j);
            vec[i++] = tmp;
        }
    }
    return vec;
}

std::vector<bool> get_array_data_bool(std::shared_ptr<arrow::Table>& Tbl, int idx, int64_t rows) {
    std::vector<bool> vec(rows);
    auto pChArray = Tbl->column(idx);
    int NChunks = pChArray->num_chunks();
    int i = 0;
    for (int n = 0; n < NChunks; n++) {
        std::shared_ptr<arrow::Array> pArray = pChArray->chunk(n);
        int64_t ArrayRows = pArray->length();
        auto pTypedArray = std::dynamic_pointer_cast<arrow::BooleanArray>(pArray);
        for (int64_t j = 0; j < ArrayRows; j++) {
            vec[i++] = pTypedArray->Value(j);
        }
    }
    return vec;
}

int main() {
    std::string path_ = "/tmp/data1.feather";
    auto table1 = read_feather(path_);
    auto schema_ = table1->schema();
    printf("schema:\n");
    // printf("%s\n", schema_->ToString().c_str());
    auto col_cnt = table1->num_columns();

    for (int i = 0; i < col_cnt; ++i) {
        auto f_ = schema_->field(i);
        auto type_ = f_->type();
        printf("%s,%s\n", f_->name().c_str(), type_->name().c_str());
    }

    auto row_cnt = table1->num_rows();
    printf("col_cnt=%d, row_cnt=%ld\n", col_cnt, row_cnt);
    auto col_names = table1->ColumnNames();
    for (auto& col_name : col_names) {
        printf("%s,", col_name.c_str());
    }
    printf("\n");

    std::vector<int> v0 = get_array_data<arrow::Int64Array, int>(table1, 0, row_cnt);
    std::vector<int> v1 = get_array_data<arrow::Int64Array, int>(table1, 1, row_cnt);
    std::vector<int> v2 = get_array_data<arrow::Int64Array, int>(table1, 2, row_cnt);
    std::vector<std::string> v3 = get_array_data_string(table1, 3, row_cnt);
    for (int i = 0; i < row_cnt; ++i) {
        printf("%d,%d,%d,%s\n", v0[i], v1[i], v2[i], v3[i].c_str());
    }
    return 0;
}