#!/usr/bin/env bash

# echo "hello world!"
clang++ -std=c++11 -o server -lgrpc++ -lprotobuf -lpthread -lgrpc++_reflection hello.pb.cc hello.grpc.pb.cc hello_rpc_server.cc
clang++ -std=c++11 -o client -lgrpc++ -lprotobuf -lpthread -lgrpc++_reflection hello.pb.cc hello.grpc.pb.cc hello_rpc_client.cc
