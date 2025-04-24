import React from 'react';
import './Product.css';
import '../App.css';
import { Link } from 'react-router-dom';


const Product = ({item}) => {
    if(item.sizes.reduce((acc, object) => {
        return acc + object.stock;
    }, 0) > 0) return (  
        <section className="product">
            <Link className='product-link' to={`/product/${item.slug}`}>
                <div className="icon">
                    <img src={item.image} alt='Ultraboost Preto'></img>
                </div>
            </Link>
            <div className="product-infos">

                <Link className='product-link' to={`/product/${item.slug}`}>
                    <p>{item.brand}</p>
                    <h3>{item.model}</h3>
                </Link>
                <span>R${(parseFloat(item.price)).toFixed(2)}</span>
            </div>
        </section>
    );
}
 
export default Product;