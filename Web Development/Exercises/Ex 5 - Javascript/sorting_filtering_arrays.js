"use strict"

let cities = [
    {
        name: "New York",
        population: 8405837,
        temperature: 20,
        weatherDescription: "Sunny"          
    },
    {
        name: "London",
        population: 8799800,
        temperature: 11,
        weatherDescription: "Cloudy" 
    },
    {
        name: "Tokyo",
        population: 13988129,
        temperature: 16,
        weatherDescription: "Cloudy" 
    },
    {
        name: "Belo Horizonte",
        population: 2722000,
        temperature: 24,
        weatherDescription: "Sunny" 
    },
    {
        name: "Manila",
        population: 1780342,
        temperature: 29,
        weatherDescription: "Clear" 
    },
    {
        name: "Cape Town",
        population: 4710000,
        temperature: 19,
        weatherDescription: "Sunny" 
    },
    {
        name: "Araraquara",
        population: 238339,
        temperature: 22,
        weatherDescription: "Rainy" 
    }
]

function sortCities(cities, sortCriterion) {
    let aux = []
    for(let city in cities) {
        aux[city] = cities[city]
    }
    switch(sortCriterion) {
        case "population":
            aux.sort(function(a,b){return a.population - b.population})
            break
        case "name":
            aux.sort(function(a,b){if (a.name < b.name) return -1; if (a.name > b.name) return 1; return 0;})
            break
        case "temperature":
            aux.sort(function(a,b){return a.temperature - b.temperature})
            break
        case "weather":
            aux.sort(function(a,b){if (a.weatherDescription < b.weatherDescription) return -1; if (a.weatherDescription > b.weatherDescription) return 1; return 0;})
            break
    }

    return aux
}

function filterCities(cities, filterCriterion) {
    let aux = cities.filter(filterCriterion)

    return aux
}

function processCities(cities, filterCriterion, sortCriterion) {
    let filteredArray = filterCities(cities, filterCriterion)

    return sortCities(filteredArray, sortCriterion)
}


/* Teste para ordenar por name

let sortedCities = sortCities(cities, "name")
for (const city in cities) {
    console.log(arrasortedCities[city])
}
*/

/* Teste para ordenar por population

 let sortedCities = sortCities(cities, "population")
 for (const city in cities) {
     console.log(arrasortedCities[city])
 }
*/

/* Teste para ordenar por temperature

 let sortedCities = sortCities(cities, "temperature")
 for (const city in cities) {
     console.log(arrasortedCities[city])
 }
*/

/* Teste para ordenar por weatherDescription

let sortedCities = sortCities(cities, "weather")
for (const city in cities) {
     console.log(arrasortedCities[city])
 }
*/

/* Teste para filtrar por weatherDescription
    console.log(filterCities(cities, c => c.weatherDescription === "Sunny"))
*/

/* Teste para filtrar por population
    console.log(filterCities(cities, c => c.population > 2000000))
*/

/* Teste para filtrar por population > 2.000.000 e ordenar por population
    console.log(processCities(cities, c => c.population > 2000000, "population"))
*/

/* Teste para filtrar por weatherDescription == "Sunny" e ordenar por name
    console.log(processCities(cities,  c => c.weatherDescription === "Sunny", "name"))
*/

/* Teste para filtrar por temperature > 20 e ordenar por temperature
    console.log(processCities(cities, c => c.temperature > 20, "temperature"))
*/