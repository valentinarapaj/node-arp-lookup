#ifndef NETWORKSCANNER_H
#define NETWORKSCANNER_H

#include <string>

std::string getMACAddressFromIP(const std::string& ipAddress);
std::string getIPFromMACAddress(const std::string& macAddress);

#endif // NETWORKSCANNER_H
