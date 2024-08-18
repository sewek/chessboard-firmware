# From https://github.com/NordicPlayground/nrf-docker/blob/saga/Dockerfile
# Removed SDK installation

FROM ubuntu:22.04
WORKDIR /workdir

ARG toolchain_version=v2.6.1
ARG NORDIC_COMMAND_LINE_TOOLS_VERSION="10-24-0/nrf-command-line-tools-10.24.0"
ARG arch=amd64

ENV DEBIAN_FRONTEND=noninteractive

SHELL [ "/bin/bash", "-euxo", "pipefail", "-c" ]

# gcc-multilib make = Host tools for native_sim build
# python 3.8 is installed by toolchain manager hence older version of libffi is required
RUN <<EOT
    apt-get -y update
    apt-get -y upgrade
    apt-get -y install git wget unzip make cmake clang-format gcc-multilib make libffi7 python3 python3-pip
    apt-get -y clean
    rm -rf /var/lib/apt/lists/*
    pip3 install -U west
EOT

# Install toolchain
# Make nrfutil install in a shared location, because when used with GitHub
# Actions, the image will be launched with the home dir mounted from the local
# checkout.
ENV NRFUTIL_HOME=/usr/local/share/nrfutil
RUN <<EOT
    wget -q https://developer.nordicsemi.com/.pc-tools/nrfutil/x64-linux/nrfutil
    mv nrfutil /usr/local/bin
    chmod +x /usr/local/bin/nrfutil
    nrfutil install toolchain-manager
    nrfutil install toolchain-manager search
    nrfutil toolchain-manager install --ncs-version ${toolchain_version}
    nrfutil toolchain-manager list
    rm -f /root/ncs/downloads/*
EOT

# Nordic command line tools
# Releases: https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download
RUN <<EOT
    NCLT_BASE=https://nsscprodmedia.blob.core.windows.net/prod/software-and-other-downloads/desktop-software/nrf-command-line-tools/sw/versions-10-x-x
    echo "Host architecture: $arch"
    case $arch in
        "amd64")
            NCLT_URL="${NCLT_BASE}/${NORDIC_COMMAND_LINE_TOOLS_VERSION}_linux-amd64.tar.gz"
            ;;
        "arm64")
            NCLT_URL="${NCLT_BASE}/${NORDIC_COMMAND_LINE_TOOLS_VERSION}_linux-arm64.tar.gz"
            ;;
    esac
    echo "NCLT_URL=${NCLT_URL}"
    if [ ! -z "$NCLT_URL" ]; then
        mkdir tmp && cd tmp
        wget -qO - "${NCLT_URL}" | tar --no-same-owner -xz
        # Install included JLink
        mkdir /opt/SEGGER
        tar xzf JLink_*.tgz -C /opt/SEGGER
        mv /opt/SEGGER/JLink* /opt/SEGGER/JLink
        # Install nrf-command-line-tools
        cp -r ./nrf-command-line-tools /opt
        ln -s /opt/nrf-command-line-tools/bin/nrfjprog /usr/local/bin/nrfjprog
        ln -s /opt/nrf-command-line-tools/bin/mergehex /usr/local/bin/mergehex
        cd .. && rm -rf tmp ;
    else
        echo "Skipping nRF Command Line Tools (not available for $arch)" ;
    fi
EOT
