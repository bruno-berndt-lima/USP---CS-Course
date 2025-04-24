import React, { useEffect, useState } from 'react';
import Searchbar from './Searchbar';
import SearchResultsList from './searchResultsList';

const EditProduct = () => {
  const [results, setResults] = useState([]);
  const [editedProduct, setEditedProduct] = useState({
    brand: '',
    model: '',
    price: '',
    description: '',
    image: '',
    sizes: [{ size: '', stock: '' }]
  });

  const handleClick = (action, productId) => {
     if (action === 'edit') {
      console.log('Editing product:', productId);
      const selectedProduct = results.find(result => result._id === productId);
      setEditedProduct(selectedProduct);
    }
  };

  const handleInputChange = (e) => {
    const {name,value} = e.target;
      setEditedProduct((prev) => {
          return { ...prev, [name]:value}
      })
  }
  
  const handleSizeChange = (e, index) => {
    const newSize = e.target.value;
    setEditedProduct((prevState) => {
      const updatedSizes = [...prevState.sizes];
      updatedSizes[index].size = newSize;
      return { ...prevState, sizes: updatedSizes };
    });
  };
  
  const handleStockChange = (e, index) => {
    const newStock = e.target.value;
    setEditedProduct((prevState) => {
      const updatedSizes = [...prevState.sizes];
      updatedSizes[index].stock = newStock;
      return { ...prevState, sizes: updatedSizes };
    });
  };
  
  const handleAddSize = () => {
    setEditedProduct((prevState) => {
      const updatedSizes = [...prevState.sizes, { size: '', stock: '' }];
      return { ...prevState, sizes: updatedSizes };
    });
  };

  const handleRemoveSize = (index) => {
    setEditedProduct((prevState) => {
      const updatedSizes = [...prevState.sizes];
      updatedSizes.splice(index, 1);
      return { ...prevState, sizes: updatedSizes };
    });
  };


  const handleUpdate = () => {
    console.log('Updating product:', editedProduct);
  
    fetch(`http://localhost:7000/products/${editedProduct._id}`, {
      method: 'PUT',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(editedProduct),
    })
      .then(response => {
        if (response.ok) {
          console.log('Product updated successfully');
  
          setResults(prevResults => {
            const updatedResults = prevResults.map(result => {
              if (result._id === editedProduct._id) {
                return editedProduct;
              } else {
                return result;
              }
            });
            return updatedResults;
          });
  
          setEditedProduct({
            brand: '',
            model: '',
            slug: '',
            price: '',
            description: '',
            image: '',
            sizes: [{ size: '', stock: '' }],
          });
        } else {
          console.log('Product update failed');
        }
      })
      .catch(error => console.log(error));
  };
  
  
  const fetchResults = () => {
    fetch('http://localhost:7000/products/admin')
      .then(response => response.json())
      .then(data => setResults(data))
      .catch(error => console.log(error));
  };


  useEffect(() => {
    fetchResults();
  }, []);

  return (
    <>
      <div className="searchbar-div">
        <Searchbar setResults={setResults} />
        <SearchResultsList
          results={results}
          command="editProduct"
          handleClick={handleClick}
          editedProduct={editedProduct}
          handleInputChange={handleInputChange}
          handleUpdate={handleUpdate}
          handleSizeChange={handleSizeChange}
          handleStockChange={handleStockChange}
          handleRemoveSize={handleRemoveSize}
          handleAddSize={handleAddSize}
        />
      </div>
    </>
  );
};

export default EditProduct;
