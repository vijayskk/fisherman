# Fisherman

Fisherman is a fast multi-threaded TCP port scanner written in C++.

## Features

- Scans system, user, private, or all ports
- Non-blocking socket logic with select-based timeout
- Multi-threaded scanning
- Clean output with optional progress bar
- Common ports dictionary with service names

## Installation

```bash
make
sudo make install
```
## Uninstallation
```bash
sudo make uninstall
```
## Usage
```bash
fisherman -s 192.168.1.10     # Scan system ports (0-1023)
fisherman -u 192.168.1.10     # Scan user ports (1024-49151)
fisherman -p 192.168.1.10     # Scan private ports (49152-65535)
fisherman -c 192.168.1.10     # Scan common service ports
fisherman -a 192.168.1.10     # Scan all ports
fisherman -h                  # Display help
```
## License

See the ```LICENSE``` file
