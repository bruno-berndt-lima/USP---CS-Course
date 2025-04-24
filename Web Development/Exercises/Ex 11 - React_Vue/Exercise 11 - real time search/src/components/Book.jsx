import React from 'react';

import './Book.css';

const Book = ({title}) => {
    return (  
        <div className="book-container">
            {title}
        </div>
    );
}
 
export default Book;