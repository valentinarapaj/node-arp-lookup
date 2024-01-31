#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Ws2_32.lib") 

std::string getMACAddressFromIP(const std::string& ipAddress) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return "";
    }

    sockaddr_in sa;
    if (inet_pton(AF_INET, ipAddress.c_str(), &sa.sin_addr) != 1) {
        std::cerr << "Invalid IP address: " << ipAddress << std::endl;
        WSACleanup();
        return "";
    }

    ULONG macAddr[2];
    ULONG macAddrLen = sizeof(macAddr);
    DWORD ret = SendARP(sa.sin_addr.s_addr, 0, macAddr, &macAddrLen);
    if (ret != NO_ERROR) {
        std::cerr << "SendARP failed with error: " << ret << std::endl;
        WSACleanup();
        return "";
    }

    char macStr[18];
    sprintf_s(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
        (int)((macAddr[0] >> 0) & 0xFF),    
        (int)((macAddr[0] >> 8) & 0xFF),  
        (int)((macAddr[0] >> 16) & 0xFF),  
        (int)((macAddr[0] >> 24) & 0xFF),    
        (int)((macAddr[1] >> 0) & 0xFF),   
        (int)((macAddr[1] >> 8) & 0xFF));

    WSACleanup();
    return macStr;
}

std::string getIPFromMACAddress(const std::string& macAddress) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return "";
    }

    MIB_IPNETTABLE* pIpNetTable = nullptr;
    DWORD dwSize = 0;
    DWORD dwRetVal = GetIpNetTable(pIpNetTable, &dwSize, false);
    if (dwRetVal == ERROR_INSUFFICIENT_BUFFER) {
        pIpNetTable = (MIB_IPNETTABLE*)malloc(dwSize);
        dwRetVal = GetIpNetTable(pIpNetTable, &dwSize, false);
    }

    if (dwRetVal != NO_ERROR) {
        std::cerr << "GetIpNetTable failed with error: " << dwRetVal << std::endl;
        WSACleanup();
        return "";
    }

    std::string foundIPAddress;
    for (DWORD i = 0; i < pIpNetTable->dwNumEntries; i++) {
        MIB_IPNETROW& row = pIpNetTable->table[i];
        char macStr[18];
        sprintf_s(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
            row.bPhysAddr[0], row.bPhysAddr[1], row.bPhysAddr[2],
            row.bPhysAddr[3], row.bPhysAddr[4], row.bPhysAddr[5]);

        std::string lowercaseMacStr = toLowercase(macStr);
        std::string lowercaseMacAddress = toLowercase(macAddress);

        if (lowercaseMacStr == lowercaseMacAddress) {
            char ipAddress[INET_ADDRSTRLEN]; 
            if (InetNtop(AF_INET, &row.dwAddr, ipAddress, INET_ADDRSTRLEN) == NULL) {
                std::cerr << "InetNtop failed\n";
                break;
            }
            foundIPAddress = ipAddress;
            break;
        }
    }

    free(pIpNetTable);
    WSACleanup();
    return foundIPAddress;
}

std::string wideCharToString(const wchar_t* wideCharStr) {
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideCharStr, -1, nullptr, 0, nullptr, nullptr);
    if (bufferSize == 0) {
        std::cerr << "WideCharToMultiByte failed\n";
        return "";
    }

    std::string result(bufferSize - 1, 0);
    if (WideCharToMultiByte(CP_UTF8, 0, wideCharStr, -1, &result[0], bufferSize, nullptr, nullptr) == 0) {
        std::cerr << "WideCharToMultiByte failed\n";
        return "";
    }

    return result;
}

std::string toLowercase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}