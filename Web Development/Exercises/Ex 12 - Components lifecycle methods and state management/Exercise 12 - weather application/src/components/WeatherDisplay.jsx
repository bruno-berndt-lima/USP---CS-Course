import React, { useEffect, useState } from 'react';
import '../App.css';

const WeatherDisplay = ({cityName}) => {
    const [data, setData] = useState({
        city: '',
        lat: null,
        lon: null,
        temperature: null,
        weatherCode: null,
        icon: '',
        isValid: false
    })

    const apiKey = '873ee81bc3de3bf22278cae45db3d6f9';

    const weather_code = {
        0: ["Clear sky", "01d"],
        1: ["Mainly clear", "01d"], 
        2: ["Partly Cloudy", "02d"],
        3: ["Overcast", "03d"],
        45: ["Fog", "50d"],
        48: ["Depositing rime fog", "50d"],
        51: ["Light drizzle", "09d"],
        53: ["Moderate drizzle", "09d"],
        55: ["Dense drizzle", "09d"],
        56: ["Light freezing drizzle", "09d"],
        57: ["Dense freezing drizzle", "09d"],
        61: ["Slight rain", "10d"],
        63: ["Moderate rain", "10d"],
        65: ["Heavy rain", "10d"],
        66: ["Light freezing rain", "13d"],
        67: ["Heavy freezing rain", "13d"],
        71: ["Slight snow fall", "13d"],
        73: ["Moderate snow fall", "13d"],
        75: ["Heavy snow fall","13d"],
        77: ["Snow grains", "13d"], 
        80: ["Slight rain showers", "09d"],
        81: ["Moderate rain showers", "09d"],
        82: ["Violent rain showers", "09d"],
        85: ["Slight snow showers", "13d"],
        86: ["Heavy snow showers", "13d"],
        95: ["Thunderstorm", "11d"],
        96: ["Thunderstorm with slight hail", "11d"],
        99: ["Thunderstorm with heavy hail", "11d"]
    }

    const getWeather = async (apikey, city) => {
        const city_url = `http://api.openweathermap.org/geo/1.0/direct?q=${city}&appid=${apikey}`;
        
        let name = '', lat = 0, lon = 0;
        let flag = false

        await fetch(city_url)
            .then(response => response.json())
            .then(data => {
                const result = data[0];
                console.log(result);
                name = result.name; lat = result.lat; lon = result.lon;
                flag = true;
            })
            .catch(error => {
                flag = false;
                setData({city: "Cidade invalida"})
                console.log(error);
            })

        /*
        const city_response = await fetch(city_url);

        const city_data = await city_response.json();

        const city_result = city_data[0];
        if(city_result == undefined) {
            setData({
                city: '',
                lat: null,
                lon: null,
                temperature: null,
                weatherCode: null,
                icon: '',
                isValid: false
            })
        }

        let name = city_result.name, lat = city_result.lat, lon = city_result.lon;
        */

        const weather_url = `http://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lon}&current_weather=true`;

        if(flag){
            await fetch(weather_url)   
                .then(response => response.json())
                .then(result => {
                    console.log(result);
                    let temperature = result.current_weather.temperature;
                    let icon = `https://openweathermap.org/img/wn/${weather_code[result.current_weather.weathercode][1]}@2x.png`
                    let code = weather_code[result.current_weather.weathercode][0];
                    console.log(name);
                    setData({
                        city: name,
                        lat: lat,
                        lon: lon,
                        temperature: temperature + " °C",
                        weatherCode: code,
                        icon: icon,
                    })
                })}
        
    }  

    useEffect(() => {
        try {
            getWeather(apiKey, cityName);
        }
        catch {
            setData({
                city: 'Cidade invalida',
                lat: null,
                lon: null,
                temperature: null,
                weatherCode: null,
                icon: '',
            })
        }
    }, [cityName]);

    return (  
        <> 
            <br />
            <span>{data.city}</span> <br />
            <img src={data.icon} width={100} /> <br />
            {data.temperature} <br />
            {data.weatherCode}
        </>
    );
}
 
export default WeatherDisplay;