import React, { useEffect, useState } from 'react';
import Header from '../../components/Header';
import Footer from '../../components/Footer';

import './cart.css';
import { Link, useNavigate } from 'react-router-dom';
import CartItem from '../../components/CartItem';

const Cart = ({results, setResults, headerUser, setHeaderUser}) => {
    // Estado que possui os itens do carrinho
    const [items, setItems] = useState(headerUser.cart);
    
    async function getResults()  {
        const response = await fetch(`http://localhost:7000/products/admin`);
        
        if (!response.ok) {
          const message = `An error occurred: ${response.statusText}`;
          console.log(message);
          return;
        }
    
        const data = await response.json();
    
    
        setResults(data);

        let tmpTotal = 0;
        // Percorre por todos itens do carrinho
        for(let i = 0; i < items.length; i++) {
            // Percorre por todos tamanhos do carrinho
            for(let j = 0; j < items[i].sizes.length; j++) {
                // Soma o preço vezes a quantidade de itens
                tmpTotal += parseFloat(data.filter(e => {
                    if(e._id === items[i].product) return e
                })[0].price) * parseFloat(items[i].sizes[j].stock);
            }
        }   
        // Atualização do estado do preço total do carrinho
        setTotal(tmpTotal);
    };

    // Estado para calculo do total do carrinho
    const [total, setTotal] = useState(0);

    const navigate = useNavigate();

    // Handler de remocao de item, tem como parametros o id e o tamanho
    const removeItem = (id, size) => {
        // É necessário filtrar os itens do carrinho
        const newState = items.filter(obj => {
            // Se o id for diferente do parametro, continua no carrinho
            if (obj.product != id) return obj;
            // Caso contrario é necessário verificar algumas condições
            else {
                // Primeiramente a quantidade de itens no carrinho com o tamanho recebido como parametro é 0
                obj.sizes = obj.sizes.map(e => {
                    if(e.size !== size) {
                        return {size: e.size, stock: e.stock}
                    }
                })
                if(obj.sizes[0] === undefined) obj.sizes = [];
                // Em sequencia verificamos se existe algum tamanho do item com quantidade maior que 0
                if(obj.sizes.length > 0) return obj //Caso exista o item é retornado ao carrinho
            } 
        })
        // Atualização do estado do usuário
        const newUser = {...headerUser, cart: newState};
        setHeaderUser(newUser);

        // Atualização do estado do carrinho
        setItems(newState);
    }
    
    // Handler da atualização de quantidade de um item do carrinho
    const handleQuantity = (qtt, size, id) => {    
        // Para atualizar percorremos pelo array de itens do carrinho   
        const newState = items.map(obj => {
            // Ao encontrar o item correto
            if(obj.product == id) {
                // Percorremos pelos tamanhos do item
                return {...obj, sizes: obj.sizes.map(newSize => {
                    // Ao encontrar o tamanho correto, atualizamos a quantidade
                    if(newSize.size == size) return{ size: newSize.size, stock: qtt};
                    // Caso contrario a quantidade correta continua a mesma
                    else return newSize
                })}
            } 
            return obj;
        })

        console.log(newState)

        // Atualização do estado do usuário
        const newUser = {...headerUser, cart: newState};
        setHeaderUser(newUser);

        // Atualização do estado do carrinho
        setItems(newState);
    }

    // Handler do botão de finalizar compra
    const handleCheckout = () => {
        // Caso o usuário esteja logado, ele é direcionado ao checkout
        if(headerUser.logged) navigate('/checkout')
        // Caso contrário, ele recebe um alerta para se logar e é redirecionado a pagina de login
        else {
            alert('É necessário estar logado em uma conta para comprar');
            navigate('/login');
        }
    }

    // Função que atualiza os itens do carrinho
    const calcCart = () => {
        // Atravessa por todos os itens do carrinho
        return items.map(item => {
            // Atravessa por todos os tamanhos do item atual
            return item.sizes.map(itemSize => {
                return <CartItem key={`${item.product}.${itemSize.size}`} results={results} item={item} size={itemSize} handleQuantity={handleQuantity} removeItem={removeItem}/>
            }) 
        })
    }

    useEffect(() => {
        getResults();
        // calcTotal();
    }, [items])
    
    // Caso a quantidade de itens no carrinho seja 0, retorna uma pagina sem a lista de itens
    if(items.length < 1) {
        return (
            <>
                <Header user={headerUser} logged={headerUser.logged}/>
                <div className="container">
                    <div className="empty-content">
                        <div className="empty-message">Your cart is currently empty</div>
                        <Link to='/'>
                            <button className='empty-button'>Return to shop</button>
                        </Link>
                    </div>
                </div>
                <Footer />
            </>
        )
        
    }
    // Caso a quantidade seja maior que 0, retorna a pagina com a lista de itens no carrinho 
    else { 
        return (
            <>
                <Header user={headerUser} logged={headerUser.logged}/>
                <div className="container">
                    <div className="cart-content">
                        <div className="cart-items">
                            <h3>Meu Carrinho</h3>
                            <div className="cart-items-list">
                                { calcCart() }
                            </div>
                        </div>
                        <div className="summary">
                            <h3>Resumo da compra</h3>
                            <div className="summary-container">
                                <div className="total-container">
                                    <div>Total</div>
                                    <div>R$ {total.toFixed(2)}</div>
                                </div>
                                <div className="button-container">
                                    <button onClick={handleCheckout} className='checkout-button'>Finalizar</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <Footer />
            </>
        )
    }
}
 
export default Cart;