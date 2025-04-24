import React from 'react';
import './showStock.css'
import Searchbar from './Searchbar';
import { useState, useEffect } from 'react';
import SearchResultsList from './searchResultsList';

const ShowStock = () => {
    const [results, setResults] = useState([]);
    
    useEffect(() => {
      fetch('http://localhost:7000/products/admin')
        .then(response => response.json())
        .then(data => setResults(data))
        .catch(error => console.log(error));
    }, []);

    
    return ( 
        <>
            <div className="searchbar-div">
                <Searchbar setResults={setResults} />

                <SearchResultsList results={results} />
            </div>
        </>
     );
}
 
export default ShowStock;