// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

import "@openzeppelin/contracts@5.0.0/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts@5.0.0/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts@5.0.0/token/ERC721/extensions/ERC721Burnable.sol";
import "@openzeppelin/contracts@5.0.0/access/Ownable.sol";
import "@openzeppelin/contracts/utils/Counters.sol";

contract IArte_NFT is ERC721, ERC721URIStorage, ERC721Burnable, Ownable {
    using Counters for Counters.Counter;

    Counters.Counter private _tokenIdCounter;

    // Setting a minting fee
    uint256 public mintPrice = 0.01 ether; // 0.01 ETH = 10000000 GWEI

    uint256 public maxSupply = 5;
    bool public isMintEnabled;

    constructor(address initialOwner) ERC721("IArte", "IART") Ownable(initialOwner) {}

    function safeMint(address to, string memory uri) public payable {
        require(isMintEnabled, "Minting is not enabled.");
        require(msg.value >= mintPrice, "Not enough ether sent for minting");
        require(_tokenIdCounter.current() < maxSupply, "Max supply reached");

        uint256 tokenId = _tokenIdCounter.current();
        _tokenIdCounter.increment();
        
        _safeMint(to, tokenId);
        _setTokenURI(tokenId, uri);
    }

    function toggleIsMintEnabled() external onlyOwner {
        isMintEnabled = !isMintEnabled;
    }

    // Function for the owner to withdraw the collected minting fees
    function withdraw() external onlyOwner {
        payable(owner()).transfer(address(this).balance);
    }
    
    // The following functions are overrides required by Solidity.

    function tokenURI(uint256 tokenId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (string memory)
    {
        return super.tokenURI(tokenId);
    }

    function supportsInterface(bytes4 interfaceId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (bool)
    {
        return super.supportsInterface(interfaceId);
    }
}