import { useEffect, useState } from "react";
import AddProduct from "../../components/addProduct";
import DeleteProduct from "../../components/deleteProduct";
import EditProduct from "../../components/editProduct";
import ShowStock from "../../components/showStock";
import './adminProducts.css'

const AdminProducts = () => {
  const [activePage, setActivePage] = useState("addProduct");
  const [results, setResults] = useState([]);

  const handlePageClick = (page) => {
    setActivePage(page);
  };

  useEffect(() => {
    fetch('http://localhost:7000/products/admin')
      .then(response => response.json())
      .then(data => setResults(data))
      .catch(error => console.log(error));
  }, []);

  const renderPage = () => {
    switch (activePage) {
      case "addProduct":
        return <AddProduct results={results} setResults={setResults}/>;
      case "seeStock":
        return <ShowStock results={results} setResults={setResults}/>;
      case "deleteProduct":
        return <DeleteProduct results={results} setResults={setResults}/>;
      case "editProduct":
        return <EditProduct results={results} setResults={setResults}/>;
      default:
        return <AddProduct />;
    }
  };

  return (
    <>
        <div className="prod-options">
                <button onClick={() => handlePageClick("addProduct")}>Add</button>
                <button onClick={() => handlePageClick("deleteProduct")}>Delete</button>
                <button onClick={() => handlePageClick("editProduct")}>Edit</button>
                <button onClick={() => handlePageClick("seeStock")}>Stock</button>
        </div>
        {renderPage()}
    </>
  );
};

export default AdminProducts;