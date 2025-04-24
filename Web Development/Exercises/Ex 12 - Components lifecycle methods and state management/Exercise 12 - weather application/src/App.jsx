import { useState } from 'react';
import './App.css';
import SearchBar from './components/SearchBar';
import WeatherDisplay from './components/WeatherDisplay';

const App = () => {
  const [city, setCity] = useState('');

  const handleCityName = (cityName) => {
    setCity(cityName);
  }

  return ( 
    <div className='container'>
      <SearchBar handleCityName={handleCityName}></SearchBar>
      <WeatherDisplay cityName={city}></WeatherDisplay>
    </div> 
  );
}
 
export default App;