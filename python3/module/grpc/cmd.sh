pip install grpcio
pip install grpcio-tools googleapis-common-protos


python -m grpc_tools.protoc -I./protos --python_out=. --grpc_python_out=. ./protos/helloworld.proto