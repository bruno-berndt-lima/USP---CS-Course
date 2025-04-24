import React from 'react';
import './CheckoutItem.css';

const CheckoutItem = ({product, quantity}) => {
    return (  
        <li key={product.id} className='checkout-item'>
            <div className='checkout-item-img'>
                <img src={product.image} alt={product.model} />
            </div>
            <div className="checkout-item-name">
                <p>{product.model}</p>
            </div>
            <div className="checkout-item-quantity">
                <p>x{quantity}</p>
            </div>
            <div className="checkout-item-price">
                <p>Total: R${(parseFloat(product.price) * parseFloat(quantity)).toFixed(2)}</p>
            </div>
        </li>
    );
}
 
export default CheckoutItem;