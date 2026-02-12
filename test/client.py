#!/usr/bin/env python3
import argparse
import socket
import sys
import threading
import time

def send_message(host, port, client_id, message, repeat):
    """Send messages from a single client"""
    try:
        with socket.create_connection((host, port)) as sock:
            for i in range(repeat):
                msg = f"{message}{client_id}" if message else f"client{client_id}\n"
                sock.sendall(msg.encode("utf-8"))
                print(f"Client {client_id} sent: {msg.strip()}")
                time.sleep(0.1)  # Small delay between messages
    except OSError as exc:
        print(f"Client {client_id} error: {exc}", file=sys.stderr)

def main() -> int:
    parser = argparse.ArgumentParser(description="Simple TCP client for testing LCP server")
    parser.add_argument("host", help="Server host, e.g. 127.0.0.1")
    parser.add_argument("port", type=int, help="Server port")
    parser.add_argument("-m", "--message", default="", help="Message prefix (client number will be appended)")
    parser.add_argument("-r", "--repeat", type=int, default=1, help="Send message N times per client")
    parser.add_argument("-c", "--clients", type=int, default=1, help="Number of concurrent clients")
    args = parser.parse_args()

    threads = []
    
    # Create and start threads for each client
    for i in range(1, args.clients + 1):
        thread = threading.Thread(
            target=send_message,
            args=(args.host, args.port, i, args.message, args.repeat)
        )
        threads.append(thread)
        thread.start()
        time.sleep(0.05)  # Small delay between starting clients
    
    # Wait for all threads to complete
    for thread in threads:
        thread.join()

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
