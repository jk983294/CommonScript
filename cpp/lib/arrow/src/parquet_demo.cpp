#include <arrow/io/file.h>
#include <parquet/stream_reader.h>
#include <parquet/stream_writer.h>

struct Article {
    std::string name;
    float price;
    int quantity;
};

void read_file();
void write_file();

int main() {
    write_file();
    read_file();
    return 0;
}

void write_file() {
    std::shared_ptr<arrow::io::FileOutputStream> outfile;

    PARQUET_ASSIGN_OR_THROW(outfile, arrow::io::FileOutputStream::Open("/tmp/test.parquet.cpp"));

    parquet::WriterProperties::Builder builder;

    parquet::schema::NodeVector fields;
    fields.push_back(parquet::schema::PrimitiveNode::Make("name", parquet::Repetition::OPTIONAL,
                                                          parquet::Type::BYTE_ARRAY, parquet::ConvertedType::UTF8));
    fields.push_back(parquet::schema::PrimitiveNode::Make("price", parquet::Repetition::REQUIRED, parquet::Type::FLOAT,
                                                          parquet::ConvertedType::NONE, -1));
    fields.push_back(parquet::schema::PrimitiveNode::Make("quantity", parquet::Repetition::REQUIRED,
                                                          parquet::Type::INT32, parquet::ConvertedType::INT_32, -1));
    std::shared_ptr<parquet::schema::GroupNode> schema = std::static_pointer_cast<parquet::schema::GroupNode>(
        parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));

    parquet::StreamWriter os{parquet::ParquetFileWriter::Open(outfile, schema, builder.build())};

    std::vector<Article> articles{Article{"x", 35.0f, 20}, Article{"y", 24.0f, 30}, Article{"z", 50.0f, 10}};
    for (const auto& a : articles) {
        os << a.name << a.price << a.quantity << parquet::EndRow;
    }
}

void read_file() {
    std::shared_ptr<arrow::io::ReadableFile> infile;

    PARQUET_ASSIGN_OR_THROW(infile, arrow::io::ReadableFile::Open("/tmp/test.parquet.cpp"));

    parquet::StreamReader os{parquet::ParquetFileReader::Open(infile)};

    std::string article;
    float price;
    int quantity;

    while (!os.eof()) {
        os >> article >> price >> quantity >> parquet::EndRow;
        printf("record %s,%f,%d\n", article.c_str(), price, quantity);
    }
}
