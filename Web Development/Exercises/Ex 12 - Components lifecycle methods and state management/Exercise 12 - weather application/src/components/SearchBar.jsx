import React from 'react';
import { useState } from 'react';
import '../App.css'

const SearchBar = ({handleCityName}) => {
    const [inputData, setInputData] = useState('');

    const handleInputData = e => {
        setInputData(e.target.value);
    }
    
    const handleSendInput = e => {
        if(e.key === 'Enter') {
            handleCityName(e.target.value);
        }
    }

    return (  
        <input type="text" onChange={handleInputData} onKeyDown={handleSendInput} value={inputData}/>
    );
}
 
export default SearchBar;