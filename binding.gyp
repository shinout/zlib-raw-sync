{
  "targets": [
    {
      "target_name": "zlib_raw_sync",
      "sources": [
        "src/zlib_raw_sync.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "link_settings": {
        "libraries": [
          "-lz"
        ]
      }
    }
  ]
}
