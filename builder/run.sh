#!/bin/bash
# ########################################
# Utility for setup and building with Docker image
# ########################################

# Absolute path where this script is located
RUN_DIRECTORY="$(dirname $(realpath ${BASH_SOURCE[0]}))"

# Docker image's ID
IMAGE_ID="soh:custom"

# Run container into current workspace with current privileges.
#
# Usage: run_docker <command with arguments>
run_docker()
{
    docker run --rm \
        --user $(id -u):$(id -g) \
        --mount "type=bind,src=/etc/passwd,dst=/etc/passwd,ro" \
        --mount "type=bind,src=/etc/group,dst=/etc/group,ro" \
        --mount "type=bind,src=/etc/shadow,dst=/etc/shadow,ro" \
        --mount "type=bind,src=$RUN_DIRECTORY/..,dst=/soh" \
        -i -t \
        --name soh soh:custom \
        $@
}

# Print available subcommands
#
# Usage: print_help <where to print>
print_help()
{
    echo "Available commands:" > $1
    echo "--------------------" > $1
    echo " - init: Initialize project" > $1
    echo " - extract-assets: Extract assets (need to put a valid rom into \"OTRExporter\")" > $1
    echo " - build: Build for Linux" > $1
    echo " - init-switch: Initialize project for Nintendo Switch" > $1
    echo " - build-switch: Build for Nintendo Switch" > $1
    echo " - clean: Delete build directory" > $1
    echo " - bash: Run bash into container" > $1
}

# ########################################
# ########################################

# Check if docker is installed
if [ -z $(command -v docker 2> /dev/null) ] ; then
    echo "\"docker\" command not found, abort it" > /dev/stderr
    exit 1
fi

# Check if image already built
# If image isn't found locally, let's build it
if [ -z "$(docker images --quiet $IMAGE_ID 2> /dev/null)" ] ; then
    echo "Builder image not found, creating..."
    docker build "$RUN_DIRECTORY" --tag $IMAGE_ID
fi

# No command provided, printing help and exit
if [ -z "$1" ] ; then
    echo "Usage: $0 <command>" > /dev/stderr
    echo > /dev/stderr
    print_help /dev/stderr
    exit 1
fi

# Everything is ready, now begin to execute tasks...
case "$1" in
    "clean")
        rm -rf "$RUN_DIRECTORY/../build"
        ;;
    "bash")
        run_docker /bin/bash
        ;;
    "help")
        print_help /dev/stdout
        ;;
    *)
        if [ -f "$RUN_DIRECTORY/actions/$1.sh" ] ; then
            run_docker /bin/bash "/soh/builder/actions/$1.sh"
        else
            echo "Unknown command: $1" > /dev/stderr
            echo > /dev/stderr
            print_help /dev/stderr
            exit 1
        fi
        ;;
esac
