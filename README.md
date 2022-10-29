# TCP server and TCP client
In-memory key-value storage TCP server and TCP client, based on boost.asio for TCP and [nlohmann-json](https://github.com/nlohmann/json) for JSON.

# How to build
1. git clone or download source code from this repo.
2. run CMake GUI (or [download](https://cmake.org/download/) at least version 3.24.0. if dont have one).
3. select directory, containing CMakeLists.txt and tcp_server and tcp_client folders (by default **boost-tcp-client-server-storage/**).
4. select directory, where CMake should build binaries - consider create a folder **build/** near CMakeLists.txt.
5. click *Configure* to start project configurating.
6. when asked, specify generator you want to use - originally used generator was MSYS Makefiles.
7. also recommended to specify C and C++ compilers you want to use for compiling by select *Specify native compilers*.
8. **Please, wait a while for CMake to download and populate boost and nlohmann-json libraries. <br/>
   It may take about 10 minutes (depends on your internet speed).**
9. after configuring done, click *Generate* to generate specific generator files which you chose on step 6.
10. at the last step you want to build tcp_server and tcp_client binaries - you can use chosen generator, or you can do this using command line: just type in *cmake --build .* while you're in build/ directory
11. after building done you'll find executables tcp_server and tcp_client in *build-folder/tcp_server/* and *build-folder/tcp_client/* folders, respectively. 

# How to use TCP server
1. start tcp_server executable from *build-folder/tcp_server/* folder.
2. enter port number you want to use from server.
3. you're finished! tcp server which is in-memory key-value storage is running and ready for your requests.
4. once a client connected to server you'll see "User _address_:_port_ connected" message.

# How to use TCP client
1. start tcp_client executable from *build-folder/tcp_client/* folder.
2. enter server IP-address and port number.
3. once you connected you'll see "Succesfully connected to server" message.
3. now you're ready to send some requests to server.

# Requests format
1. to **read** value, stored on server by key _key_ type in ***read _key_*** -> if key exist, you'll see "value: *_value_*" responce.
2. to **write** new key _key_ with value _val_ to server type in ***write _key_ _val_*** -> if write was succesfull you'll get "OK" responce.
3. if any error happens you'll see "Error: _error_description_" message.

**ENJOY**
