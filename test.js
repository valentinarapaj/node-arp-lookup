const arpLookup = require('./build/Release/arp_lookup');

// Assuming you've imported the functions from the module where they're defined
const { getIPFromMACAddress, getMACAddressFromIP } = require('./build/Release/arp_lookup');

// Example usage
const macAddress = '50:57:9c:fa:bd:8f';
const ipAddress = '192.168.68.109';

console.log("getIPFromMACAddress(macAddress) -> ", getIPFromMACAddress(macAddress));
// console.log("getMACAddressFromIP(ipAddress) -> ", getMACAddressFromIP(ipAddress));