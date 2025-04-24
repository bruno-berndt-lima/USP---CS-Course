// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

// Importing OpenZeppelin ERC721 contracts and utilities
import "@openzeppelin/contracts@5.0.0/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts@5.0.0/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts@5.0.0/token/ERC721/extensions/ERC721Burnable.sol";
import "@openzeppelin/contracts@5.0.0/access/Ownable.sol";
import "@openzeppelin/contracts/utils/Counters.sol";

contract IArte_NFT is ERC721, ERC721URIStorage, ERC721Burnable, Ownable {
    // Using Counters utility from OpenZeppelin to track token IDs
    using Counters for Counters.Counter;

    // Counter to keep track of the token IDs being minted
    Counters.Counter private _tokenIdCounter;

    // Price for minting an NFT (set to 0.01 ether = 10000000 GWEI)
    uint256 public mintPrice = 0.01 ether;

    // Maximum supply of NFTs that can be minted
    uint256 public maxSupply = 5;

    // Boolean to control if minting is enabled or not
    bool public isMintEnabled;

    // Constructor to initialize the NFT collection with a name (IArte) and symbol (IART), 
    // and set the initial owner of the contract
    constructor(address initialOwner) ERC721("IArte", "IART") Ownable(initialOwner) {}

    // Function to mint a new NFT, requires a URI (metadata link) and ether payment
    function safeMint(address to, string memory uri) public payable {
        // Ensures minting is enabled
        require(isMintEnabled, "Minting is not enabled.");
        // Ensures the correct amount of ether is sent for minting
        require(msg.value >= mintPrice, "Not enough ether sent for minting");
        // Ensures the max supply limit is not exceeded
        require(_tokenIdCounter.current() < maxSupply, "Max supply reached");

        // Get the next tokenId and increment the counter
        uint256 tokenId = _tokenIdCounter.current();
        _tokenIdCounter.increment();
        
        // Mint the NFT to the specified address and set the token URI (metadata link)
        _safeMint(to, tokenId);
        _setTokenURI(tokenId, uri);
    }

    // Function to enable or disable minting, only callable by the owner
    function toggleIsMintEnabled() external onlyOwner {
        isMintEnabled = !isMintEnabled;
    }

    // Function for the contract owner to withdraw the ether collected from minting fees
    function withdraw() external onlyOwner {
        // Transfer the entire contract balance to the owner
        payable(owner()).transfer(address(this).balance);
    }
    
    // The following functions are required overrides for Solidity when combining multiple inheritance.

    // Override tokenURI function to handle both ERC721 and ERC721URIStorage implementations
    function tokenURI(uint256 tokenId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (string memory)
    {
        return super.tokenURI(tokenId);
    }

    // Override supportsInterface function to handle interface checks for both ERC721 and ERC721URIStorage
    function supportsInterface(bytes4 interfaceId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (bool)
    {
        return super.supportsInterface(interfaceId);
    }
}
