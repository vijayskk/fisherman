#include <vector>
#include <unordered_map>

using std::vector;

std::vector<int> common_ports = {
    20,   // FTP Data
    21,   // FTP Control
    22,   // SSH
    23,   // Telnet
    25,   // SMTP
    53,   // DNS
    67,   // DHCP Server
    68,   // DHCP Client
    69,   // TFTP
    80,   // HTTP
    110,  // POP3
    111,  // RPCbind
    119,  // NNTP
    123,  // NTP
    135,  // MS RPC
    137,  // NetBIOS Name Service
    138,  // NetBIOS Datagram
    139,  // NetBIOS Session
    143,  // IMAP
    161,  // SNMP
    179,  // BGP
    194,  // IRC
    389,  // LDAP
    443,  // HTTPS
    445,  // SMB
    465,  // SMTPS
    514,  // Syslog
    515,  // Printer
    993,  // IMAPS
    995,  // POP3S
    1080, // SOCKS
    1194, // OpenVPN
    1433, // MSSQL
    1521, // Oracle DB
    1723, // PPTP
    2049, // NFS
    2082, // cPanel
    2083, // cPanel SSL
    3306, // MySQL
    3389, // RDP
    3690, // SVN
    4444, // Metasploit handler
    5000, // UPnP
    5432, // PostgreSQL
    5900, // VNC
    6000, // X11
    6379, // Redis
    8080, // HTTP-alt
    8000, // Python Server
    8443, // HTTPS-alt
    8888, // Web admin interfaces
    9000, // SonarQube, PHP-FPM
    9200, // Elasticsearch
    10000 // Webmin
};


std::unordered_map<int, std::string> common_services = {
    {20,   "FTP Data"},
    {21,   "FTP Control"},
    {22,   "SSH"},
    {23,   "Telnet"},
    {25,   "SMTP"},
    {53,   "DNS"},
    {67,   "DHCP Server"},
    {68,   "DHCP Client"},
    {69,   "TFTP"},
    {80,   "HTTP"},
    {110,  "POP3"},
    {111,  "RPCbind"},
    {119,  "NNTP"},
    {123,  "NTP"},
    {135,  "Microsoft RPC"},
    {137,  "NetBIOS Name"},
    {138,  "NetBIOS Datagram"},
    {139,  "NetBIOS Session"},
    {143,  "IMAP"},
    {161,  "SNMP"},
    {179,  "BGP"},
    {194,  "IRC"},
    {389,  "LDAP"},
    {443,  "HTTPS"},
    {445,  "SMB"},
    {465,  "SMTPS"},
    {514,  "Syslog"},
    {515,  "Printer"},
    {993,  "IMAPS"},
    {995,  "POP3S"},
    {1080, "SOCKS Proxy"},
    {1194, "OpenVPN"},
    {1433, "Microsoft SQL Server"},
    {1521, "Oracle Database"},
    {1723, "PPTP VPN"},
    {2049, "NFS"},
    {2082, "cPanel"},
    {2083, "cPanel (SSL)"},
    {3306, "MySQL"},
    {3389, "Remote Desktop (RDP)"},
    {3690, "SVN"},
    {4444, "Metasploit Handler"},
    {5000, "UPnP"},
    {5432, "PostgreSQL"},
    {5900, "VNC"},
    {6000, "X11"},
    {6379, "Redis"},
    {8000, "Python Server"},
    {8080, "HTTP-alt"},
    {8443, "HTTPS-alt"},
    {8888, "Web Admin"},
    {9000, "SonarQube/PHP-FPM"},
    {9200, "Elasticsearch"},
    {10000, "Webmin"}
};