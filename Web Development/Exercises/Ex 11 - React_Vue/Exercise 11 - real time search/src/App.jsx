import React, { useEffect, useState } from 'react';

import './App.css'
import Book from './components/Book';

const App = () => {
  const Books = [
    `A Tale of Two Cities`,
    `The Little Prince`,
    `Harry Potter and the Philosopher's Stone`,
    `And Then There Were None`,
    `Dream of the Red Chamber`,
    `The Hobbit`,
    `The Lion, the Witch and the Wardrobe`,
    `She: A History of Adventure`,
    `Vardi Wala Gunda`,
    `The Da Vinci Code`,
    `Harry Potter and the Chamber of Secrets`,
    `Harry Potter and the Prisoner of Azkaban`,
    `Harry Potter and the Goblet of Fire`,
    `Harry Potter and the Order of the Phoenix`,
    `Harry Potter and the Half-Blood Prince`,
    `Harry Potter and the Deathly Hallows`,
    `O Alquimista`,
    `The Catcher in the Rye`,
    `The Bridges of Madison County`,
    `Ben-Hur: A Tale of the Christ`
  ].sort();

  const [bookList, setBookList] = useState(Books);

  const [search, setSearch] = useState(['']);

  const handleSearch = e => {
    setSearch(e.target.value);
  }

  useEffect(() => {
    if(search === '') {
      setBookList(Books);
    } else {
      setBookList(Books.filter(book => book.toLowerCase().includes(search.toString().toLowerCase())));
    }
    console.log(search.toString().toLowerCase());
  }, [search]);

  return (  
    <div className="container">
      <h1>Search</h1>
      <input onChange={handleSearch} value={search} className='search-input' type="text" />
      <h2>Results</h2>
      <>{bookList.map(book => <Book title={book} />)}</>
    </div>
  );
}
 
export default App;