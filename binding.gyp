{
  "targets": [
    {
      "target_name": "arp_lookup",
      "sources": [
        "./src/main.cpp", 
        "./src/networkscanner.h", 
        "./src/networkscanner.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}
