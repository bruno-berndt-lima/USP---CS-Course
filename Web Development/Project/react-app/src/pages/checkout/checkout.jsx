import React, { useEffect, useState } from 'react';
import Header from '../../components/Header';
import './checkout.css';
import '../../App.css';
import CheckoutItem from '../../components/CheckoutItem';
import { useNavigate } from 'react-router-dom';

const Checkout = ({results, setResults, headerUser, setHeaderUser}) => {
    const items = headerUser.cart;

    console.log(items);

    let total = 0;

    const [card, setCard] = useState({
        number: '',
        date: '',
        cvv: ''
    })

    //Listener do numero do cartão
    const handleNumber = (e) => {
        const newState = {...card, number: e.target.value};
        setCard(newState)
    }

    //Listener da validade do cartão
    const handleDate = (e) => {
        const newState = {...card, date: e.target.value};
        setCard(newState);
    }

    //Listener do código do cartão
    const handleCVV = (e) => {
        const newState = {...card, cvv: e.target.value};
        setCard(newState);
    }

    const navigate = useNavigate();

    const handleOrder = async () => {
        //Caso todos os dados do cartão tenham sido digitados, finaliza a compra com sucesso e remove do estoque a quantidade comprada
        if(card.number != '' && card.date != '' && card.cvv != '') {
            // Percorrendo pelos items do carrinho
            let newResults = headerUser.cart.map(item => {
                // Buscando pelo item no banco de dados que se refere ao do carrinho
                return results.filter((e) => {
                    // Ao encontrar o item do carrinho
                    if(e._id == item.product) {
                        // Percorre por todos os tamanhos diminuindo a quantidade em estoque
                        item.sizes.map(x => {
                            e.sizes.find((o) => {
                                if(o.size === x.size) o.stock -= parseInt(x.stock);
                            })
                        })
                        return e;
                    }
                })[0]
            })

            console.log(newResults);

            // Função para atualizar o estoque
            const updateStock = () => {
                newResults.map(async (item) => {
                    // Busca pelos itens no banco de dados e atualiza no sistema
                    try {
                        const response = await fetch(`http://localhost:7000/products/${item._id}`, {
                            method: 'PUT',
                            headers: {
                                'Content-Type': 'application/json',
                            },
                            body: JSON.stringify(item),
                        })
                        // Caso a atualização receba ok
                        if(response.ok) {
                            console.log('Product updated successfully');
                            
                            // Atualiza o estado dos produtos
                            setResults(prevResults => {
                                const updatedResults = prevResults.map(result => {
                                if (result._id === item._id) {
                                    return item;
                                } else {
                                    return result;
                                }
                                });
                                return updatedResults;
                            });
        
                        } else {
                        console.log('Product update failed');
                        }                       
                                
                        }
                    catch (error){
                        console.log(error);
                    }
                    });
                }

            // Criando o objeto que será enviado como um novo pedido no banco de dados
            const order = {
                user: headerUser._id,
                items: headerUser.cart
            }
            
            // Adicionando um novo pedido no banco de dados
            const createOrder = async () => {
                // Tenta criar um pedido no banco de dados
                try {
                    const response = await fetch('http://localhost:7000/orders', {
                        method: 'POST',
                        headers: { "Content-Type": "application/json" },
                        body: JSON.stringify(order)
                    });
                    
                    if(response.ok) {
                        console.log("New order added");
                        console.log(JSON.stringify(order));
                    } else {
                        console.log("Create order failed");
                    }
                } catch (error) {
                    console.log(error);
                }
            }

            console.log(newResults);

            createOrder();
            updateStock();


            //Esvazia o carrinho do usuario
            const newState = {...headerUser, cart: []};
            setHeaderUser(newState);

            //Mensagem de compra realizada com sucesso e retorna a pagina inicial
            alert("Compra realizada com sucesso");
            navigate('/')

        } else { //Caso contrário, da um alerta para preencher os dados do cartão
            alert('Digite os dados corretos do cartão')
        }
    }

    return (  
        <>
            <Header user={headerUser} logged={headerUser.logged}/>
            <div className="container">
                <div className="payment-card">
                    <h3>Digite os detalhes do pagamento</h3>
                    <span>Número do Cartão</span>
                    <input value={card.number} onChange={handleNumber} type='number' placeholder='Card Number'></input>
                    <span>Validade</span>
                    <input value={card.date} onChange={handleDate} type='month'></input>
                    <span>Código de Segurança</span>
                    <input value={card.cvv} onChange={handleCVV} type='text' placeholder='CVV' pattern='[0-9]{3}'></input>
                </div>
                <div className="checkout-items">
                    <h3>Itens da compra</h3>
                    <ul>
                        {items.map(item => {
                            let aux = 0;
                            item.sizes.map(itemSize => {
                                aux += parseInt(itemSize.stock)
                            })
                            let price = results.filter(e => {if(e._id === item.product) return e})[0].price;
                            total += aux * price;
                            return <CheckoutItem product={results.filter(e => {if(e._id === item.product) return e})[0]} quantity={aux}/>;
                        })}
                    </ul>
                    <div className="place-order">
                        <h3>Total: R${total.toFixed(2)}</h3>
                        <button onClick={handleOrder}>
                        <span>CHECKOUT</span></button>
                    </div>
                </div>
            </div>
        </>
    );
}
 
export default Checkout;