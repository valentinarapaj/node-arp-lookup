/**
 * Library for performing ARP lookups to find IP addresses from MAC addresses and vice versa.
 */
declare module 'arp-lookup' {
    /**
     * Retrieves the IP address corresponding to the provided MAC address.
     * @param macAddress The MAC address for which to find the IP address.
     * @returns A promise that resolves with the corresponding IP address if found, otherwise rejects with an error.
     */
    export function getIPFromMACAddress(macAddress: string): Promise<string>;

    /**
     * Retrieves the MAC address corresponding to the provided IP address.
     * @param ipAddress The IP address for which to find the MAC address.
     * @returns A promise that resolves with the corresponding MAC address if found, otherwise rejects with an error.
     */
    export function getMACAddressFromIP(ipAddress: string): Promise<string>;
}
