1. Make a zipper file
  - In this file, we define methods 
    - We first check if the user specified a folder or a file (DONE)
    - for reading files specified by the user (DONE)
      - Make the huffmanTree (DONE)
      - %HuffmanTree:TreeSize%:Pack the Huffman Tree at the start of the file
      - %filename:filesize%:Make the compressed file
    - The user may specify a folder
      - We make a global HuffmanTree
      - Concatenate HuffmanTree before the FolderTree
      - We make a tree for the folder structure
        - It contains the name and size of each file
      - %FolderTree:FolderTreeSize%
2. Making an unzipper file
  - In this file, we define methods: 
