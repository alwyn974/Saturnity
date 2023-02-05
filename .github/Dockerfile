FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y gcc-multilib g++ cmake git fd-find lsb-release wget software-properties-common gnupg
RUN apt-get install -y libglfw3 libglfw3-dev libx11-dev libxcursor-dev libxrandr-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libfreetype-dev libfreetype6 libfreetype6-dev # SFML deps
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 16
RUN apt-get install -y clang-format-16 clang-tidy-16
