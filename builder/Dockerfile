FROM ubuntu:22.04

# Install build tools
RUN apt update && \
	apt install -y \
		apt-transport-https \
		build-essential \
        binutils \
        patchelf \
        lsb-release \
        file \
		cmake \
		wget \
		ninja-build \
		libsdl2-dev \
		libsdl2-net-dev \
		libpng-dev \
		libglew-dev \
        libpulse-dev \
        zlib1g-dev \
        libbz2-dev \
        lld \
        imagemagick

# Install SDL2 2.26.1
RUN wget https://www.libsdl.org/release/SDL2-2.26.1.tar.gz && \
    tar -xzf SDL2-2.26.1.tar.gz && \
    cd SDL2-2.26.1 && \
    ./configure && \
    make && \
    make install && \
    cd .. && \
    rm -rf SDL2-2.26.1 && \
    rm SDL2-2.26.1.tar.gz && \
    cp -av /usr/local/lib/libSDL* /lib/x86_64-linux-gnu/

# Install SDL2-net 2.2.0
RUN wget https://www.libsdl.org/projects/SDL_net/release/SDL2_net-2.2.0.tar.gz && \
    tar -xzf SDL2_net-2.2.0.tar.gz && \
    cd SDL2_net-2.2.0 && \
    ./configure && \
    make && \
    make install && \
    cd .. && \
    rm -rf SDL2_net-2.2.0 && \
    rm SDL2_net-2.2.0.tar.gz && \
    cp -av /usr/local/lib/libSDL* /lib/x86_64-linux-gnu/

# Install DevkitPro
RUN ln -sf /proc/self/mounts /etc/mtab && \
	mkdir -p /usr/local/share/keyring/ && \
	wget -O /usr/local/share/keyring/devkitpro-pub.gpg https://apt.devkitpro.org/devkitpro-pub.gpg && \
	echo "deb [signed-by=/usr/local/share/keyring/devkitpro-pub.gpg] https://apt.devkitpro.org stable main" > /etc/apt/sources.list.d/devkitpro.list && \
	apt-get update -y && \
	apt-get install -y devkitpro-pacman && \
	dkp-pacman -Syu switch-dev switch-portlibs wiiu-dev wiiu-portlibs --noconfirm

ENV DEVKITPRO=/opt/devkitpro
ENV DEVKITARM=/opt/devkitpro/devkitARM
ENV DEVKITPPC=/opt/devkitpro/devkitPPC
ENV PATH=$PATH:/opt/devkitpro/portlibs/switch/bin/:$DEVKITPPC/bin
ENV WUT_ROOT=$DEVKITPRO/wut

# Finalize
RUN mkdir /soh
WORKDIR /soh
