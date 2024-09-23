#!/bin/bash

# setup_node.sh
# Script to set up a Crytex blockchain node

# Variables
NODE_DIR="crytex_node"             # Directory for node's data
CONFIG_FILE="node_config.json"      # Node configuration file
PORT=4000                           # Default port number for the node
PEER_NODE=""                        # IP address or hostname of a peer node (optional)

# Function to create a new node directory
function create_node_directory() {
    echo "Creating node directory..."
    mkdir -p $NODE_DIR
    echo "Node directory created at ./$NODE_DIR"
}

# Function to create a default configuration file
function create_config_file() {
    echo "Creating configuration file..."
    cat <<EOL > $NODE_DIR/$CONFIG_FILE
{
    "port": $PORT,
    "peers": [
        "$PEER_NODE"
    ]
}
EOL
    echo "Configuration file created at ./$NODE_DIR/$CONFIG_FILE"
}

# Function to start the node
function start_node() {
    echo "Starting the Crytex node..."
    cd $NODE_DIR
    ../crytex --config $CONFIG_FILE &  # Start the node with the configuration file
    NODE_PID=$!
    echo "Crytex node started with PID $NODE_PID"
}

# Main script

echo "Setting up Crytex node..."

# Step 1: Create node directory
create_node_directory

# Step 2: Create configuration file
create_config_file

# Step 3: Start the node
start_node

echo "Node setup complete."
