const arpLookup = require('./build/Release/arp_lookup');

async function getIPFromMACAddress(macAddress) {
    return new Promise((resolve, reject) => {
        const ip = arpLookup.getIPFromMACAddress(macAddress);

        if (ip) resolve(ip)
        else reject("Could not find IP Address for the given Mac Address")
    });
}

async function getMACAddressFromIP(ipAddress) {
    return new Promise((resolve, reject) => {
        const mac = arpLookup.getMACAddressFromIP(ipAddress);

        if (mac) resolve(mac)
        else reject("Could not find Mac Address for the given IP Address")
    });
}

module.exports = {
    getIPFromMACAddress,
    getMACAddressFromIP
};
