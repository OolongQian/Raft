# Raft: A consensus algorithm for distributed system
2018 SJTU PPCA project

## Project summary 
Consensus algorithms allow a collection of machines to work as a coherent group that can survive the failues of some of its members. Thus they play a key role in building reliable large-scale software systems. Raft is an understandable and practical consensus algorithm. 
A server in our constext is typically modeled as a replicated state machine. It executes a series of commands stored in replicated log in order. Keeping relicated log consistent ensures all state machines operate in the same way. 
In our implementation, user interface is defined as a KV map which supports "Put" and "Get" methods. 

## Properties
1. Servers never return an incorrect result. 
2. Server cluster is fully functional as long as majority of the servers are operational and can communicate with each other and with clients. 
3. They don't depend on consistent timing. 
4. A command can complete as soon as a majority of the cluster has responded to a single round of remote procedure calls; a minority of slow servers needn't impacting overall system performance. 