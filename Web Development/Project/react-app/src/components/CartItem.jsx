import React, { useEffect, useState } from 'react';
import './CartItem.css'
import {MdDeleteOutline} from 'react-icons/md'
import { Link } from 'react-router-dom';

const CartItem = ({results, item, size, handleQuantity, removeItem}) => {
    // console.log(item)
    // const [product, setProduct] = useState(results.filter(e => {
    //     if(e._id === item.product) return e;
    // })[0]);
    const [product, setProduct] = useState({});

    async function getCartItem()  {
        const response = await fetch(`http://localhost:7000/products/admin/${item.product}`);
        
        if (!response.ok) {
          const message = `An error occurred: ${response.statusText}`;
          console.log(message);
          return;
        }    
        const data = await response.json();    
    
        setProduct(data);
    };

    useEffect(() => {
        getCartItem();
        console.log(product)
    }, []);

    //Listener do botão de diminuir quantidade de um produto no carrinho
    const handleDecrement = () => {
        //Caso a quantidade seja maior que 1 pode ser removida uma unidade
        if(size.stock > 1) {
            //Carregando o novo estado, atraves de um map dos tamanhos do produto em questão
            const newState = {...product, sizes: product.sizes.map(e => {
                //Ao encontrar o tamanho correto, o estoque (quantidade de itens no carrinho do cliente) é diminuído em uma unidade
                if(e.size == size.size) return {size: e.size, stock: e.stock - 1};
                //Caso contrário continua a mesma quantidade
                else return e
            })};

            //Função que modifica as quantidades no carrinho em si para calculo de total
            handleQuantity(size.stock - 1, size.size, product._id);

            //Atualizando estado do produto
            setProduct(newState);
        }      
    }

    //Listener do botão de aumentar quantidade de um produto no carrinho
    const handleIncrement = () => {   
        //Para essa função é necessário encontrar o item em si dentro do banco de dados para encontrar o estoque real do item
        const filterItem = results.filter(item => {
            if(item._id == product._id) return item;
        })[0];

        //Apos encontrar o item, é necessário encontrar o tamanho no array sizes
        const filterSize = filterItem.sizes.filter(e => {
            if(size.size == e.size) return e;
        })[0];

        //Para incrementar é necessário que a quantidade de produtos em seu tamanho seja menor que no estoque de mesmo tamanho e produto
        if(parseInt(size.stock) < parseInt(filterSize.stock)) {
            const newState = {...product, sizes: product.sizes.map(e => {
                if(e.size == size.size) return {size: e.size, stock: parseInt(e.stock) + 1};
                else return e
            })};

            //Função que modifica as quantidades no carrinho em si para calculo de total
            handleQuantity(parseInt(size.stock) + 1, size.size, product._id);

            //Atualizando estado do produto
            setProduct(newState);
        } else { //Caso a quantidade no carrinho ao incrementar seja maior que no estoque, da um alerta ao usuario e não incrementa
            alert('Quantidade acima do estoque')
        }
    }

    const handleDelete = () => {
        //Função para remover um item deve ser realizada no carrinho, um item não é capaz de se remover
        removeItem(product._id, size.size);
    }

    return (  
        <>
            <div className="cart-item-container">
                <div className="cart-item-info">
                    <div className="cart-item-icon">
                        <img src={product.image} alt={product.model} />
                    </div>
                    <div className="cart-item-info-text">
                        <div className="cart-item-name">
                            <Link to={`/product/${product.slug}`}><p>{product.model}</p></Link>
                            <MdDeleteOutline onClick={handleDelete}/>
                        </div>
                        <div className="cart-item-size">
                            <p>Tamanho: {size.size}</p>
                        </div>
                    </div>
                </div>
                <div className="cart-item-quantity-price">
                    <div className="cart-item-qtt-selection">
                        <button onClick={handleDecrement}>-</button>
                        <input type='number' value={size.stock} readOnly='readonly'></input>
                        <button onClick={handleIncrement}>+</button>
                    </div>
                    <p>R$ {(product.price * size.stock).toFixed(2)}</p>
                </div>
            </div>
        </>
    );
}
 
export default CartItem;