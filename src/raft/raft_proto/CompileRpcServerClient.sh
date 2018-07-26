#!/usr/bin/env bash

# make command for compiling proto file to .h and .cc grpc files.
#make raft_peer.grpc.pb.cc raft_peer.pb.cc

# make command for creating executable files.
#clang++ -std=c++11 -o server -lgrpc++ -lprotobuf -lpthread -lgrpc++_reflection raft_peer.pb.cc raft_peer.grpc.pb.cc raft_peer_rpc_server.cc
#clang++ -std=c++11 -o client -lgrpc++ -lprotobuf -lpthread -lgrpc++_reflection raft_peer.pb.cc raft_peer.grpc.pb.cc raft_peer_rpc_client.cc
