import React from 'react';
import { useState, useEffect } from 'react';
import OrderDetails from './adminOrdersDetails';
import './adminOrders.css'


const AdminOrders = () => {
    const [results, setResults] = useState([]);
    
    useEffect(() => {
      fetch('http://localhost:7000/orders')
        .then(response => response.json())
        .then(data => setResults(data))
        .catch(error => console.log(error));
    }, []);

    return ( 
        <div className="orders-container">
            {results && results.map(result => (
                <OrderDetails result={result} key={result._id} />
            ))}
        </div>
     );
}
 
export default AdminOrders;