# ARP Lookup

ARP Lookup is a library for performing ARP lookups to find IP addresses from MAC addresses and vice versa.

## Installation

You can install this module via npm:

```bash
npm install arp-lookup
```

## API

### getIPFromMACAddress(macAddress: string): Promise<string>

Returns the IP address corresponding to the provided MAC address. If no IP address is found for the given MAC address, the promise is rejected with an error message.

### getMACAddressFromIP(ipAddress: string): Promise<string>

Returns the MAC address corresponding to the provided IP address. If no MAC address is found for the given IP address, the promise is rejected with an error message.

## Example

Here's a simple example of how to use `arp-lookup`:
```javascript
const { getIPFromMACAddress, getMACAddressFromIP } = require('arp-lookup');

// Example usage
const macAddress = '50:57:9c:fa:bd:8f';
const ipAddress = '192.168.68.109';

// Retrieve IP address from MAC address
getIPFromMACAddress(macAddress)
    .then(ip => console.log(`IP address corresponding to MAC address ${macAddress}: ${ip}`))
    .catch(error => console.error(`Error: ${error}`));

// Retrieve MAC address from IP address
getMACAddressFromIP(ipAddress)
    .then(mac => console.log(`MAC address corresponding to IP address ${ipAddress}: ${mac}`))
    .catch(error => console.error(`Error: ${error}`));

```
## License

This project is licensed under the MIT License
