import { useEffect, useState } from "react";
import { useNavigate } from 'react-router-dom'
import './addProduct.css'

const AddProduct = () => {
    const [results, setResults] = useState([]);

    useEffect(() => {
        fetch('http://localhost:7000/products/admin')
          .then(response => response.json())
          .then(data => setResults(data))
          .catch(error => console.log(error));
      }, []);

    const [brand, setBrand] = useState('');
    const [model, setModel] = useState('');
    const [slug, setSlug] = useState('');
    const [price, setPrice] = useState('');
    const [description, setDescription] = useState('');
    const [image, setImage] = useState('');
    const [size, setSize] = useState('');
    const [stock, setStock] = useState('');
    const [sizesArray, setSizesArray] = useState([]);

    const [isPending, setIsPending] = useState(false);
    const navigate = useNavigate();

    const handleSubmit = (e) => {
        e.preventDefault();
        const product = { brand, model, slug, price, sizes: sizesArray, description, image };
        setIsPending(true)

        let newResults = [...results];
        newResults.push(product);
        setResults(newResults);

        fetch('http://localhost:7000/products', {
            method: 'POST',
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(product)
        }).then(() => {
            console.log('new product added');
            setIsPending(false);
            navigate('/admin');
        });
    }

    const handleAddSize = (e) => {
        e.preventDefault();
        setSizesArray([...sizesArray, { size, stock }]);
        setSize('');
        setStock('');
    };

    const handleAddAnotherProduct = () => {
        setBrand('');
        setModel('');
        setSlug('');
        setPrice('');
        setDescription('');
        setImage('');
        setSize('');
        setStock('');
        setSizesArray([]);
    };

    return (
        <div className="add-product">
            <h2>Add a New Product</h2>
            <form onSubmit={handleSubmit}>

                <label>Brand:</label>
                <input 
                    type="text"
                    required
                    value={brand}
                    onChange={(e) => setBrand(e.target.value)}
                />
                <label>Model:</label>
                <input 
                    type="text"
                    required
                    value={model}
                    onChange={(e) => setModel(e.target.value)}
                />
                <label>Slug:</label>
                <input 
                    type="text"
                    required
                    value={slug}
                    onChange={(e) => setSlug(e.target.value)}
                />
                <label>Price:</label>
                <input 
                    type="text"
                    required
                    value={price}
                    onChange={(e) => setPrice(e.target.value)}
                />
                <label>Description:</label>
                <textarea
                    required
                    value={description}
                    onChange={(e) => setDescription(e.target.value)}
                ></textarea>

                {/* {sizesArray.map((sizeObj, index) => (
                    <div key={index}>
                        <p>Size: {sizeObj.size}</p>
                        <p>Size quantity: {sizeObj.stock}</p>
                    </div>
                ))} */}
                
                <div>
                    <label>Size:</label>
                    <input
                        type="text"
                        value={size}
                        onChange={(e) => setSize(e.target.value)}
                    />
                </div>
                <div>
                    <label>Size quantity:</label>
                    <input
                        type="text"
                        value={stock}
                        onChange={(e) => setStock(e.target.value)}
                    />
                </div>
                <button onClick={handleAddSize}>
                    Add Size
                </button>

                <label>Image URL:</label>
                <textarea
                    required
                    value={image}
                    onChange={(e) => setImage(e.target.value)}
                ></textarea>
        
                
                {!isPending && <button>Add Product</button>}

                <button id="add-new-btn" type="button" onClick={handleAddAnotherProduct}>
                    Add Another Product
                </button>   
                
            </form>
        </div>
    );
}

export default AddProduct;
