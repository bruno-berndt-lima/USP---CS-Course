import React from 'react';
import './searchResultsList.css';
import ProductDetails from '../pages/admin/adminProductDetails';
import UsersDetails from '../pages/admin/adminUsersDetails';

const SearchResultsList = ({ 
    results, 
    command, 
    handleClick, 
    editedProduct, 
    handleInputChange, 
    handleUpdate, 
    handleSizeChange, 
    handleStockChange, 
    handleRemoveSize, 
    handleAddSize }) => {
    console.log(editedProduct);
    if(results.length > 0) {
        return (
            <div className="results-list">
            {results.map(result => {
                return (
                <div className="product-container" key={result._id}>
                    <ProductDetails result={result} />
                    
                    {command === 'deleteProduct' && (
                        <button className="delete-btn" onClick={() => handleClick('delete', result._id)}>
                            Delete
                        </button>
                    )}
    
                    {command === 'editProduct' && (
                        <button className="edit-btn" onClick={() => handleClick('edit', result._id)}>
                            Edit
                        </button>
                    )}
    
                    {editedProduct && result._id === editedProduct._id ? (
                    <div className="edit-product-container">
                        <div className="input-container">
                        <label htmlFor="brand">Brand:</label>
                        <input
                            type="text"
                            id="brand"
                            name="brand"
                            value={editedProduct.brand}
                            onChange={handleInputChange}
                        />
                        </div>
                        <div className="input-container">
                        <label htmlFor="model">Model:</label>
                        <input
                            type="text"
                            id="model"
                            name="model"
                            value={editedProduct.model}
                            onChange={handleInputChange}
                        />
                        </div >
                        <div className="input-container">
                        <label htmlFor="slug">Slug:</label>
                        <input
                            type="text"
                            id="slug"
                            name="slug"
                            value={editedProduct.slug}
                            onChange={handleInputChange}
                        />
                        </div>
                        <div className="input-container">
                        <label htmlFor="price">Price:</label>
                        <input
                            type="number"
                            id="price"
                            name="price"
                            value={editedProduct.price}
                            onChange={handleInputChange}
                        />
                        
                        </div>
                        
                        <div className="input-container">
                        <label htmlFor="description">Description:</label>
                        <input
                            type="text"
                            id="description"
                            name="description"
                            value={editedProduct.description}
                            onChange={handleInputChange}
                        />
                        </div>
                        <div className="input-container">
                        <label htmlFor="image">Image:</label>
                        <input
                            type="text"
                            id="image"
                            name="image"
                            value={editedProduct.image}
                            onChange={handleInputChange}
                        />
                        </div>
                        {editedProduct.sizes.map((sizeObj, index) => (
                        <div className="input-container">
                            <label htmlFor={`size-${index}`}>Size:</label>
                            <input
                            type="text"
                            id={`size-${index}`}
                            name={`size-${index}`}
                            value={sizeObj.size}
                            onChange={(e) => handleSizeChange(e, index)}
                            />
                            <label htmlFor={`stock-${index}`}>Quantity:</label>
                            <input
                            type="text"
                            id={`stock-${index}`}
                            name={`stock-${index}`}
                            value={sizeObj.stock}
                            onChange={(e) => handleStockChange(e, index)}
                            />
                            <button onClick={() => handleRemoveSize(index)}>Remove</button>
    
                        </div>
                        ))}
                        <div className="input-container">
                            <button onClick={handleAddSize}>Add New Size</button>
                        </div>
    
                        <button id='update-btn' onClick={handleUpdate}>Update</button>
                    </div>
                    ) : (<></>)}
                </div>
                );
            })}
            </div>
        );
    } else return (<></>);
};

export default SearchResultsList;
