import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import Header from '../../components/Header';
import './login.css';
import '../../App.css';
import Footer from '../../components/Footer';


const Login = ({headerUser, setHeaderUser}) => {
    const navigate = useNavigate();

    // Estado do usuário
    const [user, setUser] = useState({
        _id: null,
        name: '',
        cpf: '',
        email: '',
        phones: [],
        password: '',
        logged: false,
        address: [],
        cart: [],
        admin: false,
    })

    // Estado do email de cadastro
    const [signupEmail, setSignupEmail] = useState('');

    // Estado para verificação se o usuário está logado ou deslogado
    const [logged, setLogged] = useState(headerUser.logged);

    // Handler do input de email
    const handleEmail = (e) => {
        const newState = {...user, email: e.target.value}
        setUser(newState);
    };
  
    // Handler do input de senha
    const handlePassword = (e) => {
        const newState = {...user, password: e.target.value}
        setUser(newState);
    };

    // Handler do input de email de cadastro
    const handleSignupEmail = (e) => {
        setSignupEmail(e.target.value)
    }
  
    // Handler do botão de login
    const handleLogin = async () => {
        // Utilizamos um post para verificação se o login está correto
        const response = await fetch('http://localhost:7000/login', {
            method: 'POST',
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(user)
        })

        if(!response.ok) {
            const message = `An error occurred: ${response.statusText}`;
            return;
        }

        const client = await response.json();

        const responseItems = await fetch(`http://localhost:7000/products/admin`);
        
        if (!responseItems.ok) {
          const message = `An error occurred: ${responseItems.statusText}`;
          return;
        }
    
        const data = await responseItems.json();
  
        // Verifica se houve algum retorno do banco de dados, em caso positivo atualiza o usuário geral (headerUser)
        if(client.length === 1) {
            let newState = {
                _id: client[0]._id, 
                name: client[0].name, 
                password: "",
                cpf: client[0].cpf,
                email: client[0].email,
                phones: client[0].phones,
                logged: true, 
                admin: client[0].admin, 
                address: client[0].address,
                cart: client[0].cart
            };

            // Verificando o carrinho do usuário
            newState.cart = newState.cart.filter(item => {
                const sizes = item.sizes; // Tamanhos do item do carrinho
                let sizesStock = data.filter(result => { // Tamanhos do estoque
                    if(result._id === item.product) return result
                })[0].sizes;
                // Filtrando os tamanhos com quantidade disponível no estoque
                let availableSizes = sizes.filter(size => {
                    // Estoque da loja
                    let stock = sizesStock.filter(e => {
                        if(e.size === size.size) return e;
                    });
                    if(stock.len < 1){
                        stock = stock[0].stock; 
                        // Caso o estoque da loja seja maior que o do carrinho retorna o tamanho
                        if(stock >= size.stock) return size
                    } 
                });
                const final = { product: item.product, sizes: availableSizes };
                // Caso existam tamanhos disponíveis retorna o item com os tamanhos disponíveis
                if(availableSizes.length > 0) return { product: item.product, sizes: availableSizes };
            })
            setUser(newState);
            setHeaderUser(newState);
            setLogged(true);
            // Caso seja cliente, é direcionado a home page 
            if(!newState.admin)
                navigate('/', {replace: true})
            // Caso contrário, é redirecionado a página de adm
            else
                navigate('/admin', {replace: true})
        } else {
            alert("User and password does not match")
        }
    };

    const handleSignup = async () => {
        if(signupEmail.length > 0) {
            // Utilizamos um post para verificação se o login está correto
            const response = await fetch(`http://localhost:7000/login/${signupEmail}`)
    
            if(!response.ok) {
                const message = `An error occurred: ${response.statusText}`;
                return;
            }
    
            const client = await response.json();
    
            if(client.length > 0 || signupEmail.length < 1) {
                alert("Email already registered!")
            } else {
                setHeaderUser({...headerUser, email:signupEmail});
                navigate('/signup');
            }
        } else {
            alert("Type a valid email");
        }
    }

    return (  
        <>
            <Header user={headerUser} logged={logged}/>
            <div className="container">
                <div className="content">
                    <div className="login content-box">
                        <h1>I am a User</h1>
                        <input value={user.email} onChange={handleEmail} type='email' placeholder='Email'></input>
                        <input value={user.password} onChange={handlePassword} type='password' placeholder='Password'></input>
                        <button onClick={handleLogin} className='access-button'>LOGIN</button>
                    </div>

                    <div className="partition"></div>

                    <div className="signup content-box">
                        <h1>Create Account</h1>
                        <input value={signupEmail} onChange={handleSignupEmail} type='email' placeholder='Type your email'></input>
                        <button onClick={handleSignup} className='access-button'>PROCCEED</button>
                    </div>
                </div>
            </div>
            <Footer />
        </>
    );
}
 
export default Login;