import React from 'react';
import './adminOrdersDetails.css'

const OrderDetails = ({result}) => {
    console.log(result);
    return ( 
        <>
            <div className="order-header">
                <div className="order-id">Order ID</div>
                <div className="order-username">User</div>
                <div className="order-user-address">Delivery Address</div>
                <div className="order-items">Products</div>
            </div>
            
            <div className="order-preview" key={result.number}>
                <div className="order-id">
                    <p>{result.number}</p>
                </div>

                <div className="order-username">
                    <h2>{result.user.name}</h2>
                </div>
                
                <div className="order-user-address">
                    <p><strong>Address</strong></p>
                {result && result.user && result.user.address ? (
                    <React.Fragment key={result.user.address._id}>
                        <p>{result.user.address.street}, N° {result.user.address.number} - {result.user.address.neighbourhood}</p>
                        <p>{result.user.address.complement}</p>
                        <p>{result.user.address.city} - {result.user.address.state}</p>
                        <p>CEP: {result.user.address.cep}</p>
                        <p>{result.user.address.additional}</p>
                    </React.Fragment>
                    ) : <></>}
                </div>

                <div className="order-items">
                    {result && result.items && result.items.map((itemsInfo) => (
                            <React.Fragment key={itemsInfo._id}>
                            <p><strong>{itemsInfo.product.brand}  {itemsInfo.product.model}</strong></p>
                            <p>Size: | {itemsInfo.sizes && itemsInfo.sizes.map(e => {
                            if(e.stock > 0) return ` ${e.size} |`;
                            })}</p>
                            <p>Quantity: | {itemsInfo.sizes && itemsInfo.sizes.map(e => {
                                if(e.stock > 0) return ` ${e.stock} |`;
                            })}</p>
                            <p>Total: R$ {(itemsInfo.product.price * itemsInfo.sizes.reduce((acc, object) => {
                                return acc + object.stock;
                            }, 0)).toFixed(2)}</p>

                            </React.Fragment>
                    ))}
                </div>
            </div>
        </>
     );
}
 
export default OrderDetails;